//============================================================================
// Name        : hello.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
//#include <string>
#include <sstream>
#include <exception>
#include <typeinfo>
//#include <fiostream.h>
#include <fstream>
#include <vector>

using namespace std;

namespace first {
int var = 5;
}

namespace second {
double var = 3.1416;
}

inline int max(int,int,int);

/*inline */int isnumber(char ch);

template<typename T>

T max3(T a, T b, T c/*, T d*/) {//定义一个通用函数,用T作虚拟的类型名
	if (b > a)
		a = b;
	if (c > a)
		a = c;
//	if(d>a)
//		a=d;
	return a;
}

template<class T> T GetMax(T a, T b) {
	T result;
	result = (a > b) ? a : b;
	return (result);
}

//template<class T> class pair {
//	T value1, value2;
//public:
//	pair(T first, T second) {
//		value1 = first;
//		value2 = second;
//	}
//	T getmax();
//};
//template<class T>
//T pair::getmax() {
//	T retval;
//	retval = value1 > value2 ? value1 : value2;
//	return retval;
//}

//template<class T> class pair {
//	T value1, value2;
//public:
//	pair(T first, T second) {
//		value1 = first;
//		value2 = second;
//	}
//	T module() {
//		return 0;
//	}
//};
//template<>
//class pair<int> {
//	int value1, value2;
//public:
//	pair(int first, int second) {
//		value1 = first;
//		value2 = second;
//	}
//	int module();
//};
//
//template<>
//int pair<int>::module() {
//	return value1 % value2;
//}

template<class T, int N>
class array {
	T memblock[N];
public:
	void setmember(int x, T value);
	T getmember(int x);
};
template<class T, int N>
void array<T, N>::setmember(int x, T value) {
	memblock[x] = value;
}
template<class T, int N>
T array<T, N>::getmember(int x) {
	return memblock[x];
}

int a;

string name[50], num[50];//定义两个字符串数组,分别存放姓名和学号

int n;//n是实际的学生数

#define N_MOVIES 5

struct Student2 {
	char name[10];
	int num;
	char sex;
};

struct movies_t {
	char title[50];
	int year;
} mine, yours, films[N_MOVIES], amovie, * pmovie;

int subtraction (int a, int b) {
    return (a-b);
}

int (*minus)(int,int) = subtraction;

class CSquare;

class CRectangle {
	int x, y;
	int *width, *height;
public:
	void set_values(int, int);
	int area(void) {
		return (x * y);
	}
	friend CRectangle duplicate (CRectangle);
//	CRectangle ();
//	CRectangle (int,int);
//	~CRectangle ();
	int area2(void) {
		return (*width * *height);
	}
	void convert (CSquare a);
};

class CSquare {
private:
	int side;
public:
	void set_side(int a) {
		side = a;
	}
	friend class CRectangle;//因此CRectangle可以访问CSquare 的protected 和 private 成员
};

void CRectangle::convert(CSquare a) {
	x = a.side;
	y = a.side;
}

void CRectangle::set_values(int a, int b) {
	x = a;
	y = b;
}
//CRectangle::CRectangle() {
//	x = 5;
//	y = 5;
//}
//CRectangle::CRectangle(int a, int b) {
//	x = a;
//	y = b;
//	width = new int;
//	height = new int;
//	*width = a;
//	*height = b;
//}
//CRectangle::~CRectangle() {//析构函数特别适用于当一个对象被动态分别内存空间，而在对象被销毁的时我们希望释放它所占用的空间的时候
//	delete width;
//	delete height;
//}

class CVector {
public:
	int x, y;
	CVector() {};
	CVector(int, int);
	CVector operator +(CVector);
	CVector& operator= (const CVector& param);
};

CVector::CVector(int a, int b) {
	x = a;
	y = b;
}

CVector& CVector::operator=(const CVector& param) {
	x = param.x;
	y = param.y;
	return *this;
}

CVector CVector::operator+(CVector param) {
	CVector temp;
	temp.x = x + param.x;
	temp.y = y + param.y;
	return (temp);
}

class CDummy {
public:
	int isitme(CDummy& param);
	static int n;
	CDummy() {
		n++;
	};
	~CDummy() {
		n--;
	};
};

int CDummy::n=0;

int CDummy::isitme(CDummy& param) {
	if (&param == this)
		return 1;
	else
		return 0;
}

class CPolygon {
protected:
	int width, height;
public:
	void set_values(int a, int b) {
		width = a;
		height = b;
	}
	virtual int area(void) {
		return (0);
	}
};

class CPolygon2 {
protected:
	int width, height;
public:
	void set_values(int a, int b) {
		width = a;
		height = b;
	}
	virtual int area (void) =0;
	void printarea(void) {
		cout << this->area() << endl;
	}
};

class COutput {
public:
	void output(int i);
};

void COutput::output(int i) {
	cout << i << endl;
}

class CRectangle2: public CPolygon {
public:
	int area(void) {
		return (width * height);
	}
};

class CRectangle4: public CPolygon2 {
public:
	int area(void) {
		return (width * height);
	}
};

class CTriangle: public CPolygon {
public:
	int area(void) {
		return (width * height / 2);
	}
};

class CTriangle3: public CPolygon2 {
public:
	int area(void) {
		return (width * height / 2);
	}
};

class CRectangle3: public CPolygon, public COutput {
public:
	int area(void) {
		return (width * height);
	}
};

class CTriangle2: public CPolygon, public COutput {
public:
	int area(void) {
		return (width * height / 2);
	}
};

class mother {
public:
	mother() {
		cout << "mother: no parameters\n";
	}
	mother(int a) {
		cout << "mother: int parameter\n";
	}
};

class daughter: public mother {
public:
	daughter(int a) {// 没有特别制定：调用默认constructor
		cout << "daughter: int parameter\n\n";
	}
};

class son: public mother {
public:
	son(int a) : mother(a) {// 指定了constructor: 调用被指定的构造函数
		cout << "son: int parameter\n\n";
	}
};

class A {
	virtual void f() {
	}
	;
};

const char * filename = "E:\\Workspaces_eclipse_cpp\\hello world\\src\\hello world.cpp";

class CommonUtil{
public:
	//字符串split
	static void strSplit(const string& src, vector<string>& dest, const string& delimiter = ",") {
		string::size_type lpos = 0;
		string::size_type pos = src.find_first_of(delimiter, lpos);
		while (lpos != string::npos) {
			dest.insert(dest.end(), src.substr(lpos, pos - lpos));
			lpos = (pos == string::npos) ? string::npos : pos + 1;
			pos = src.find_first_of(delimiter, lpos);
		}
	}

	//字符串split
	static void strSplit2(const string& src, vector<string>& dest, const string& separator) {
		string str = src;
		string substring;
		string::size_type start = 0, index;
		do {
			index = str.find_first_of(separator, start);
			if (index != string::npos) {
				substring = str.substr(start, index - start);
				dest.push_back(substring);
				start = str.find_first_not_of(separator, index);
				if (start == string::npos)
					return;
			}
		} while (index != string::npos);
		//the last token
		substring = str.substr(start);
		dest.push_back(substring);
	}

	//月天数
	static int monthDays(int y, int m) {
		int d;
		int day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (2 == m) {
			d = (((0 == y % 4) && (0 != y % 100) || (0 == y % 400)) ? 29 : 28);
		} else {
			d = day[m - 1];

		}
		return d;
	}

	//int2string
	static string int2str(int n) {
	    char t[256];
	    int i = 0;
	    while (n) {
	        t[i++] = (n % 10) + '0';
	        n /= 10;
	    }
	    t[i] = 0;
	    return string(strrev(t));
	}

	//int2string
	static string int2str2(int n) {
		char t[256];
		string s;
		sprintf(t, "%d", n);
		s = t;
		return s;
	}

	//读文件
	static char* readFile(char* filePath){
		char buffer[64 * 1024 + 100];
		ifstream ifile(filePath);
		if (!ifile.is_open()) {
			cout << "Error opening file";
			exit(1);
		}
		char line[256];
		while (!ifile.eof()) {
			ifile.getline(line, 100);
//			cout << buffer << endl;
			strncat(buffer, line, strlen(line));
		}
		ifile.close();
		return buffer;
	}

	//读文件
	static void readFile(char* file, char* filePath){
		ifstream ifile(filePath);
		if (!ifile.is_open()) {
			cout << "Error opening file";
			exit(1);
		}
		char line[256];
		while (!ifile.eof()) {
			ifile.getline(line, 100);
//			cout << file << endl;
			strncat(file, line, strlen(line));
		}
		ifile.close();
	}

};

