#ifndef DEF_H
#define DEF_H

#include "compile.h"

/* files to define the global macro 

*/
#define TRUE	1
#define FALSE	0 

#define MAXSUBSESSION 1024
#define MAXSESSIONLEN 512
typedef enum cfgErrors {
        errNoError = 0, errFile, errSession, errName
}cfgErrors;

#ifdef __cplusplus
extern "C" {
#endif
typedef char (*SESSIONBUF)[MAXSESSIONLEN];
/** @defgroup group_aiconfig aiconfig
 * header file: "common/aiconfig.h"
 *  @{
 */

/*! \brief initialize config with a file */
int32 init_config(const char * szCfgFile);

/*! \brief get a config item */
/*!
 example:
 \code
 if (get_config("[common]", "sysinfo", buf) != 0) ...
 \endcode
 */
cfgErrors get_config(const char *m_session,const char *name,char *value);

cfgErrors get_subConfig(const char *log_filename,const char *log_session,const char *log_name, char *log_value);
cfgErrors get_itemInSession(const char * log_session,char ***session_value);
/** @} */

/*! get multi-line configuration and merge them into one value
 * a sample is:
 * CORBA_ORB1=...
 * CORBA_ORB2=...
 */
cfgErrors get_multiLineConfig(const char* szSession, const char* szConfigName,
    char* szConfigValue, const char* szSeparator = " ");

//! parse szCmdLine and create corresponding argc&argv
char** aiconfig_parseArgv(const char* szCmdLine, int* argc);

//! free value returned by aiconfig_parseArgv
void aiconfig_freeArgv(char** argv);

#ifdef __cplusplus
};

#endif

#endif
