#ifndef _BASE_DEFINE_H_
#define _BASE_DEFINE_H_

//---------------------------------------------------------------------------
// program name:        base_define.h
// description:         define system level const, marco
// created by:          zhanghua
// History:
//      02-09-20        create
// Known Issue:
// Todo:                
//---------------------------------------------------------------------------

// Version number of package 
#define VERSION "2.2"

#include "compile.h"

#include <string>
#include <vector>

#define TRUE	1
#define FALSE	0

const short OK		= 0;

const short WAIT_SECOND	= 10;

const short TRANS_COMMIT = 0;
const short TRANS_NOCOMMIT = 1;

#define  _MOBILETYPE_GSM_CHR_       'G'
#define  _MOBILETYPE_CDMA_CHR_      'C'

#define  _MOBILETYPE_GSM_STR_       "G"
#define  _MOBILETYPE_CDMA_STR_      "C"

#define  _ROAMTYPE_L_NUM_           0
#define  _ROAMTYPE_PR_NUM_          1
#define  _ROAMTYPE_NRIN_NUM_        2
#define  _ROAMTYPE_IRIN_NUM_        3
#define  _ROAMTYPE_NROUT_NUM_       4
#define  _ROAMTYPE_IROUT_NUM_       5
#define  _ROAMTYPE_PR_BORBER_NUM_       6
#define  _ROAMTYPE_NI_BORBER_NUM_       7
#define  _ROAMTYPE_NO_BORBER_NUM_       8

#define  _ROAMTYPE_L_STR_           "L"
#define  _ROAMTYPE_PR_STR_          "PO"
#define  _ROAMTYPE_PRIN_STR_        "PO"
#define  _ROAMTYPE_NRIN_STR_        "NI"
#define  _ROAMTYPE_IRIN_STR_        "II"
#define  _ROAMTYPE_PROUT_STR_       "PO"
#define  _ROAMTYPE_NROUT_STR_       "NO"
#define  _ROAMTYPE_IROUT_STR_       "IO"

#define  _ROAMTYPE_RIN_STR_         "RI"
#define  _ROAMTYPE_ROUT_STR_        "RO"
#define  _MOBILETYPE_ALL_STR_       "ALL"

#define _ALL_SERVICE_ID_            -1
#define _ALL_TABLE_TYPE_            "TOTAL"
#define _ALL_BILLING_TYPE_          -1
#define _ALL_ROAM_TYPE_             "TOTAL"
#define _ALL_BUREAU_CODE_           "TOTAL"
#define _ALL_REGION_NUM_            "TOTAL"

#define DEFAULT_PROGRAM_NAME		"OPENBOSS_DEFAULT_APP"
#define DEFAULT_RESULT				0

#define PASSWORDKEY 				"781296-5e32-89122"

typedef AISTD vector<AISTD string STL_ALLOC>	CStringList;
typedef AISTD vector<int32 STL_ALLOC>		CIntegerList;
typedef AISTD vector<int16 STL_ALLOC>		CShortList;
typedef AISTD vector<int64 STL_ALLOC>		CLongList;
typedef CIntegerList				IntList;

#endif // _BASE_DEFINE_H_
