//---------------------------------------------------------------------------
// Filename:        ob_kernel.h
// Date:            2003-8-24
// Author:          Li xiaoping
// Function:        Open BOSS kernel tier OTL algorithm
// History:
//      2003-8-24   Create this file
//      2004-8-12   Add UsedMarker
//---------------------------------------------------------------------------
#ifndef __OB_KERNEL_H__
#define __OB_KERNEL_H__

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#if !defined(_Windows) && !defined(AIXV3)
    #include <strings.h>
#endif

#include <string>
#include <vector>

#include "otl.h"
#include "compile.h"
#include "base_class.h"
#include "base_func.h"
#include "obd_basic_def.h"

#ifdef DEBUG
#  ifdef OB_NO_STD
    #include <iostream.h>
#  else
    #include <iostream>
#  endif
    #include "ailog.h"
#endif

#define OBK_USE_USED_MARKER
#define ABOUT_OBSOLETE_2004_8_12
//---------------------------------------------------------------------------
/** @defgroup group_ob_kernel ob_kernel
 *  Open BOSS kernel tier OTL based algorithm by template class ob_kernel
 *  @{
 */
//! template class for OBD class list(CObdDataList)
/*! 
 * ob_kernel is a template class which provide common DB operations for classes
 * defined in OBD(Open BOSS difinition) file. ob_kernel will not involve
 * all kinds of DB operation, but most used operations such as insert, delete,
 * update and select with OBD classes. By ob_kernel, advanced OTL operations
 * can also be done with the auxiliary functions.
 *
 * ob_kernel is designed to three level:
 * \li helper of formating a SQL statement for future use, such as get_insertSQL();
 * \li open a otl_stream, stream in and stream out is left to user, such as
 *     open_insertOtlStream();
 * \li direct insert, delete, update and select with OBD classes, such as insert().
 *
 * header file: "ob_kernel.h"
 */
template <class CObdDataList>
class ob_kernel
{
public:
    //! basic item data type of CObdDataList
    typedef typename CObdDataList::value_type     CObdData;

private:
    otl_connect&        m_conn;

    int                 m_iInsertBufferSize;
    int                 m_iSelectBufferSize;

    AISTD string        m_strInsertHint;
    AISTD string        m_strRemoveHint;
    AISTD string        m_strUpdateHint;
    AISTD string        m_strSelectHint;

    AISTD string        m_strLastSQL;
    AISTD string        m_strSchemaName;

private:
    void cvt_toUpper(AISTD string& s)
    {
        for ( AISTD string::iterator it = s.begin(); it != s.end(); ++it )
        {
            *it = toupper(*it);
        }
    }

    bool is_dbFields(
        const uint64&           llMarker)
    {
        uint64 llBit = 1;
        for ( int i = 0; i < CObdData::MEMBER_FIELD_COUNT; ++i, llBit <<= 1 )
        {
            if ( (llBit & llMarker) == 0 ) continue;
            if ( CObdData::ARRAY_MEMBER_TYPE_INFO[i].m_nTableNameIndex < 0 )
                return false;
        }

        return true;
    }

    bool is_inSameTable(
        const uint64&           llMarker)
    {
        if ( CObdData::IMPORT_TABLE_COUNT <= 1 )
            return true;

        int iTableNameIndex = -1;
        uint64 llBit = 1;
        for ( int i = 0; i < CObdData::MEMBER_FIELD_COUNT; ++i, llBit <<= 1 )
        {
            if ( (llBit & llMarker) == 0 ) continue;
            int n = CObdData::ARRAY_MEMBER_TYPE_INFO[i].m_nTableNameIndex;
            if ( n == iTableNameIndex || n < 0 ) continue;

            if ( iTableNameIndex >= 0 )
                return false;
            iTableNameIndex = n;
        }

        return true;
    }

    void check_fields(
        const uint64&           llMarker,
        const bool              bMustBeDbField,
        const bool              bMustInSameTable)
    {
        if ( bMustBeDbField && !is_dbFields(llMarker) )
        {
            throw_exception("Field must be DB-field");
        }

        if ( bMustInSameTable && !is_inSameTable(llMarker) )
        {
            throw_exception("All fields must be in same table");
        }
    }

    void check_markerRange(
        const uint64&           llMarker)
    {
        if ( llMarker == 0 || llMarker > CObdData::BITS_ALL_MARKER )
            throw_exception("Invalid marker range");
    }

    AISTD string get_checkedTableName(
        const uint64&           llMarker,
        const char*             szTableName)
    {
        AISTD string strResult;

        if ( szTableName != 0 )
        {
            if ( strchr(szTableName, '.') == 0 && !m_strSchemaName.empty() )
            {
                strResult = m_strSchemaName;
                strResult.append(1, '.');
            }
            strResult.append(szTableName);
            return strResult;
        }

        if ( !m_strSchemaName.empty() )
        {
            strResult = m_strSchemaName;
            strResult.append(1, '.');
        }

        uint64 llBit = 1;
        for ( int i = 0; i < CObdData::MEMBER_FIELD_COUNT; ++i, llBit <<= 1 )
        {
            if ( (llBit & llMarker) == 0 ) continue;
            int idx = CObdData::ARRAY_MEMBER_TYPE_INFO[i].m_nTableNameIndex;
            if ( idx >= 0 )
            {
                strResult.append(CObdData::ARRAY_IMPORT_TABLES[idx]);
                return strResult;
            }
        }

        throw_exception("No table name specified");
#ifdef _AIX // return a pseudo value
        strResult.erase();
        return strResult;        
#endif
    }

    int get_tableIndex(
        const AISTD string&     strTableName)
    {
        if ( strTableName.empty() )
        {
            return CObdData::IMPORT_TABLE_COUNT >= 0 ? 0 : -1;
        }

        AISTD string s(strTableName);
        cvt_toUpper(s);

        for ( int i = 0; i < CObdData::IMPORT_TABLE_COUNT; ++i )
        {
            if ( !strncmp(CObdData::ARRAY_IMPORT_TABLES[i], s.c_str(), s.size()) )
            {
                return i;
            }
        }

        return -1;
    }

    AISTD string get_sqlCondition(
        const uint64&           llConditionMarker,
        const char*             szMoreCondition,
        const bool              bIsMultiTableOperation)
    {
        AISTD string strCondition;
        if ( llConditionMarker != 0 )
        {
            check_markerRange(llConditionMarker);
            check_fields(llConditionMarker, false, !bIsMultiTableOperation);
            strCondition = get_placeHolderExpr(llConditionMarker, " = ", "",
                " and ", bIsMultiTableOperation);
        }

        if ( szMoreCondition != 0 )
        {
            if ( !strCondition.empty() )
            {
                strCondition.append(" ");
            }
            strCondition.append(szMoreCondition);
        }

        return strCondition;
    }

    AISTD string get_sqlConditionEx(
        const uint64&           llConditionMarker,
        const uint64&           llConditionValueMarker,
        const char*             szMoreCondition,
        const bool              bIsMultiTableOperation)
    {
        AISTD string strCondition;
        if ( llConditionMarker != 0 )
        {
            check_markerRange(llConditionMarker);
            check_fields(llConditionMarker, false, !bIsMultiTableOperation);
            strCondition = get_placeHolderExprEx(llConditionMarker, llConditionValueMarker,
                " is null ", " = ", "", " and ", bIsMultiTableOperation);
        }

        if ( szMoreCondition != 0 )
        {
            if ( !strCondition.empty() )
            {
                strCondition.append(" ");
            }
            strCondition.append(szMoreCondition);
        }

        return strCondition;
    }

    bool is_partOfWhereClause(const AISTD string& s)
    {
        const char* CLAUSE_IDS[4] = { "order", "group", "having", "union" };
        if ( s.size() == 0 ) return true;

        const char* p = s.c_str();
        for ( ; *p && ( *p == ' ' || *p == '\t' || *p == '\n' ); ++p );

        for ( int i = 0; i < 4; ++i )
        {
            int n = strlen(CLAUSE_IDS[i]);
#ifdef _Windows        	
            if ( strnicmp(CLAUSE_IDS[i], p, n) == 0 )
#else
            if ( strncasecmp(CLAUSE_IDS[i], p, n) == 0 )
#endif            
            {
                if ( p[n] == ' ' || p[n] == '\t' || p[n] == '\n' ) return false;
            }
        }

        return true;
    }

    void process_hint(
        AISTD string&           strStatement,
        const AISTD string&     strHint)
    {
        if ( !strHint.empty() )
        {
            strStatement.append(" /* ");
            strStatement.append(strHint);
            strStatement.append(" */ ");
        }
    }

    void process_otlException(
        otl_exception&          e)
    {
        AISTD string strErrorMsg((char *)e.msg);
        strErrorMsg.append("\n");
        strErrorMsg.append(e.stm_text);
        strErrorMsg.append("\n");
        strErrorMsg.append(e.var_info);

        throw_exception("otl exception", strErrorMsg.c_str(), e.code);
    }

