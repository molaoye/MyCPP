#ifndef _BASE_CLASS_H_
#define _BASE_CLASS_H_

/*---------------------------------------------------------------------------O
  program name:       	base_class.h
  description:         	define base class below
			CBSBasic
			CBSException
			CBSErrorMsg
  created by:  		ZhangHua
  History:
	02-09-20        create
  Known Issue:
  Todo:
O---------------------------------------------------------------------------*/

#include "compile.h"
#include "base_define.h"

#ifndef	_Windows
//	#include 	<pthread.h>
#endif // _Windows

#include <string>
#  ifdef OB_NO_STD
    #include <iostream.h>
	#include <strstream.h>
#  else
    #include <iostream>
	#include <sstream>
#  endif

//*****************************************************************************
//*         Class CBSBasic
//*****************************************************************************
//-----------------------------------------------------------------------------
class CBSBasic
{
protected:
        int32	m_useFlag;
	/* 0: nothing using this class, 1: something is using this class. */
        int32	m_loadFlag;
	/* 0: no data has loaded, 1: data loaded, 2 : is loading data */
    #ifndef _Windows
        pthread_mutex_t	m_threadLock;
    #endif

	AISTD string  m_tableName;

public:
	CBSBasic() {
		m_useFlag = 0; m_loadFlag = 0;
        #ifndef _Windows
#if defined( _PTHREADS_DRAFT4 )
		pthread_mutex_init(&m_threadLock,pthread_mutexattr_default);
#else
		pthread_mutex_init(&m_threadLock,NULL);
#endif
        #endif
	};
    virtual ~CBSBasic() {};

	virtual bool isNull() const {return true;};
	virtual void clear() {};

protected:
#ifndef _Windows
	void acquire_use()
	{
       	pthread_mutex_lock(&m_threadLock);
       	m_useFlag ++;
       	pthread_mutex_unlock(&m_threadLock);
	}
	void release_use()
	{
       	pthread_mutex_lock(&m_threadLock);
       	m_useFlag --;
       	pthread_mutex_unlock(&m_threadLock);
	}
#endif // _Windows
	int32 get_useFlag() const {return m_useFlag;}
	int32 get_loadFlag() const {return m_loadFlag;}
	void set_loadFlag(int32 loadFlag)
	{
    #ifndef _Windows
       	pthread_mutex_lock(&m_threadLock);
       	m_loadFlag = loadFlag;
       	pthread_mutex_unlock(&m_threadLock);
    #endif // _Windows
	}
};


//*****************************************************************************
//*         Class CBSException
//*****************************************************************************

class CBSException
{
public:
	CBSException() {}
	CBSException( 
		const AISTD string& pProgramName,
		const AISTD string& pFunctionName,
		const AISTD string& pErrmsg ) :
		its_program( pProgramName ),
		its_position( pFunctionName ),
		its_errmsg( pErrmsg ) 	{}

	CBSException( 
		const AISTD string& pFunctionName,
		const AISTD string& pErrmsg ) :
		its_program( DEFAULT_PROGRAM_NAME ),
		its_position( pFunctionName ),
		its_errmsg( pErrmsg ) 	{}

	CBSException( const AISTD string& pErrmsg ) :
		its_program( DEFAULT_PROGRAM_NAME ),
		its_errmsg( pErrmsg ) 	{}

	virtual const char *what() const { return its_errmsg.data(); }
	virtual const char *where() const { return (its_program+"--"+its_position+"::").data(); }

	virtual ~CBSException() {}

	void display( AISTD ostream& d ) const
	{ 
		d 
		<< "\n --- Exception Report ---"
		<< "\n program-name " << its_program.data()
		<< "\n function-name " << its_position.data()
		<< "\n error-message " << its_errmsg.data() 
		<< AISTD endl;
	}

	friend AISTD ostream& operator<<( AISTD ostream& d, const CBSException& s )
	{
		s.display( d );
		return d;
	}

protected:
	AISTD string its_program;
	AISTD string its_position;
	AISTD string its_errmsg;
};

//*****************************************************************************
//*         Class CBSErrorMsg
//*****************************************************************************
//-----------------------------------------------------------------------------

#define DEFAULT_MESSAGE		"no error"

class CBSErrorMsg
{
public:
	CBSErrorMsg() : m_sErrorCode( 0 ), m_iMinErrorCode( 0 ),
					m_strMessage( DEFAULT_MESSAGE ), 
					m_strHint( DEFAULT_MESSAGE ) 	{}
	CBSErrorMsg( int32 iErrCode, const char * szMsg, 
			const char * szHint, int32 iMinErrorCode = 0 ) : 
				m_sErrorCode( iErrCode ),  
				m_iMinErrorCode( iMinErrorCode ),
				m_strMessage( szMsg ), m_strHint( szHint )
				{ }
	virtual ~CBSErrorMsg() 					{}

	inline void set_errorCode( const int32 sErrorCode )
		{ m_sErrorCode = sErrorCode; }
	inline int32 get_errorCode() const
		{ return m_sErrorCode; }

	inline void set_minErrorCode( const int32 iMinErrorCode )
		{ m_iMinErrorCode = iMinErrorCode; }
	inline int32 get_minErrorCode() const
		{ return m_iMinErrorCode; }

	inline void set_errorMsg( const AISTD string& strMessage ) 
		 { m_strMessage = strMessage; }
	inline const AISTD string get_errorMsg() const
		{ return m_strMessage; }
	
	inline void set_hint( const AISTD string & strHint )
		{ m_strHint = strHint; }
	inline const AISTD string get_hint() const
		{ return m_strHint; }

	inline void clear()
		{
			m_sErrorCode = 0;
			m_iMinErrorCode = 0;
			m_strMessage = DEFAULT_MESSAGE;
			m_strHint = DEFAULT_MESSAGE;
		}

	inline operator const char * () const
		{
#ifdef OB_NO_STD
			AISTD strstream ss;
			ss << *this;
			return ss.str();
#else
			AISTD stringstream ss;
			ss << *this;
			return ss.str().c_str();
#endif
		}

	inline operator AISTD string () const
		{
#ifdef OB_NO_STD
			AISTD strstream ss;
#else
			AISTD stringstream ss;
#endif
			ss << *this;
			return ss.str();
		}

	friend AISTD ostream & operator << ( AISTD  ostream & os, 
			const CBSErrorMsg cErrorMsg );

protected:
	int32			m_sErrorCode;
	int32			m_iMinErrorCode;	// low level error code, for example:
										// Oracle Error Code
	AISTD string 	m_strMessage;
	AISTD string 	m_strHint;
};


inline AISTD ostream & operator << ( AISTD ostream & os, 
		const CBSErrorMsg cErrorMsg )
{
	return os 
			<< "[Code   ] " << cErrorMsg.m_sErrorCode << AISTD endl
			<< "[MinCode] " << cErrorMsg.m_iMinErrorCode << AISTD endl
			<< "[Message] " << cErrorMsg.m_strMessage << AISTD endl
			<< "[Hint   ] " << cErrorMsg.m_strHint << AISTD endl;
}

#endif // _BASE_CLASS_H_
