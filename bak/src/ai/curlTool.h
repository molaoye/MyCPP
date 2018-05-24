#ifndef _CURLTOOL_H
#define _CURLTOOL_H

#include "include/ob_kernel.h"
#include "../tools/json/include/json.h"
#include "c_curl_util.h"
#include "stdio.h"
#include "time.h"

#define TIME_OUT 60


class CCurltool
{
public:
    CCurltool();
    CCurltool(const AISTD string& strUrl, const AISTD string& strPostData);
    
    //����URL
    inline void set_url(const AISTD string& strUrl)
    {
        m_strUrl = strUrl;
    }
    
    //�����������ݣ�����Ѵ���ԭ�����򸲸�
    int32 set_postData(const AISTD string& strPostData);

    //���� BusiCode
    int32 set_busiCode(const AISTD string& strBusiCode);
    
    //��ȡURL
    inline AISTD string get_url() const
    {
        return m_strUrl;
    }
    
    //��ȡ���������ַ���
    inline AISTD string get_postData()
    {
        //return m_strPostData;
        return jsonFastWriter.write(jsonReqRoot);;
    }
    
    //��ȡ��Ӧ�����ַ���
    inline AISTD string get_resData()
    {
        //return m_strResData;
        return jsonFastWriter.write(jsonResRoot);;
    }
    
    //�������󲢽�����Ӧ����
    int32 postHttpResponse();
    
    //���������ƴ���Ӧ�����л�ȡֵ
    AISTD string getFieldValue(
        const AISTD string& strFieldName
    );
    
    //׷����������
    int32 appendReqData(
        const AISTD string& strFieldName,
        const AISTD string& strFieldValue
    );

    //׷�ӹ�����Ϣ
    int32 appendPubData(
        const AISTD string& strFieldName,
        const AISTD string& strFieldValue
    );

private:
    AISTD string m_strUrl;
    //AISTD string m_strPostData;
    //AISTD string m_strResData;

    Json::Reader jsonReader;
    Json::FastWriter jsonFastWriter;
    Json::Value jsonReqRoot;
    Json::Value jsonResRoot;
    
};

#endif

