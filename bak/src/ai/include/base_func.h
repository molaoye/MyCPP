#ifndef _BASE_FUNC_H_
#define _BASE_FUNC_H_

#include "compile.h"
#include "base_define.h"

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>

#include <math.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>

#ifndef _Windows
#include <strings.h>
#include <unistd.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
// not used?(lixp) #include <sys/socket.h>
//#include <sys/wait.h>
#endif

#  ifdef OB_NO_STD
    #include <strstream.h>
    #include <fstream.h>
    #include <iostream.h>
#  else
    #include <sstream>
    #include <fstream>
    #include <iostream>
#  endif

//#include "datetime.h"

/** @defgroup group_base_func basic functions
 *  header file: "common/base_func.h"
 *  @{
 */
//#ifndef _RTLDLL

/** @defgroup group_bf_string string utils
 *  @{
 */
/** @} */

/** @defgroup group_bf_scalar scalar convertion
 *  @{
 */
/** @} */

/** @defgroup group_bf_datetime datetime convertion
 *  @{
 */
/** @} */

/** @defgroup group_bf_misc miscellaneous functions
 *  @{
 */
/** @} */

//#ifndef _Windows

//! \ingroup group_bf_string
// to upper characters from input string
AISTD string toUpper(AISTD string &	in_str);

//! \ingroup group_bf_string
// to upper characters from input string
AISTD string toUpper(const AISTD string &	in_str);

//! \ingroup group_bf_string
// to lower characters from input string
AISTD string toLower(AISTD string &	in_str);

//! \ingroup group_bf_string
// to lower characters from input string
AISTD string toLower(const AISTD string &	in_str);

//! \ingroup group_bf_string
// Trim both space from input string
AISTD string trimBoth(
	AISTD string &	in_str,
	char		pat=' '
);

//! \ingroup group_bf_string
// Trim both space from input string
AISTD string trimBoth(
	const AISTD string &	in_str,
	char		pat=' '
);

//! \ingroup group_bf_string
// Trim leading space from input string
AISTD string trimLeading(
	AISTD string &	in_str,
	char		pat=' '
);

//! \ingroup group_bf_string
// Trim leading space from input string
AISTD string trimLeading(
	const AISTD string &	in_str,
	char		pat=' '
);

//! \ingroup group_bf_string
// Trim trailing space from input string
AISTD string trimTrailing(
	AISTD string &	in_str,
	char		pat=' '
);

//! \ingroup group_bf_string
// Trim trailing space from input string
AISTD string trimTrailing(
	const AISTD string &	in_str,
	char		pat=' '
);

//! \ingroup group_bf_scalar
// short to string.
AISTD string itoa(
	short	i
);

//! \ingroup group_bf_scalar
// int32 to string.
AISTD string itoa(
	int32	i
);

//! \ingroup group_bf_scalar
// int64 to string.
AISTD string itoa(
	int64	i
);

//! \ingroup group_bf_scalar
// unsigned to string.
AISTD string itoa(
	unsigned	i
);

//! \ingroup group_bf_scalar
// short to string (with format).
AISTD string itoa(
	short	in_number,
	int32   in_len,
	short   in_fill=0,
	short   in_alignment=0,
	char    in_fillChar=' '
);

//! \ingroup group_bf_scalar
// int32 to string (with format).
AISTD string itoa(
	int32	in_number,
	int32	in_len,
	short	in_fill=0,
	short	in_alignment=0,
	char    in_fillChar=' '
);

//! \ingroup group_bf_scalar
// int64 to string (with format).
AISTD string itoa(
	int64    in_number,
	int32     in_len,
	short   in_fill=0,
	short   in_alignment=0,
	char    in_fillChar=' '
);

//! \ingroup group_bf_scalar
// unsigned to string (with format).
AISTD string itoa(
	unsigned	in_number,
	int32		in_len,
	short		in_fill=0,
	short		in_alignment=0,
	char		in_fillChar=' '
);

//! \ingroup group_bf_scalar
// Octal short to string.
AISTD string itox(
	short	i
);

//! \ingroup group_bf_scalar
// Octal int32 to string.
AISTD string itox(
	int32	i
);

//! \ingroup group_bf_scalar
// Octal int64 to string.
AISTD string itox(
	int64	i
);

//! \ingroup group_bf_scalar
// Octal unsigned to string.
AISTD string itox(
	unsigned	i
);

//! \ingroup group_bf_scalar
// Octal short to string.
AISTD string itox(
	short	in_number,
	int32	in_len,
	short	in_fill=0,
	short	in_alignment=0,
	char	in_fillChar=' '
);

