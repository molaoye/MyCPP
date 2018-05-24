
#include <cassert>
#include <stdarg.h>
#include "c_curl_util.h"
#include "../tools/curl/curl/include/curl/curl.h"

namespace base
{

//
// Buffer
//
Buffer::Buffer(int nSize) : m_nDataSize(0), m_nSize(nSize)
{
    m_pBuffer = new char[m_nSize];
}

Buffer::Buffer(const Buffer& rhs)
{
    m_nDataSize = rhs.m_nDataSize;
    m_nSize = rhs.m_nSize;
    m_pBuffer = new char[m_nSize];    
    memcpy(m_pBuffer, rhs.m_pBuffer, m_nDataSize);
}

Buffer::Buffer(const std::string& nSrcStr)
{
    m_nDataSize = m_nSize = nSrcStr.length();
    m_pBuffer = new char[m_nSize];
    memcpy(m_pBuffer, nSrcStr.data(), m_nDataSize);
}

Buffer::Buffer(const char* pSrcStr)
{
    m_nDataSize = m_nSize = strlen(pSrcStr);
    m_pBuffer = new char[m_nSize];
    memcpy(m_pBuffer, pSrcStr, m_nDataSize);
}

Buffer::~Buffer()
{
    delete []m_pBuffer;
}

Buffer& Buffer::operator=(const Buffer& rhs)
{
    if (this != &rhs)
    {
        if (m_nSize < rhs.m_nSize) //只有小于的时候才释放重新申请
        {
            delete []m_pBuffer;
            m_nSize = rhs.m_nSize;
            m_pBuffer = new char[m_nSize];
        }
        m_nDataSize = rhs.m_nDataSize;
        memcpy(m_pBuffer, rhs.m_pBuffer, m_nDataSize);
    }
    return *this;
}

Buffer& Buffer::Append(const Buffer& rhs)
{
    if (rhs.m_nDataSize > 0)
        Append(rhs.m_pBuffer, rhs.m_nDataSize);
    return *this;
}

Buffer& Buffer::Append(const std::string& nSrcStr)
{
    int n = nSrcStr.length();
    if (n > 0)
    {
        Append(nSrcStr.data(), n);
    }
    return *this;
}

Buffer& Buffer::Append(const char* pSrcStr)
{
    int n = strlen(pSrcStr);
    if (n > 0)
    {
        Append(pSrcStr, n);
    }
    return *this;
} 

Buffer& Buffer::Append(const void* p, int nSize)
{
    int nNewSize = nSize + m_nDataSize;
    if (nNewSize > m_nSize)
        GrowBuffer(nNewSize + 64);
    
    memcpy(m_pBuffer + m_nDataSize, p, nSize);
    m_nDataSize += nSize;
    return *this;
}

void Buffer::GrowBuffer(int nNewSize)
{
    if (nNewSize > m_nSize)
    {
        char* p = new char[nNewSize];
        memcpy(p, m_pBuffer, m_nDataSize);
        delete []m_pBuffer;
        m_nSize = nNewSize;
        m_pBuffer = p;
    }
}

Buffer& Buffer::AppendF(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    
    char* buf = m_pBuffer + m_nDataSize;
    int buflen = m_nSize - m_nDataSize;
    if (buflen < strlen(fmt))
    {
        buflen = strlen(fmt);
        int nNewSize = m_nDataSize + buflen;
        GrowBuffer(nNewSize);
        buf = m_pBuffer + m_nDataSize; //需要重新设置
    }
    
    va_list cpy;
    
    while(1) //通过多次尝试以获得最终的实际长度
    {
        buf[buflen - 2] = '\0';
        va_copy(cpy, ap);
        vsnprintf(buf, buflen, fmt, cpy);
        va_end(ap);
        
        if (buf[buflen - 2] != '\0')
        {
            buflen *= 2;
            int nNewSize = m_nDataSize + buflen;
            GrowBuffer(nNewSize);
            buf = m_pBuffer + m_nDataSize;
            continue;
        }
        
        //计算写入的长度
        m_nDataSize += strlen(buf);
        break;
    }
    va_end(ap);
    
    return *this;
}

void Buffer::Clear()
{
    m_nDataSize = 0;
    if (m_nSize > 512)
    {
        delete []m_pBuffer;
        m_pBuffer = new char[512];
        m_nSize = 512;
    }
}

std::string Buffer::GetAsString() const
{    
    std::string str(m_pBuffer, m_nDataSize);
    return str;
}

//
// HttpMethod
//
HttpMethod::HttpMethod() : 
    m_bPost(false),
    m_pCurlRef(NULL), 
    m_pReadBuffer(NULL), 
    m_pRespBuffer(NULL),
    m_pReader(NULL), 
    m_pWriter(NULL),
    m_pCommonHeaderList(NULL)
{
}

HttpMethod::~HttpMethod()
{
    Close();
}

bool HttpMethod::Open()
{
    assert(m_pCurlRef == NULL);
    m_pCurlRef = curl_easy_init();
    if (m_pCurlRef)
    {
        curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_NOSIGNAL, 1L);
    }
    return m_pCurlRef != NULL;
}