class Test{
public:
	static void stringTest1(){
		string strBulletinType="other";//unread_type_id	all_type_id

		int nSortType=100;

		string messageIdCondition="";
		string messageIdCondition1="";
		messageIdCondition1+="SELECT message_id FROM xg.sys_message_receive WHERE ";
//		messageIdCondition1+=field.value("receive_id",iRecvOpId).get_fieldExpession();
		messageIdCondition1+="receive_id= ";
		messageIdCondition1+=" AND ";
//		messageIdCondition1+=field.value("receive_id_type",0).get_fieldExpession();
		messageIdCondition1+="receive_id_type=0 ";
		messageIdCondition1+="\nUNION\n";
		messageIdCondition1+="SELECT a1.message_id FROM xg.sys_message_receive a1,\
			(SELECT org_id FROM xg.sys_organizations CONNECT BY PRIOR pri_org_id = org_id \
			START WITH org_id IN (SELECT org_id FROM xg.sys_operators WHERE ";
//		messageIdCondition1+=field.value("op_id",iRecvOpId).get_fieldExpession();
		messageIdCondition1+="op_id= ";
		messageIdCondition1+=")) b1 WHERE a1.receive_id = b1.org_id AND a1.receive_id_type = 1";
		string messageIdCondition2="";
		if("unread_type_id"==strBulletinType)
		{
			messageIdCondition2+="\nMINUS\n";
			messageIdCondition2+="SELECT message_id FROM xg.sys_broad_message_log WHERE ";
//			messageIdCondition2+=field.value("read_op_id",iRecvOpId).get_fieldExpession();
			messageIdCondition2+="read_op_id= ";
			messageIdCondition=messageIdCondition1+messageIdCondition2;
		}
		else
		{
			messageIdCondition=messageIdCondition1;
		}
		string messageCondition="";
		messageCondition+="SELECT * FROM (SELECT * FROM xg.sys_broad_message WHERE message_id IN (";
		messageCondition+=messageIdCondition;
		messageCondition+=") AND valid_date <= SYSDATE AND expire_date >= SYSDATE AND is_draft = 0 AND ";
		string searchCondition="";
//		if(strSearchTitle!=""){
//			searchCondition=field.value("message_caption","%"+strSearchTitle+"%","like").get_fieldExpession();
			searchCondition="message_caption like %%";
			messageCondition+=searchCondition;
			messageCondition+=" AND ";
//		}
//		if(strSearchContent!=""){
//			searchCondition=field.value("message_content","%"+strSearchContent+"%","like").get_fieldExpession();
			searchCondition="message_content like %%";
			messageCondition+=searchCondition;
			messageCondition+=" AND ";
//		}
		if(strBulletinType!="unread_type_id"&&strBulletinType!="all_type_id")
		{
//			messageCondition+=field.value("message_type",iMessageType).get_fieldExpession();
			messageCondition+="message_type= ";
			messageCondition+=" AND ";
		}
		string orderByCondition="ORDER BY ";
		if(11==nSortType)
		{
			orderByCondition+="send_time DESC, message_id DESC)";
		}
		else if(10==nSortType)
		{
			orderByCondition+="send_time, message_id)";
		}
		else if(20==nSortType)
		{
			orderByCondition+="message_type, message_id)";
		}
		else// if(21==nSortType)
		{
			orderByCondition+="message_type DESC, message_id DESC)";
		}
		string unionAllCondition1="";
		unionAllCondition1+=messageCondition;
		unionAllCondition1+="substr(display_flag, 1, 1) = 1 AND sticky_expire_date >= SYSDATE ";
		unionAllCondition1+=orderByCondition;
		string unionAllCondition2="";
		unionAllCondition2+=messageCondition;
		unionAllCondition2+="(substr(display_flag, 1, 1) = 1 AND sticky_expire_date < SYSDATE \
			OR substr(display_flag, 1, 1) = 0) ";
		unionAllCondition2+=orderByCondition;
		string readOrNotCondition="";
		string pagingCondition="";
		if(strBulletinType!="unread_type_id")
		{
			pagingCondition+="SELECT a3.message_id,a3.message_caption,a3.message_content,\
				a3.message_keyword,a3.message_file,a3.message_type,a3.message_level,\
				a3.send_op_id,a3.send_time,a3.valid_date,a3.expire_date,a3.is_draft,\
				a3.display_flag,a3.schedule_flag,a3.message_remark,a3.last_modify_op_id,\
				a3.last_modify_time,a3.modify_times,a3.sticky_expire_date,\
				decode(b3.message_id,NULL,0,1) read_or_not FROM (SELECT * FROM (";
		}
		else
		{
			pagingCondition+="SELECT message_id,message_caption,message_content,\
			message_keyword,message_file,message_type,message_level,send_op_id,send_time,\
			valid_date,expire_date,is_draft,display_flag,schedule_flag,message_remark,\
			last_modify_op_id,last_modify_time,modify_times,sticky_expire_date FROM (";
		}
		pagingCondition+="SELECT rownum row_num, a2.* FROM ( ";
		pagingCondition+=unionAllCondition1;
		pagingCondition+="\nUNION ALL\n";
		pagingCondition+=unionAllCondition2;
		pagingCondition+=") a2\n";
		pagingCondition+="WHERE ";
//		pagingCondition+=field.value("rownum",iPageNum*iPageSize,"<=").get_fieldExpession();
		pagingCondition+="rownum <= ";
		pagingCondition+=") ";
		pagingCondition+=" WHERE ";
//		pagingCondition+=field.value("row_num",(iPageNum-1)*iPageSize+1,">=").get_fieldExpession();
		pagingCondition+="row_num>= ";
		readOrNotCondition+=pagingCondition;
		if(strBulletinType!="unread_type_id")
		{
			readOrNotCondition+=") a3,(SELECT message_id FROM xg.sys_broad_message_log WHERE ";
//			readOrNotCondition+=field.value("read_op_id",iRecvOpId).get_fieldExpession();
			readOrNotCondition+="read_op_id= ";
			readOrNotCondition+=") b3 WHERE a3.message_id = b3.message_id(+)";
		}
		cout << readOrNotCondition << endl;
	}

	static void stringTest2(){
		string strBulletinType="other";//unread_type_id	all_type_id

		int nSortType=100;

		string messageIdCondition="";
		string messageIdCondition1="";
		messageIdCondition1+="SELECT message_id FROM xg.sys_message_receive WHERE ";
		messageIdCondition1+="receive_id= ";
		messageIdCondition1+=" AND ";
		messageIdCondition1+="receive_id_type=0 ";
		messageIdCondition1+="\nUNION\n";
		messageIdCondition1+="SELECT a1.message_id FROM xg.sys_message_receive a1,\
			(SELECT org_id FROM xg.sys_organizations CONNECT BY PRIOR pri_org_id = org_id \
			START WITH org_id IN (SELECT org_id FROM xg.sys_operators WHERE ";
		messageIdCondition1+="op_id= ";
		messageIdCondition1+=")) b1 WHERE a1.receive_id = b1.org_id AND a1.receive_id_type = 1";
		string messageIdCondition2="";
		if("unread_type_id"==strBulletinType)
		{
			messageIdCondition2+="\nMINUS\n";
			messageIdCondition2+="SELECT message_id FROM xg.sys_broad_message_log WHERE ";
			messageIdCondition2+="read_op_id= ";
			messageIdCondition=messageIdCondition1+messageIdCondition2;
		}
		else
		{
			messageIdCondition=messageIdCondition1;
		}
		string messageCondition="";
		messageCondition+="SELECT * FROM (SELECT * FROM xg.sys_broad_message \
			WHERE message_id IN (";
		messageCondition+=messageIdCondition;
		messageCondition+=") AND valid_date <= SYSDATE AND expire_date >= SYSDATE AND is_draft = 0 AND ";
		string searchCondition="";
//		if(strSearchTitle!=""){
			searchCondition="message_caption like %% ";
			messageCondition+=searchCondition;
			messageCondition+=" AND ";
//		}
//		if(strSearchContent!=""){
			searchCondition="message_content like %% ";
			messageCondition+=searchCondition;
			messageCondition+=" AND ";
//		}
		if(strBulletinType!="unread_type_id"&&strBulletinType!="all_type_id")
		{
			messageCondition+="message_type= ";
			messageCondition+=" AND ";
		}
		string orderByCondition="ORDER BY ";
		if(11==nSortType)
		{
			orderByCondition+="send_time DESC, message_id DESC)";
		}
		else if(10==nSortType)
		{
			orderByCondition+="send_time, message_id)";
		}
		else if(20==nSortType)
		{
			orderByCondition+="message_type, message_id)";
		}
		else// if(21==nSortType)
		{
			orderByCondition+="message_type DESC, message_id DESC)";
		}
		string unionAllCondition1="";
		unionAllCondition1+=messageCondition;
		unionAllCondition1+="substr(display_flag, 1, 1) = 1 AND sticky_expire_date >= SYSDATE ";
		unionAllCondition1+=orderByCondition;
		string unionAllCondition2="";
		unionAllCondition2+=messageCondition;
		unionAllCondition2+="(substr(display_flag, 1, 1) = 1 AND sticky_expire_date < SYSDATE \
			OR substr(display_flag, 1, 1) = 0) ";
		unionAllCondition2+=orderByCondition;

		string itemizeCondition="";
		itemizeCondition="SELECT a3.message_id,a3.message_caption,a3.message_content,\
			a3.message_keyword,a3.message_file,a3.message_type,a3.message_level,a3.send_op_id,\
			a3.send_time,a3.valid_date,a3.expire_date,a3.is_draft,a3.display_flag,\
			a3.schedule_flag,a3.message_remark,a3.last_modify_op_id,a3.last_modify_time,\
			a3.modify_times,a3.sticky_expire_date,b3.prev_message_id,b3.next_message_id ";
		itemizeCondition+="FROM xg.sys_broad_message a3,(SELECT a2.message_id,\
			lag(a2.message_id, 1, 0) over(ORDER BY a2.row_num) AS prev_message_id,\
			lead(a2.message_id, 1, 0) over(ORDER BY a2.row_num) AS next_message_id FROM \
			(SELECT rownum row_num, c1.* FROM (";
		itemizeCondition+=unionAllCondition1;
		itemizeCondition+="\nUNION ALL\n";
		itemizeCondition+=unionAllCondition2;
		itemizeCondition+=") c1) a2) b3 WHERE ";
		itemizeCondition+="b3.message_id= ";
		itemizeCondition+=" AND a3.message_id = b3.message_id";
		cout << itemizeCondition << endl;
	}