//! \ingroup group_bf_scalar
// Octal int32 to string.
AISTD string itox(
	int32	in_number,
	int32	in_len,
	short	in_fill=0,
	short	in_alignment=0,
	char	in_fillChar=' '
);

//! \ingroup group_bf_scalar
// Octal int64 to string.
AISTD string itox(
	int64    in_number,
	int32     in_len,
	short   in_fill=0,
	short   in_alignment=0,
	char    in_fillChar=' '
);

//! \ingroup group_bf_scalar
// Octal unsigned to string.
AISTD string itox(
	unsigned	in_number,
	int32		in_len,
	short		in_fill=0,
	short		in_alignment=0,
	char		in_fillChar=' '
);

//! \ingroup group_bf_scalar
// short to string.
AISTD string itooct(
        short   i
);

//! \ingroup group_bf_scalar
// int32 to string.
AISTD string itooct(
        int32     i
);

//! \ingroup group_bf_scalar
// int64 to string.
AISTD string itooct(
        int64    i
);

//! \ingroup group_bf_scalar
// unsigned to string.
AISTD string itooct(
        unsigned        i
);

//! \ingroup group_bf_scalar
// short to string (with format).
AISTD string itooct(
        short   in_number,
        int32     in_len,
        short   in_fill=0,
        short   in_alignment=0,
        char    in_fillChar=' '
);

//! \ingroup group_bf_scalar
// int32 to string (with format).
AISTD string itooct(
        int32     in_number,
        int32     in_len,
        short   in_fill=0,
        short   in_alignment=0,
        char    in_fillChar=' '
);

//! \ingroup group_bf_scalar
// int64 to string (with format).
AISTD string itooct(
        int64    in_number,
        int32     in_len,
        short   in_fill=0,
        short   in_alignment=0,
        char    in_fillChar=' '
);

//! \ingroup group_bf_scalar
// unsigned to string (with format).
AISTD string itooct(
        unsigned        in_number,
        int32             in_len,
        short           in_fill=0,
        short           in_alignment=0,
        char            in_fillChar=' '
);

//! \ingroup group_bf_scalar
// float to string.
AISTD string ftoa(
	float	f
);

//! \ingroup group_bf_scalar
// double to string.
AISTD string ftoa(
	double	f
);

//! \ingroup group_bf_scalar
// float to string.
AISTD string ftoa(
	float	in_number,
	int32     in_len,
	short   in_fill=0,
	short   in_alignment=0,
	char    in_fillChar=' '
);

//! \ingroup group_bf_scalar
// double to string.
AISTD string ftoa(
	double	in_number,
	int32     in_len,
	short   in_fill=0,
	short   in_alignment=0,
	char    in_fillChar=' '
);

//! \ingroup group_bf_scalar
// string to spec format string.
AISTD string atoa(
	const	AISTD string&	in_str,
	int32		in_len,
	short		in_fill=0,
	short		in_alignment=0,
	char		in_fillChar=' '
);

//! \ingroup group_bf_scalar
// convert string to 64bit integer
extern int64 atol64(const char* szStr);

//! \ingroup group_bf_scalar
// convert string to 64bit integer
extern int64 atol64(const AISTD string& str);

//! \ingroup group_bf_datetime
// Analyse date format from input string. return 0:Not date format; 1:YYYYMMDD; 2:YYYYMM; 3:YYMMDD;
//-----------------------------------------------------------------------------
int32 str_is_date(
	const	AISTD string&	in_dateStr
);

//! \ingroup group_bf_datetime
// Change string(format: YYYYMMDD) to CBSDate.
//-----------------------------------------------------------------------------
bool str_to_date(
	const	AISTD string&	in_str,
	CBSDate&		out_date
);

//! \ingroup group_bf_datetime
// Change string(format: YYYYMMDD) to struct tm. timeFlag: 0 is 0:0:0 , 1 is 23:59:59
bool str_to_date(
	const	AISTD string&	in_str,
	struct tm& out_date,
	int32 timeFlag
);

//! \ingroup group_bf_datetime
// Change string(format: YYYYMMDD) to time_t. timeFlag: 0 is 0:0:0 , 1 is 23:59:59
bool str_to_date(
	const	AISTD string&	in_str,
	time_t& out_date,
	int32 timeFlag
);

//! \ingroup group_bf_datetime
// Change string(YYYY/MM/DD hh:mm:ss; MM/DD/YYYY hh:mm:ss; MM/DD/YY hh:mm:ss) to CBSDateTime.
CBSDateTime str_to_time(
        const AISTD string&   in_str
);

