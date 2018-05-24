#include <string>
#include <fstream>
#include <list>
#include "ivrUtil.h"

//---------------------------------------------------------------------------
int getCurrDay()
{
	time_t tNow;
	time( &tNow );
#ifdef RW_MULTI_THREAD
    struct tm tmTmp;
    localtime_r( &tNow, &tmTmp );
    return tmTmp.tm_mday;
#else
    struct tm *today = localtime( &tNow );
    return today->tm_mday;
#endif
}
//---------------------------------------------------------------------------
int getCurrMonth()
{
	time_t tNow;
	time( &tNow );
#ifdef RW_MULTI_THREAD
    struct tm tmTmp;
    localtime_r( &tNow, &tmTmp );
    return (tmTmp.tm_mon + 1);
#else
    struct tm *today = localtime( &tNow );
    return (today->tm_mon + 1);
#endif
}
//---------------------------------------------------------------------------
int getCurrYear()
{
	time_t tNow;
	time( &tNow );
#ifdef RW_MULTI_THREAD
    struct tm tmTmp;
    localtime_r( &tNow, &tmTmp );
    return (tmTmp.tm_year + 1900);
#else
    struct tm *today = localtime( &tNow );
    return (today->tm_year + 1900);
#endif
}
//---------------------------------------------------------------------------

size_t getDTBuffer( char *szBuf, const char *szFmt )
{
	time_t tNow;
	time( &tNow );
#ifdef RW_MULTI_THREAD
    struct tm tmTmp;
	return strftime( szBuf, LONG_DATETIME_LEN, szFmt, localtime_r( &tNow, &tmTmp ) );
#else
	return strftime( szBuf, LONG_DATETIME_LEN, szFmt, localtime( &tNow ) );
#endif
}
//---------------------------------------------------------------------------

void getLocalSysTime(SYSTEMTIME* lpSystemTime)
{
#ifdef win32
    GetLocalTime(lpSystemTime);
#else
    struct timeval tv;
    gettimeofday (&tv , NULL);
    struct tm tm_now;
    localtime_r(&tv.tv_sec, &tm_now);
    lpSystemTime->wYear = tm_now.tm_year+1900; //年份
    lpSystemTime->wMonth = tm_now.tm_mon+1; //月 tm[0-11] sys[1-12]
    lpSystemTime->wDay = tm_now.tm_mday; //日
    // tm一星期的日数，从星期一算起，范围为0-6 sys从星期日算起
    lpSystemTime->wDayOfWeek = (tm_now.tm_wday+1)%7;
    lpSystemTime->wHour =tm_now.tm_hour;   //小时
    lpSystemTime->wMinute = tm_now.tm_min; //分钟
    lpSystemTime->wSecond = tm_now.tm_sec; //秒
    lpSystemTime->wMilliseconds = tv.tv_usec/1000; //毫秒
#endif
}
//---------------------------------------------------------------------------

short adjustUserBrand(char *UserBrand, char *VipFlag) {
    short nVipFlag = atoi(VipFlag);
    return (nVipFlag >0) ? (10 + nVipFlag) : atoi(UserBrand);
}
//---------------------------------------------------------------------------

int splitCalledNo(char* calledNo)
{
    try {
        //去掉费率区
        if (memcmp(calledNo, "077", 3) == 0) {
            strcpy(calledNo, calledNo + 4);
        }
        int iLen = strlen(calledNo);
        //去掉费率区后，如果依然超过14位，则截断
        if (iLen > 14) {
            *(calledNo + 15) = '\0';
            //memcpy(calledNo, calledNo, 15);
        }
        return 1;
    } catch(...) {
        return 0;
    }
}
//---------------------------------------------------------------------------