    void process_otlException(
        const bool              bCommit,
        otl_exception&          e)
    {
        try {
#if 0 // maybe need rollback?
            if ( bCommit )
            {
                m_conn.rollback();
            }
#endif            
        }
        catch(...)
        {
        }

        process_otlException(e);
    }

    void throw_exception(
        const char*             szMsg,
        const char*             szDetail = 0,
        const int               iErrorCode = 0)
    {
        AISTD string strMsg("ob_kernel exception: ");
        strMsg.append(szMsg);
        if ( szDetail != 0 )
        {
            strMsg.append(": ");
            strMsg.append(szDetail);
        }

        CBSErrorMsg cErrorMsg(iErrorCode, szMsg, strMsg.c_str(), iErrorCode);
        throw cErrorMsg;
    }

private:
    AISTD string _get_insertSQL(
        const uint64&           llInsertMarker,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        check_markerRange(llInsertMarker);
        check_fields(llInsertMarker, false, true);
        AISTD string strOpTableName(get_checkedTableName(llInsertMarker, szTableName));

        uint64 llNoValueMarker = (llInsertMarker & CObdData::BITS_NOT_NULL_MARKER) ^
            CObdData::BITS_NOT_NULL_MARKER;
        if ( llNoValueMarker != 0 )
        {
            AISTD string s = strOpTableName;
            s += " -- some not nullable fields not set yet";
            throw_exception(s.c_str(), text_byMarker(llNoValueMarker).c_str());
        }

        AISTD string strNames(get_dbFieldNames(llInsertMarker));
        AISTD string strValues(get_placeHolders(llInsertMarker));

        AISTD string strSQL("insert ");
        process_hint(strSQL, m_strInsertHint);
        strSQL.append(" into ");
        strSQL.append(strOpTableName);
        strSQL.append(" (");
        strSQL.append(strNames);
        strSQL.append(" ) values(");
        strSQL.append(strValues);
        strSQL.append(")");

        return strSQL;
    }

    void _open_insertOtlStream(
        otl_stream&             stream,
        const uint64&           llInsertMarker,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        try {
            m_strLastSQL = _get_insertSQL(llInsertMarker, szTableName);
#ifdef DEBUG
            LogAppend(DEBUG_LEVEL, "DebugInfo", m_strLastSQL.c_str());
#endif
            stream.open(m_iInsertBufferSize, m_strLastSQL.c_str(), m_conn);
        }
        catch(otl_exception& e)
        {
            process_otlException(false, e);
        }
    }

    void _insert(
        const uint64&           llInsertMarker,
        const CObdData&         cObdData,
        const bool              bCommit = false,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        otl_nocommit_stream stream;
        _open_insertOtlStream(stream, llInsertMarker, szTableName);
        try {
#ifdef DEBUG
            AISTD cout << cObdData;
#endif
            cObdData.otl_streamOut(llInsertMarker, stream, otl_null());
            stream.flush();

            if ( bCommit )
            {
                m_conn.commit();
            }
        }
        catch(otl_exception& e)
        {
            process_otlException(bCommit, e);
        }
    }

    void _insert_list(
        const uint64&           llInsertMarker,
        const CObdDataList&     listValue,
        const bool              bCommit = false,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        otl_nocommit_stream stream;
        _open_insertOtlStream(stream, llInsertMarker, szTableName);
        try {
            for ( typename CObdDataList::const_iterator it = listValue.begin();
                it != listValue.end(); ++it )
            {
#ifdef DEBUG
                AISTD cout << *it;
#endif
                it->otl_streamOut(llInsertMarker, stream, otl_null());
            }
            stream.flush();

            if ( bCommit )
            {
                m_conn.commit();
            }
        }
        catch(otl_exception& e)
        {
            process_otlException(bCommit, e);
        }
    }

private:
    AISTD string _get_removeSQL(
        const uint64&           llConditionMarker,
        const uint64&           llConditionValueMarker,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        AISTD string strCondition(get_sqlConditionEx(llConditionMarker,
            llConditionValueMarker, szMoreCondition, false));
        AISTD string strOpTableName(get_checkedTableName(CObdData::BITS_ALL_MARKER,
            szTableName));

        AISTD string strSQL("delete ");
        process_hint(strSQL, m_strRemoveHint);
        strSQL.append(" from ");
        strSQL.append(strOpTableName);
        if ( !strCondition.empty() )
        {
            strSQL.append(" where ");
            strSQL.append(strCondition);
        }

        return strSQL;
    }

    void _open_removeOtlStream(
        otl_stream&             stream,
        const uint64&           llConditionMarker,
        const uint64&           llConditionValueMarker,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        try {
            m_strLastSQL = _get_removeSQL(llConditionMarker,
                llConditionValueMarker, szMoreCondition, szTableName);
#ifdef DEBUG
            LogAppend(DEBUG_LEVEL, "DebugInfo", m_strLastSQL.c_str());
#endif
            stream.open(1, m_strLastSQL.c_str(), m_conn);
        }
        catch(otl_exception& e)
        {
            process_otlException(false, e);
        }
    }

    int _remove(
        const AISTD string&     strCondition,
        const bool              bCommit = false,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        otl_nocommit_stream stream;
        _open_removeOtlStream(stream, 0, 0, strCondition.c_str(), szTableName);
        try {
            int iCount = stream.get_rpc();
            if ( bCommit )
            {
                m_conn.commit();
            }
            return iCount;
        }
        catch(otl_exception& e)
        {
            process_otlException(bCommit, e);
        }
#ifdef _AIX // return a pseudo value
        return -1;
#endif
    }
    
    int _remove(
        const uint64&           llConditionMarker,
        const CObdData&         cConditionValue,
        const bool              bCommit = false,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        otl_nocommit_stream stream;
        uint64 llValueMarker = cConditionValue.get_marker();
        _open_removeOtlStream(stream, llConditionMarker, llValueMarker,
            szMoreCondition, szTableName);
        try {
#ifdef DEBUG
            AISTD cout << "ConditionValue: " << cConditionValue << AISTD endl;
#endif
            cConditionValue.otl_streamOut(llValueMarker, stream);

            int iCount = stream.get_rpc();
            if ( bCommit )
            {
                m_conn.commit();
            }
            return iCount;
        }
        catch(otl_exception& e)
        {
            process_otlException(bCommit, e);
        }
#ifdef _AIX // return a pseudo value
        return -1;
#endif
    }

private:
    AISTD string _get_updateSQL(
        const uint64&           llUpdateMarker,
        const uint64&           llConditionMarker,
        const uint64&           llConditionValueMarker,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        check_markerRange(llUpdateMarker);
        check_fields(llUpdateMarker, false, true);
        AISTD string strOpTableName(get_checkedTableName(llUpdateMarker, szTableName));
        AISTD string strCondition(get_sqlConditionEx(llConditionMarker,
            llConditionValueMarker, szMoreCondition, false));
        AISTD string strFieldExpr(get_placeHolderExpr(llUpdateMarker, " = ", "f", ", "));

        AISTD string strSQL("update ");
        process_hint(strSQL, m_strUpdateHint);
        strSQL.append(strOpTableName);
        strSQL.append(" set ");
        strSQL.append(strFieldExpr);
        if ( !strCondition.empty() )
        {
            strSQL.append(" where ");
            strSQL.append(strCondition);
        }

        return strSQL;
    }

    AISTD string _get_updateSQL(
        const AISTD string&     strCustomFields,
        const uint64&           llConditionMarker,
        const uint64&           llConditionValueMarker,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        AISTD string strOpTableName(get_checkedTableName(
                CObdData::BITS_ALL_MARKER, szTableName));
        AISTD string strCondition(get_sqlConditionEx(llConditionMarker,
            llConditionValueMarker, szMoreCondition, false));

        AISTD string strSQL("update ");
        process_hint(strSQL, m_strUpdateHint);
        strSQL.append(strOpTableName);
        strSQL.append(" set ");
        strSQL.append(strCustomFields);
        if ( !strCondition.empty() )
        {
            strSQL.append(" where ");
            strSQL.append(strCondition);
        }

        return strSQL;
    }

    void _open_updateOtlStream(
        otl_stream&             stream,
        const uint64&           llUpdateMarker,
        const uint64&           llConditionMarker,
        const uint64&           llConditionValueMarker,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        try {
            m_strLastSQL = _get_updateSQL(llUpdateMarker, llConditionMarker,
                llConditionValueMarker, szMoreCondition, szTableName);
#ifdef DEBUG
            LogAppend(DEBUG_LEVEL, "DebugInfo", m_strLastSQL.c_str());
#endif
            stream.open(1, m_strLastSQL.c_str(), m_conn);
        }
        catch(otl_exception& e)
        {
            process_otlException(false, e);
        }
    }