	static void stringTest3(){
		 string TOTAL_SQL_BACKDAIL= string("insert into kf.stat_aswork_appeal_archive\n") +
													  string("  (STAT_KEY      ,\n") +
													  string("   STAT_YEAR     ,\n") +
													  string("   STAT_MONTH    ,\n") +
													  string("   STAT_DAY      ,\n") +
													  string("   STAT_HOUR     ,\n") +
													  string("   AREA_ID       ,\n") +
													  string("   ACCEPT_TYPE   ,\n") +
													  string("   ACCEPT_FROM   ,\n") +
													  string("   HANDLE_OP     ,\n") +
													  string("   HANDLE_DEPT   ,\n") +
													  string("   APPEAL_TYPE   ,\n") +
													  string("   REASONABLE    ,\n") +
													  string("   APPEAL_COUNT  ,\n") +
													  string("   DISPATCH_COUNT,\n") +
													  string("   DEAL_COUNT    ,\n") +
													  string("   STAT_TIME)     \n") +
													  string("     select  to_char(apply_date, 'yyyymmddhh24') + 1,\n") +
													  string("             to_char(apply_date, 'yyyy'),\n") +
													  string("             to_char(apply_date, 'mm'),\n") +
													  string("             to_char(apply_date, 'dd'),\n") +
													  string("             to_char(apply_date, 'hh24') + 1,\n") +
													  string("             e.cust_area area_id,                               \n") +
													  string("             10 accept_type,                                    \n") +
													  string("             10 accept_from,                                    \n") +
											          string("             e.group_opid_dest handle_op,                       \n") +
											          string("             o.org_id  handle_dept,                              \n") +
													  string("             '000000' appeal_type,                                   \n") +
													  string("             0 reasonable,                                      \n") +
													  string("             count(distinct e.ucid) appeal_count,                             \n") +
													  string("             0 dispatch_count,                                  \n") +
													  string("             0 deal_count,                                      \n") +
													  string("             sysdate                                            \n") +
													  string("     from kf.ivr_backdial_ext e ,xg.sys_operators o             \n") +
													  string("     where e.group_opid_dest = o.op_id                          \n") +
													  string("       and e.trans_status = 1                                   \n") +
													  string("       and e.appeal_support = 2                                 \n") +
													  string("       and e.skill_group_dest in ('9','20','21','22')           \n") +
													  string("       and e.group_opid_dest is not null 			           \n") +
													  string("       and apply_date >=(to_date('##START_KEY##','YYYYMMDDHH24')+1/24)\n") +
													  string("       and apply_date <  to_date('##END_KEY##',	 'YYYYMMDDHH24')\n") +
													  string("                                                                \n") +
													  string("      group by to_char(apply_date, 'yyyymmddhh24') + 1,\n") +
													  string("               to_char(apply_date, 'yyyy'),\n") +
													  string("               to_char(apply_date, 'mm'),\n") +
													  string("               to_char(apply_date, 'dd'),\n") +
													  string("               to_char(apply_date, 'hh24') + 1,\n") +
													  string("               e.cust_area,                                     \n") +
											          string("               e.group_opid_dest,                               \n") +
											          string("               o.org_id                                         \n") +
													  string("                                                                \n") +
													  string("     union all                                                     \n") +
													  string("                                                                \n") +
													  string("     select  to_char(apply_date, 'yyyymmddhh24') + 1,\n") +
													  string("             to_char(apply_date, 'yyyy'),\n") +
													  string("             to_char(apply_date, 'mm'),\n") +
													  string("             to_char(apply_date, 'dd'),\n") +
													  string("             to_char(apply_date, 'hh24') + 1,\n") +
													  string("             f.cust_area area_id,                               \n") +
													  string("             10 accept_type,                                    \n") +
													  string("             10 accept_from,                                    \n") +
											          string("             f.group_opid_dest handle_op,                       \n") +
											          string("             s.org_id handle_dept,     		                   \n") +
													  string("             '000000' appeal_type,                              \n") +
													  string("             0 reasonable,                                      \n") +
													  string("             0 appeal_count,                                    \n") +
													  string("             count(distinct f.ucid) dispatch_count,             \n") +
													  string("             0 deal_count,                               	   \n") +
													  string("             sysdate                                            \n") +
													  string("     from kf.ivr_backdial_ext f,xg.sys_operators s              \n") +
													  string("     where f.group_opid_dest = s.op_id                          \n") +
													  string("       and f.trans_status = 1                                   \n") +
													  string("       and f.appeal_support = 2                                 \n") +
													  string("       and f.book = 2                                          \n") +
													  string("       and f.skill_group_dest in ('9','20','21','22')           \n") +
													  string("       and f.group_opid_dest is not null 			           \n") +
													  string("       and apply_date >=(to_date('##START_KEY##','YYYYMMDDHH24')+1/24)\n") +
													  string("       and apply_date <  to_date('##END_KEY##',	 'YYYYMMDDHH24')\n") +
													  string("      group by to_char(apply_date, 'yyyymmddhh24') + 1,\n") +
													  string("               to_char(apply_date, 'yyyy'),\n") +
													  string("               to_char(apply_date, 'mm'),\n") +
													  string("               to_char(apply_date, 'dd'),\n") +
													  string("               to_char(apply_date, 'hh24') + 1,\n") +
													  string("               f.cust_area,                                     \n") +
											          string("               f.group_opid_dest,                               \n") +
											          string("               s.org_id                                         \n") ;
		 cout << TOTAL_SQL_BACKDAIL << endl;
	}

	static void stringTest4(){
		bool isNeedHour=true;

		string strSqlOper("");
		strSqlOper.append(
									"select count(*) TOTAL_COUNTS ,\
								       		sum(decode(t.result, 1, 1, 0)) SUCC_COUNTS,\
								       		to_number(t.dial_opid ) dial_opid,\
								      		t.status,\
							       			t.result,\
							       			b.login_name "
		);
		strSqlOper.append(" from ivr_backdial_ext         t,\
	       										  xg.sys_operators b \
	       										  ");
		strSqlOper.append(" where  dial_date between to_date('");
//		strSqlOper.append(szTimeStamp);
	    if(isNeedHour)strSqlOper.append("0000','YYYYMMDDHH24MISS') and to_date('");
		else strSqlOper.append("000000','YYYYMMDDHH24MISS') and to_date('");
//	    strSqlOper.append(szTimeStamp);
	    if(isNeedHour)strSqlOper.append("5959','YYYYMMDDHH24MISS') ");
		else strSqlOper.append("235959','YYYYMMDDHH24MISS') ");
		strSqlOper.append(" and status=2 \
	   										and to_number(t.dial_opid ) = b.op_id \ group by (t.result,t.status,t.dial_opid,b.login_name)");
		cout << strSqlOper << endl;
	}

	static void stringTest5(){
		string sql(   string("insert  into stat_center_busi_detail select * from (select \n")+
		 string(" 	to_char(refund_date,'yyyymmddhh24') STAT_KEY,\n")+
		 string(" 	to_char(refund_date,'yyyy') STAT_YEAR,\n")+
  		 string(" 	to_char(refund_date,'mm') STAT_MONTH,\n")+
  		 string(" 	to_char(refund_date,'dd') STAT_DAY,\n")+
  		 string(" 	to_char(refund_date,'hh24') STAT_HOUR,\n")+
		 string(" 	a.phone_id,\n")+
  		 string("  nvl((select distinct t.new_region_name\n")+
  		 string(" 	from  xg.sys_county_map t\n")+
  		 string(" 	where t.new_region_code=a.is_region_code\n")+
  		 string(" 	),' ') is_region_code,\n")+
  		 string("  nvl(a.ticket_nbr,' ') ticket_nbr,\n")+
  		 string(" 	nvl((select decode(b.oper_mode, 0, '梦网', '自有')\n")+
  		 string(" 	from cp.pm_sp_info@dbsale b\n")+
  		 string(" 	where to_char(b.sp_code)=a.sp_code\n")+
  		 string(" 	and to_char(sysdate, 'yyyymmdd') between b.valid_date and\n")+
  		 string(" 	 b.expire_date\n")+
  		 string(" 	 and rownum <= 1),'　')  busi_flag,\n")+
  		 string(" 	 nvl((select op_id\n")+
  		 string(" 	 from xg.sys_operators@dbsale c where op_id = a.op_id and rownum <= 1),0) op_id,\n")+
  		 string(" 	 nvl((select login_name from xg.sys_operators@dbsale c  where op_id = a.op_id and rownum <= 1),' ') login_name,\n")+
  		 string(" 	 (decode(a.refund_from, 4, '投诉', 5, '抱怨')) refund_from,\n")+
  		 string(" 	 nvl((select f.busi_name from cp.pm_sp_operator_code@dbsale b, zk.cm_radius_gui_rule@dbsale  c, cp.pm_busi_type_def@dbsale    f  where b.sp_type = c.serv_type and c.busi_type = f.busi_type  and to_char(b.sp_code) = a.sp_code  and b.operator_code = a.operator_code and sysdate between b.valid_date and b.expire_date and rownum <= 1),'  ') busi_name,\n")+
  		 string(" 	 nvl(decode(a.dr_type,420, null, (select sp_name from cp.pm_sp_info@dbsale b where to_char(sp_code) = a.sp_code  and to_char(sysdate, 'yyyymmdd') between b.valid_date and b.expire_date and rownum <= 1)), '　') sp_name,\n")+
		 string(" 	 nvl(a.service_code,'  ') service_code,\n")+
		 string(" 	 nvl(decode(a.times_type,1,'一倍',2,'双倍',to_char(a.times_type)),' ') times_type,\n")+
		 string(" 	 nvl(decode(a.dr_type, 420, null, a.sp_code),' ') sp_code,\n")+
		 string(" 	 nvl((select decode(b.bill_flag, 2, '点播', 3, '包月') from cp.pm_sp_operator_code@dbsale b where to_char(b.sp_code) = a.sp_code and b.operator_code = a.operator_code and sysdate between b.valid_date and b.expire_date and rownum <= 1), '　') bill_flag,\n")+
		 string("   nvl(decode(a.dr_type, 420,'通信费',(select b.operator_name  from cp.pm_sp_operator_code@dbsale b where to_char(b.sp_code) = a.sp_code  and b.operator_code = a.operator_code and sysdate between b.valid_date and b.expire_date and rownum <= 1)), '　') operator_name,	\n")+
		 string(" 	 nvl((select b.operator_code from cp.pm_sp_operator_code@dbsale b where sp_code = TO_NUMBER(trim(a.sp_code)) and b.operator_code = a.operator_code and sysdate between b.valid_date and b.expire_date and rownum <= 1),'  ')operator_code,\n")+
		 string(" 	 to_char(a.start_time, 'yyyy-mm-dd hh24:mi:ss') start_time,\n")+
		 string(" 	 to_char(a.refund_date, 'yyyy-mm-dd hh24:mi:ss') refund_date,\n")+
		 string(" 	 nvl(to_char(a.so_nbr),' ') so_nbr,\n")+
		 string(" 	to_char(decode(a.times_type,0,a.amount / 100,a.amount * a.times_type / 100)) amount,\n")+
		 string(" 	decode(a.refund_type,1,'先退费，后查证',2,'不知情定制',3,'业务使用异常',4,'二次放号',5,'取消后仍产生扣费',6,'满意度退费') refund_type,\n")+
		 string(" 	a.rec_nbr ,\n")+
		 string(" 	'' phone_no\n")+
		 string(" 	from zg.acc_sp_refund@dbacct a\n")+
		 string(" 	where a.refund_from in (4, 5)\n")+
		 string(" 	and a.rec_sts = 0\n")+
		 string(" 	and a.refund_date >= (to_date('##START_KEY##','YYYYMMDDHH24')+1/24)\n")+
		 string(" 	and a.refund_date <= to_date('##END_KEY##','YYYYMMDDHH24')\n")+
		 string(" 	)\n")
			);
		cout << sql << endl;
	}

