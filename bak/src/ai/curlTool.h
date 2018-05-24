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
    
    //设置URL
    inline void set_url(const AISTD string& strUrl)
    {
        m_strUrl = strUrl;
    }
    
    //设置请求数据，如果已存在原数据则覆盖
    int32 set_postData(const AISTD string& strPostData);

    //设置 BusiCode
    int32 set_busiCode(const AISTD string& strBusiCode);
    
    //获取URL
    inline AISTD string get_url() const
    {
        return m_strUrl;
    }
    
    //获取请求数据字符串
    inline AISTD string get_postData()
    {
        //return m_strPostData;
        return jsonFastWriter.write(jsonReqRoot);;
    }
    
    //获取响应数据字符串
    inline AISTD string get_resData()
    {
        //return m_strResData;
        return jsonFastWriter.write(jsonResRoot);;
    }
    
    //发送请求并接收响应数据
    int32 postHttpResponse();
    
    //根据域名称从响应数据中获取值
    AISTD string getFieldValue(
        const AISTD string& strFieldName
    );
    
    //追加请求数据
    int32 appendReqData(
        const AISTD string& strFieldName,
        const AISTD string& strFieldValue
    );

    //追加公共信息
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