    void _open_updateOtlStream(
        otl_stream&             stream,
        const AISTD string&     strCustomFields,
        const uint64&           llConditionMarker,
        const uint64&           llConditionValueMarker,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        try {
            m_strLastSQL = _get_updateSQL(strCustomFields, llConditionMarker,
                llConditionValueMarker, szMoreCondition, szTableName);
#ifdef DEBUG
            LogAppend(DEBUG_LEVEL, "DebugInfo", m_strLastSQL.c_str());
#endif
            stream.open(1, m_strLastSQL.c_str(), m_conn);
        }
        catch(otl_exception& e)
        {
            process_otlException(false, e);
        }
    }

    int _update(
        const uint64&           llUpdateMarker,
        const CObdData&         cObdData,
        const AISTD string&     strCondition,
        const bool              bCommit = false,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        otl_nocommit_stream stream;
        _open_updateOtlStream(stream, llUpdateMarker, 0, 0, strCondition.c_str(),
            szTableName);
        try {
            cObdData.otl_streamOut(llUpdateMarker, stream, otl_null());

            int iCount = stream.get_rpc();
            if ( bCommit )
            {
                m_conn.commit();
            }
            return iCount;
        }
        catch(otl_exception& e)
        {
            process_otlException(bCommit, e);
        }
#ifdef _AIX // return a pseudo value
        return -1;
#endif
    }

    int _update(
        const uint64&           llUpdateMarker,
        const CObdData&         cObdData,
        const uint64&           llConditionMarker,
        const CObdData&         cConditionValue,
        const bool              bCommit = false,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        otl_nocommit_stream stream;
        uint64 llValueMarker = cConditionValue.get_marker();
        _open_updateOtlStream(stream, llUpdateMarker, llConditionMarker, llValueMarker,
            szMoreCondition, szTableName);
        try {
#ifdef DEBUG
            AISTD cout << "ConditionValue: " << cConditionValue << AISTD endl;
#endif
            cObdData.otl_streamOut(llUpdateMarker, stream, otl_null());
            cConditionValue.otl_streamOut(llValueMarker, stream);

            int iCount = stream.get_rpc();
            if ( bCommit )
            {
                m_conn.commit();
            }
            return iCount;
        }
        catch(otl_exception& e)
        {
            process_otlException(bCommit, e);
        }
#ifdef _AIX // return a pseudo value
        return -1;
#endif
    }

    int _update(
        const AISTD string&     strCustomFields,
        const AISTD string&     strCondition,
        const bool              bCommit = false,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        otl_nocommit_stream stream;
        _open_updateOtlStream(stream, strCustomFields, 0, 0, strCondition.c_str(),
            szTableName);
        try {
            int iCount = stream.get_rpc();
            if ( bCommit )
            {
                m_conn.commit();
            }
            return iCount;
        }
        catch(otl_exception& e)
        {
            process_otlException(bCommit, e);
        }
#ifdef _AIX // return a pseudo value
        return -1;
#endif
    }

    int _update(
        const AISTD string&     strCustomFields,
        const uint64&           llConditionMarker,
        const CObdData&         cConditionValue,
        const bool              bCommit = false,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        otl_nocommit_stream stream;
        uint64 llValueMarker = cConditionValue.get_marker();
        _open_updateOtlStream(stream, strCustomFields, llConditionMarker, llValueMarker,
            szMoreCondition, szTableName);
        try {
#ifdef DEBUG
            AISTD cout << "ConditionValue: " << cConditionValue << AISTD endl;
#endif
            cConditionValue.otl_streamOut(llValueMarker, stream);

            int iCount = stream.get_rpc();
            if ( bCommit )
            {
                m_conn.commit();
            }
            return iCount;
        }
        catch(otl_exception& e)
        {
            process_otlException(bCommit, e);
        }
#ifdef _AIX // return a pseudo value
        return -1;
#endif
    }

private:
    // because field name in OBD struct is unique, so don't process '.' in strMarkerText
    void detect_markers(
        int&                    iColCount,
        uint64&                 llMarker,
        uint64                  pMarkers[64],
        const AISTD string&     strMarkerText)
    {
        const char* begin = strMarkerText.c_str();
        char buf[256];
        int n = (int)strMarkerText.size(), p;
        uint64 llBit;

        iColCount = 0;
        llMarker = 0;
        for ( int i = 0; i < n; ++i )
        {
            while ( begin[i] == ' ' && i < n ) ++i;
            if ( i >= n ) break;

            for ( p = 0; i < n && begin[i] != ',' && begin[i] != ' ' &&
                p < sizeof(buf) - 1; )
            {
                buf[p++] = toupper(begin[i++]);
            }
            if ( p == 0 ) continue;
            buf[p] = 0;

            llBit = 1;
            for ( int j = 0; j < CObdData::MEMBER_FIELD_COUNT; ++j, llBit <<= 1 )
            {
                if ( !strcmp(buf, CObdData::ARRAY_MEMBER_TYPE_INFO[j].m_szFieldName) )
                {
                    llMarker |= llBit;
                    pMarkers[iColCount++] = llBit;
                    llBit = 0;
                    break;
                }
            }

            if ( llBit != 0 ) // not found
            {
                throw_exception("Field not found", buf);
            }
        }
    }

    // detect marker of select otl_stream
    void detect_markers(
        int&                    iColCount,
        uint64&	                llMarker,
        uint64                  pMarkers[64],
        otl_stream&             stream)
    {
        uint64 llBit;
        otl_column_desc* desc = stream.describe_select(iColCount);
        if ( desc == 0 || iColCount <= 0 )
        {
            throw_exception("Only select OTL stream is allowed in select()");
        }

		llMarker = 0;
        for ( int i = 0; i < iColCount; ++i )
        {
            llBit = 1;
            pMarkers[i] = 0;
            for ( int j = 0; j < CObdData::MEMBER_FIELD_COUNT; ++j, llBit <<= 1 )
            {
                int iScanFlag = 0;
                for (const char* p = desc[i].name, *q = CObdData::
                    ARRAY_MEMBER_TYPE_INFO[j].m_szFieldName; iScanFlag == 0; )
                {
                    if ( *p == '.' ) // restart scan field name
                    {
                        p++;
                        q = CObdData::ARRAY_MEMBER_TYPE_INFO[j].m_szFieldName;
                    }
                    else if ( toupper(*p) == *q )
                    {
                        if ( *q == 0 )
                            iScanFlag = 1;
                        else ++p, ++q;
                    }
                    else {
                        iScanFlag = -1;
                    }
                }
                if ( iScanFlag == 1 )
                {
                    pMarkers[i] = llBit;
                    llMarker |= llBit;
                    llBit = 0;
                    break;
                }
            }

            if ( llBit != 0 ) // not found
            {
                throw_exception("Can not find filed: ", desc[i].name);
            }
        }
    }

    AISTD string _get_selectSQL(
        const uint64&           llSelectMarker,
        const uint64&           llConditionMarker,
        const uint64&           llConditionValueMarker,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        bool bIsMultiTableOperation = !is_inSameTable(llSelectMarker);
        check_markerRange(llSelectMarker);
        check_fields(llSelectMarker, false, !bIsMultiTableOperation);
        AISTD string strOpTableName(get_checkedTableName(llSelectMarker, szTableName));

        AISTD string strCondition(get_sqlConditionEx(llConditionMarker,
            llConditionValueMarker, szMoreCondition, bIsMultiTableOperation));
        AISTD string strFieldExpr(get_dbFieldNames(llSelectMarker,
            bIsMultiTableOperation));

        AISTD string strSQL("select ");
        process_hint(strSQL, m_strSelectHint);
        strSQL.append(strFieldExpr);
        strSQL.append(" from ");
        strSQL.append(strOpTableName);
        if ( !strCondition.empty() )
        {
            strSQL.append(" ");
            if ( is_partOfWhereClause(strCondition) )
                strSQL.append("where ");
            strSQL.append(strCondition);
        }

        return strSQL;
    }

    void _open_selectOtlStream(
        otl_stream&             stream,
        const uint64&           llSelectMarker,
        const uint64&           llConditionMarker,
        const uint64&           llConditionValueMarker,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        try {
            m_strLastSQL = _get_selectSQL(llSelectMarker, llConditionMarker,
                llConditionValueMarker, szMoreCondition, szTableName);
#ifdef DEBUG
            LogAppend(DEBUG_LEVEL, "DebugInfo", m_strLastSQL.c_str());
#endif
            stream.open(m_iSelectBufferSize, m_strLastSQL.c_str(), m_conn);
        }
        catch(otl_exception& e)
        {
            process_otlException(false, e);
        }
    }

    void _select(
        CObdDataList&           listResult,
        const uint64&           llSelectMarker,
        const AISTD string&     strCondition,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        otl_nocommit_stream stream;
        _open_selectOtlStream(stream, llSelectMarker, 0, 0, strCondition.c_str(),
            szTableName);
        otl_streamInList(listResult, llSelectMarker, stream);
    }