	static void stringTest6(){
		string szSubTableExt="aaaaaaaaaaa";

		string strSqlOper("select d.op_id, e.org_id, c.operation_code, c.operation_type, c.area_id region_code, count(*) oper_count ");
		strSqlOper.append(" from kf.ivr_log_busi_accept");
		strSqlOper.append(szSubTableExt);
		strSqlOper.append(" c, ");
		strSqlOper.append(" kf.cps_log_manualcall");
		strSqlOper.append(szSubTableExt);
		strSqlOper.append(" g, ");
	    strSqlOper.append("      (select max(rowid),uc_id,op_id from kf.agent_wizard");
	    strSqlOper.append(szSubTableExt);
	    strSqlOper.append(" group by uc_id,op_id) d, ");
	    strSqlOper.append("       xg.sys_operators e");

		strSqlOper.append(" where c.begin_time >=");
	    strSqlOper.append("to_date('");
//	    strSqlOper.append(szTimeStamp);
	    strSqlOper.append("0000','YYYYMMDDHH24MISS') and c.begin_time <= to_date('");
//	    strSqlOper.append(szTimeStamp);
	    strSqlOper.append("5959','YYYYMMDDHH24MISS')");

		//strSqlOper.append(szPartitionCond);
		///////////////////////////////
		strSqlOper.append("     and c.ucid=d.uc_id and d.op_id=e.op_id ");
		strSqlOper.append("     and c.ucid=g.ucid ");
	    strSqlOper.append("     and g.tel_called like '1008666%' ");
	    strSqlOper.append("     and c.part_id=");
//	    strSqlOper.append(szPartitionCond);
	    strSqlOper.append("     and g.part_id=");
//	    strSqlOper.append(szPartitionCond);
	    strSqlOper.append("     and c.flag='0' ");
	    strSqlOper.append("     and c.called='1601' ");
	    strSqlOper.append(" group by d.op_id,e.org_id,c.operation_code,c.operation_type,c.area_id ");
		/////////////////////////////////

	    strSqlOper.append(" \n union all \n");

		strSqlOper.append("select a.OP_ID, b.org_id, TO_CHAR(f.cmd_id) operation_code, a.BUSI_TYPE operation_type, TO_CHAR(a.region_code) region_code, count(*) oper_count");
		strSqlOper.append(" from kf.IVR_TO_SMS_BOSS a,XG.SYS_CMD_DEF f,xg.sys_operators b");

		strSqlOper.append(" where a.accept_date >= ");
	    strSqlOper.append("to_date('");
//	    strSqlOper.append(szTimeStamp);
	    strSqlOper.append("0000','YYYYMMDDHH24MISS') and a.accept_date <= to_date('");
//	    strSqlOper.append(szTimeStamp);
	    strSqlOper.append("5959','YYYYMMDDHH24MISS')");

		///////////////////////////////
		strSqlOper.append("     and a.op_id=b.op_id ");
		strSqlOper.append("     and (f.region_code = '999' or f.region_code=a.region_code) ");
		strSqlOper.append("     and f.cmd_str = a.cmd_str ");
		strSqlOper.append("     and a.op_id <> 0 and a.src_type=2 ");
		strSqlOper.append("     and (a.result_type = 1 or a.result_type = 2) ");
		strSqlOper.append(" group by a.op_id,b.org_id,f.cmd_id,a.busi_type,a.region_code ");
		cout << strSqlOper << endl;
	}

	static void stringTest7(){
		 string TOTAL_SQL= string("insert into kf.STAT_OFFLINE_RECALL ") +
				 string("(STAT_KEY,STAT_YEAR,STAT_MONTH,STAT_DAY,STAT_HOUR,\n") +
				 string("ORG_ID,OP_ID,SKILL_ID,COUNT_WAIT,STAT_TIME) \n") +
				 string("   select to_char(TIME_CALLBACK, 'yyyymmddhh24') + 1,to_char(TIME_CALLBACK, 'yyyy'),to_char(TIME_CALLBACK, 'mm'),to_char(TIME_CALLBACK, 'dd'),to_char(TIME_CALLBACK, 'hh24') + 1,\n") +
				 string("b.org_id,a.op_id,a.skill_id,count(*) count_wait,sysdate \n") +
				 string("   from kf.IVR_OFFLINE_QUEUE_##TOTAL_MONTH## a,xg.sys_operators b  where a.op_id=b.op_id and a.status=3 and \n") +
				 string(" TIME_CALLBACK >=(to_date('##START_KEY##','YYYYMMDDHH24')+1/24) and  TIME_CALLBACK <  to_date('##END_KEY##','YYYYMMDDHH24')\n") +
				 string(" group by to_char(TIME_CALLBACK, 'yyyymmddhh24') + 1,to_char(TIME_CALLBACK, 'yyyy'),to_char(TIME_CALLBACK, 'mm'),to_char(TIME_CALLBACK, 'dd'),to_char(TIME_CALLBACK, 'hh24') + 1,\n") +
				 string("b.org_id,a.op_id,a.skill_id");
		 cout << TOTAL_SQL << endl;
	}

	static void stringTest8(){
		 string TOTAL_SQL =  string("insert into TOTAL_TABLE_NAME") +
			 string("(seqid, refund_date, op_id, op_name, phone_id, brand_code, brand_name, is_region_code, region_name, is_county_code, total_fee, \n") +
			 string("	 rec_type, rec_name, dr_type, dr_name, so_nbr, refund_type, refund_name, times_type, start_time, cdr_fee,  \n") +
			 string("	 sp_name, sp_code, operator_name, operator_code, service_code, remarks) \n") +
			 string(" select kf.seq_stat_sp_refund.nextval, refund_date, o.op_id, o.op_name op_name, to_char(phone_id), brand, p.brand_name, is_region_code, region_name, is_county_code, total_fee, \n") +
			 string("   		rec_type, t1.cname rec_name, dr_type, t2.cname dr_name, to_char(so_nbr), refund_type, t3.cname refund_name, times_type, to_char(start_time, 'yyyy-mm'), cdr_fee, \n") +
			 string("   		to_char(sp_name), to_char(sp_code), to_char(operator_name), to_char(operator_code), to_char(service_code), to_char(remarks) \n") +
			 string(" from (\n") +
			 string("		select a.refund_date, b.op_id, a.phone_id, e.brand, a.is_region_code, f.new_region_name region_name, a.is_county_code, a.cdr_fee * a.times_type total_fee, \n") +
			 string("	 		a.rec_type, a.dr_type, a.so_nbr, a.refund_type, a.times_type, a.start_time, a.cdr_fee, \n") +
			 string("      	c.sp_name, a.sp_code, d.operator_name, a.operator_code, a.service_code, a.remarks \n") +
			 string("      from zg.acc_sp_refund@ZG_DBLINK") +
			 string(" a, zg.acc_busi_rec_0FEE_CODEYearMonth@ZG_DBLINK") +
			 string(" b, \n") +
			// string("      	jf.ismg_sp_info@") + JF_DBLINK +
			// string(" c, jf.ismg_rate@") + JF_DBLINK +
			 string("      	bd.RS_SP_INFO@ZG_DBLINK") +
			 string(" c, bd.RS_ISMG_RATE@ZG_DBLINK") +
			 string(" d, zk.cm_user@ZK_DBLINK") +
			 string(" e, xg.sys_county_map f \n") +
			 string("      where a.so_nbr = b.so_nbr  and a.sp_code = c.sp_code   \n") +
			 string("      and a.operator_code = d.operator_code and a.phone_id = e.phone_id \n") +
			 string("      and a.is_county_code = f.county_code and f.old_region_code = ") +
			 string("      and a.refund_date between to_date('") +
			 string("0000', 'YYYYMMDDHH24MISS') and to_date('") +
			 string("5959', 'YYYYMMDDHH24MISS') \n") +
			 string("      group by a.refund_date, b.op_id, a.phone_id, e.brand, a.is_region_code, f.new_region_name, a.is_county_code,  \n") +
			 string("      	a.rec_type, a.dr_type, a.so_nbr, a.refund_type, a.times_type, a.start_time, a.cdr_fee,  \n") +
			 string("      	c.sp_name, a.sp_code, d.operator_name, a.operator_code, a.service_code, a.remarks \n") +
			 string("      order by a.refund_date  \n") +
			 string(" ) r, xg.sys_operators o, cp.pm_brands p, \n") +
			 string("(select * from xg.sys_base_type where enum_name = 'CDR_TABLE@DR_TYPE') t1, \n") +
			 string("(select * from xg.sys_base_type where enum_name = 'STAT_5054_SP_REFUND@DR_TYPE') t2,  \n") +
			 string("(select * from xg.sys_base_type where enum_name = 'ACC_SP_REFUND@REFUND_TYPE') t3 \n") +
			 string("where r.op_id = o.op_id and r.brand = p.brand_id and r.rec_type = t1.code_value \n") +
			 string("	and r.dr_type = t2.code_value and r.refund_type = t3.code_value  \n");

		cout << TOTAL_SQL << endl;
	}

	static void stringstreamTest2(){
		stringstream ss;
		ss << "select "
						<< " a.* "
						<< " from " << "aaaaaaaaa" << "." << "bbbbbbbbbbb" << " a, "
						<< "("
						<< "select t2.id_rept, t2.priv_type from (select role_id from xg.sys_op_role where op_id = ) t1, "
								<< "aaaaaaaaa" << ".ss_perm_rept_role t2 where t1.role_id = t2.role_id"
						<< " union "
						<< "select id_rept, priv_type from ss_perm_rept_op where perm_cls = 1"
						<< " union "
						<< "select id_rept, priv_type from ss_perm_rept_op where perm_cls = 2 and sysdate >= effect_time and sysdate <= expire_time"
						<< " minus "
						<< "select id_rept, priv_type from ss_perm_rept_op where perm_cls = 0"
						<< ") b where a.id_rept = b.id_rept and a.is_visi = 1 order by a.id_catg, a.ordi_no";

		cout << ss.str() << endl;
	}

