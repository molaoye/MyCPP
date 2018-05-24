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
    lpSystemTime->wYear = tm_now.tm_year+1900; //���
    lpSystemTime->wMonth = tm_now.tm_mon+1; //�� tm[0-11] sys[1-12]
    lpSystemTime->wDay = tm_now.tm_mday; //��
    // tmһ���ڵ�������������һ���𣬷�ΧΪ0-6 sys������������
    lpSystemTime->wDayOfWeek = (tm_now.tm_wday+1)%7;
    lpSystemTime->wHour =tm_now.tm_hour;   //Сʱ
    lpSystemTime->wMinute = tm_now.tm_min; //����
    lpSystemTime->wSecond = tm_now.tm_sec; //��
    lpSystemTime->wMilliseconds = tv.tv_usec/1000; //����
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
        //ȥ��������
        if (memcmp(calledNo, "077", 3) == 0) {
            strcpy(calledNo, calledNo + 4);
        }
        int iLen = strlen(calledNo);
        //ȥ���������������Ȼ����14λ����ض�
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

//��ȡIP��ַ�ַ���: 1=�ɹ���0=ʧ��
int getlocalIp(char* localIp) {
    int i = 0;
    int sockfd;
    struct ifconf ifconf;
    char buf[512];
    struct ifreq *ifreq;
    char* ip;
    //��ʼ��ifconf
    ifconf.ifc_len = 512;
    ifconf.ifc_buf = buf;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return 0;
    }
    ioctl(sockfd, SIOCGIFCONF, &ifconf); //��ȡ���нӿ���Ϣ
    close(sockfd);
    //������һ��һ���Ļ�ȡIP��ַ
    // modified by wangtao at 2014-02-12 XQ2014012371349 �����Ż�IVRͨ����¼����TEL_ORGCALLED�ֶλ�ȡIP��ַ������
    ifreq = (struct ifreq*)buf;
    std::string strIp = "";
    for (i = (ifconf.ifc_len/sizeof(struct ifreq)); i>0; i--) {
        strIp = inet_ntoa(((struct sockaddr_in*)&(ifreq->ifr_addr))->sin_addr);
        if (0 == strIp.find ("127.0.0")) { //�ų�127.0.0���Σ�������һ��
            ifreq++;
            continue;
        }
        strcpy(localIp, strIp.c_str ());
        return 1;
    }
    // end (modified by wangtao at 2014-02-12 XQ2014012371349 �����Ż�IVRͨ����¼����TEL_ORGCALLED�ֶλ�ȡIP��ַ������)
    return 0;
}

