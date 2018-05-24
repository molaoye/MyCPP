#ifndef _COMPLIE_H_
#define _COMPLIE_H_

#ifndef __cplusplus
    #error "CBS must be compiled by c++ compiler!"
#endif

//---------------------------------------------------------------------------
// program name:	comipile.h
// description: 	define platform and compiler relative types and marcos
// created by:		zhanghua
// History:
//	02-09-20	create
//  03-07-18    LXP: modify basic types
//                   _CBS_Export -> _CBS_EXPORT
//                   _Windows -> _MSC_VER & __BORLANDC__
//                   redefine _USE_THREAD_
//                   add AICBS macro
// Known Issue:
// Todo:
//---------------------------------------------------------------------------

#define AICBS

// basic types on all platforms
typedef char                *pchar;
typedef unsigned char       byte;
typedef unsigned char       *pbyte;

typedef short               int16;
typedef unsigned short      uint16;
typedef unsigned short      word16;

typedef int                 int32;
typedef unsigned int        uint32;
typedef unsigned long  	    word32;

#define AISTD               std::

#ifdef LINUX
    typedef long long           int64;
    typedef unsigned long long  uint64;
    typedef unsigned long long  word64;

    // STL compiler setting
	#ifdef OB_NO_STD
		#define AISTD
	#else
	    #define AISTD               std::
	#endif

    #define AITYPENAME		typename
    #define STL_ALLOC

    // DLL export define
    #define _CBS_EXPORT
    #define _CBS_API(FUNC_TYPE) FUNC_TYPE

    #define	I64(A)	A##LL

    #define _USE_THREAD_

#endif // LINUX

#ifdef SOLARIS
    typedef long long           int64;
    typedef unsigned long long  uint64;
    typedef unsigned long long  word64;

    // STL compiler setting
    #ifdef OB_NO_STD
        #define AISTD
    #else
        #define AISTD               std::
    #endif

    #define AITYPENAME		typename
    #define STL_ALLOC

    // DLL export define
    #define _CBS_EXPORT
    #define _CBS_API(FUNC_TYPE) FUNC_TYPE

    #define	I64(A)	A##LL

    #define _USE_THREAD_

#endif // SOLARIS

#ifdef AIXV3
#ifdef BIT64
	// typedef long				int64
	typedef unsigned long		uint64;
	typedef unsigned long		word64;
#else
    typedef long long int   int64;
    typedef unsigned long long int   uint64;
    typedef unsigned long long int   word64;
#endif

    // STL compiler setting
    #ifdef OB_NO_STD
        #define AISTD
    #else
        #define AISTD               std::
    #endif

    #define AITYPENAME		typename
    #define STL_ALLOC

    // DLL export define
    #define _CBS_EXPORT
    #define _CBS_API(FUNC_TYPE) FUNC_TYPE

#ifndef AIXV5
    #define atoll	a64l
#endif

    #define	I64(A)	A##LL

    #define _USE_THREAD_

#endif // AIXV3

#ifdef DIGITAL
    #define atoll	atol

    #define _USE_THREAD_

#endif // DIGITAL

#ifdef HPUX
    typedef long long           int64;
    typedef unsigned long long 	uint64;
    typedef unsigned long long	word64;

    // STL compiler setting
    #ifdef OB_NO_STD
        #define AISTD
    	#define OTL_STL_NOSTD_NAMESPACE
    #else
        #define AISTD               std::
    #endif

    #define AITYPENAME		typename

    #ifdef RW_NO_STL
	#define STL_ALLOC , allocator
    #else
	#define STL_ALLOC
    #endif

    // DLL export define
    #define _CBS_EXPORT
    #define _CBS_API(FUNC_TYPE) FUNC_TYPE

    // define function
    #define	atoll	a64l
    #define	I64(A)	A##LL

    #define _USE_THREAD_

#endif // HPUX

#ifdef GCC
    typedef long long           int64;
    typedef unsigned long int  	uint64;
    typedef unsigned long int   word64;

    // DLL export define
    #define _CBS_EXPORT
    #define _CBS_API(FUNC_TYPE) FUNC_TYPE

    // STL compile setting
    #ifdef OB_NO_STD
        #define AISTD
    #else
        #define AISTD               std::
    #endif

    #define STL_ALLOC

    #define	I64(A)	A##LL

    #define _USE_THREAD_

#endif // GCC

#ifdef  __BORLANDC__
    #define AISTD std::
    #define STL_ALLOC

    typedef __int64             int64;
    typedef unsigned __int64    uint64;
    typedef unsigned __int64    word64;

    #ifdef __DLL_BUILD
	#define _CBS_API(FUNC_TYPE) extern "C" FUNC_TYPE __stdcall __export
	#define _CBS_EXPORT  __declspec (dllexport)
    #else
	#define _CBS_API(FUNC_TYPE) extern "C" FUNC_TYPE __stdcall __import
	#define _CBS_EXPORT __declspec (dllimport)
    #endif

    #define	I64(A)	A##i64

    #ifdef __MT__
        #define _USE_THREAD_
    #endif

    #define _VCL_USED

#endif // __BORLANDC__

#ifdef  _MSC_VER
    #define AISTD std::
    #define STL_ALLOC

    typedef __int64             int64;
    typedef unsigned __int64    uint64;
    typedef unsigned __int64    word64;

    #ifdef __DLL_BUILD
        #define _CBS_API(FUNC_TYPE) extern "C" FUNC_TYPE __declspec(dllexport)
        #define _CBS_EXPORT  __declspec (dllexport)
    #else
        #define _CBS_API(FUNC_TYPE) extern "C" FUNC_TYPE __declspec(dllimport)
	#define _CBS_EXPORT __declspec (dllimport)
    #endif

    #define	I64(A)	A##i64

    #ifdef _MT
        #define _USE_THREAD_
    #endif

#endif // _MSC_VER

#endif // _COMPLIE_H_
