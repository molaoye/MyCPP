//---------------------------------------------------------------------------
// Filename:        obd_basic_def.h
// Date:            2003-8-23
// Author:          Li xiaoping
// Function:        basic definition for OBD generated files
// History:
//      2003-8-23   Create this file
//---------------------------------------------------------------------------

#ifndef __OBD_BASIC_DEF_H__
#define __OBD_BASIC_DEF_H__

#include <exception>
#include <string>
#include <vector>

#include "compile.h"

#define OBE_MIN_CODE				-9999
#define OBE_SVR_CALL_APP			-9999
#define OBE_SVR_MARSHALLING_IN		-9998
#define OBE_SVR_MARSHALLING_OUT		-9997
#define OBE_CLN_MARSHALLING_IN		-9996
#define OBE_CLN_MARSHALLING_OUT		-9995
#define OBE_SVR_IN_BEGIN_STREAM		-9994
#define OBE_SVR_IN_END_STREAM		-9993
#define OBE_SVR_OUT_BEGIN_STREAM	-9992
#define OBE_SVR_OUT_END_STREAM		-9991
#define OBE_CLN_IN_BEGIN_STREAM		-9990
#define OBE_CLN_IN_END_STREAM		-9989
#define OBE_CLN_OUT_BEGIN_STREAM	-9988
#define OBE_CLN_OUT_END_STREAM		-9987
#define OBE_SVR_OBB_EXCEPTION		-9986
#define OBE_CLN_OBB_EXCEPTION		-9985
#define OBE_SVR_OBB_IMPORT			-9984
#define OBE_SVR_OBB_EXPORT			-9983
#define OBE_CLN_OBB_IMPORT			-9982
#define OBE_CLN_OBB_EXPORT			-9981
#define OBE_CLN_CALL_SERVER			-9980
#define OBE_CLN_NO_IMPLEMENT		-9979
#define OBE_CLN_NOT_INIT			-9978
#define OBE_SVR_GET_DBPOOL			-9977
#define OBE_CLN_NULL_POINTER		-9976
#define OBE_CLN_NO_INTERFACE		-9975
#define OBE_CLN_INIT_ERROR			-9974
#define OBE_CLN_OPEN_DOMAIN			-9973
#define	OBE_SVR_DBCONN_IS_NULL		-9972
#define OBE_SVR_UNCAUGHT_EXCEPTION  -9971
#define OBE_SVR_NO_IMPLEMENT		-9970
#define OBE_MAX_CODE				-9969

#define IS_OBD_ERROR(iErrorCode)	(iErrorCode >= OBE_MIN_CODE && iErrorCode < OBE_MAX_CODE)

#define OBD_OK              0
#define OBD_FAIL            -1
#define OBD_EXCEPTION       OBE_CLN_OBB_EXCEPTION
#define OBD_NO_IMPLEMENT    OBE_CLN_NO_IMPLEMENT
#define OBD_NO_INIT         OBE_CLN_NOT_INIT

#define OBD_ERROR_MSG_NAME    ("_CBSErrorMsg")
#define OBD_MARKER_NAME       ("_Marker")
#define OBD_USED_MARKER_NAME  ("_UsedMarker")
#define OBD_LIST_ITEM_NAME    ("_Item")

const char* _CBS_EXPORT obd_getErrorMsg(const int iErrorCode);

enum {
    OBD_NULL_TYPE       = 0,
    OBD_CHAR            = 1,
    OBD_STRING          = 2,
    OBD_INT16           = 3,
    OBD_INT32           = 4,
    OBD_INT64           = 5,
    OBD_FLOAT           = 6,
    OBD_DOUBLE          = 7,
    OBD_DATE            = 8,
    OBD_TIME            = 9,
    OBD_DATETIME        = 10,
    OBD_STRUCT          = 11,
    OBD_CLASS           = 12,
    OBD_LIST            = 13
};

#define IS_OBD_BASIC_TYPE(iType)	(iType >= OBD_CHAR && iType <= OBD_DATETIME)

enum { // this is bit value
	OBD_EXP_NONE		= 0,
	OBD_EXP_ENCRYPTED	= 1,
	OBD_EXP_ZIP			= 2
};

#endif