    void _select(
        CObdDataList&           listResult,
        const uint64&           llSelectMarker,
        const uint64&           llConditionMarker,
        const CObdData&         cConditionValue,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        otl_nocommit_stream stream;
        uint64 llValueMarker = cConditionValue.get_marker();
        _open_selectOtlStream(stream, llSelectMarker, llConditionMarker, llValueMarker,
            szMoreCondition, szTableName);
        try {
#ifdef DEBUG
            AISTD cout << "ConditionValue: " << cConditionValue << AISTD endl;
#endif
            cConditionValue.otl_streamOut(llValueMarker, stream);
            otl_streamInList(listResult, llSelectMarker, stream);
        }
        catch(otl_exception& e)
        {
            process_otlException(false, e);
        }
    }

public:
    //! constructor of ob_kernel
    /*!
     \param conn a otl_connect to finish most DB operations
     \param strSchemaName schema name of table
     \param iInsertBufferSize buffer size for insert operation
     \param iSelectBufferSize buffer size for select operation

     example:
     \code
     #include "ob_kernel.h"
     ......
     typedef ob_kernel<SSampleList> CSampleKernel;
     otl_connect conn;
     ......
     CSampleKernel cSampleKernel(conn, "OBDEMO");
     \endcode
    */
    ob_kernel(
        otl_connect& conn,
        const AISTD string strSchemaName,
        const int iSelectBufferSize = 50,
        const int iInsertBufferSize = 50) :
            m_conn(conn),
            m_strSchemaName(strSchemaName),
            m_iInsertBufferSize(iInsertBufferSize),
            m_iSelectBufferSize(iSelectBufferSize)
    {
    }

/** @defgroup group_common_otl common otl_stream based functions
 *  common otl_stream based functions for list stream in & stream out
 *  @ingroup group_ob_kernel
 *  @{
 */
public:
    //! get a list from otl_stream, getting field is indicated by llMarker
    /*!
     \param listValue a list to hold getted values
     \param llMarker field marker
     \param stream a otl_stream to read data from
     \throw CBSErrorMsg throwed exception when error occurs
     \attention fields are streamed in in order of llMarker bit, from low to high
     \remarks using marker(uint64) instead of marker text is effeciency consideration
     \sa otl_streamInListEx()

     example:
     \code
     SSampleList listSample;
     otl_stream stream(50, "select id, name, age from sample", conn);
     ob_kernel<SSampleList>::otl_streamInList(listSample, SSample::BIT_ID |
        SSample::BIT_NAME | SSample::BIT_AGE, stream);
     \endcode
    */
    void otl_streamInList(
        CObdDataList&           listValue,
        const uint64&           llMarker,
        otl_stream&             stream)
            throw (CBSErrorMsg)
    {
        if ( *stream.adb == 0 )
        {
            throw_exception("Bad otl_stream connection");
        }
        try {
            while ( !stream.eof() )
            {
                CObdData cObdData;
                cObdData.otl_streamIn(llMarker, stream);
                listValue.insert(listValue.end(), cObdData);
            }
        }
        catch(otl_exception& e)
        {
            process_otlException(e);
        }
    }

    //! put a list data into a otl_stream, putting field is indicated by llMarker
    /*!
     \param llMarker field marker
     \param stream a otl_stream to write data to
     \param listValue a list holding output data
     \param bCommit whether commit to database after all data are writen
     \param bOutputNull whether put a otl_null when a field is marked by llMarker
            while it has not been assigned a value yet
     \throw CBSErrorMsg throwed exception when error occurs
     \attention fields are streamed in in order of llMarker bit, from low to high
     \remarks using marker(uint64) instead of marker text is effeciency consideration
     \sa otl_streamOutListEx()

     example:
     \code
     SSampleList listSample;
     otl_stream stream;
     ......
     ob_kernel<SSampleList>::otl_streamOutList(SSample::BIT_ID | SSample::BIT_NAME |
        SSample::BIT_AGE, stream, listSample);
     \endcode
    */
    void otl_streamOutList(
        const uint64&           llMarker,
        otl_stream&             stream,
        const CObdDataList&     listValue,
        const bool              bCommit = false,
        const bool              bOutputNull = false)
            throw (CBSErrorMsg)
    {
        if ( *stream.adb == 0 )
        {
            throw_exception("Bad otl_stream connection");
        }
        try {
            otl_null cNull;
            for ( typename CObdDataList::const_iterator it = listValue.begin();
                it != listValue.end(); ++it )
            {
                if ( bOutputNull )
                {
                    it->otl_streamOut(llMarker, stream, cNull);
                }
                else {
                    it->otl_streamOut(llMarker, stream);
                }
            }

            if ( bCommit )
            {
                (*stream.adb)->commit();
            }
        }
        catch(otl_exception& e)
        {
            process_otlException(bCommit, e);
        }
    }

    //! get a list from otl_stream, getting field is indicated by marker text
    /*!
     \param listValue a list to hold getted values
     \param strMarkerText marker text, sucha as "ID, NAME"
     \param stream a otl_stream to read data from
     \throw CBSErrorMsg throwed exception when error occurs
     \remarks restriction of marker order is eliminated in this member function
     \sa otl_streamInList()

     example:
     \code
     SSampleList listSample;
     otl_stream stream(50, "select id, name, age from sample", conn);
     ob_kernel<SSampleList>::otl_streamInListEx(listSample, "ID, NAME, AGE", stream);
     \endcode
    */
    void otl_streamInListEx(
        CObdDataList&           listValue,
        const AISTD string&     strMarkerText,
        otl_stream&             stream)
            throw (CBSErrorMsg)
    {
        if ( *stream.adb == 0 )
        {
            throw_exception("Bad otl_stream connection");
        }

        int iColCount;
        uint64 llUsedMarker, pMarkers[64];
        detect_markers(iColCount, llUsedMarker, pMarkers, strMarkerText);

        try {
            while ( !stream.eof() )
            {
                CObdData cObdData;
                uint64 llMarker = 0;
                for ( int i = 0; i < iColCount; ++i )
                {
                    uint64 llBit = pMarkers[i];
                    cObdData.otl_streamIn(llBit, stream);
                    llMarker |= cObdData.get_marker();
                }
                cObdData.set_marker(llMarker);
                cObdData.set_usedSet(llUsedMarker);
                listValue.insert(listValue.end(), cObdData);
            }
        }
        catch(otl_exception& e)
        {
            process_otlException(e);
        }
    }

    //! put a list data into a otl_stream, putting field is indicated by marker text
    /*!
     \param strMarkerText marker text, sucha as "ID, NAME"
     \param stream a otl_stream to write data to
     \param listValue a list holding output data
     \param bCommit whether commit to database after all data are writen
     \param bOutputNull whether put a otl_null when a field is marked by llMarker
            while it has not been assigned a value yet
     \throw CBSErrorMsg throwed exception when error occurs
     \remarks restriction of marker order is eliminated in this member function
     \sa otl_streamOutList

     example:
     \code
     SSampleList listSample;
     otl_stream stream;
     ......
     ob_kernel<SSampleList>::otl_streamOutListEx("ID, NAME, AGE", stream, listSample);
     \endcode
    */
    void otl_streamOutListEx(
        const AISTD string&     strMarkerText,
        otl_stream&             stream,
        const CObdDataList&     listValue,
        const bool              bCommit = false,
        const bool              bOutputNull = false)
            throw (CBSErrorMsg)
    {
        if ( *stream.adb == 0 )
        {
            throw_exception("Bad otl_stream connection");
        }

        int iColCount;
        uint64 llMarker, pMarkers[64];
        detect_markers(iColCount, llMarker, pMarkers, strMarkerText);

        try {
            otl_null cNull;
            for ( typename CObdDataList::const_iterator it = listValue.begin();
                it != listValue.end(); ++it )
            {
                for ( int i = 0; i < iColCount; ++i )
                {
                    uint64 llBit = pMarkers[i];
                    if ( bOutputNull )
                    {
                        it->otl_streamOut(llBit, stream, cNull);
                    }
                    else {
                        it->otl_streamOut(llBit, stream);
                    }
                }
            }

            if ( bCommit )
            {
                (*stream.adb)->commit();
            }
        }
        catch(otl_exception& e)
        {
            process_otlException(bCommit, e);
        }
    }

/** @} */

/** @defgroup group_auxiliary auxiliary functions
 *  auxiliary functions for insert/remove/update/select when writing direct
 *  OTL operations
 *  @ingroup group_ob_kernel
 *  @{
 */
public:
    //! execute a constant SQL statement
    /*!
     \param strSQL a SQL statement
     \param bCommit whether commit to database
     \return amount of deleted records, return -1 means a error
     \throw CBSErrorMsg throwed exception when error occurs
     */
    int direct_exec(
        const AISTD string&     strSQL,
        const bool              bCommit = false)
            throw (CBSErrorMsg)
    {
        otl_nocommit_stream os;
        m_strLastSQL = strSQL;
        try {
#ifdef DEBUG
            LogAppend(DEBUG_LEVEL, "DebugInfo", m_strLastSQL.c_str());
#endif        	
            otl_cursor::direct_exec(m_conn, m_strLastSQL.c_str());
            int iCount = os.get_rpc();
            if ( bCommit )
            {
                m_conn.commit();
            }
            return iCount;
        }
        catch(otl_exception& e)
        {
            process_otlException(bCommit, e);
        }
#ifdef _AIX // return a pseudo value
        return -1;
#endif
    }

