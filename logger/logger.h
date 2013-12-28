

/* edit on 20131228 */

#ifndef _WS_LOGGER_H_
#define _WS_LOGGER_H_

#include "tchar.h"
#include <string.h>
#include <sstream>
using namespace std;


#ifdef _UNICODE
#define tstring wstring
#define tstringstream wstringstream
#else
#define tstring string
#define tstringstream stringstream
#endif


#define _WS_DEBUG_
#ifdef _WS_DEBUG_
#define DLOG(fmt, ...)  Logger::Instance().DLog("%s():%d:"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define DLOGT(fmt, ...)  Logger::Instance().DLogT(_T("%s():%d:") fmt _T("\n"), _T(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#else
#define DLOG(fmt, ...)
#define DLOGT(fmt, ...)
#endif



#define _WS_LOG_
#ifdef _WS_LOG_
#define LOG(fmt, ...) Logger::Instance().Log("%s():%d:"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGT(fmt, ...) Logger::Instance().LogT(_T("%s():%d:") fmt _T("\n"), _T(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#else
#define LOG(fmt, ...)
#define LOGT(fmt, ...)
#endif

class Logger
{
public:
    bool Open(LPCTSTR logname);
    void Close(void);
    static Logger& Instance(void);
    bool Clear(void);
    void LogT(LPCTSTR fmt, ...);
    void Log(LPCSTR fmt, ...);
    void DLogT(LPCTSTR fmt, ...);
    void DLog(LPCSTR fmt, ...);
    void SetLog(bool status);
    void SetDLog(bool status);


private:
    Logger(void);
    ~Logger(void);
    bool m_log_on;
    bool m_dlog_on;
    static Logger *m_instance; 
    static bool m_inited;
    FILE *m_log_fp;
    CRITICAL_SECTION m_lock;
    tstring m_exe_dir;
    tstringstream m_fullpath;
};



#endif