//! \ingroup group_bf_datetime
// Change string(YYYY/MM/DD hh:mm:ss; MM/DD/YYYY hh:mm:ss; MM/DD/YY hh:mm:ss) to CBSTime.
bool str_to_time(
	const AISTD string&	in_str,
	CBSDateTime&		out_time
);

//! \ingroup group_bf_datetime
// Change string(YYYY/MM/DD hh:mm:ss; MM/DD/YYYY hh:mm:ss; MM/DD/YY hh:mm:ss) to struct tm.
bool str_to_time(
	const AISTD string&	in_str,
	struct tm&	out_time
);

//! \ingroup group_bf_datetime
// Change string(YYYY/MM/DD hh:mm:ss; MM/DD/YYYY hh:mm:ss; MM/DD/YY hh:mm:ss) to time_t.
bool str_to_time(
	const AISTD string&	in_str,
	time_t&	out_time
);

//! \ingroup group_bf_datetime
// Change CBSDate to string. format: '%Y':YYYY,'%y':YY,'%M':MM,'%m':M,'%D':DD,'%d':D.
AISTD string date_to_str(
	const	CBSDate&	in_date,
	const	AISTD string&		in_format
);

/*! \ingroup group_bf_datetime
  \brief Change CBSTime to string. format: '%Y':YYYY, '%y':YY,'%M':MM,'%m':M,
 '%D':DD,'%d':D, '%H':HH,'%h':H,'%N':mm,'%n':m,'%S':SS,'%s':S. */
AISTD string time_to_str(
	const	CBSTime&	in_time,
	const	AISTD string&		in_format
);

/*! \ingroup group_bf_datetime
 \brief Change CBSDateTime to string.
 format: '%Y':YYYY,'%y':YY,'%M':MM,'%m':M,'%D':DD,'%d':D,
         '%H':HH,'%h':H,'%N':mm,'%n':m,'%S':SS,'%s':S. */
AISTD string time_to_str(
	const	CBSDateTime&	in_time,
	const	AISTD string&		in_format
);

/*! \ingroup group_bf_datetime
 \brief Change struct tm to string.
 format: '%Y':YYYY,'%y':YY,'%M':MM,'%m':M,'%D':DD,'%d':D,
         '%H':HH,'%h':H,'%N':mm,'%n':m,'%S':SS,'%s':S. */
AISTD string time_to_str(
	const	struct tm&	in_time,
	const	AISTD string&	in_format
);

/*! \ingroup group_bf_datetime
 \brief Change time_t to string.
 format: '%Y':YYYY,'%y':YY,'%M':MM,'%m':M,'%D':DD,'%d':D,
         '%H':HH,'%h':H,'%N':mm,'%n':m,'%S':SS,'%s':S. */
AISTD string time_to_str(
	const	time_t&	in_time,
	const	AISTD string&	in_format
);

//! \ingroup group_bf_string
// Divide string by input flag strings. (allow space). return >0:success; <=0:failed.
int32 base_divide_str(
	const	AISTD string&		in_str,
	const	AISTD string&		in_divideStr,
	CStringList*	out_list
);

//! \ingroup group_bf_string
// Divide string by input flag strings. (allow space). return >0:success; <=0:failed.
int32 base_divide_str(
    const   AISTD string&      in_str,
    const   AISTD string&      in_divideStr,
    CStringList& out_list
);

//! \ingroup group_bf_string
// Divide string by input flag strings. (estop space). return >0:success; <=0:failed.
int32 divide_str(
	const	AISTD string&		in_str,
	const	AISTD string&		in_divideStr,
	CStringList*	out_list
);

//! \ingroup group_bf_string
// Divide string by input flag strings. (estop space). return >0:success; <=0:failed.
//-----------------------------------------------------------------------------
int32 divide_str(
    const   AISTD string&      in_str,
    const   AISTD string&      in_divideStr,
    CStringList&    out_list
);

//! \ingroup group_bf_misc
// Make directory from input filename with path.
bool mkdir_fromFileName(
	const	AISTD string&	in_fileName
);

//! \ingroup group_bf_misc
// Translate environment variables like "$(xx)" in a string, return translated number
int translate_envStr(const char* sour, char* dest);

//! \ingroup group_bf_misc
// Formula analyser. simple + - * / () and number calculator.
bool parse_formula(
	const	char*	in_str,
	double&	out_val
);