    //! format field name from uint64 marker, such as "ID, NAME, AGE"
    /*!
     \param llMarker field marker
     \param bAddTablePrefix whether add table name (followed with a '.') as prefix
     \param szSeparator separator of between field names
     \return formated field name

     example:
     \code
     AISTD string strMarker = ob_kernel<SSampleList>::get_dbFieldNames(
        SSample::BIT_ID | SSample::BIT_NAME | SSample::BIT_AGE);
     // strMarker would has value: "ID, NAME, AGE"
     \endcode
    */
    AISTD string get_dbFieldNames(
        const uint64&           llMarker,
        const bool              bAddTablePrefix = false,
        const char*             szSeparator = ", ")
    {
        AISTD string strResult;
        uint64 llBit = 1;

        for ( int i = 0; i < CObdData::MEMBER_FIELD_COUNT; ++i, llBit <<= 1 )
        {
            if ( (llMarker & llBit) == 0 ) continue;

            if ( !strResult.empty() && szSeparator != 0 )
            {
                strResult.append(szSeparator);
            }

            if ( bAddTablePrefix )
            {
                int idx = CObdData::ARRAY_MEMBER_TYPE_INFO[i].m_nTableNameIndex;
                if ( idx >= 0 )
                {
                    strResult.append(CObdData::ARRAY_IMPORT_TABLES[idx]);
                    strResult.append(1, '.');
                }
            }

            strResult.append(CObdData::ARRAY_MEMBER_TYPE_INFO[i].m_szFieldName);
        }

        return strResult;
    }

    //! get all field marker of a table in a OBD struct
    /*!
     \param strTableName table name
     \return field marker of this table
     */
    uint64 get_markerOfTable(
        const AISTD string&     strTableName)
    {
        int iTableIndex = get_tableIndex(strTableName);
        uint64 llMarker = 0;

        if ( iTableIndex >= 0 )
        {
            uint64 llBit = 1;
            for ( int i = 0; i < CObdData::MEMBER_FIELD_COUNT; ++i, llBit <<= 1 )
            {
                if ( CObdData::ARRAY_MEMBER_TYPE_INFO[i].m_nTableNameIndex == iTableIndex )
                {
                    llMarker |= llBit;
                }
            }
        }
        else llMarker = CObdData::BITS_ALL_MARKER;

        return llMarker;
    }

    //! format OTL place holder string from marker, such as ":1<short>, :2<int>"
    /*!
     \param llMarker field marker
     \param szPrefix prefix of each place holder
     \param szSeparator separator of between place holders
     \return formated place holder

     example:
     \code
     AISTD string strPlaceHolders = ob_kernel<SSampleList>::get_placeHolders(
        SSample::BIT_ID | SSample::BIT_NAME | SSample::BIT_AGE, "f");
     // strPlaceHolders would has value: ":f0<int>, :f1<char[24]>, :f2<float>"
     \endcode
     */
    AISTD string get_placeHolders(
        const uint64&           llMarker,
        const char*             szPrefix = "",
        const char*             szSeparator = ", ")
    {
        char buf[256];
        const char* pPrefix = szPrefix == 0 ? "" : szPrefix;
        AISTD string strResult;
        uint64 llBit = 1;

        for ( int i = 0; i < CObdData::MEMBER_FIELD_COUNT; ++i, llBit <<= 1 )
        {
            if ( (llMarker & llBit) == 0 ) continue;
            switch ( CObdData::ARRAY_MEMBER_TYPE_INFO[i].m_nObdTypeId )
            {
                case OBD_CHAR:
                case OBD_STRING:
                    {
                        int nSize = CObdData::ARRAY_MEMBER_TYPE_INFO[i].m_iDataSize;
                        if ( nSize == 0 ) nSize = 256;
                        else nSize++;
                        sprintf(buf, ":%s%d<char[%d]>", pPrefix, i, nSize);
                    }
                    break;
                case OBD_INT16:
                    sprintf(buf, ":%s%d<short>", pPrefix, i);
                    break;
                case OBD_INT32:
                    sprintf(buf, ":%s%d<int>", pPrefix, i);
                    break;
                case OBD_INT64:
                case OBD_DOUBLE:
                    sprintf(buf, ":%s%d<double>", pPrefix, i);
                    break;
                case OBD_FLOAT:
                    sprintf(buf, ":%s%d<float>", pPrefix, i);
                    break;
                case OBD_DATE:
                case OBD_TIME:
                case OBD_DATETIME:
                    sprintf(buf, ":%s%d<timestamp>", pPrefix, i);
                    break;
                default:
                    continue;
            }

            if ( !strResult.empty() && szSeparator != 0 )
            {
                strResult.append(szSeparator);
            }
            strResult.append(buf);
        }

        return strResult;
    }

    //! format OTL place holder expression from marker, such as "name=:1<char[23]>"
    /*!
     \param llMarker field marker
     \param szOperator operator between field name and palce holder
     \param szPrefix prefix of each place holder
     \param szSeparator separator between each expression
     \param bAddTablePrefix whether add table name as expression's prefix
     \return formated expression

     example:
     \code
     AISTD string strExpr = ob_kernel<SSampleList>::get_placeHolderExpr(
        SSample::BIT_ID | SSample::BIT_NAME | SSample::BIT_AGE);
     // strExpr's value: "ID = :0<int> and NAME = :1<char[24]> and AGE = :2<float>"
     \endcode
     */
    AISTD string get_placeHolderExpr(
        const uint64&           llMarker,
        const char*             szOperator = " = ",
        const char*             szPrefix = "",
        const char*             szSeparator = " and ",
        const bool              bAddTablePrefix = false)
    {
        AISTD string strResult;
        uint64 llBit = 1;

        for ( int i = 0; i < CObdData::MEMBER_FIELD_COUNT; ++i, llBit <<= 1 )
        {
            if ( (llMarker & llBit) == 0 ) continue;
            if ( !strResult.empty() && szSeparator != 0 )
            {
                strResult.append(szSeparator);
            }
            strResult.append(get_dbFieldNames(llBit, bAddTablePrefix));
            if ( szOperator != 0 )
            {
                strResult.append(szOperator);
            }
            strResult.append(get_placeHolders(llBit, szPrefix));
        }

        return strResult;
    }

    //! format OTL place holder expression from marker, such as "name=:1<char[23]>", process "is null"
    /*!
     \param llTotalMarker total field marker which including llValueMarker
     \param llValueMarker field marker indicates values
     \param szNonvalueExpr expression for non-value marker
     \param szOperator operator between field name and palce holder
     \param szPrefix prefix of each place holder
     \param szSeparator separator between each expression
     \param bAddTablePrefix whether add table name as expression's prefix
     \return formated expression

     example:
     \code
     AISTD string strExpr = ob_kernel<SSampleList>::get_placeHolderExpr(
        SSample::BIT_ID | SSample::BIT_NAME | SSample::BIT_AGE, SSample::BIT_ID | SSample::BIT_NAME);
     // strExpr's value: "ID = :0<int> and NAME = :1<char[24]> and AGE is null"
     \endcode
     */
    AISTD string get_placeHolderExprEx(
        const uint64&           llTotalMarker,
        const uint64&           llValueMarker,
        const char*             szNonvalueExpr = " is null ",
        const char*             szOperator = " = ",
        const char*             szPrefix = "",
        const char*             szSeparator = " and ",
        const bool              bAddTablePrefix = false)
    {
        AISTD string strResult;
        uint64 llBit = 1;

        for ( int i = 0; i < CObdData::MEMBER_FIELD_COUNT; ++i, llBit <<= 1 )
        {
            if ( (llTotalMarker & llBit) == 0 ) continue;
            if ( !strResult.empty() && szSeparator != 0 )
            {
                strResult.append(szSeparator);
            }
            strResult.append(get_dbFieldNames(llBit, bAddTablePrefix));
            if ( llValueMarker & llBit ) // valued marker
            {
                if ( szOperator != 0 )
                {
                    strResult.append(szOperator);
                }
                strResult.append(get_placeHolders(llBit, szPrefix));
            }
            else { // non-value
                strResult.append(szNonvalueExpr);
            }
        }

        return strResult;
    }