// added by wangtao at 2014-02-12 XQ2014012371349 �����Ż�IVRͨ����¼����TEL_ORGCALLED�ֶλ�ȡIP��ַ������
int getConfigLocalIp (const std::string &strCfgPath, char *pstrLocalIp)
{
    // �������ļ�
    std::fstream objCfgFile;
    objCfgFile.open (strCfgPath.c_str (), std::ios::in);
    if (!objCfgFile.is_open ())
    {
        // �ļ��޷���
        return -1;
    }
    // ��ȡ�����ļ�����
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

    //��ʼ��ifconf
    objIfConf.ifc_len = 512;
    objIfConf.ifc_buf = pstrBuf;
    if ((iSockFd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    {
        return -2;
    }
    ioctl(iSockFd, SIOCGIFCONF, &objIfConf); //��ȡ���нӿ���Ϣ
    close(iSockFd);

    //������һ��һ���Ļ�ȡIP��ַ
    pIfReq = (struct ifreq*)pstrBuf;
    for (int i = (objIfConf.ifc_len/sizeof(struct ifreq)); i > 0; i--) 
    {
        // ��ȡ����IP����
        strIp = inet_ntoa(((struct sockaddr_in*)&(pIfReq->ifr_addr))->sin_addr);
        if (0 == strIp.find ("127.0.0")) 
        { //�ų�127.0.0���Σ�������һ��
            pIfReq++;
            continue;
        }

        // ���������ļ��е�IP�����ƥ�䵽����˵���Ѿ��ҵ�����IP���������
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
// end (added by wangtao at 2014-02-12 XQ2014012371349 �����Ż�IVRͨ����¼����TEL_ORGCALLED�ֶλ�ȡIP��ַ������)

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
    //��������ɱ����.
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

//���ַ�������߽�ȡn���ַ�
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
//���ַ������м��ȡn���ַ�: nΪ���ȣ�mΪλ��
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
//���ַ������ұ߽�ȡn���ַ�
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
//�ж��Ƿ��ƶ����벻׼ȷ������
bool isMobileNo(char* PhoneNo) //�ƶ�����
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
//���������Ĺ������ε绰
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

//�ж�һ���ַ����Ƿ����ִ�
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
    char DgSkill[20][40] = {"771","��ͨ�����绰,����,771���еش�",
                            "772","��ͨ�����绰,����,772���еش�",
                            "773","��ͨ�����绰,����,773���еش�",
                            "774","��ͨ�����绰,����,774���еش�",
                            "775","��ͨ�����绰,����,775���еش�",
                            "776","��ͨ�����绰,����,776���еش�",
                            "777","��ͨ�����绰,����,777���еش�",
                            "778","��ͨ�����绰,����,778���еش�",
                            "779","��ͨ�����绰,����,779���еش�",
                            "770","��ͨ�����绰,����,770���еش�"
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
        char AppealskillGroup[22][40]={"��ͨ�����绰,����,Ͷ�߻�����","21",
                                       "��ͨ�����绰,����,Ͷ��������������","20",
                                       "��ͨ�����绰,����,Ͷ��ҵ��ʹ����","22",
                                       "��ͨ�����绰,����,Ͷ��רϯ","9",
                                       "��ͨ�����绰,����,6�ż�Ͷ��������","88",
                                       "��ͨ�����绰,����,1.5��ͨ���Լ���","69",
                                       "��ͨ�����绰,����,6�ż�������","44",
                                       "��ͨ�����绰,����,6�ż�������","45" ,
                                       "��ͨ�����绰,����,6�ż�������","53" ,
                                       "��ͨ�����绰,����,6�ż�����������","54",
                                       "��ͨ�����绰,����,6�ż�ҵ��ʹ����","55"
                                       };
        char ServiceSkillGroup[10][40]={"��ͨ�����绰,����,ҵ�����ת��ר��","41",
                                       "��ͨ�����绰,����,VIP�绰Ӫҵ��","12",
                                       "��ͨ�����绰,����,ȫ��ͨ�绰Ӫҵ��","11",
                                       "��ͨ�����绰,����,��ͨ�绰Ӫҵ��","10",
                                       "��ͨ�����绰,����,1.5VIP���Լ���","70"
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

//�ָ�һ���ַ���������ֵ��ʾ�ɹ�ʧ��
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
//������һ����һ�µ�����
int getMonthDays(int iYear, int iMonth)
{
     if (iMonth == 1 || iMonth == 3 || iMonth == 5 || iMonth == 7 || iMonth == 8 || iMonth == 10 || iMonth == 12) return 31;
     else if (iMonth == 4 || iMonth == 6 || iMonth == 9 || iMonth == 11) return 30;
     else if (iMonth == 2) {
        if ((iYear%4 == 0 && iYear%100 != 0) || (iYear%400 == 0)) return 29;
        else return 28;
     }
     else return 0; //�·ݲ���ȷ
}
//---------------------------------------------------------------------------
//�滻�ַ�����һ�������ַ���Ϊָ���ַ���
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

//�滻�ַ����������ַ���Ϊָ���ַ���
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
        return 1;  //������������֤����
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
    try { //������GPRS20��GPRS100��GPRS200��prodId��ͳһ
        char ProdIdList[10][3][10]= {
            {"70100010","70100001","70100012"},  //����
            {"71100005","71100006","71100007"},  //����
            {"72100003","72100023","72100024"},  //����
            {"73100008","73100009","73100010"},  //����
            {"74100004","74100020","74100005"},  //����
            {"75100001","75100002","75100003"},  //����
            {"76100019","76100002","76100003"},  //��ɫ
            {"77100002","77100015","77100016"},  //����
            {"78100002","78100003","78100004"},  //�ӳ�
            {"79100002","79100003","79100004"}   //����
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
        //���� 3
        {"30512101","1","KTCLTC#5","��ͨ5Ԫ�����ײ�","0"},
        {"30512001","1","KTCLTC#10","��ͨ10Ԫ�����ײ�","0"},
        {"RBTS","3","QXCLTC","ȡ�������ײ�","0"},
        //�����ײ� 9      --service_id=50005
        {"99100116","1","KTDXTC#1","��ͨ1Ԫ�����ײ�","0"},
        {"99100098","1","KTDXTC#5","��ͨ5Ԫ�����ײ�","0"}, //3021
        {"99100097","1","KTDXTC#10","��ͨ10Ԫ�����ײ�","0"}, //3022
        {"99100117","1","KTDXTC#15","��ͨ15Ԫ�����ײ�","0"}, //3023
        {"99100118","1","KTDXTC#20","��ͨ20Ԫ�����ײ�","0"},
        {"99100119","1","KTDXTC#30","��ͨ30Ԫ�����ײ�","0"},
        {"99100120","1","KTDXTC#50","��ͨ50Ԫ�����ײ�","0"},
        {"99100121","1","KTDXTC#100","��ͨ100Ԫ�����ײ�","0"},
        {"SMS","3","QXDXTC","ȡ�������ײ�","0"}, //3024
        //�����ײ� 6      --service_id=50014
        {"99100158","1","KTCXTC#1","��ͨ1Ԫ�����ײ�","0"},
        {"99100074","1","KTCXTC#3","��ͨ3Ԫ�����ײ�","0"},
        {"99100160","1","KTCXTC#5","��ͨ5Ԫ�����ײ�","0"},
        {"99100161","1","KTCXTC#10","��ͨ10�������ײ�","0"},
        {"99100162","1","KTCXTC#20","��ͨ20�������ײ�","0"},
        {"MMS","3","QXCXTC","ȡ�������ײ�","0"},
        //�������ΰ� 14    --service_id=50001
        {"99100142","1","KTYYTH","��ͨ12593�ػݰ�","0"},
        {"99100122","1","KTCHYY","��ͨ����9Ԫ�����Żݰ�","0"},
        {"99100123","1","KTCHB#19","��ͨ����19Ԫ�����Żݰ�","0"},
        {"99100124","1","KTCHB#39","��ͨ����39Ԫ�����Żݰ�","0"},
        {"99100125","1","KTCHB#69","��ͨ����69Ԫ�����Żݰ�","0"},
        {"99100126","1","KTCHB#99","��ͨ����99Ԫ�����Żݰ�","0"},
        {"99100128","1","KTMYYH","��ͨ����9Ԫ�����Żݰ�","0"}, //4031
        {"99100129","1","KTMYYH#19","��ͨ����19Ԫ�����Żݰ�","0"},
        {"99100130","1","KTMYYH#29","��ͨ����29Ԫ�����Żݰ�","0"},
        {"99100131","1","KTMYYH#49","��ͨ����49Ԫ�����Żݰ�","0"},
        {"99100132","1","KTMYYH#99","��ͨ����99Ԫ�����Żݰ�","0"},
        {"12593","3","QXYYTH","ȡ��12593�ػݰ�","0"},
        {"LDTEL","3","QXCHYHALL","ȡ�������Żݰ�","0"},
        {"ROAM","3","QXMYYHALL","ȡ�������Żݰ�","0"},
        //GPRS 9   --service_id=53001
        {"30502501","1","SWKT","��ͨGPRS","0"}, //3054
        {"30502501","3","SWGB","ȡ��GPRS","0"}, //3055
        {"GPRSBASIC","1","GPRSBZZF","��ͨGPRS��׼�ʷ�","0"},
        {"99100148","1","3051","��ͨ5ԪGPRS�ײ�","0"}, //KTSWTC#5
        {"99100023","1","3056","��ͨ8ԪGPRS�ײ�","0"}, //KTSWTC#8
        {"GPRS20","1","KTGPRSTC#20","��ͨ20ԪGPRS�ײ�","0"},
        {"GPRS100","1","KTGPRSTC#100","��ͨ100ԪGPRS�ײ�","0"},
        {"GPRS200","1","KTGPRSTC#200","��ͨ200ԪGPRS�ײ�","0"},
        {"GPRS","3","QXSWTC","ȡ��GPRS�ײ�","0"}, //3052
        //����ҵ�� 18
        {"30506001","1","KTLDTX","��ͨ��������","0"},
        {"30506001","3","QXLDTX","��ͨ��������","0"},
        {"30501101","1","KTLDXS","��ͨ������ʾ","0"},
        {"30501101","3","QXLDXS","��ͨ������ʾ","0"},
        {"30502201","1","KTYDMS","��ͨ5Ԫ�ƶ�����","0"},
        {"30502201","3","QXYDMS","��ͨ5Ԫ�ƶ�����","0"},
        {"SJZWB","1","KTSJZWB","��ͨ�ֻ�����","0"},
        {"SJZWB","3","QXSJZWB","ȡ���ֻ�����","0"},
        {"IIC","1","KTFX","��ͨ����","0"},
        {"IIC","3","QXFX","ȡ������","0"},
        {"+MCHAT","1","KTFXJY","��ͨ���Ž���","0"},
        {"+MCHAT","3","QXFXJY","ȡ�����Ž���","0"},
        {"-MAILA","1","KTSJYX#200M","��ͨ200M�ֻ�����","0"},
        {"-MAILB","1","KTSJYX#500M","��ͨ500M�ֻ�����","0"},
        {"-MAILC","1","KTSJYX#1G","��ͨ1G�ֻ�����","0"},
        {"-MAILA","3","QXSJYX200M","ȡ��200M�ֻ�����","0"},
        {"-MAILB","3","QXSJYX500M","ȡ��500M�ֻ�����","0"},
        {"-MAILC","3","QXSJYX1G","ȡ��1G�ֻ�����","0"}
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
//����תΪ����(��֧��1-10)
void NumToCHS(int num, char* ch) {
    if (num < 1 || num > 10) return;
    switch(num){
        case 1: strcpy(ch,"һ");break;
        case 2: strcpy(ch,"��");break;
        case 3: strcpy(ch,"��");break;
        case 4: strcpy(ch,"��");break;
        case 5: strcpy(ch,"��");break;
        case 6: strcpy(ch,"��");break;
        case 7: strcpy(ch,"��");break;
        case 8: strcpy(ch,"��");break;
        case 9: strcpy(ch,"��");break;
        case 10: strcpy(ch,"ʮ");break;
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
//YearMonth����Ҫ����6λ������201204
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
