

/******************************************************************************
*   Copyright(c) 2008-2013 DPtech 版权所有
*
*   文件名称： logger.cpp
*   简要描述： 日志打印操作类
*
*   创建者：wangshaojie
*
*   版本： 1.0
*   日期： 2013.12
******************************************************************************/
#include <stdafx.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "logger.h"

bool  Logger::m_inited = false;
Logger* Logger::m_instance = NULL;


Logger::Logger(void): m_log_on(true), m_dlog_on(true), m_log_fp(NULL)
{
    TCHAR dir[MAX_PATH];
    DWORD nCount = 0;
    nCount = GetModuleFileName(NULL, dir, MAX_PATH);
    dir[MAX_PATH - 1] = 0;
    m_exe_dir = dir;
    m_exe_dir = m_exe_dir.substr(0, m_exe_dir.rfind('\\'));
    m_exe_dir += _T('\\');

    /* 设置输出字符编码 */
    setlocale(LC_ALL, "chs");
    ::InitializeCriticalSection(&m_lock);
}


Logger::~Logger(void)
{
    Close();
    ::DeleteCriticalSection(&m_lock);
}


/* 获取单例 */
Logger& Logger::Instance(void)
{
    if (!m_inited)
    {
        m_instance = new Logger();
        m_inited = true;
    }
    return *m_instance;
}


bool Logger::Open(LPCTSTR logname)
{
    bool ret = true;
    m_fullpath << m_exe_dir << logname;
    ::EnterCriticalSection(&m_lock);
    if(!m_log_fp)
    {
        m_log_fp = _tfopen(m_fullpath.str().c_str(), _T("a+"));
        if (NULL == m_log_fp)
        {
            ret = false;
        }
    }
    ::LeaveCriticalSection(&m_lock);
    return ret;
}


void Logger::Close(void)
{
    ::EnterCriticalSection(&m_lock);
    if(m_log_fp)
    {
        fflush(m_log_fp);
        fclose(m_log_fp);
        m_log_fp = NULL;
    }
    ::LeaveCriticalSection(&m_lock);
}


void Logger::LogT(LPCTSTR fmt, ...)
{
    if (!m_log_on)
    {
        return;
    }
    va_list list; 
    va_start(list, fmt);
    TCHAR szTime[MAX_PATH];
    time_t now = time(NULL);
    _tcsftime(szTime, MAX_PATH, _T("%c"), localtime(&now));

    ::EnterCriticalSection(&m_lock);
    if(m_log_fp) {
        _ftprintf(m_log_fp, _T("[%s]"), szTime); 
        _vftprintf(m_log_fp, fmt, list);
        fflush(m_log_fp);
    }
    ::LeaveCriticalSection(&m_lock);
    va_end(list);
}

void Logger::Log(LPCSTR fmt, ...)
{
    if (!m_log_on)
    {
        return;
    }
    va_list list; 
    va_start(list, fmt);
    char szTime[MAX_PATH];
    time_t now = time(NULL);
    strftime(szTime, MAX_PATH, "%c", localtime(&now));

    ::EnterCriticalSection(&m_lock);
    if(m_log_fp) {
        fprintf(m_log_fp, "[%s]", szTime); 
        vfprintf(m_log_fp, fmt, list);
        fflush(m_log_fp);
    }
    ::LeaveCriticalSection(&m_lock);
    va_end(list);
}


void Logger::DLog(LPCSTR fmt, ...)
{
    if (!m_dlog_on)
    {
        return;
    }
    va_list list; 
    va_start(list, fmt);
    char szTime[256];
    time_t now = time(NULL);
    strftime(szTime, sizeof(szTime), "%c", localtime(&now));

    ::EnterCriticalSection(&m_lock);
    if(m_log_fp) {
        fprintf(m_log_fp, "[%s]", szTime);
        vfprintf(m_log_fp, fmt, list);
        fflush(m_log_fp);
    }
    ::LeaveCriticalSection(&m_lock);
    va_end(list);
}

void Logger::DLogT(LPCTSTR fmt, ...)
{
    if (!m_dlog_on)
    {
        return;
    }
    va_list list; 
    va_start(list, fmt);
    TCHAR szTime[MAX_PATH];
    time_t now = time(NULL);
    _tcsftime(szTime, MAX_PATH, _T("%c"), localtime(&now));

    ::EnterCriticalSection(&m_lock);
    if(m_log_fp) {
        _ftprintf(m_log_fp, _T("[%s]"), szTime); 
        _vftprintf(m_log_fp, fmt, list);
        fflush(m_log_fp);
    }
    ::LeaveCriticalSection(&m_lock);
    va_end(list);
}

//打开或者关闭log
void Logger::SetLog(bool status)
{
    ::EnterCriticalSection(&m_lock);
    m_log_on = status;
    ::LeaveCriticalSection(&m_lock);
}

//打开或者关闭 dlog
void Logger::SetDLog(bool status)
{
    ::EnterCriticalSection(&m_lock);
    m_dlog_on = status;
    ::LeaveCriticalSection(&m_lock);
}

//清掉所有日志
bool Logger::Clear(void)
{
    bool ret = true;
    ::EnterCriticalSection(&m_lock);
    if (m_log_fp != NULL)
    {
        m_log_fp = _tfreopen(m_fullpath.str().c_str(), _T("w"), m_log_fp);
        if (NULL == m_log_fp)
        {
            ret = false;
        }
    }
    ::LeaveCriticalSection(&m_lock);
    return ret;
}