    //! convert text marker to uint64, such as "ID, NAME, AGE"
    /*!
     \param strText text marker, such as "ID, NAME, AGE"
     \param szTableName not used now
     \return converted marker
     \throw CBSErrorMsg throwed exception when error occurs

     example:
     \code
     uint64 llMarker = ob_kernel<SSampleList>::marker_byText("ID, NAME, AGE");
     // llMarker equals to SSample::BIT_ID | SSample::BIT_NAME | SSample::BIT_AGE
     \endcode
     */
    uint64 marker_byText(
        const AISTD string&     strText,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        const char* begin = strText.c_str();
        char buf[256];
        int n = (int)strText.size(), p;
        uint64 llMarker = 0, llBit;

        for ( int i = 0; i < n; ++i )
        {
            while ( i < n && begin[i] == ' ' ) ++i;
            if ( i >= n ) break;

            for ( p = 0; i < n && begin[i] != ',' && begin[i] != ' ' &&
                p < sizeof(buf) - 1; )
            {
                buf[p++] = toupper(begin[i++]);
            }
            if ( p == 0 ) continue;
            buf[p] = 0;

            llBit = 1;
            for ( int j = 0; j < CObdData::MEMBER_FIELD_COUNT; ++j, llBit <<= 1 )
            {
                if ( !strcmp(buf, CObdData::ARRAY_MEMBER_TYPE_INFO[j].m_szFieldName) )
                {
                    llMarker |= llBit;
                    llBit = 0;
                    break;
                }
            }

            if ( llBit != 0 ) // not found
            {
                throw_exception("Field not found", buf);
            }
        }

        return llMarker;
    }

    //! convert uint64 to text marker, such as "ID, NAME, AGE"
    /*!
     \param llMarker a int64 marker
     \param szSeparator separator between each marker text
     \param szPrefix prefix of each marker text
     \return marker text

     example:
     \code
     uint64 llMarker = SSample::BIT_ID | SSample::BIT_NAME | SSample::BIT_AGE;
     AISTD string strMarker = ob_kernel<SSampleList>::text_byMarker(llMarker, ",");
     // strMarker equals to "ID, NAME, AGE"
     \endcode
     */
    AISTD string text_byMarker(
        const uint64&     llMarker,
        const char*             szSeparator = 0,
        const char*             szPrefix = 0)
    {
        AISTD string strMarker;
        uint64 llBit = 1;
        for ( int j = 0; j < CObdData::MEMBER_FIELD_COUNT; ++j, llBit <<= 1 )
        {
            if ( (llMarker & llBit) == 0 )
                continue;

            AISTD string s;
            if ( strMarker.size() > 0 ) // process separator
            {
                s = szSeparator == NULL ? " " : szSeparator;
            }
            if ( szPrefix != NULL )
                s.append(szPrefix);
            s.append(CObdData::ARRAY_MEMBER_TYPE_INFO[j].m_szFieldName);

            strMarker.append(s);
        }
        return strMarker;
    }

/** @} */

/** @defgroup group_insert insert functions
 *  a series functions for OTL based insert operations
 *  @ingroup group_ob_kernel
 *  @{
 */
public:
    //! format a insert SQL
    /*!
     \param strInsertFields marker text indicating which fields should be inserted
     \param szTableName new table name which override default table name
     \return insert SQL
     \throw CBSErrorMsg throwed exception when error occurs
     */
    AISTD string get_insertSQL(
        const AISTD string&     strInsertFields,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llInsertMarker(marker_byText(strInsertFields));
        return _get_insertSQL(llInsertMarker, szTableName);
    }

    //! open a otl_stream for insert
    /*!
     \param stream a otl_strema to open
     \param strInsertFields marker text indicating which fields should be inserted
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void open_insertOtlStream(
        otl_stream&             stream,
        const AISTD string&     strInsertFields,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llInsertMarker(marker_byText(strInsertFields));
        _open_insertOtlStream(stream, llInsertMarker, szTableName);
    }

    //! insert all members of cObdData into database
    /*!
     \param cObdData data to be inserted
     \param bCommit whether commit to database
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void insert(
        const CObdData&         cObdData,
        const bool              bCommit = false,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
#ifdef OBK_USE_USED_MARKER
        _insert(cObdData.get_usedSet(), cObdData, bCommit, szTableName);
#else
        _insert(CObdData::BITS_ALL_MARKER, cObdData, bCommit, szTableName);
#endif
    }

#ifndef ABOUT_OBSOLETE_2004_8_12
    //! insert cObdData into database, inserting field is specified by strInsertFields
    /*!
     \param strInsertFields inserting marker text of inserting field
     \param cObdData data need to be inserted
     \param bCommit whether commit to database
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void insert(
        const AISTD string&     strInsertFields,
        const CObdData&         cObdData,
        const bool              bCommit = false,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llInsertMarker(marker_byText(strInsertFields));
        _insert(llInsertMarker, cObdData, bCommit, szTableName);
    }
#endif
    //! insert all members of listValue into database
    /*!
     \param listValue a list of data to be inserted
     \param bCommit whether commit to database
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void insert(
        const CObdDataList&     listValue,
        const bool              bCommit = false,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
#ifdef OBK_USE_USED_MARKER
        if ( listValue.size() == 0 )
            return ;
        uint64 llInsertMarker = listValue.begin()->get_usedSet();
        for ( typename CObdDataList::const_iterator it = listValue.begin();
            it != listValue.end(); ++it )
         {
            	if ( it->get_usedSet() != llInsertMarker )
            	    throw_exception("when inserting a list, all UsedSet of list item MUST be same");
         }
        _insert_list(llInsertMarker, listValue, bCommit, szTableName);
#else
        _insert_list(CObdData::BITS_ALL_MARKER, listValue, bCommit, szTableName);
#endif
    }

#ifndef ABOUT_OBSOLETE_2004_8_12
    //! insert listValue into database, inserting field is specified by strInsertFields
    /*!
     \param strInsertFields inserting marker text of inserting field
     \param listValue a list of data need to be inserted
     \param bCommit whether commit to database
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void insert(
        const AISTD string&     strInsertFields,
        const CObdDataList&     listValue,
        const bool              bCommit = false,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llInsertMarker(marker_byText(strInsertFields));
        _insert_list(llInsertMarker, listValue, bCommit, szTableName);
    }
#endif
/** @} */

/** @defgroup group_delete delete functions
 *  a series functions for OTL based delete operations.
 *  since delete is a c++ keyword, the replacer is remove, :(
 *  @ingroup group_ob_kernel
 *  @{
 */
public:
    //! format a delete SQL
    /*!
     \param strConditionFields marker text indicating the fields should be used
            as part of equal condition in WHERE clause(but excluded WHERE)
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \return delete SQL
     \throw CBSErrorMsg throwed exception when error occurs
     */
    AISTD string get_removeSQL(
        const AISTD string&     strConditionFields,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llConditionMarker(marker_byText(strConditionFields));
        uint64 llConditionValueMarker = llConditionMarker;
        return _get_removeSQL(llConditionMarker, llConditionValueMarker, szMoreCondition, szTableName);
    }

    //! open a otl_stream for delete
    /*!
     \param stream a otl_stream to open
     \param strConditionFields marker text indicating the fields should be used
            as part of equal condition in WHERE clause(but excluded WHERE)
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void open_removeOtlStream(
        otl_stream&             stream,
        const AISTD string&     strConditionFields,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llConditionMarker(marker_byText(strConditionFields));
        uint64 llConditionValueMarker = llConditionMarker;
        _open_removeOtlStream(stream, llConditionMarker, llConditionValueMarker,
            szMoreCondition, szTableName);
    }

    //! delete some records using a simple condition
    /*!
     \param strCondition customized condition
     \param bCommit whether commit to database
     \param szTableName new table name which override default table name
     \return amount of deleted records
     \throw CBSErrorMsg throwed exception when error occurs
     */
    int remove(
        const AISTD string&     strCondition,
        const bool              bCommit = false,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        return _remove(strCondition, bCommit, szTableName);
    }

    //! delete records whose fields equal to cConditionValue's members
    /*!
     \param cConditionValue condition value
     \param bCommit whether commit to database
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \return amount of deleted records
     \throw CBSErrorMsg throwed exception when error occurs
     */
    int remove(
        const CObdData&         cConditionValue,
        const bool              bCommit = false,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
#ifdef OBK_USE_USED_MARKER
        return _remove(cConditionValue.get_usedSet(), cConditionValue,
            bCommit, szMoreCondition, szTableName);
#else
        return _remove(cConditionValue.get_marker(), cConditionValue,
            bCommit, szMoreCondition, szTableName);
#endif
    }

#ifndef ABOUT_OBSOLETE_2004_8_12
    //! delete records whose fields equal to cConditionValue's members
    //! specified by a marker text(strConditionFields)
    /*!
     \param strConditionFields marker text indicating the fields should be used
            as part of equal condition in WHERE clause(but excluded WHERE)
     \param cConditionValue condition value
     \param bCommit whether commit to database
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \return amount of deleted records
     \throw CBSErrorMsg throwed exception when error occurs
     */
    int remove(
        const AISTD string&     strConditionFields,
        const CObdData&         cConditionValue,
        const bool              bCommit = false,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llConditionMarker(marker_byText(strConditionFields));
        return _remove(llConditionMarker, cConditionValue, bCommit,
            szMoreCondition, szTableName);
    }
#endif
/** @} */

/** @defgroup group_update update functions
 *  a series functions for OTL based update operations.
 *  @ingroup group_ob_kernel
 *  @{
 */
public:
    //! format a update SQL
    /*!
     \param strUpdateFields marker text indicating the fields should be updated
     \param strConditionFields marker text indicating which field should be used
            as part of equal condition in WHERE clause(but excluded WHERE)
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \return update SQL
     \throw CBSErrorMsg throwed exception when error occurs
     */
    AISTD string get_updateSQL(
        const AISTD string&     strUpdateFields,
        const AISTD string&     strConditionFields,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llUpdateMarker(marker_byText(strUpdateFields));
        uint64 llConditionMarker(marker_byText(strConditionFields));
        uint64 llConditionValueMarker = llConditionMarker;
        return _get_updateSQL(llUpdateMarker, llConditionMarker, llConditionValueMarker,
            szMoreCondition, szTableName);
    }

