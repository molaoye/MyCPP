#ifndef LOGC_H
#define LOGC_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdarg.h>

#include "base_class.h"
#include "aiconfig.h"


/* following define the log level, while the less the level, the more server the error */

/** @defgroup group_ailog ailog
 * header file: "common/ailog.h"
 *  @{
 */

/*! the highest error log */
#define FATAL_LEVEL		4
/*! the severe error log */
#define SEVERE_LEVEL	3
/*! warning log level */
#define WARN_LEVEL		2
/*! informative log level */
#define INFO_LEVEL		1
/*! debugging log level */
#define DEBUG_LEVEL		0

/* Default Datatime format */
#define DEF_DATETIME_FMT	"%y-%m-%d %H:%M:%S"

/* most of time, you only need to call this init function */
/* if you follow the log section as defined, you only need  */
/* to call LoagInit */

extern int32	bToLog;
extern int32	bToConsoleLog;
extern int32	iLogLevel;

/*! init log with a configuration file */
/*!
  \param cfgFile configuration file with a log section
  \param modName name of module which has "modName/log" section in config file
  \param appName Application name appeared in log
  \return TRUE or FALSE

  example:
  \code
  LogInit("sample.cfg", "sample", "SampleApp");
  \endcode


  the corresponding config file - "sample.cfg" will be(note a message file shoule
  be defined in common section):

  [common]

  messageFile=msgFile.txt

  [sample/log]

  logFile=/boss/home1/lixp/cbsrun/log

  logLevel=DEBUG_LEVEL

  logOn=TRUE

  consoleOn=TRUE
 */
int32 LogInit( const char *cfgFile, const char *modName, const char* appName );

int32 LogInitAll( const char * modName, const char * appname, 
		const char * filename, const char * messagename, 
		int32 level, int32 logOn, int32 consoleOn );

/* init routines, you can use LogInit() instead */
int32 LogSetConsoleOn( int32 yesornot );
int32 LogSetLogOn( int32 yesornot );
int32 LogSetLevel( int32 level );
int32 LogSetFileName( const char *filename );
int32 LogSetMessageName( const char *messagename );
int32 LogSetMessage();
int32 LogGetNum( char* shortName );
int32 LogSetAppName( const char *appname );
int32 LogSetModName( const char *modname );
char* LogGetFileName();
void sort_message();

/* the routine that you often need to use */

/*! append log info. */
/*!
  \param iErrorLevel error level, such as DEBUG_LEVEL
  \param shortName a message item in message file
  \param ... parameters of shortName's detail message
  \return TRUE or FALSE
 */
int32 LogAppend( int32 iErrorLevel, const char*  shortName, ... ); 
int32 LogAppend( int32 iErrorLevel, const CBSErrorMsg & cErrMsg );
char* LogGetErrorCode ( char*  shortName ); 
int32 LogTruncate( char *filename );

/** @} */

#endif