//! \ingroup group_bf_datetime
// Get stat_date from input CBSDate.
bool get_statDate(
	const	CBSDate&	in_date,
	const	int32&		in_statDay,
	CBSDate&	out_date
);

//! \ingroup group_bf_datetime
// Get stat_date from input string. format: YYYYMMDD
bool get_statDate(
	const	AISTD string&	in_dateStr,
	const	int32&	in_statDay,
	CBSDate&	out_date
);

//! \ingroup group_bf_datetime
// Get stat_date from input CBSDate.
bool get_statDateStr(
	const	CBSDate&	in_date,
	const	int32&		in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get stat_date from input string. format: YYYYMMDD
bool get_statDateStr(
	const	AISTD string&	in_dateStr,
	const	int32&	in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get stat_month from input CBSDate.
bool get_statMonthStr(
	const	CBSDate&	in_date,
	const	int32&		in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get stat_month from input string. format: YYYYMMDD
bool get_statMonthStr(
	const	AISTD string&	in_dateStr,
	const	int32&	in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get stat_year from input CBSDate.
bool get_statYearStr(
	const	CBSDate&	in_date,
	const	int32&		in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get stat_year from input string. format: YYYYMMDD
bool get_statYearStr(
	const	AISTD string&	in_dateStr,
	const	int32&	in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get previous stat_month from input CBSDate.
bool get_prevStatMonthStr(
	const	CBSDate&	in_date,
	const	int32&		in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get previous stat_month from input string. format: YYYYMMDD
bool get_prevStatMonthStr(
	const	AISTD string&	in_dateStr,
	const	int32&	in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get next stat_month from input CBSDate.
bool get_nextStatMonthStr(
	const	CBSDate&	in_date,
	const	int32&		in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get next stat_month from input string. format: YYYYMMDD
bool get_nextStatMonthStr(
	const	AISTD string&	in_dateStr,
	const	int32&	in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get previous nature_month from input CBSDate.
bool get_prevMonthStr(
	const	CBSDate&		in_date,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get previous nature_month from input string. format: YYYYMM
bool get_prevMonthStr(
	const	AISTD string&	in_dateStr,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get next nature_month from input CBSDate.
bool get_nextMonthStr(
	const	CBSDate&		in_date,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get next nature_month from input string. format: YYYYMM
bool get_nextMonthStr(
	const	AISTD string&	in_dateStr,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get previous stat_date from input CBSDate.
bool get_prevStatDateStr(
	const	CBSDate&		in_date,
	const	int32&		in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get previous stat_date from input string. format: YYYYMMDD
bool get_prevStatDateStr(
	const	AISTD string&	in_dateStr,
	const	int32&		in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get next stat_date from input CBSDate.
bool get_nextStatDateStr(
	const	CBSDate&		in_date,
	const	int32&		in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get next stat_date from input string. format: YYYYMMDD
bool get_nextStatDateStr(
	const	AISTD string&	in_dateStr,
	const	int32&		in_statDay,
	AISTD string&	out_dateStr
);

//! \ingroup group_bf_datetime
// Get stat_start_date and stat_end_date from input string. format: YYYYMM
bool get_statStartEndDateStr(
	const	AISTD string&	in_dateStr,
	const	int32&		in_statDay,
	AISTD string&	out_startDateStr,
	AISTD string&	out_endDateStr
);

//! \ingroup group_bf_datetime
// Get days from input string. format: YYYYMM. return <=0:failed; >0:success.
int32 get_daysInMonth(
	const	AISTD string&	in_dateStr
);

//! \ingroup group_bf_datetime
// Get months from input start_month and end_month (string). format: YYYYMM. return <=0:failed; >0:success.
int32 get_monthDiff(
	const	AISTD string&	startMonthStr,
	const	AISTD string&	endMonthStr
);

//! \ingroup group_bf_misc
// Get filename from input string (filename without path).
AISTD string get_baseFileName(
	const	AISTD string&	sPathFileName
);

//! \ingroup group_bf_misc
// crc32 function
uint32 crc32(const char* inchar);

//! \ingroup group_bf_string
// SubStr function
AISTD string SubStr(const AISTD string& in_string, const AISTD string& in_char);

//----------------------------------------------------------------------------
//#endif  // _Windows

//! \ingroup group_bf_misc
// check whether id card is correct
bool	check_idCard ( const AISTD string strId );

//! \ingroup group_bf_datetime
//! get month list
void get_monthList (
	const CBSDate & startDate,
	const CBSDate & endDate,
	CIntegerList &	monthList
	);

/** @} */
#endif  //_BASE_FUNC_H_