    //! open a otl_stream for update
    /*!
     \param strUpdateFields marker text indicating the fields should be updated
     \param stream a otl_stream to open
     \param strConditionFields marker text indicating the fields should be used
            as part of equal condition in WHERE clause(but excluded WHERE)
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void open_updateOtlStream(
        otl_stream&             stream,
        const AISTD string&     strUpdateFields,
        const AISTD string&     strConditionFields,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llUpdateMarker(marker_byText(strUpdateFields));
        uint64 llConditionMarker(marker_byText(strConditionFields));
        uint64 llConditionValueMarker = llConditionMarker;
        _open_updateOtlStream(stream, llUpdateMarker, llConditionMarker,
            llConditionValueMarker, szMoreCondition, szTableName);
    }

    //! update record whose new value specified in cObdData's member,
    //! using strCondition as WHERE condition
    /*!
     \param cObdData updating value
     \param strCondition WHERE clause(but excluded WHERE)
     \param bCommit whether commit to database
     \param szTableName new table name which override default table name
     \return amount of updated records
     \throw CBSErrorMsg throwed exception when error occurs
     */
    int update(
        const CObdData&         cObdData,
        const AISTD string&     strCondition,
        const bool              bCommit = false,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
#ifdef OBK_USE_USED_MARKER
        return _update(cObdData.get_usedSet(), cObdData,
            strCondition, bCommit, szTableName);
#else
        return _update(cObdData.get_marker(), cObdData,
            strCondition, bCommit, szTableName);
#endif
    }

    //! update record whose new value specified by a custom expression in
    //! set clause, such as "f1 = f1 + 1", using strCondition as WHERE condition
    /*!
     \param strCustomFields custom set expression
     \param strCondition WHERE clause(but excluded WHERE)
     \param bCommit whether commit to database
     \param szTableName new table name which override default table name
     \return amount of updated records
     \throw CBSErrorMsg throwed exception when error occurs
     */
    int update(
        const AISTD string&     strCustomFields,
        const AISTD string&     strCondition,
        const bool              bCommit = false,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        return _update(strCustomFields, strCondition, bCommit, szTableName);
    }

    //! update record whose new value specified in cObdData's member,
    //! WHERE clause(but excluded WHERE) is composed by cConditionValue and szMoreCondition
    /*!
     \param cObdData updating value
     \param cConditionValue condition value
     \param bCommit whether commit to database
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \return amount of updated records
     \throw CBSErrorMsg throwed exception when error occurs
     */
    int update(
        const CObdData&         cObdData,
        const CObdData&         cConditionValue,
        const bool              bCommit = false,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
#ifdef OBK_USE_USED_MARKER
        return _update(cObdData.get_usedSet(), cObdData, cConditionValue.get_usedSet(),
            cConditionValue, bCommit, szMoreCondition, szTableName);
#else
        return _update(cObdData.get_marker(), cObdData, cConditionValue.get_marker(),
            cConditionValue, bCommit, szMoreCondition, szTableName);
#endif
    }

    //! update record whose new value specified by a custom expression in
    //! set clause, such as "f1 = f1 + 1", using strCondition as WHERE condition
    /*!
     \param strCustomFields custom set expression
     \param cConditionValue condition value
     \param bCommit whether commit to database
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \return amount of updated records
     \throw CBSErrorMsg throwed exception when error occurs
     */
    int update(
        const AISTD string&     strCustomFields,
        const CObdData&         cConditionValue,
        const bool              bCommit = false,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
#ifdef OBK_USE_USED_MARKER
        return _update(strCustomFields, cConditionValue.get_usedSet(), cConditionValue,
            bCommit, szMoreCondition, szTableName);
#else
        return _update(strCustomFields, cConditionValue.get_marker(), cConditionValue,
            bCommit, szMoreCondition, szTableName);
#endif
    }

#ifndef ABOUT_OBSOLETE_2004_8_12
    //! update record whose new value specified in cObdData's member
    //! (by strUpdateFields), using strCondition as WHERE condition
    /*!
     \param strUpdateFields marker text indicating the fields should be updated
     \param cObdData updating value
     \param strCondition WHERE clause(but excluded WHERE)
     \param bCommit whether commit to database
     \param szTableName new table name which override default table name
     \return amount of updated records
     \throw CBSErrorMsg throwed exception when error occurs
     */
    int update(
        const AISTD string&     strUpdateFields,
        const CObdData&         cObdData,
        const AISTD string&     strCondition,
        const bool              bCommit = false,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llUpdateMarker(marker_byText(strUpdateFields));
        return update(llUpdateMarker, cObdData, strCondition, bCommit,
            szTableName);
    }

    //! update record whose new value specified in cObdData's member,
    //! (by strUpdateFields), WHERE clause(but excluded WHERE) is composed by cConditionValue
    //! and szMoreCondition
    /*!
     \param strUpdateFields marker text indicating the fields should be updated
     \param cObdData updating value
     \param cConditionValue condition value
     \param bCommit whether commit to database
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \return amount of updated records
     \throw CBSErrorMsg throwed exception when error occurs
     */
    int update(
        const AISTD string&     strUpdateFields,
        const CObdData&         cObdData,
        const CObdData&         cConditionValue,
        const bool              bCommit = false,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llUpdateMarker(marker_byText(strUpdateFields));
#ifdef OBK_USE_USED_MARKER
        return update(llUpdateMarker, cObdData, cConditionValue.get_usedSet(),
        	cConditionValue, bCommit, szMoreCondition, szTableName);
#else
        return update(llUpdateMarker, cObdData, cConditionValue.get_marker(),
        	cConditionValue, bCommit, szMoreCondition, szTableName);
#endif
    }

    //! update record whose new value specified in cObdData's member,
    //! (by strUpdateFields), WHERE clause(but excluded WHERE) is composed by cConditionValue
    //! and szMoreCondition
    /*!
     \param strUpdateFields marker text indicating the fields should be updated
     \param cObdData updating value
     \param strConditionFields marker text indication the fields in cConditionValue
     \param cConditionValue condition value
     \param bCommit whether commit to database
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \return amount of updated records
     \throw CBSErrorMsg throwed exception when error occurs
     */
    int update(
        const AISTD string&     strUpdateFields,
        const CObdData&         cObdData,
        const AISTD string&     strConditionFields,
        const CObdData&         cConditionValue,
        const bool              bCommit = false,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llUpdateMarker(marker_byText(strUpdateFields));
        uint64 llConditionMarker(marker_byText(strConditionFields));
        return update(llUpdateMarker, cObdData, llConditionMarker,
            cConditionValue, bCommit, szMoreCondition, szTableName);
    }
#endif
/** @} */

/** @defgroup group_select select functions
 *  a series functions for OTL based select operations.
 *  @ingroup group_ob_kernel
 *  @{
 */
public:
    //! format a select SQL
    /*!
     \param strSelectFields marker text indicating the fields should be selected
     \param strCondition WHERE clause(but excluded WHERE) of SELECT
     \param szTableName new table name which override default table name
     \return select SQL
     \throw CBSErrorMsg throwed exception when error occurs
     */
    AISTD string get_selectSQL(
        const AISTD string&     strSelectFields,
        const AISTD string&     strCondition,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llSelectMarker(marker_byText(strSelectFields));
        return _get_selectSQL(llSelectMarker, 0, 0, strCondition.c_str(),
            szTableName);
    }

    //! format a select SQL
    /*!
     \param strSelectFields marker text indicating the fields should be selected
     \param strConditionFields marker text indicating which field should be used
            as part of equal condition in WHERE clause(but excluded WHERE)
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \return select SQL
     \throw CBSErrorMsg throwed exception when error occurs
     */
    AISTD string get_selectSQLEx(
        const AISTD string&     strSelectFields,
        const AISTD string&     strConditionFields,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llSelectMarker(marker_byText(strSelectFields));
        uint64 llConditionMarker(marker_byText(strConditionFields));
        uint64 llConditionValueMarker = llConditionMarker;
        return _get_selectSQL(llSelectMarker, llConditionMarker, llConditionValueMarker,
            szMoreCondition, szTableName);
    }