//获取IP地址字符串: 1=成功，0=失败
int getlocalIp(char* localIp) {
    int i = 0;
    int sockfd;
    struct ifconf ifconf;
    char buf[512];
    struct ifreq *ifreq;
    char* ip;
    //初始化ifconf
    ifconf.ifc_len = 512;
    ifconf.ifc_buf = buf;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return 0;
    }
    ioctl(sockfd, SIOCGIFCONF, &ifconf); //获取所有接口信息
    close(sockfd);
    //接下来一个一个的获取IP地址
    // modified by wangtao at 2014-02-12 XQ2014012371349 关于优化IVR通话记录表中TEL_ORGCALLED字段获取IP地址的需求
    ifreq = (struct ifreq*)buf;
    std::string strIp = "";
    for (i = (ifconf.ifc_len/sizeof(struct ifreq)); i>0; i--) {
        strIp = inet_ntoa(((struct sockaddr_in*)&(ifreq->ifr_addr))->sin_addr);
        if (0 == strIp.find ("127.0.0")) { //排除127.0.0网段，继续下一个
            ifreq++;
            continue;
        }
        strcpy(localIp, strIp.c_str ());
        return 1;
    }
    // end (modified by wangtao at 2014-02-12 XQ2014012371349 关于优化IVR通话记录表中TEL_ORGCALLED字段获取IP地址的需求)
    return 0;
}