void HttpMethod::Close()
{
    if (m_pCurlRef)
        curl_easy_cleanup((CURL*)m_pCurlRef);
    
    if (m_pReadBuffer)
        delete m_pReadBuffer;

    if (m_pReader)
        delete m_pReader;
    
    if (m_pWriter)
    {
        delete m_pRespBuffer;
        delete m_pWriter;
    }
    
    if (m_pCommonHeaderList)
    {
        curl_slist_free_all((struct curl_slist*)m_pCommonHeaderList);
        m_pCommonHeaderList = NULL;
    }
    
    m_strHeaderStore.clear();    
    m_pCurlRef = NULL;
    m_pReadBuffer = NULL;
    m_pRespBuffer = NULL;
    m_pReader = NULL;
    m_pWriter = NULL;
}

static int curl_http_debug_callback
       (CURL *handle,      /* the handle/transfer this concerns */
        curl_infotype type, /* what kind of data */
        char *data,        /* points to the data */
        size_t size,       /* size of the data pointed to */
        void *userptr)
{
    switch(type)
    {
    case CURLINFO_TEXT:
        //((LogAppendFP)userptr)(1, "DebugInfo", data);
        break;
    default:
        break;
    }
    return size;
}

/*
HttpMethod& HttpMethod::OpenLog(LogAppendFP fp)
{
    assert(m_pCurlRef != NULL);
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_DEBUGFUNCTION, curl_http_debug_callback);
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_DEBUGDATA, fp);
    return *this;
}
*/

HttpMethod& HttpMethod::SetTimeOutMS(long ms)
{
    assert(m_pCurlRef != NULL);
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_TIMEOUT_MS, ms);
    return *this;
}

HttpMethod& HttpMethod::SetPost()
{
    assert(m_pCurlRef != NULL);
    m_bPost = true;
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_POST, 1L);
    return *this;
}

HttpMethod& HttpMethod::SetGet()
{
    assert(m_pCurlRef != NULL);
    m_bPost = false;
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_POST, 0L);
    return *this;
}

HttpMethod& HttpMethod::SetUrl(const std::string& url)
{
    assert(m_pCurlRef != NULL);
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_URL, url.c_str());
    return *this;
}

HttpMethod& HttpMethod::SetPostData(const Buffer& nBuffer)
{
    assert(m_pCurlRef != NULL);
    assert(m_bPost == true);
    
    if (m_pReader)
        delete m_pReader;
    if (m_pReadBuffer)
        delete m_pReadBuffer;
        
    m_pReadBuffer = new Buffer(nBuffer);
    m_pReader = new ReadDataFromBuffer(*m_pReadBuffer);
    
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_READFUNCTION, &HttpMethod::read_callback);
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_READDATA, m_pReader);
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_POSTFIELDSIZE, m_pReadBuffer->GetDataSize());
    
    return *this;
}

HttpMethod& HttpMethod::SetContentType(const std::string& strContentType)
{
    m_strHeaderStore.push_back(std::string("Content-Type: ") + strContentType);

    m_pCommonHeaderList = curl_slist_append((struct curl_slist*)m_pCommonHeaderList, 
        m_strHeaderStore[m_strHeaderStore.size() - 1].c_str());
    
    return *this;
}