    //! open a otl_stream for select
    /*!
     \param stream a otl_stream to open
     \param strSelectFields marker text indicating the fields should be selected
     \param strCondition WHERE clause(but excluded WHERE) of SELECT
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void open_selectOtlStream(
        otl_stream&             stream,
        const AISTD string&     strSelectFields,
        const AISTD string&     strCondition,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llSelectMarker(marker_byText(strSelectFields));
        _open_selectOtlStream(stream, llSelectMarker, 0, 0, strCondition.c_str(),
            szTableName);
    }

    //! open a otl_stream for select
    /*!
     \param stream a otl_stream to open
     \param strSelectFields marker text indicating the fields should be selected
     \param strConditionFields marker text indicating which field should be used
            as part of equal condition in WHERE clause(but excluded WHERE)
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void open_selectOtlStreamEx(
        otl_stream&             stream,
        const AISTD string&     strSelectFields,
        const AISTD string&     strConditionFields,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llSelectMarker(marker_byText(strSelectFields));
        uint64 llConditionMarker(marker_byText(strConditionFields));
        uint64 llConditionValueMarker = llConditionMarker;
        _open_selectOtlStream(stream, llSelectMarker, llConditionMarker,
            llConditionValueMarker, szMoreCondition, szTableName);
    }

    //! select some fields into listResult
    /*!
     \param listResult a list to hold selected values
     \param strSelectFields marker text indicating the fields should be selected
     \param strCondition WHERE clause(but excluded WHERE) of SELECT
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void select(
        CObdDataList&           listResult,
        const AISTD string&     strSelectFields,
        const AISTD string&     strCondition,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llSelectMarker(marker_byText(strSelectFields));
        _select(listResult, llSelectMarker, strCondition, szTableName);
    }

    //! select some fields into listResult
    /*!
     \param listResult a list to hold selected values
     \param strSelectFields marker text indicating the fields should be selected
     \param cConditionValue condition value
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void select(
        CObdDataList&           listResult,
        const AISTD string&     strSelectFields,
        const CObdData&         cConditionValue,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llSelectMarker(marker_byText(strSelectFields));
#ifdef OBK_USE_USED_MARKER
        uint64 llConditionMarker = cConditionValue.get_usedSet();
#else
        uint64 llConditionMarker = cConditionValue.get_marker();
#endif
        _select(listResult, llSelectMarker, llConditionMarker, cConditionValue, 
            szMoreCondition, szTableName);
    }

#ifndef ABOUT_OBSOLETE_2004_8_12
    //! select some fields into listResult("is null" support)
    /*!
     \param listResult a list to hold selected values
     \param strSelectFields marker text indicating the fields should be selected
     \param strConditionFields marker text indication the fields in cConditionValue
     \param cConditionValue condition value
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void select(
        CObdDataList&           listResult,
        const AISTD string&     strSelectFields,
        const AISTD string&     strConditionFields,
        const CObdData&         cConditionValue,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llSelectMarker(marker_byText(strSelectFields));
        otl_nocommit_stream stream;
        uint64 llConditionMarker = marker_byText(strConditionFields);
        uint64 llValueMarker = cConditionValue.get_marker();
        open_selectOtlStream(stream, llSelectMarker, llConditionMarker, llValueMarker,
            szMoreCondition, szTableName);
        try {
#ifdef DEBUG
            AISTD cout << "ConditionValue: " << cConditionValue << AISTD endl;
#endif
            cConditionValue.otl_streamOut(llValueMarker, stream);
            otl_streamInList(listResult, llSelectMarker, stream);
        }
        catch(otl_exception& e)
        {
            process_otlException(false, e);
        }
    }
#endif
    //! select somoe fields into listResult, selected field is auto-detected.
    //! selected out fields must be defined in corresponed OBD struct.
    /*!
     \param listResult a list to hold selected values
     \param strSQL a select SQL statement
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void select(
        CObdDataList&           listResult,
        const AISTD string&     strSQL)
            throw (CBSErrorMsg)
    {
        otl_nocommit_stream stream;
        m_strLastSQL = strSQL;
        try {
#ifdef DEBUG
            LogAppend(DEBUG_LEVEL, "DebugInfo", m_strLastSQL.c_str());
#endif
            stream.open(m_iSelectBufferSize, m_strLastSQL.c_str(), m_conn);
            select(listResult, stream);
        }
        catch(otl_exception& e)
        {
            process_otlException(false, e);
        }
    }

    //! select somoe fields into listResult, selected field is auto-detected.
    //! selected out fields must be defined in corresponed OBD struct.
    /*!
     \param listResult a list to hold selected values
     \param stream a otl_stream opened by a select SQL statement
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void select(
        CObdDataList&           listResult,
        otl_stream&             stream)
            throw (CBSErrorMsg)
    {
        if ( *stream.adb == 0 || !stream.connected )
        {
            throw_exception("Bad otl_stream connection");
        }

        int iColCount;
        uint64 pMarkers[64], llUsedSet;
        detect_markers(iColCount, llUsedSet, pMarkers, stream);

        try {
            while ( !stream.eof() )
            {
                CObdData cObdData;
                uint64 llMarker = 0;
                for ( int i = 0; i < iColCount; ++i )
                {
                    uint64 llBit = pMarkers[i]; // process only one field
                    cObdData.otl_streamIn(llBit, stream);
                    llMarker |= cObdData.get_marker();
                }
                cObdData.set_marker(llMarker);
                cObdData.set_usedSet(llUsedSet);
                listResult.insert(listResult.end(), cObdData);
            }
        }
        catch(otl_exception& e)
        {
            process_otlException(e);
        }
    }

    //! select all fields into listResult
    /*!
     \param listResult a list to hold selected values
     \param strCondition WHERE clause(but excluded WHERE) of SELECT
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void select_all(
        CObdDataList&           listResult,
        const AISTD string&     strCondition,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llSelectMarker(get_markerOfTable(""));
        _select(listResult, llSelectMarker, strCondition, szTableName);
    }

    //! select all fields into listResult
    /*!
     \param listResult a list to hold selected values
     \param cConditionValue condition value
     \param szMoreCondition more customized condition
     \param szTableName new table name which override default table name
     \throw CBSErrorMsg throwed exception when error occurs
     */
    void select_all(
        CObdDataList&           listResult,
        const CObdData&         cConditionValue,
        const char*             szMoreCondition = 0,
        const char*             szTableName = 0)
            throw (CBSErrorMsg)
    {
        uint64 llSelectMarker(get_markerOfTable(""));
#ifdef OBK_USE_USED_MARKER
        uint64 llConditionMarker = cConditionValue.get_usedSet();
#else
        uint64 llConditionMarker = cConditionValue.get_marker();
#endif
        _select(listResult, llSelectMarker, llConditionMarker, cConditionValue, 
            szMoreCondition, szTableName);
    }
/** @} */

/** @defgroup group_transactions transaction functions
 *  a series functions for transaction managements.
 *  @ingroup group_ob_kernel
 *  @{
 */
public:
    //! commit current transaction
    void commit()
    {
        try {
            m_conn.commit();
        }
        catch(otl_exception& e)
        {
            process_otlException(e);
        }
    }

    //! rollback current transaction
    bool rollback()
    {
        try {
            m_conn.rollback();
        }
        catch(otl_exception& e)
        {
            process_otlException(e);
        }
    }

/** @} */

/** @defgroup group_options option functions
 *  a series functions for change ob_kernel's options.
 *  @ingroup group_ob_kernel
 *  @{
 */
public:
    //! get last SQL executed statement
    AISTD string get_lastSQL()
    {
        return m_strLastSQL;
    }

    //! set buffer size for insert operation
    void set_insertBufferSize(const int iSize)
    {
        if ( iSize > 0 )
        {
            m_iInsertBufferSize = iSize;
        }
    }

    //! set buffer size for select operation
    void set_selectBufferSize(const int iSize)
    {
        if ( iSize > 0 )
        {
            m_iSelectBufferSize = iSize;
        }
    }

    //! set hint of ORACLE INSERT statement
    void set_insertHint(const AISTD string& strHint)
    {
        m_strInsertHint = strHint;
    }

    //! set hint of ORACLE DELETE statement
    void set_removeHint(const AISTD string& strHint)
    {
        m_strRemoveHint = strHint;
    }

    //! set hint of ORACLE UPDATE statement
    void set_updateHint(const AISTD string& strHint)
    {
        m_strUpdateHint = strHint;
    }

    //! set hint of ORACLE SELECT statement
    void set_selectHint(const AISTD string& strHint)
    {
        m_strSelectHint = strHint;
    }
/** @} */
};
//---------------------------------------------------------------------------
/** @} */
#endif
