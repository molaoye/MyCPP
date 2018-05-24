#ifndef __BASE_CURL_UTIL_H__
#define __BASE_CURL_UTIL_H__

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

namespace base
{

//Buffer对象
class Buffer
{
public:
    Buffer(int nSize = 256);
    Buffer(const Buffer& rhs);
    Buffer(const std::string& nSrcStr);
    Buffer(const char* pSrcStr);
    ~Buffer();
    
    Buffer& operator=(const Buffer& rhs);
    
    //Append数据块 
    Buffer& Append(const Buffer& rhs);
    Buffer& Append(const std::string& nSrcStr);
    Buffer& Append(const char* pSrcStr);
    Buffer& Append(const void* p, int nSize);
    
    //格式化同printf
    Buffer& AppendF(const char* fmt, ...);
    
    //清空所有内容，将数据大小设置为0
    void Clear();
    
    const char* GetBufferPtr() const { return m_pBuffer; }
    int         GetDataSize() const { return m_nDataSize; }
    std::string GetAsString() const;

private:
    void GrowBuffer(int nNewSize);
    
private:
    char* m_pBuffer;
    int   m_nSize;
    int   m_nDataSize;
};

/////////////////////////////////////////
class ReadData
{
public:
    virtual ~ReadData() {}
    
    //
    virtual bool IsOk() = 0;
    
    //pBuffer: 缓存指针
    //size：缓存大小
    //返回实际读取的数据大小
    virtual int Read(void* pBuffer, int size) = 0;
};

class WriteData
{
public:
    virtual ~WriteData() {}
    
    virtual bool IsOk() = 0;
    
    //pData:数据指针
    //size：数据大小
    //返回实际写入的数据大小
    virtual int Write(void* pData, int size) = 0;
};
///////////////////////////
//
// ReadDataFromBuffer
//
class ReadDataFromBuffer : public ReadData
{
public:
    ReadDataFromBuffer(const Buffer& rhs) : m_nBuffer(rhs), m_nReadOffset(0) {}
    virtual bool IsOk() { return true; }
    virtual int Read(void* pBuffer, int size);

private:
    const Buffer& m_nBuffer;
    int   m_nReadOffset;
};

//
// WriteDataToBuffer
//
class WriteDataToBuffer : public  WriteData
{
public:
    WriteDataToBuffer(Buffer& rhs) : m_nBuffer(rhs) {}
    virtual bool IsOk() { return true; }
    virtual int Write(void* pBuffer, int size);
    
private:
    Buffer& m_nBuffer;
};

//
// ReadDataFromFile
//
class ReadDataFromFile : public ReadData
{
public:
    ReadDataFromFile(const std::string& strFileName);
    virtual bool IsOk() { return m_pFp != NULL; }
    virtual int Read(void* pBuffer, int size);
        
private:
    FILE* m_pFp;
};

//
// WriteDataToFile
//
class WriteDataToFile : public WriteData
{
public:
    WriteDataToFile(const std::string& strFileName);
    virtual bool IsOk() { return m_pFp != NULL; }
    virtual int Write(void* pBuffer, int size);
      
private:
    FILE* m_pFp;
};

//typedef int32 (*LogAppendFP) (int32 iErrorLevel,const char * shortName, ... );
//typedef int (*LogAppendFP) (int iErrorLevel,const char * shortName, ... );

//HTTP Method
class HttpMethod
{
public:
    HttpMethod();
    ~HttpMethod();
    
    bool Open();
    void Close();
    
    //HttpMethod& OpenLog(LogAppendFP fp);
    
    HttpMethod& SetTimeOutMS(long ms);
    HttpMethod& SetPost();
    HttpMethod& SetGet();
    HttpMethod& SetUrl(const std::string& url);
    HttpMethod& SetPostData(const Buffer& nBuffer);
    HttpMethod& SetContentType(const std::string& strContentType);
    HttpMethod& SetHeader(const std::string& strName, const std::string& strValue);
    
    //注意该reader控制权交由HttpMethod
    HttpMethod& SetPostDataReader(ReadData* reader);
    
    //注意该writer控制权交由HttpMethod
    HttpMethod& SetRespWriter(WriteData* writer);
    
    //发送请求
    bool Call();
    
    //获取响应的Buffer
    const Buffer* GetRespBuffer() const { return m_pRespBuffer; }
    int GetRespCode() const;
    
private:
    static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp);
    static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userp);
    
private:
    bool       m_bPost;
    void*      m_pCurlRef;    
    Buffer*    m_pReadBuffer;
    Buffer*    m_pRespBuffer;
    ReadData*  m_pReader;
    WriteData* m_pWriter;
    
    std::vector<std::string> m_strHeaderStore; //slist不会管理data的内存
    void*      m_pCommonHeaderList; //struct curl_slist
};

};

#endif