HttpMethod& HttpMethod::SetHeader(const std::string& strName, const std::string& strValue)
{
    m_strHeaderStore.push_back(strName + ": " + strValue);

    m_pCommonHeaderList = curl_slist_append((struct curl_slist*)m_pCommonHeaderList, 
        m_strHeaderStore[m_strHeaderStore.size() - 1].c_str());
    
    return *this;
}

HttpMethod& HttpMethod::SetPostDataReader(ReadData* reader)
{
    assert(m_pCurlRef != NULL);
    assert(m_bPost == true);
    
    if (!m_pReader)
        delete m_pReader;
    
    m_pReader = reader;
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_READFUNCTION, &HttpMethod::read_callback);
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_READDATA, m_pReader);
    
    m_pCommonHeaderList = curl_slist_append((struct curl_slist*)m_pCommonHeaderList, 
        "Transfer-Encoding: chunked");
    
    return *this;
}

HttpMethod& HttpMethod::SetRespWriter(WriteData* writer)
{
    assert(m_pCurlRef != NULL);
    if (m_pWriter)
        delete m_pWriter;
    
    m_pWriter = writer;
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_WRITEFUNCTION, &HttpMethod::write_callback);
    curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_WRITEDATA, m_pWriter);
    
    return *this;
}

int HttpMethod::GetRespCode() const
{
    assert(m_pCurlRef != NULL);
    long n = 0;
    curl_easy_getinfo((CURL*)m_pCurlRef, CURLINFO_RESPONSE_CODE, &n);
    return n;
}

bool HttpMethod::Call()
{
    assert(m_pCurlRef != NULL);
    if (!m_pWriter)
    {
        m_pRespBuffer = new Buffer();
        SetRespWriter(new WriteDataToBuffer(*m_pRespBuffer));
    }
    
    if (m_pCommonHeaderList)
    {
        curl_easy_setopt((CURL*)m_pCurlRef, CURLOPT_HTTPHEADER, (struct curl_slist*)m_pCommonHeaderList);
    }
    //return curl_easy_perform((CURL*)m_pCurlRef) == CURLE_OK;
    return curl_easy_perform((CURL*)m_pCurlRef);
}

size_t HttpMethod::read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
    ReadData* pThis = (ReadData*)userp;
    size_t nSize = size * nmemb;
    return pThis->Read(ptr, nSize);
}

size_t HttpMethod::write_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
    WriteData* pThis = (WriteData*)userp;
    return pThis->Write(ptr, size * nmemb);
}

//
// ReadDataFromBuffer
//
int ReadDataFromBuffer::Read(void* pBuffer, int size)
{
    int nLeftSize = m_nBuffer.GetDataSize() - m_nReadOffset;
    if (nLeftSize <= 0)
        return 0;
        
    if (nLeftSize < size)
        size = nLeftSize;
    
    memcpy(pBuffer, m_nBuffer.GetBufferPtr(), size);
    m_nReadOffset += size;
    
    return size;
}

//
// WriteDataToBuffer
//
int WriteDataToBuffer::Write(void* pBuffer, int size)
{
    m_nBuffer.Append(pBuffer, size);
    return size;
}

//
// ReadDataFromFile
//
ReadDataFromFile::ReadDataFromFile(const std::string& strFileName)
{
    m_pFp = fopen(strFileName.c_str(), "rb");
}

int ReadDataFromFile::Read(void* pBuffer, int size)
{
    int n = fread(pBuffer, 1, size, m_pFp);
    return n;
}

//
// WriteDataToFile
//
WriteDataToFile::WriteDataToFile(const std::string& strFileName)
{
    m_pFp = fopen(strFileName.c_str(), "wb");
}

int WriteDataToFile::Write(void* pBuffer, int size)
{
    int n = fwrite(pBuffer, 1, size, m_pFp);
    return n;
}

//
// CurlLoader
//
class CurlLoader
{
public:
    CurlLoader()
    {
        CURLcode res = curl_global_init(CURL_GLOBAL_DEFAULT);
        if(res != CURLE_OK)
        {
            //fprintf(stderr, "curl_global_init() failed: %s\n",
            //    curl_easy_strerror(res));
        }
    }
    
    ~CurlLoader()
    {
        curl_global_cleanup();
    }
};

static CurlLoader g_nCurlLoader;

};