// added by wangtao at 2014-02-12 XQ2014012371349 关于优化IVR通话记录表中TEL_ORGCALLED字段获取IP地址的需求
int getConfigLocalIp (const std::string &strCfgPath, char *pstrLocalIp)
{
    // 打开配置文件
    std::fstream objCfgFile;
    objCfgFile.open (strCfgPath.c_str (), std::ios::in);
    if (!objCfgFile.is_open ())
    {
        // 文件无法打开
        return -1;
    }
    // 读取配置文件内容
    std::list<std::string> listCfgIp;
    std::string strIp;
    while (!objCfgFile.eof ())
    {
        objCfgFile>>strIp;
        listCfgIp.push_back (strIp);
    }
    objCfgFile.close ();

    int iSockFd;
    struct ifconf objIfConf;
    char pstrBuf[512];
    memset (pstrBuf, 0, 512);
    struct ifreq *pIfReq;

    //初始化ifconf
    objIfConf.ifc_len = 512;
    objIfConf.ifc_buf = pstrBuf;
    if ((iSockFd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    {
        return -2;
    }
    ioctl(iSockFd, SIOCGIFCONF, &objIfConf); //获取所有接口信息
    close(iSockFd);

    //接下来一个一个的获取IP地址
    pIfReq = (struct ifreq*)pstrBuf;
    for (int i = (objIfConf.ifc_len/sizeof(struct ifreq)); i > 0; i--) 
    {
        // 读取网卡IP配置
        strIp = inet_ntoa(((struct sockaddr_in*)&(pIfReq->ifr_addr))->sin_addr);
        if (0 == strIp.find ("127.0.0")) 
        { //排除127.0.0网段，继续下一个
            pIfReq++;
            continue;
        }

        // 遍历配置文件中的IP，如果匹配到，则说明已经找到本机IP，否则继续
        std::list<std::string>::iterator iterCfg = listCfgIp.begin (), iterEnd = listCfgIp.end ();
        while (iterCfg != iterEnd)
        {
            if (0 == strIp.compare ((*iterCfg)))
            {
                strcpy (pstrLocalIp, strIp.c_str ());
                return 0;
            }

            iterCfg++;
        }

        pIfReq++;
    }
    return -3;
}
// end (added by wangtao at 2014-02-12 XQ2014012371349 关于优化IVR通话记录表中TEL_ORGCALLED字段获取IP地址的需求)

//---------------------------------------------------------------------------

void AsynWriteFile(char* FilePath, char* FileData)
{
    FILE * pFile;
    if( ( pFile = fopen (FilePath, "a") ) == NULL){
        return;
    }
    fprintf(pFile, "%s\n", FileData);
    fflush(pFile);
    fclose(pFile);
}
//---------------------------------------------------------------------------

void AsynLogAppend(char* FilePath, char *szfmt, ...)
{
    char messageBuffer[1024];
    memset(messageBuffer, 0, sizeof(messageBuffer));
    //分析输入可变参数.
    va_list args;
    va_start(args, szfmt);
    vsprintf(messageBuffer, szfmt, args);
    va_end(args);
    char dtBuffer[LONG_DATETIME_LEN];
    getDTBuffer(dtBuffer, LONG_DATETIME_FORMAT);
    char logBuffer[2048];
    sprintf(logBuffer, "%s %s", dtBuffer, messageBuffer);
    AsynWriteFile(FilePath, logBuffer);
}
//---------------------------------------------------------------------------

//从字符串的左边截取n个字符
char * leftStr(char *dst,char *src, int n) {
    char *p = src;
    char *q = dst;
    int len = strlen(src);
    if(n>len) n = len;
    while(n--) *(q++) = *(p++);
    *(q++)='\0';
    return dst;
}
//---------------------------------------------------------------------------
//从字符串的中间截取n个字符: n为长度，m为位置
char * midStr(char *dst,char *src, int n,int m) {
    char *p = src;
    char *q = dst;
    int len = strlen(src);
    if(n>len) n = len-m;
    if(m<0) m=0;
    if(m>len) return NULL;
    p += m;
    while(n--) *(q++) = *(p++);
    *(q++)='\0';
    return dst;
}
//---------------------------------------------------------------------------
//从字符串的右边截取n个字符
char * rightStr(char *dst,char *src, int n) {
    char *p = src;
    char *q = dst;
    int len = strlen(src);
    if(n>len) n = len;
    p += (len-n);
    while(*(q++) = *(p++));
    return dst;
}
//---------------------------------------------------------------------------

bool isACMobileNo(char* PhoneNo) //125 + MobileNo
{
    bool bACMobile = false;
    if ( (strlen(PhoneNo) >= 12) && (memcmp(PhoneNo, "125", 3) == 0) ) {
        bACMobile = true;
    }
    return bACMobile;
}
//---------------------------------------------------------------------------
//判断是否移动号码不准确，待改
bool isMobileNo(char* PhoneNo) //移动号码
{
    try {
        if (strlen( PhoneNo ) != 11) return false;
        char HeadNo[4];
        leftStr(HeadNo, PhoneNo, 3);
        //memcpy(HeadNo, PhoneNo, 3);
        int iThree = atoi(HeadNo);
        if ((iThree>=134 && iThree<=139) || (iThree == 159) || (iThree == 158) || (iThree == 150)) return true;
        return false;
    }catch(...){
        return false;
    }
}
//---------------------------------------------------------------------------
//北京过来的国际漫游电话
bool isInternationalNo(char* PhoneNo)
{
    for (int i=0; i<44; i++) {
        if (strcmp(PhoneNo, InternationalNo[i]) == 0) {
            return true;
        }
    }
    for(int i=0; i<45; i++) {
        if (strcmp(PhoneNo,DeputyNo[i]) == 0) {
            return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------

bool isLeapYear(int iYear)
{
    return  ((iYear % 4) == 0) && (((iYear % 100) != 0) || ((iYear % 400) == 0));
}
//---------------------------------------------------------------------------

void getRelativeTime(long iSeconds, char* returnTime)
{
    time_t tNow = time(NULL) + iSeconds;
#ifdef RW_MULTI_THREAD
    struct tm tmTmp;
	strftime( returnTime, LONG_DATETIME_LEN, SHORT_DATETIME_FORMAT, localtime_r( &tNow, &tmTmp ) );
#else
	strftime( returnTime, LONG_DATETIME_LEN, SHORT_DATETIME_FORMAT, localtime( &tNow ) );
#endif
}
//---------------------------------------------------------------------------

//判断一个字符串是否数字串
bool isNumber(char* strString)
{
    if (strString == NULL) return false;
    for(int i = 0; strString[i] != '\0'; i++) {
        if (!isdigit(strString[i])) return false;
    }
    return true;
}
//---------------------------------------------------------------------------

int getDgSkill(char *skill,int iFeeArea )
{
    char DgSkill[20][40] = {"771","普通语音电话,国语,771动感地带",
                            "772","普通语音电话,国语,772动感地带",
                            "773","普通语音电话,国语,773动感地带",
                            "774","普通语音电话,国语,774动感地带",
                            "775","普通语音电话,国语,775动感地带",
                            "776","普通语音电话,国语,776动感地带",
                            "777","普通语音电话,国语,777动感地带",
                            "778","普通语音电话,国语,778动感地带",
                            "779","普通语音电话,国语,779动感地带",
                            "770","普通语音电话,国语,770动感地带"
                           };
    char area[10]="\0";
    sprintf(area, "%d", iFeeArea);
    for(int i=0; i<20; i++) {
        if(strcmp(area, DgSkill[i++]) == 0) {
            strcpy(skill,DgSkill[i]);
            return 1;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
int skillGroupSorted(char* skillGroup)
{
    try {
        char AppealskillGroup[22][40]={"普通语音电话,国语,投诉话费类","21",
                                       "普通语音电话,国语,投诉梦网和其它类","20",
                                       "普通语音电话,国语,投诉业务使用类","22",
                                       "普通语音电话,国语,投诉专席","9",
                                       "普通语音电话,国语,6号键投诉质量类","88",
                                       "普通语音电话,国语,1.5普通测试技能","69",
                                       "普通语音电话,国语,6号键话费类","44",
                                       "普通语音电话,国语,6号键网络类","45" ,
                                       "普通语音电话,国语,6号键梦网类","53" ,
                                       "普通语音电话,国语,6号键服务质量类","54",
                                       "普通语音电话,国语,6号键业务使用类","55"
                                       };
        char ServiceSkillGroup[10][40]={"普通语音电话,国语,业务办理转接专线","41",
                                       "普通语音电话,国语,VIP电话营业厅","12",
                                       "普通语音电话,国语,全球通电话营业厅","11",
                                       "普通语音电话,国语,普通电话营业厅","10",
                                       "普通语音电话,国语,1.5VIP测试技能","70"
                                      };
        for(int i=0;i<22;i++) {
            if(strcmp(skillGroup,AppealskillGroup[i]) == 0)
            return 1;
        }
        for(int i=0;i<10;i++) {
            if(strcmp(skillGroup,ServiceSkillGroup[i]) == 0)
            return 2;
        }
        return 0;
    } catch(...) {
        return 0;
    }
}
//---------------------------------------------------------------------------

int parseIdcard(char *Idcard,int type,char *changedId)
{
    strcpy(changedId, Idcard);
    int iLen = strlen(changedId);
    if (strcmp(changedId+iLen-1,"*") == 0) {
        if (type == 0) {
            strcpy(changedId+iLen-1,"x");
        } else {
            strcpy(changedId+iLen-1,"X");
        }
    }
    return 1;
}
//---------------------------------------------------------------------------

int splitPhoneNo(char* phoneNo)
{
    int iLen = strlen(phoneNo);
    if (iLen > 14) {
        strcpy(phoneNo, phoneNo + iLen - 11);
    }
    return 1;
}
//---------------------------------------------------------------------------

int getCalledArea(char *CalledNo, char *FeeArea)
{
    try {
        if (memcmp(CalledNo, "077", 3) == 0) {
            midStr(FeeArea, CalledNo, 3, 1);
            return 1;
        }
        return 0;
    }catch(...){
        strcpy(FeeArea, "771");
        return 0;
    }
}
//---------------------------------------------------------------------------

//分割一个字符串，返回值表示成功失败
bool splitString(char* strString,char division,char* subStr1,char* substr2)
{
    char *pt = strString;
    int iLen = strlen(strString);
    for (int i=0; i<iLen; i++) {
        if (strString[i] == division) {
            strncpy(subStr1,strString,i);
            strcpy(substr2,pt+1);
            return true;
        }
        pt++;
    }
    return false;
}
//---------------------------------------------------------------------------
//计算任一年任一月的天数
int getMonthDays(int iYear, int iMonth)
{
     if (iMonth == 1 || iMonth == 3 || iMonth == 5 || iMonth == 7 || iMonth == 8 || iMonth == 10 || iMonth == 12) return 31;
     else if (iMonth == 4 || iMonth == 6 || iMonth == 9 || iMonth == 11) return 30;
     else if (iMonth == 2) {
        if ((iYear%4 == 0 && iYear%100 != 0) || (iYear%400 == 0)) return 29;
        else return 28;
     }
     else return 0; //月份不正确
}
//---------------------------------------------------------------------------
//替换字符串中一个特征字符串为指定字符串
int strreplace(char *sSrc, char *sMatchStr, char *sReplaceStr)
{
    char sNewString[256] = "\0";
    if ((sSrc == NULL) || (sMatchStr == NULL) || (sReplaceStr == NULL)) return -1;
    char *FindPos = strstr(sSrc, sMatchStr);
    if ( FindPos == NULL ) return -1;
    strncpy(sNewString, sSrc, FindPos - sSrc);
    strcat(sNewString, sReplaceStr);
    strcat(sNewString, FindPos + strlen(sMatchStr));
    strcpy(sSrc, sNewString);
    return 0;
}
//---------------------------------------------------------------------------

//替换字符串中特征字符串为指定字符串
int strrep(char *sSrc, char *sMatchStr, char *sReplaceStr)
{
    char sNewString[256];
    if ((sSrc == NULL) || (sMatchStr == NULL) || (sReplaceStr == NULL)) return -1;
    char *FindPos = strstr(sSrc, sMatchStr);
    if (!FindPos) return -1;
    while( FindPos ) {
        memset(sNewString, '\0', sizeof(sNewString));
        strncpy(sNewString, sSrc, FindPos - sSrc);
        strcat(sNewString, sReplaceStr);
        strcat(sNewString, FindPos + strlen(sMatchStr));
        strcpy(sSrc, sNewString);
        FindPos = strstr(sSrc, sMatchStr);
    }
    return 0;
}
//---------------------------------------------------------------------------
int AnalyseNodeCode(char *nodeCode,char* busiCode,char* type)
{
    if (nodeCode == NULL) return 0;
    char node[40];
    strcpy(node,nodeCode);
    int iLen = strlen(node);
    if (iLen <=3) return 0;
    char *pValue;
    pValue = strtok(node,"|");
    strcpy(busiCode,pValue);
    pValue = strtok(NULL,"|");
    strcpy(type, pValue);
    //strcpy(type,"1");
    if (( strcmp(type,"1") == 0) || (strcmp(type,"2") == 0) || (strcmp(type,"3") == 0)) {
        return 1;  //本机办理，不验证密码
    }
    return 0;
}
//---------------------------------------------------------------------------

bool isSelfBusiPhone(char* CalledNo)
{
    try {
        char CalledPhone[8];
        memset(CalledPhone, '\0', sizeof(CalledPhone));
        if (memcmp(CalledNo, "077", 3) == 0) {
            strncpy(CalledPhone, CalledNo+4, 7);
        } else {
            strncpy(CalledPhone, CalledNo, 7);
        }
        if (strcmp(CalledPhone, "1008666") == 0) return true;
        return false;
    }catch(...){
        return false;
    }
}
//---------------------------------------------------------------------------

int  getGprsProdId(char* GprsName,char* FeeArea,char* ProdId)
{
    try { //各地市GPRS20、GPRS100、GPRS200的prodId不统一
        char ProdIdList[10][3][10]= {
            {"70100010","70100001","70100012"},  //防城
            {"71100005","71100006","71100007"},  //南宁
            {"72100003","72100023","72100024"},  //柳州
            {"73100008","73100009","73100010"},  //桂林
            {"74100004","74100020","74100005"},  //梧州
            {"75100001","75100002","75100003"},  //玉林
            {"76100019","76100002","76100003"},  //百色
            {"77100002","77100015","77100016"},  //钦州
            {"78100002","78100003","78100004"},  //河池
            {"79100002","79100003","79100004"}   //北海
        };
        int iFeeArea = atoi(FeeArea) - 770;
        if (strcmp(GprsName,"GPRS20") == 0) {
            strcpy(ProdId,ProdIdList[iFeeArea][0]);
            return 1;
        } else if (strcmp(GprsName,"GPRS100") == 0) {
            strcpy(ProdId,ProdIdList[iFeeArea][1]);
            return 1;
        } else if (strcmp(GprsName,"GPRS200") == 0) {
            strcpy(ProdId,ProdIdList[iFeeArea][2]);
            return 1;
        }
        return 0; 
    }catch(...)
    {
        return 0;
    }
}
//---------------------------------------------------------------------------
int getCmdByProd(char* ProdId,char* BusiType,char* CmdStr,char* Descript,char* isChecked)
{
    const int iLen = 59;
    char Prod2Cmd[iLen][5][128]= {
        //彩铃 3
        {"30512101","1","KTCLTC#5","开通5元彩铃套餐","0"},
        {"30512001","1","KTCLTC#10","开通10元彩铃套餐","0"},
        {"RBTS","3","QXCLTC","取消彩铃套餐","0"},
        //短信套餐 9      --service_id=50005
        {"99100116","1","KTDXTC#1","开通1元短信套餐","0"},
        {"99100098","1","KTDXTC#5","开通5元短信套餐","0"}, //3021
        {"99100097","1","KTDXTC#10","开通10元短信套餐","0"}, //3022
        {"99100117","1","KTDXTC#15","开通15元短信套餐","0"}, //3023
        {"99100118","1","KTDXTC#20","开通20元短信套餐","0"},
        {"99100119","1","KTDXTC#30","开通30元短信套餐","0"},
        {"99100120","1","KTDXTC#50","开通50元短信套餐","0"},
        {"99100121","1","KTDXTC#100","开通100元短信套餐","0"},
        {"SMS","3","QXDXTC","取消短信套餐","0"}, //3024
        //彩信套餐 6      --service_id=50014
        {"99100158","1","KTCXTC#1","开通1元彩信套餐","0"},
        {"99100074","1","KTCXTC#3","开通3元彩信套餐","0"},
        {"99100160","1","KTCXTC#5","开通5元彩信套餐","0"},
        {"99100161","1","KTCXTC#10","开通10彩信信套餐","0"},
        {"99100162","1","KTCXTC#20","开通20彩信信套餐","0"},
        {"MMS","3","QXCXTC","取消彩信套餐","0"},
        //长话漫游包 14    --service_id=50001
        {"99100142","1","KTYYTH","开通12593特惠包","0"},
        {"99100122","1","KTCHYY","开通国内9元长话优惠包","0"},
        {"99100123","1","KTCHB#19","开通国内19元长话优惠包","0"},
        {"99100124","1","KTCHB#39","开通国内39元长话优惠包","0"},
        {"99100125","1","KTCHB#69","开通国内69元长话优惠包","0"},
        {"99100126","1","KTCHB#99","开通国内99元长话优惠包","0"},
        {"99100128","1","KTMYYH","开通区内9元漫游优惠包","0"}, //4031
        {"99100129","1","KTMYYH#19","开通区内19元漫游优惠包","0"},
        {"99100130","1","KTMYYH#29","开通区内29元漫游优惠包","0"},
        {"99100131","1","KTMYYH#49","开通区内49元漫游优惠包","0"},
        {"99100132","1","KTMYYH#99","开通区内99元漫游优惠包","0"},
        {"12593","3","QXYYTH","取消12593特惠包","0"},
        {"LDTEL","3","QXCHYHALL","取消长话优惠包","0"},
        {"ROAM","3","QXMYYHALL","取消漫游优惠包","0"},
        //GPRS 9   --service_id=53001
        {"30502501","1","SWKT","开通GPRS","0"}, //3054
        {"30502501","3","SWGB","取消GPRS","0"}, //3055
        {"GPRSBASIC","1","GPRSBZZF","开通GPRS标准资费","0"},
        {"99100148","1","3051","开通5元GPRS套餐","0"}, //KTSWTC#5
        {"99100023","1","3056","开通8元GPRS套餐","0"}, //KTSWTC#8
        {"GPRS20","1","KTGPRSTC#20","开通20元GPRS套餐","0"},
        {"GPRS100","1","KTGPRSTC#100","开通100元GPRS套餐","0"},
        {"GPRS200","1","KTGPRSTC#200","开通200元GPRS套餐","0"},
        {"GPRS","3","QXSWTC","取消GPRS套餐","0"}, //3052
        //其他业务 18
        {"30506001","1","KTLDTX","开通来电提醒","0"},
        {"30506001","3","QXLDTX","开通来电提醒","0"},
        {"30501101","1","KTLDXS","开通来电显示","0"},
        {"30501101","3","QXLDXS","开通来电显示","0"},
        {"30502201","1","KTYDMS","开通5元移动秘书","0"},
        {"30502201","3","QXYDMS","开通5元移动秘书","0"},
        {"SJZWB","1","KTSJZWB","开通手机早晚报","0"},
        {"SJZWB","3","QXSJZWB","取消手机早晚报","0"},
        {"IIC","1","KTFX","开通飞信","0"},
        {"IIC","3","QXFX","取消飞信","0"},
        {"+MCHAT","1","KTFXJY","开通飞信交友","0"},
        {"+MCHAT","3","QXFXJY","取消飞信交友","0"},
        {"-MAILA","1","KTSJYX#200M","开通200M手机邮箱","0"},
        {"-MAILB","1","KTSJYX#500M","开通500M手机邮箱","0"},
        {"-MAILC","1","KTSJYX#1G","开通1G手机邮箱","0"},
        {"-MAILA","3","QXSJYX200M","取消200M手机邮箱","0"},
        {"-MAILB","3","QXSJYX500M","取消500M手机邮箱","0"},
        {"-MAILC","3","QXSJYX1G","取消1G手机邮箱","0"}
    };
    for (int i=0;i<iLen;i++) {
        if ((strcmp(ProdId,Prod2Cmd[i][0]) == 0) && (strcmp(BusiType,Prod2Cmd[i][1]) == 0)) {
            strncpy(CmdStr,Prod2Cmd[i][2],20);
            strncpy(Descript,Prod2Cmd[i][3],128);
            strncpy(isChecked,Prod2Cmd[i][4],10);
            return 1;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
//数字转为汉字(仅支持1-10)
void NumToCHS(int num, char* ch) {
    if (num < 1 || num > 10) return;
    switch(num){
        case 1: strcpy(ch,"一");break;
        case 2: strcpy(ch,"二");break;
        case 3: strcpy(ch,"三");break;
        case 4: strcpy(ch,"四");break;
        case 5: strcpy(ch,"五");break;
        case 6: strcpy(ch,"六");break;
        case 7: strcpy(ch,"七");break;
        case 8: strcpy(ch,"八");break;
        case 9: strcpy(ch,"九");break;
        case 10: strcpy(ch,"十");break;
    }
}
//---------------------------------------------------------------------------

void getMillSecBuffer(char *szBuf)
{
    SYSTEMTIME pST;
    getLocalSysTime(&pST);
    //sprintf(szBuf, LONG_MILLSEC_FORMAT, pST.wYear,pST.wMonth,pST.wDay,pST.wHour,pST.wMinute,pST.wSecond,pST.wMilliseconds);
    sprintf(szBuf, SHORT_MILLSEC_RORMAT, pST.wHour,pST.wMinute,pST.wSecond,pST.wMilliseconds);
}
//---------------------------------------------------------------------------

int makeDirectory(const char *filePath)
{
    char dirName[256];
    strcpy(dirName, filePath);
    int iLen = strlen( filePath );
    if (dirName[iLen - 1] != '/') {
        strcat(dirName, "/");
    }
    iLen = strlen( dirName );
    for (int i = 1; i < iLen; i++) {
        if (dirName[i] == '/') {
            dirName[i] = 0;
            if (access(dirName, NULL) != 0) {
                if (mkdir(dirName, 0755) == -1) {
                    perror("mkdir error");
                    return -1;
                }
            }
            dirName[i] = '/';
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
//YearMonth参数要求是6位，比如201204
int increaseMonth(int YearMonth, int NumberOfMonths)
{
    int iYear = YearMonth / 100;
    int iMonth = YearMonth % 100;
    iMonth += NumberOfMonths;
    if (iMonth > 12) {
        do {
            iMonth -= 12;
            iYear++;
        } while (iMonth > 12);
    } else if (iMonth <= 0) {
        do {
            iMonth += 12;
            iYear--;
        } while (iMonth <=0);
    }
    return (iYear * 100 + iMonth);
}
//---------------------------------------------------------------------------

void DelayMicroSeconds(long nMicroSeconds)
{
    struct timeval tv;
	tv.tv_sec = nMicroSeconds / 1000;           //Seconds
	tv.tv_usec = (nMicroSeconds % 1000) * 1000; //Microseconds
	select(0, NULL, NULL, NULL, &tv);
	//select(0, (fd_set*)0, (fd_set*)0, (fd_set*)0, &tv);
}
//---------------------------------------------------------------------------
