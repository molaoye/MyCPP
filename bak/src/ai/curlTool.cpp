
#include "curlTool.h"

CCurltool::CCurltool()
{
    //��ʼ�� jsonReqRoot
    Json::Value jsonPubInfo;
    Json::Value jsonRequest;
    Json::Value jsonBusiParams;
    
    std::string num = itoa(rand()%10000);
    
    time_t t = time(0); 
    char tmp[64];
	  strftime( tmp, sizeof(tmp), "%Y%m%d%H%M%S",localtime(&t) );    
    
    //������Ϣ
    jsonPubInfo["TransactionId"] = std::string("kf")+std::string(tmp)+std::string(num);//"DB1451892166400";
    jsonPubInfo["TransactionTime"] = std::string(tmp);
    jsonPubInfo["InterfaceId"] = "6014";
    jsonPubInfo["InterfaceType"] = "14";
    jsonPubInfo["OpId"] = "96660015";
    jsonPubInfo["OrgId"] = "71001001";
    jsonPubInfo["RegionCode"] = "771";
    jsonPubInfo["CountyCode"] = "7101";
    jsonPubInfo["ClientIP"] = "127.0.0.1";
    jsonPubInfo["ClerkId"] = "";
    
    //���빫����Ϣ
    jsonReqRoot["PubInfo"] = jsonPubInfo;
    jsonRequest["BusiParams"] = jsonBusiParams;
    jsonReqRoot["Request"] = jsonRequest;

    //����Ĭ�� URL
    m_strUrl = "http://172.20.35.46:50001/CRMService";
}

CCurltool::CCurltool(const AISTD string& strUrl, const AISTD string& strPostData)
{
    //��ʼ�� jsonReqRoot
    char logInfo[1024] = { 0 };
    set_url(strUrl);
    if( !jsonReader.parse(strPostData, jsonReqRoot) )
    {
        LogAppend(DEBUG_LEVEL, "DebugInfo", "���캯��������JSON��ʽʧ�ܣ�");
        sprintf(logInfo, "Data=[%s]", strPostData.c_str());
        LogAppend(DEBUG_LEVEL, "DebugInfo", logInfo);
    }
}

int32 CCurltool::set_postData(const AISTD string& strPostData)
{
    char logInfo[1024] = { 0 };
    jsonReqRoot.clear();
    if( !jsonReader.parse(strPostData, jsonReqRoot) )
    {
        LogAppend(DEBUG_LEVEL, "DebugInfo", "set_postData������JSON��ʽʧ�ܣ�");
        sprintf(logInfo, "Data=[%s]", strPostData.c_str());
        LogAppend(DEBUG_LEVEL, "DebugInfo", logInfo);
        return 1;
    }
    
    return 0;
}

int32 CCurltool::postHttpResponse()
{
    char logInfo[1024] = { 0 };
    LogAppend(INFO_LEVEL, "DebugInfo", "=========��ʼ��http�ӿ�=====");
    
    if ( m_strUrl.length() == 0 )
    {
        LogAppend(INFO_LEVEL, "DebugInfo", "ERROR:URL is NULL");
        return 1;
    }
    
    base::HttpMethod clHttpMethod;
    if( !clHttpMethod.Open() )
    {
        LogAppend(DEBUG_LEVEL, "DebugInfo", "HttpMethod open����!");
        return 1;
    }

    std::string strData = jsonFastWriter.write(jsonReqRoot);
    base::Buffer iBuffer(strData.c_str());
    sprintf(logInfo, "������ =  postHttpResponse, urlParams=%s", m_strUrl.c_str());
    LogAppend(DEBUG_LEVEL, "DebugInfo", logInfo);
    sprintf(logInfo, "data=[%s]!", iBuffer.GetBufferPtr());
    LogAppend(DEBUG_LEVEL, "DebugInfo", logInfo);
    clHttpMethod.SetTimeOutMS( TIME_OUT*1000 );
    //clHttpMethod.SetGet();
    //clHttpMethod.SetHeader("Accept","application/json");
    clHttpMethod.SetHeader("Content-Type","application/x-www-form-urlencoded;charset=UTF-8");
    //clHttpMethod.SetHeader("charset","utf-8");
    //char szTmp[32];
    //memset(szTmp, 0, sizeof(szTmp));
    //sprintf(szTmp, "%d", iBuffer.GetDataSize());
    //clHttpMethod.SetHeader("Content-Length",szTmp);
    clHttpMethod.SetPost();
    clHttpMethod.SetPostData(iBuffer);
    if ( m_strUrl.length() > 0 )
    {
        clHttpMethod.SetUrl(m_strUrl);
    }
    else
    {
        //Ĭ����ַ
        clHttpMethod.SetUrl("http://172.20.35.27:8500/ivr-rest/api/v1");
    }

    int nRet = clHttpMethod.Call();
    if( nRet )
    {
        sprintf(logInfo, "HttpMethod.Call error[%d]!", nRet);
        LogAppend(DEBUG_LEVEL, "DebugInfo", logInfo);
        return 1;
    }

    if( clHttpMethod.GetRespCode() != 200 )
    {
        sprintf(logInfo, "�ӿڴ��󣬷��ش�����:[%d]", clHttpMethod.GetRespCode());
        LogAppend(DEBUG_LEVEL, "DebugInfo", logInfo);
        return 1;
    }
    
    const base::Buffer* pBuffer = clHttpMethod.GetRespBuffer();
    std::string strResponse = pBuffer->GetAsString();
    sprintf(logInfo, "response data=[%s]!", strResponse.c_str());
    LogAppend(DEBUG_LEVEL, "DebugInfo", logInfo);
    
    if( !jsonReader.parse(strResponse, jsonResRoot) )
    {
        LogAppend(DEBUG_LEVEL, "DebugInfo", "�������ص�JSON��ʽ����ʧ��");
        return 1;
    }
    
    LogAppend(INFO_LEVEL, "DebugInfo", "=========����http�ӿ� OK=====");

    return 0;
}