	static void stringstreamTest1(){
		string strBulletinType="other";//all_type_id	unread_type_id

		stringstream ss;
		  ss<<"SELECT COUNT(*) message_count\n";
		  ss<<"FROM xg.sys_broad_message\n";
			ss<<"WHERE message_id IN ";
			ss<<"(SELECT message_id\n";
			ss<<"FROM xg.sys_message_receive\n";
			ss<<"WHERE ""receive_id= "<<" AND "<<"receive_id_type=0"<<"\n";
			ss<<"UNION\n";
			ss<<"SELECT a1.message_id message_id\n";
			ss<<"FROM xg.sys_message_receive a1,";
			ss<<"(SELECT org_id FROM xg.sys_organizations CONNECT BY PRIOR pri_org_id = org_id START WITH org_id IN ";
			ss<<"(SELECT org_id FROM xg.sys_operators WHERE "<<"op_id= "")) b1\n";
			ss<<"WHERE a1.receive_id = b1.org_id AND "<<"a1.receive_id_type=1 ";
			if("unread_type_id"==strBulletinType) // 未读公告拼接部分
			{
				ss<<"\n";
				ss<<"MINUS\n";
				ss<<"SELECT message_id\n";
				ss<<"FROM xg.sys_broad_message_log\n";
				ss<<"WHERE "<<"read_op_id= "")\n";
			}
			else if("all_type_id"==strBulletinType) // 所有公告分页拼接部分
			{
				ss<<")\n";
			}
			else // 类型公告分页拼接部分
			{
				ss<<")\n";
				ss<<"AND "<<"message_type= ";
			}
			ss<<"AND valid_date <= SYSDATE\n";
			ss<<"AND expire_date >= SYSDATE\n";
//			if(strSearchTitle!=""){
				ss<<"AND "<<"message_caption like %% ";
//			}
//			if(strSearchContent!=""){
				ss<<"AND "<<"message_content like %%";
//			}
		cout << ss.str() << endl;
	}

	static void strFunTest_strcat1(){
		char szTmp[8192] = { 0 };
		char strSMSContent[16384] = "\0";
		int * p=NULL;
		char * c='\0';//NULL;
		strcat(strSMSContent, "\0");
//		strcat(szTmp, c);//c=NULL或0不会运行下去
		cout << "szTmp:" << szTmp << endl;
		cout << "p:" << p<< endl;
		cout << "c:" << c << endl;
	}

	static void strcmptest1(){
		char c1[1];
		memset(c1, 0x00, sizeof(c1));
		strcpy(c1, "1");
		int i=strcmp((char *)c1, "1");
		int i2=strcmp(c1, "1");
		cout << i << endl;
		cout << i2 << endl;
		bool b1=strcmp(c1, "1")==0;
		cout << b1 << endl;
		bool b2=strcmp((char *)c1, "1")==1;
		cout << b2 << endl;
	}

	static void itoaTest1(){
		int num = 100;
		char str[25];
		itoa(num, str, 10);
		printf("The number 'num' is %d and the string 'str' is %s. \n" ,
		num, str);
	}

	static void CommonUtilTest1(){
		char filePath[256]="C:\\Users\\chency\\Desktop\\OUT20170908061035TS2017090851028050451090.xml";

//		char file[64 * 1024 + 100];
//		memset( file, 0x00, sizeof(file) );
//		CommonUtil::readFile(file, filePath);
		char* file=CommonUtil::readFile(filePath);

//		cout << strlen(file) << endl;
		cout << file << endl;
	}

	static void ParseNode(char *source, const char *Node, const char *eNode, char *resultstr) {
		char *pstart;
		char *pend;
		pstart = strstr(source, Node);
		pend = strstr(source, eNode);
		if (pstart)
			pstart = pstart + strlen(Node);
		//if(pend){
		if (pend && pstart) {
			for (; pstart < pend; pstart++) {
				*resultstr = *pstart;
				if (resultstr != NULL)
					resultstr++;
				else
					break;
			}
		}
		if (resultstr != NULL)
			*resultstr = '\0';
	}

	static void AItest1(){
		char filePath[256]="C:\\Users\\chency\\Desktop\\OUT20170908061035TS2017090851028050451090.xml";

//		char file[64 * 1024 + 100];
//		memset( file, 0x00, sizeof(file) );
//		CommonUtil::readFile(file, filePath);
		char* file=CommonUtil::readFile(filePath);

//		cout << strlen(file) << endl;
		cout << file << endl;
		char AppealID[256];
		char AppealResult[64 * 1024 + 100];
		memset( AppealID, 0x00, sizeof(AppealID) );
		memset( AppealResult, 0x00, sizeof(AppealResult) );
		ParseNode((char*)file,"<appealid>","</appealid>",(char*)AppealID);
		cout << AppealID << endl;
//		printf("%s", AppealID);
		ParseNode((char*)file,"<result>","</result>",(char*)AppealResult);
		cout << AppealID << endl;
		cout << AppealResult << endl;
	}
};


CRectangle duplicate(CRectangle rectparam) {
	CRectangle rectres;
	rectres.x = rectparam.x * 2;
	rectres.y = rectparam.y * 2;
	return (rectres);
}

void printmovie(movies_t movie) {
	cout << movie.title;
	cout << " (" << movie.year << ")\n";
}

int operation (int x, int y, int (*functocall)(int,int)) {
    int g;
    g = (*functocall)(x,y);
    return (g);
}

int addition (int a, int b) {
    return (a+b);
}

void increase(void* data, int type) {
	switch (type) {
	case sizeof(char):
		(*((char*) data))++;//先类型转换再取值操作
		break;
	case sizeof(short):
		(*((short*) data))++;
		break;
	case sizeof(long):
		(*((long*) data))++;
		break;
	}
}

void setstring(char szOut[], char szIn[]) {
	int n = 0;
	do {
		szOut[n] = szIn[n];
	} while (szIn[n++] != '\0');
}

int divide(int a, int b = 2) {
	int r;
	r = a / b;
	return (r);
}

void prevnext(int x, int& prev, int& next) {
	prev = x - 1;
	next = x + 1;
}

void duplicate(int& a, int& b, int& c) {
	a *= 2;
	b *= 2;
	c *= 2;
}

void input_data()
{
	int i;
	for (i = 0; i < n; i++) {
		cout << "input name and NO. of student " << i + 1 << "："; //输入提示
		cin >> name[i] >> num[i];//输入n个学生的姓名和学号
	}
}

void search(string find_name)
{
	int i;
	bool flag = false;
	for (i = 0; i < n; i++){
		if (name[i] == find_name) //如果要找的姓名与本班某一学生姓名相同
		{
			cout << name[i] << " has been found, his number is " << num[i] << endl; //输出姓名与学号
			flag = true;
			break;
		}
	}
	if (flag == false)
		cout << "can′t find this name"; //如找不到,输出“找不到”的信息
}

inline int isnumber(char ch){
	return (ch>'0' && ch <='9')?1:0;
}

inline int max(int a, int b, int c) //定义max为内置函数
{
	if (b > a)
		a = b; //求a,b,c中的最大者
	if (c > a)
		a = c;
	return a;
}

//求a,b,c中的最大者
int max2(int a, int b, int c){
	if (b > a)
		a = b;
	if (c > a)
		a = c;
	return a;
}

double max2(double a, double b, double c)
//定义求3个双精度数中的最大者的函数
{
	if (b > a)
		a = b;
	if (c > a)
		a = c;
	return a;
}

long max2(long a, long b, long c)
//定义求3个长整数中的最大者的函数
{
	if (b > a)
		a = b;
	if (c > a)
		a = c;
	return a;
}

int max(int a, int b){
	int c;
	if(a>b){
		c=a;
	}else{
		c=b;
	}
	return (c);
}

int max2(int a, int b){
	int c;
	if(a>b){
		c=a;
	}else{
		c=b;
	}
	return (c);
}

//求a,b,c中的最大者
int max4(int a, int b, int c) {
	if (b > a)
		a = b;
	if (c > a)
		a = c;
	return a;
}