AISTD string CCurltool::getFieldValue(const AISTD string& strFieldName)
{
    char logInfo[1024] = { 0 };
    
    if ( jsonResRoot.empty() )
    {
        LogAppend(INFO_LEVEL, "DebugInfo", "getFieldValue, response data is empty");
        return "";
    }
    
    //�Ӹ��ڵ��ȡ Response �ڵ�
    if ( !jsonResRoot.isMember("Response") )
    {
        LogAppend(DEBUG_LEVEL, "DebugInfo", "getFieldValue, member Response not found");
        return "";
    }
    Json::Value& response =jsonResRoot["Response"];

    //�� Response �ڵ��ȡ ErrorInfo �ڵ�
    if ( !response.isMember("ErrorInfo") )
    {
        LogAppend(DEBUG_LEVEL, "DebugInfo", "getFieldValue, member ErrorInfo not found");
        return "";
    }
    Json::Value& errorInfo=response["ErrorInfo"];

    //�� Response �ڵ��ȡ RetInfo �ڵ�
    if ( !response.isMember("RetInfo") )
    {
        LogAppend(DEBUG_LEVEL, "DebugInfo", "getFieldValue, member RetInfo not found");
        return "";
    }
    Json::Value& retInfo=response["RetInfo"];

    //��ʼ����
    if ( retInfo.isMember(strFieldName) )
    {
        //�� RetInfo �ڵ����
        return retInfo[strFieldName].asString();
    }
    else
    {
        //����� RetInfo �ڵ���Ҳ��������� ErrorInfo �ڵ����
        if ( errorInfo.isMember(strFieldName) )
        {
            return errorInfo[strFieldName].asString();
        }
        else
        {
            //�򲻴���
            sprintf(logInfo, "getFieldValue, field=[%s] not found", strFieldName.c_str());
            LogAppend(DEBUG_LEVEL, "DebugInfo", logInfo);
            return "";
        }
    }
    
    return "";
}

int32 CCurltool::appendReqData(const AISTD string& strFieldName, const AISTD string& strFieldValue)
{
    if ( jsonReqRoot.empty() )
    {
        LogAppend(INFO_LEVEL, "DebugInfo", "addRequestData, data root is empty");
        return 1;
    }
    
    //�Ӹ��ڵ��ȡ Request �ڵ�
    if ( !jsonReqRoot.isMember("Request") )
    {
        LogAppend(DEBUG_LEVEL, "DebugInfo", "addRequestData, member Request not found");
        return 1;
    }
    Json::Value& request =jsonReqRoot["Request"];
    
    //�� Request �ڵ��ȡ BusiParams �ڵ�
    if ( !request.isMember("BusiParams") )
    {
        LogAppend(DEBUG_LEVEL, "DebugInfo", "addRequestData, member BusiParams not found");
        return 1;
    }
    Json::Value& busiparams = request["BusiParams"];
    
    //������������
    busiparams[strFieldName] = strFieldValue;
    
    return 0;
}

int32 CCurltool::appendPubData(const AISTD string& strFieldName, const AISTD string& strFieldValue)
{
    if ( jsonReqRoot.empty() )
    {
        LogAppend(INFO_LEVEL, "DebugInfo", "appendPubData, data root is empty");
        return 1;
    }
    
    //�Ӹ��ڵ��ȡ PubInfo �ڵ�
    if ( !jsonReqRoot.isMember("PubInfo") )
    {
        LogAppend(DEBUG_LEVEL, "DebugInfo", "appendPubData, member PubInfo not found");
        return 1;
    }
    Json::Value& pubinfo = jsonReqRoot["PubInfo"];
    
    //������������
    pubinfo[strFieldName] = strFieldValue;
    
    return 0;
}

int32 CCurltool::set_busiCode(const AISTD string& strBusiCode)
{
    if ( jsonReqRoot.empty() )
    {
        LogAppend(INFO_LEVEL, "DebugInfo", "addRequestData, data root is empty");
        return 1;
    }

    jsonReqRoot["BusiCode"] = strBusiCode;

    return 0;
}