float add(float x, float y) //定义add函数
{
	float z;
	z = x + y;
	return (z);
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

//	int max(int x, int y);
//	int a, b, m;
//	cin >> a >> b;
//	m = max(a, b);
//	cout<<"max="<<m<<'\n';

////	int max(int, int);
//	int a, b, c;
//	cin >> a >> b;
//	c = max(a, b);
//	cout << "max=" << c << endl;

	//控制浮点数值显示
//	double amount = 22.0 / 7;
//	cout << amount << endl;
//	cout << setprecision(0) << amount << endl
//			<< setprecision(1) << amount << endl
//			<< setprecision(2) << amount << endl
//			<< setprecision(3) << amount << endl
//			<< setprecision(4) << amount << endl;
//	cout << setiosflags(ios::fixed);
//	cout << setprecision(8) << amount << endl;
//	cout << setiosflags(ios::scientific) << amount << endl;
//	cout << setprecision(6); //重新设置成原默认设置

	//输出8进制和16进制数
//	int number=1001;
//	cout << "Decimal(10进制):" << dec << number << endl
//			<< "Hexadecimal(16进制):" << hex << number << endl
//			<< "Octal(8进制):" << oct << number << endl;

	//使用填充字符
//	cout << setfill('*')
//			<< setw(2) << 21 << endl
//			<< setw(3) << 21 << endl
//			<< setw(4) << 21 << endl
//			<< setw(5) << 21 << endl
//			<< setw(9) << 21 << endl;
//	cout << setfill(' ');  // 恢复默认设置

	//左右对齐输出
//	cout << /*setiosflags(ios::right) <<*/ setw(5) << 1 << setw(5) << 2 << setw(5) << 3 << endl;
//	cout << setiosflags(ios::left) << setw(5) << 1 << setw(5) << 2 << setw(5) << 3 << endl;

	//强制显示小数点和符号位
////	cout << 10.0 / 5 << endl;
////	cout << setiosflags(ios::showpoint) << 10.0 / 5 << endl;
//
////	cout << 10 << "  " << -20 << endl;
////	cout << setiosflags(ios::showpos) << 10 << "  " << -20 << endl;
//
//	double a = 123.456, b = 3.14159, c = -3214.67;
//	cout << setiosflags(ios::fixed) << setiosflags(ios::right) << setprecision(2);
//	cout << setw(10) << a << endl;
//	cout << setw(10) << b << endl;
//	cout << setw(10) << c << endl;

	//putchar函数getchar函数
////	char a, b, c;
////	a = 'B';
////	b = 'O';
////	c = 'Y';
////	putchar(a);
////	putchar(b);
////	putchar(c);
////	putchar('\n');
////	putchar(66);
////	putchar(79);
////	putchar(89);
////	putchar(10);
//
//	char c;
//	c = getchar();
//	putchar(c + 32);
//	putchar('\n');

	//scanf和printf函数
////	int a;
////	float b;
////	char c;
////	scanf("%d %c %f", &a, &c, &b); //注意在变量名前要加地址运算符&
////	printf("a=%d,b=%f,c=%c\n", a, b, c);
//
////	int a = 10, b = 20;
////	printf("%d, %d", a, b);
//////	system("pause");
//
////	unsigned int a=65533;
////	int b=-2;
////	printf("a=%d,%o,%x,%u,%7u\n", a,a,a,a,a);
////	printf("b=%d,%o,%x,%u,%6u\n", b,b,b,b,b);
//
////	float x=123.456;
////	double y=321.654321;
////	/*long */double z=3.141592653;
////	printf("%f,%-7.2f,%10.4f\n", x,x,x);
////	printf("%lf,%-7.2lf,%10.4lf\n", y,y,y);
////	printf("%Lf,%-7.2Lf,%10.4Lf,%14.10Lf\n", z,z,z,z);
//
////	int a,b;
////	char ch1,ch2;
////	float f,g;
//////	scanf("%d %d", &a,&b);
//////	scanf("%c%c", &ch1,&ch2);
////	scanf("%f,%f", &f,&g);
////	printf("%f,%f", f,g);
//
//	char BillId[12];
//	scanf("%s", &BillId);
//	printf("%s", BillId);

	//函数
//	float add(float x, float y); //对add函数作声明
//	float a, b, c;
//	cout << "please enter a,b:";
//	cin >> a >> b;
//	c = add(a, b); //函数调用
//	cout << "sum=" << c << endl;
	//内联函数
////	int i = 10, j = 20, k = 30, m;
////	m = max(i, j, k);
////	cout << "max=" << m << endl;
//	char c;
//	while((c=cin.get())!='\n'){//接收键盘输入
//		if(isnumber(c)){
//			cout << "you entered a digit\n";
//		}else{
//			cout << "you entered a non-digit\n";
//		}
//	}
	//函数的重载
////	int max2(int a, int b, int c); //函数声明
////	double max2(double a, double b, double c);//函数声明
////	long max2(long a, long b, long c); //函数声明
////	int i1, i2, i3, i;
////	cin >> i1 >> i2 >> i3; //输入3个整数
////	i = max2(i1, i2, i3); //求3个整数中的最大者
////	cout << "i_max=" << i << endl;
////	double d1, d2, d3, d;
////	cin >> d1 >> d2 >> d3; //输入3个双精度数
////	d = max2(d1, d2, d3); //求3个双精度数中的最大者
////	cout << "d_max=" << d << endl;
////	long g1, g2, g3, g;
////	cin >> g1 >> g2 >> g3; //输入3个长整数
////	g = max2(g1, g2, g3); //求3个长整数中的最大者
////	cout << "g_max=" << g << endl;
//	int max2(int a, int b, int c); //函数声明
//	int max2(int a, int b); //函数声明
//	int a = 8, b = -12, c = 27;
//	cout << "max(a,b,c)=" << max2(a, b, c) << endl;
//	//输出3个整数中的最大者
//	cout << "max(a,b)=" << max2(a, b) << endl;
//	//输出两个整数中的最大者
	//默认参数的函数
//////	int max2(int a, int b, int c = 0);//函数声明,形参c有默认值
//////	int a, b, c;
//////	cin >> a >> b >> c;
//////	cout << "max(a,b,c)=" << max2(a, b, c) << endl;
//////	//输出3个数中的最大者
//////	cout << "max(a,b)=" << max2(a, b) << endl;
//////	//输出2个数中的最大者
////	int max4(int a, int b, int c=3);
////	cout << "max(a,b,c)=" << max4(1, 2) << endl;
////	cout << "max(a,b,c)=" << max4(1, 2, 0) << endl;
//	int divide(int a, int b = 2);
//	cout << divide (12);
//	cout << endl;
//	cout << divide (20,4);
	//按地址传递
////	void duplicate(int& a, int& b, int& c);
////	int x = 1, y = 3, z = 7;
////	duplicate(x, y, z);
////	cout << "x=" << x << ", y=" << y << ", z=" << z;
//	void prevnext(int x, int& prev, int& next);
//	int x = 100, y, z;
//	prevnext(x, y, z);
//	cout << "Previous=" << y << ", Next=" << z;

	//变量作用域
//	int a=1;//局部变量
//	::a=2;//全局变量
//	cout << ::a << endl;
//	cout << a << endl;

	//变量初始化
////	int a=1;
////	int b(2);//等同于int b=2;
////	cout << a+b << endl;
//	string str1 ("str1");
//	string str2="str2";
//	cout << str1+str2 << endl;

	//常量
////	#define PI 3.14159265
////	#define NEWLINE '\n'
////	#define WIDTH 100
////	cout << PI << NEWLINE << WIDTH << endl;
//	const int width = 100;
//	const char tab = '\t';
//	cout << width << tab << endl;

	//字符串
	//字符串运算
//////////	string string1, string2, string3, temp;
//////////	cout << "please input three strings：";
//////////	//这是对用户输入的提示
//////////	cin >> string1 >> string2 >> string3;
//////////	//输入3个字符串
//////////	if (string2 > string3) {
//////////		temp = string2;
//////////		string2 = string3;
//////////		string3 = temp;
//////////	}
//////////	//使串2≤串3
//////////	if (string1 <= string2){//如果串1≤串2,则串1≤串2≤串3
//////////		cout << string1 << " " << string2 << " " << string3 << endl;
//////////	}else if (string1 <= string3){//如果串1＞串2,且串1≤串3,则串2＜串1≤串3
//////////		cout << string2 << " " << string1 << " " << string3 << endl;
//////////	}else{//如果串1＞串2,且串1＞串3,则串2＜串3＜串1
//////////		cout << string2 << " " << string3 << " " << string1 << endl;
//////////	}
//////////	string str1="abcdef", str2="DEF";
////////	string str1="abcdef", str2="def";
////////	if(str1>str2){
////////		cout << "str1>" << endl;
////////	}else{
////////		cout << "str2>" << endl;
////////	}
//////	void input_data(); //函数声明
//////	void search(string find_name); //函数声明
//////	string find_name; //定义字符串变量’find_name是要找的学生
//////	cout << "please input number of this class：";//输入提示:请输入本班学生的人数
//////	cin >> n; //输入学生数
//////	input_data();//调用input_data函数,输入学生数据
//////	cout << "please input name you want find：";//输入提示: 请输入你要找的学生名
//////	cin >> find_name; //输入要找的学生的姓名
//////	search(find_name); //调用search函数,寻找该学生姓名
////	string st;
////	char f[256];
////	sprintf(f, "%s", "212030501001");
////	st.append(f).append(",").append(f);
////	cout << st << endl;
//	string str;
//	for(int i=0;i<3;i++){
//		string str2="adad";
//		if(strlen(str.c_str())>0){
//			str.append(",").append(str2);
//		}else{
//			str.append(str2);
//		}
//	}
//	cout << str;

	// 字符串流的使用示例
////	string mystr;
////	float price = 0;
////	int quantity = 0;
////	cout << "Enter price: ";
////	getline(cin, mystr);
////	stringstream(mystr) >> price;
////	cout << "Enter quantity: ";
////	getline(cin, mystr);
////	stringstream(mystr) >> quantity;
////	cout << "Total price: " << price * quantity << endl;
//	long offerId=212030501001;
//	stringstream ss1;
//	char b[256];
//	sprintf(b, "%lld", offerId);
//	ss1<<string(b);
//	ss1<<","<<offerId;
//	ss1<<","<<offerId;
//	cout << ss1.str() << endl;//output:1577103497
//	string str;
//	stringstream ss2;
//	ss2<<offerId;
//	ss2>>str;
//	cout << str << endl;
	//字符串和其它数据类型的转换
//	char mybuffer [100];
//	float price;
//	int quantity;
//	cout << "Enter price: ";
//	cin.getline (mybuffer,100);
//	price = atof (mybuffer);//将字符串string 转换为浮点型float
//	cout << "Enter quantity: ";
//	cin.getline (mybuffer,100);
//	quantity = atoi (mybuffer);//将字符串string 转换为整型int
//	cout << "Total price: " << price*quantity;
	//char*转string
//	char* c="abc";
////	string s(c);
//	string s=c;
//	cout << s << endl;
	//char*转char[]
//	char* c="abcd";
//	char log[10]={"0"};
//	strcpy(log, c);
//	cout << log;
	//字符串操作函数
	/*
	 * strcat: char* strcat (char* dest, const char* src); //将字符串src 附加到字符串dest 的末尾，返回dest
	 * strcmp: int strcmp (const char* string1, const char* string2); //比较两个字符串string1 和string2。如果两个字符串相等，返回0
	 * strcpy: char* strcpy (char* dest, const char* src); //将字符串src 的内容拷贝给dest，返回dest
	 * strlen: size_t strlen (const char* string); //返回字符串的长度
	 */

	//数组
	//字符序列 （Character Sequences）
////	char szMyName [20];
//////	strcpy (szMyName,"J. Soulie");
////	void setstring(char szOut[], char szIn[]);
////	setstring(szMyName,"J. Soulie");
////	cout << szMyName;
//	char mybuffer [100];
//	cout << "What's your name? ";
//	cin.getline (mybuffer,100);
//	cout << "Hello " << mybuffer << ".\n";
//	cout << "Which is your favourite team? ";
//	cin.getline (mybuffer,100);
//	cout << "I like " << mybuffer << " too.\n";

	//指针
////////////	int value1 = 5, value2 = 15;
////////////	int * mypointer;
////////////	mypointer = &value1;
////////////	*mypointer = 10;
////////////	mypointer = &value2;
////////////	*mypointer = 20;
////////////	cout << "value1=" << value1 << " / value2=" << value2;
//////////	int value1 = 5, value2 = 15;
//////////	int *p1, *p2;
//////////	p1 = &value1; // p1 = address of value1
//////////	p2 = &value2; // p2 = address of value2
//////////	*p1 = 10; // value pointed by p1 = 10
//////////	*p2 = *p1; // value pointed by p2 = value pointed by p1
//////////	p1 = p2; // p1 = p2 (value of pointer copied)。p1指向了value2
//////////	*p1 = 20; // value pointed by p1 = 20。改变value2值
//////////	cout << "value1=" << value1 << " / value2=" << value2;
////////	int numbers[5];
////////	int * p;
////////	p = numbers;//numbers[0]
////////	*p = 10;
////////	p++;//numbers[1]
////////	*p = 20;
////////	p = &numbers[2];//numbers[2]
////////	*p = 30;
////////	p = numbers + 3;//numbers[3]
////////	*p = 40;
////////	p = numbers;
////////	*(p+4) = 50;//numbers[4]
////////	for (int n=0; n<5; n++){
////////		cout << numbers[n] << " ";
////////	}
//////	//空指针void pointers
//////	void increase(void* data, int type);
//////	char a = 5;
//////	short b = 9;
//////	long c = 12;
//////	increase (&a,sizeof(a));
//////	increase (&b,sizeof(b));
//////	increase (&c,sizeof(c));
//////	cout << (int) a << ", " << b << ", " << c;
////	//函数指针Pointers to functions
////	int addition (int a, int b);
////	int operation (int x, int y, int (*functocall)(int,int));
////	int m, n;
////	m = operation(7, 5, addition);
//////	n = operation(20, m, minus);
////	n = operation(20, m, subtraction);
////	cout << n << endl;
//	//动态分配/撤销内存的运算符new和delete
//////	Student2 *p;
//////	p = new Student2;
//////	strcpy(p->name, "Wang Fun");
//////	p->num = 10123;
//////	p->sex = 'M';
//////	cout << p->name << "  " << p->num << "  " << p->sex << endl;
//////	delete p;
////	//逗号运算符 ,
////	int a=9,b(0);
////	b=(a++,b+a);//这行代码首先a++，然后将 b+a赋值给变量b,最后变量b的值为10。
////	cout << b << endl;
//	char input[100];
//	int i, n;
//	long * l;
//	cout << "How many numbers do you want to type in? ";
//	cin.getline(input, 100);
//	i = atoi(input);
//	l = new long[i];
//	if (l == NULL)
//		exit(1);
//	for (n = 0; n < i; n++) {
//		cout << "Enter number: ";
//		cin.getline(input, 100);
//		l[n] = atol(input);
////		cout << l[n] << endl;
//	}
////	cout << n << endl;
//	cout << "You have entered: ";
//	for (n = 0; n < i; n++) {
//		cout << l[n] << " ";
////		delete[] l;//放这里输出有问题
//	}
//	delete[] l;
////	cout << endl << n;
//	/*
//	 * C:函数 free用来释放malloc, calloc 或realloc所分配的内存块。
//	 */

	//结构 struct
//////	void printmovie(movies_t movie);
//////	char buffer [50];
//////	strcpy (mine.title, "2001 A Space Odyssey");
//////	mine.year = 1968;
//////	cout << "Enter title: ";
//////	cin.getline (yours.title,50);
//////	cout << "Enter year: ";
//////	cin.getline (buffer,50);
//////	yours.year = atoi (buffer);
//////	cout << "My favourite movie is:\n ";
//////	printmovie (mine);
//////	cout << "And yours:\n";
//////	printmovie (yours);
////	void printmovie(movies_t movie);
////	char buffer[50];
////	int n;
////	for (n = 0; n < N_MOVIES; n++) {
////		cout << "Enter title: ";
////		cin.getline(films[n].title, 50);
////		cout << "Enter year: ";
////		cin.getline(buffer, 50);
////		films[n].year = atoi(buffer);
////	}
////	cout << "\nYou have entered these movies:\n";
////	for (n = 0; n < N_MOVIES; n++) {
////		printmovie(films[n]);
////	}
//	char buffer[50];
//	pmovie = & amovie;
//	cout << "Enter title: ";
//	cin.getline (pmovie->title,50);//pmovie->title==(*pmovie).title,*pmovie.title==*(pmovie.title)
//	cout << "Enter year: ";
//	cin.getline (buffer,50);
//	pmovie->year = atoi (buffer);
//	cout << "\nYou have entered:\n";
//	cout << pmovie->title;
//	cout << " (" << pmovie->year << ")\n";
//	/*
//	 * pmovie.title	结构pmovie 的元素title
//	 * pmovie->title	指针pmovie 所指向的结构其元素title 的值	(*pmovie).title
//	 * *pmovie.title	结构pmovie 的元素title 作为指针所指向的值	*(pmovie.title)
//	 */

	//类 class
//	CRectangle rect1, rect2;
//	rect1.set_values(3, 4);
//	rect2.set_values(5, 9);
//	cout << "area1: " << rect1.area() << endl << "area2: " << rect2.area();
	//构造函数 Constructors
//	CRectangle rect(3, 4);
//	CRectangle rectb(5, 6);
//	cout << "rect area: " << rect.area() << endl;
//	cout << "rectb area: " << rectb.area() << endl;
	//析构函数 destructors
//	CRectangle rect(3, 4), rectb(5, 6);
//	cout << "rect area: " << rect.area() << endl;
//	cout << "rectb area: " << rectb.area() << endl;
	//构造函数重载(Overloading Constructors)
//	CRectangle rect(3, 4);
//	CRectangle rectb;
//	cout << "rect area: " << rect.area() << endl;
//	cout << "rectb area: " << rectb.area() << endl;
	//类的指针(Pointers to classes)
//	CRectangle a, *b, *c;
//	CRectangle * d = new CRectangle[2];
//	b = new CRectangle;
//	c = &a;
//	a.set_values(1, 2);
//	b->set_values(3, 4);
//	d->set_values(5, 6);
//	d[1].set_values(7, 8);
//	cout << "a area: " << a.area() << endl;
//	cout << "*b area: " << b->area() << endl;
//	cout << "*c area: " << c->area() << endl;
//	cout << "d[0] area: " << d[0].area() << endl;
//	cout << "d[1] area: " << d[1].area() << endl;
//	/*
//	 * *x 读作: pointed by x （由x指向的）
//	 * &x 读作: address of x（x的地址）
//	 * x.y 读作: member y of object x （对象x的成员y）
//	 * (*x).y 读作: member y of object pointed by x（由x指向的对象的成员y）
//	 * x->y 读作: member y of object pointed by x (同(*x).y等价)
//	 * x[n] 读作: (n+1)th object pointed by x（由x指向的第n+1个对象）
//	 */
	//操作符重载（Overloading operators）
//	CVector a(3, 1);
//	CVector b(1, 2);
//	CVector c;
//	c = a + b;
////	c = a.operator+ (b);//等于c = a + b
//	cout << c.x << "," << c.y;
	//关键字 this
////	CDummy a;
////	CDummy* b = &a;
////	if (b->isitme(a)){
////		cout << "yes, &a is b";
////	}
//	CVector a(3, 1);
//	CVector b;
////	b.operator =(a);//等于b = a
//	b = a;
//	cout << b.x << endl << b.y;
	//静态成员(Static members)
//	CDummy a;//CDummy()
//	CDummy b[5];//CDummy() 5次
//	CDummy * c = new CDummy;//CDummy()
//	cout << a.n << endl;
//	delete c;//~CDummy()
//	cout << CDummy::n << endl;
	//类之间的关系(Relationships between classes)
	//友元函数(Friend functions)
////	CRectangle rect, rectb;
////	rect.set_values(2, 3);
////	rectb = duplicate(rect);//不是CRectangle类成员
////	cout << rectb.area();
//	//友元类 (Friend classes)
//	CSquare sqr;
//	CRectangle rect;
//	sqr.set_side(4);
//	rect.convert(sqr);
//	cout << rect.area();
	//继承 Inheritance
////	CRectangle2 rect;
////	CTriangle trgl;
////	rect.set_values(4, 5);
////	trgl.set_values(4, 5);
////	cout << rect.area() << endl;
////	cout << trgl.area() << endl;
	//继承构造函数
//    daughter cynthia (1);
//    son daniel(1);
	//多重继承(Multiple inheritance)
//	CRectangle3 rect;
//	CTriangle2 trgl;
//	rect.set_values(4, 5);
//	trgl.set_values(4, 5);
//	rect.output(rect.area());
//	trgl.output(trgl.area());
	//多态 (Polymorphism)
	//基类的指针(Pointers to base class)
//	CRectangle2 rect;
//	CTriangle trgl;
//	CPolygon * ppoly1 = &rect;
//	CPolygon * ppoly2 = &trgl;
//	ppoly1->set_values(4, 5);
//	ppoly2->set_values(4, 5);
//	cout << rect.area() << endl;
//	cout << trgl.area() << endl;
	//虚拟成员(Virtual members)
//	CRectangle2 rect;
//	CTriangle trgl;
//	CPolygon poly;
//	CPolygon * ppoly1 = &rect;
//	CPolygon * ppoly2 = &trgl;
//	CPolygon * ppoly3 = &poly;
//	ppoly1->set_values(4, 5);
//	ppoly2->set_values(4, 5);
//	ppoly3->set_values(4, 5);
//	cout << ppoly1->area() << endl;
//	cout << ppoly2->area() << endl;
//	cout << ppoly3->area() << endl;
	//抽象基类(abstract base classes)
////	CRectangle4 rect;
////	CTriangle3 trgl;
////	CPolygon2 * ppoly1 = &rect;
////	CPolygon2 * ppoly2 = &trgl;
////	ppoly1->set_values(4, 5);
////	ppoly2->set_values(4, 5);
////	cout << ppoly1->area() << endl;
////	cout << ppoly2->area() << endl;
//	CRectangle4 rect;
//	CTriangle3 trgl;
//	CPolygon2 * ppoly1 = &rect;
//	CPolygon2 * ppoly2 = &trgl;
//	ppoly1->set_values(4, 5);
//	ppoly2->set_values(4, 5);
//	ppoly1->printarea();
//	ppoly2->printarea();

	//模板(Templates)
	//函数模板
////	int i1 = 185, i2 = -76, i3 = 567/*, i4=123*/, i;
////	double d1 = 56.87, d2 = 90.23, d3 = -3214.78/*, d4=2342.99*/, d;
////	long g1 = 67854, g2 = -912456, g3 = 673456/*, g4=452234*/, g;
////	i = max3(i1, i2, i3/*, i4*/); //调用模板函数,此时T被int取代
////	d = max3(d1, d2, d3/*, d4*/);
////	//调用模板函数,此时T被double取代
////	g = max3(g1, g2, g3/*, g4*/);
////	//调用模板函数,此时T被long取代
////	cout << "i_max=" << i << endl;
////	cout << "d_max=" << d << endl;
////	cout << "g_max=" << g << endl;
//	int i = 5, j = 6, k;
//	long l = 10, m = 5, n;
//	k = GetMax(i, j);
//	n = GetMax(l, m);
//	cout << k << endl;
//	cout << n << endl;
	//类模板(Class templates) ?代码有问题?
//	pair myobject(100, 75);
//	cout << myobject.getmax();
	//模板特殊化(Template specialization) ?代码有问题?
//	pair<int> myints(100, 75);
//	pair<float> myfloats(100.0, 75.0);
//	cout << myints.module() << '\n';
//	cout << myfloats.module() << '\n';
	//模板的参数值(Parameter values for templates)
//	array<int, 5> myints;
//	array<float, 5> myfloats;
//	myints.setmember(0, 100);
//	myfloats.setmember(3, 3.1416);
//	cout << myints.getmember(0) << '\n';
//	cout << myfloats.getmember(3) << '\n';

	//名空间 (Namespaces)
//////	cout << first::var << endl;
//////	cout << second::var << endl;
////	using namespace second;
////	cout << var << endl;
////	cout << (var*2) << endl;
//    {
//		using namespace first;
//		cout << var << endl;
//	}
//	{
//		using namespace second;
//		cout << var << endl;
//	}

	//Exception
//////	char myarray[10];
//////	try {
//////		for (int n = 0; n <= 10; n++) {
//////			if (n > 9)
//////				throw "Out of range";
//////			myarray[n] = 'z';
//////		}
//////	} catch (char * str) {
//////		cout << "Exception: " << str << endl;
//////	}
////	try {
////		char * mystring;
////		mystring = new char[10];
////		if (mystring == NULL)
////			throw "Allocation failure";
////		for (int n = 0; n <= 100; n++) {
////			if (n > 9)
////				throw n;
////			mystring[n] = 'z';
////		}
////	} catch (int i) {
////		cout << "Exception: ";
////		cout << "index " << i << " is out of range" << endl;
////	} catch (char * str) {
////		cout << "Exception: " << str << endl;
////	}
//	try {
//		A * a = NULL;
//		typeid (*a);
//	} catch (/*std::*/exception& e) {
//		cout << "Exception: " << e.what();
//	}

	// 类型转换高级 (Advacned Class Type-casting)
	/*
	 * ANSI-C++ 标准定义了4种新的类型转换操作符： reinterpret_cast, static_cast, dynamic_cast 和 const_cast
	 */

	//typeid
//	A * a, b;
//	if (typeid(a) != typeid(b)) {
//		cout << "a and b are of different types:\n";
//		cout << "a is: " << typeid(a).name() << '\n';
//		cout << "b is: " << typeid(b).name() << '\n';
//	}

	//预处理指令 (Preprocessor Directives)
	//#define
//	#define getmax(a,b) a>b?a:b
//	int x = 5, y;
//	y = getmax(x,8);
//	cout << y;
	//#undef #undef 完成与 #define相反的工作，它取消对传入的参数的宏定义
//	#define MAX_WIDTH 100
//	cout << MAX_WIDTH << endl;
//	#undef MAX_WIDTH
//	#define MAX_WIDTH 200
//	cout << MAX_WIDTH << endl;
	//#ifdef, #ifndef, #if, #endif, #else, #elif(=else if)
//	//#ifdef, #ifndef
////	#ifdef MAX_WIDTH
////	char str[MAX_WIDTH];
////	#endif
////	#ifndef MAX_WIDTH
////	#define MAX_WIDTH 100
////	#endif
////	char str[MAX_WIDTH];
//	//#if, #else, #elif
//	#if MAX_WIDTH>200
//	#undef MAX_WIDTH
//	#define MAX_WIDTH 200
//	#elsif MAX_WIDTH<50
//	#undef MAX_WIDTH
//	#define MAX_WIDTH 50
//	#else
//	#undef MAX_WIDTH
//	#define MAX_WIDTH 100
//	#endif
//	char str[MAX_WIDTH];
	//#line
//	#line 1 "assigning variable"
//	int a?;
	//#error
//	#ifndef __cplusplus
//	#error A C++ compiler is required
//	#endif
	//#include
//	#include "file" //指定的文件
//	#include <file> //头文件
	//#pragma

	//预定义的宏名称 (Predefined macro names)
//	cout << "This is the line number " << __LINE__;//__LINE__:整数值，表示当前正在编译的行在源文件中的行数。
//	cout << " of file " << __FILE__ << ".\n";//__FILE__:字符串，表示被编译的源文件的文件名。
//	cout << "Its compilation began " << __DATE__;//__DATE__:一个格式为 "Mmm dd yyyy" 的字符串，存储编译开始的日期。
//	cout << " at " << __TIME__ << ".\n";//__TIME__:一个格式为 "hh:mm:ss" 的字符串，存储编译开始的时间。
//	cout << "The compiler gives a " << "__cplusplus value of " << __cplusplus;//__cplusplus:整数值，所有C++编译器都定义了这个常量为某个值。如果这个编译器是完全遵守C++标准的，它的值应该等于或大于199711L，具体值取决于它遵守的是哪个版本的标准。

	//文件的输入输出 (Input/Output with files)
//	//打开文件写内容
//	ofstream examplefile("E:\\Workspaces_eclipse_cpp\\hello world\\temp\\example.txt");
//	if (examplefile.is_open()) {
//		examplefile << "This is a line.\n";
//		examplefile << "This is another line.\n";
//		examplefile.close();
//		cout << "write file complete";
//	}
//	//打开文件读内容
////	char buffer[256];
////	ifstream examplefile("E:\\Workspaces_eclipse_cpp\\hello world\\temp\\example.txt");
////	if (!examplefile.is_open()) {
////		cout << "Error opening file";
////		exit(1);
////	}
////	while (!examplefile.eof()) {
////		examplefile.getline(buffer, 100);
////		cout << buffer << endl;
////	}
//	//获得文件的字节大小
////	long l, m;
////	ifstream file(filename, ios::in | ios::binary);
////	l = file.tellg();//tellg:get流指针的位置
////	file.seekg(0, ios::end);//seekg:改变流指针get的位置
////	m = file.tellg();
////	file.close();
////	cout << "size of " << filename;
////	cout << " is " << (m - l) << " bytes.\n";
//	//二进制文件(Binary files)
////	char * buffer;
////	long size;
////	ifstream file(filename, ios::in | ios::binary | ios::ate);
////	size = file.tellg();
////	file.seekg(0, ios::beg);
////	buffer = new char[size];
////	file.read(buffer, size);
////	file.close();
////	cout << "the complete file is in a buffer";
////	delete[] buffer;

	//CommonUtil
	//strSplit
//	string src = "Accsvr:tcp     -h   127.0.0.1:-p /t 20018   ";
//	vector<string> d;
////	vector<string>::iterator p;
//	CommonUtil::strSplit(src, d, " ");
////	for (p = d.begin(); p != d.end(); ++p) {
////		cout << *p << endl;
////	}
//	for(int i=0;i<d.size();i++){
//		string s=d[i];
//		cout << s << endl;
//	}
	//monthDays
//	int y=2020;
//	cout << CommonUtil::monthDays(y, 1) << endl;
//	cout << CommonUtil::monthDays(y, 2) << endl;
//	cout << CommonUtil::monthDays(y, 3) << endl;
//	cout << CommonUtil::monthDays(y, 4) << endl;
//	cout << CommonUtil::monthDays(y, 5) << endl;
//	cout << CommonUtil::monthDays(y, 6) << endl;
//	cout << CommonUtil::monthDays(y, 7) << endl;
//	cout << CommonUtil::monthDays(y, 8) << endl;
//	cout << CommonUtil::monthDays(y, 9) << endl;
//	cout << CommonUtil::monthDays(y, 10) << endl;
//	cout << CommonUtil::monthDays(y, 11) << endl;
//	cout << CommonUtil::monthDays(y, 12) << endl;
	//int2str
//	int i=990;
//	string s=CommonUtil::int2str(i);
//	cout << s << endl;
	//test 月初月底
//	vector<string> varr;
//	CommonUtil::strSplit("2013-02", varr, "-");
//	int y=atoi(varr[0].c_str());
//	int m=atoi(varr[1].c_str());
//	int monthDays=CommonUtil::monthDays(y, m);
//	string s_m=strlen(varr[1].c_str())<2?"0"+varr[1]:varr[1];
//	string beginTime=varr[0]+"-"+s_m+"-01";
//	string endTime=varr[0]+"-"+s_m+"-"+CommonUtil::int2str2(monthDays);
//	cout << "beginTime:"+beginTime+"," << "endTime:"+endTime;

//	string s="20160122";
//	cout << s.substr(0, 4)+"," << s.substr(4, 2)+"," << s.substr(6, 2);

	//ivrLib.cpp-->int ivrHaltPhoneExt(char* PhoneNo)
//	short iUserSts = 1;//2	1
//	int iRetValue = 0;
//	if (iUserSts > 1) {
//		iRetValue = 1;
//	} else {
//		char UserSts[64];
////		strcpy(UserSts, "0000000000000010000000000000000000000000000000000000000000000000");
//		strcpy(UserSts, "0000000000000000000000000000000000000000000000000000000000000000");
//		int iPos = 0;
//		int iLen = strlen(UserSts);
//		for (int i = 0; i < iLen; i++) {
//			if (UserSts[i] == '1')
//				iPos = i + 1; //记录最后一个1位置
//		}
//		cout << iPos << endl;
//		if (iPos == 0) {
//			iRetValue = 0;
//		} else if ((iPos >= 11) && (iPos <= 30)) {
//			iRetValue = 1; //帐务停、管理停
//		} else if (iPos == 3) {
//			iRetValue = 2; //iPos=3为营业停机 add by yuanjun
//		} else if (iPos == 2) {
//			iRetValue = 4;//iPos=2为挂失停机
//		} else {
//			iRetValue = 3; //iPos=1 连带停机  2 挂失停机 请参见zk.cm_para_user_sts_rule
//		}
//	}
//    cout << iRetValue << endl;

	//ivrLib.cpp-->int getStartLevel(char* phoneNo, char* custClass)
//	short creditId=1;
//	char* custClass;
//	switch (creditId) {
//	case 58: //5星钻
//		sprintf(custClass, "%s\0", "3");
//		break;
//	case 57: //5星金
//		sprintf(custClass, "%s\0", "3");
//		break;
//	case 5: //5星
//		sprintf(custClass, "%s\0", "2");
//		break;
//	case 4: //4星
//		sprintf(custClass, "%s\0", "1");
//		break;
//	case 3: //3星及以下
//		sprintf(custClass, "%s\0", "0");
//		break;
//	default:
//		sprintf(custClass, "%s\0", "0");
//	}
//	cout << custClass;

//	Test::stringstreamTest2();
//	Test::stringTest8();
//	Test::strFunTest_strcat1();
//	Test::strcmptest1();
//	Test::itoaTest1();
//	Test::CommonUtilTest1();
	Test::AItest1();









	return 0;
}
