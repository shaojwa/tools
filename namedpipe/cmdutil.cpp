
#include "stdafx.h"
#include "cmdutil.h"
#include "logger.h"

HANDLE CmdUtil::_pipe = NULL;
bool CmdUtil::_inited = false;
CmdUtil* CmdUtil::_instance = NULL;
DWORD CmdUtil::_result  = 0;
DWORD CmdUtil::_bufsize = 16;
DWORD CmdUtil::_timeout = 1000;
LPCTSTR CmdUtil::_piplename = _T("\\\\.\\pipe\\namedpipe_cmdutil");

CmdUtil* CmdUtil::GetInst()
{
    if (!_inited)
    {
        _instance = new CmdUtil();
        _inited = true;
    }
    return _instance;
}

/************************************************************************/
/* 以下是服务端功能代码                                               */
/************************************************************************/

BOOL CmdUtil::StartListenThread()
{
    LOG(">>");
    DWORD dwError = 0;
    HANDLE hThread = CreateThread(NULL, 0, ListenCmdProc, NULL, 0, NULL);
    if (NULL == hThread)
    {
        dwError = GetLastError();
        LOG("error: create listen-cmd-thread failed.");
        return FALSE;
    }
    return TRUE;
}


DWORD CmdUtil::ListenCmdProc(LPVOID lpParam)
{
    LOG(">>");
    LPPIPEINST lpPipeInst;

    /*创建一个事件用来通知*/
    HANDLE hConnectEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
    if (NULL == hConnectEvent)
    {
        LOG("error(%d): create connect-event fail.", GetLastError()); 
        return 0;
    }

    OVERLAPPED oConnect;
    oConnect.hEvent = hConnectEvent;
    BOOL fPendingIO = CreateAndConnectInstance(&oConnect);

    while (true)
    {
        /*
        等待客户端进程的连接事件或者读写完成事件 
        */
        DWORD dwWait = WaitForSingleObjectEx(hConnectEvent, INFINITE, TRUE);
        switch (dwWait)
        {
        case 0:
            {
                if (fPendingIO) 
                {
                    DWORD cbRet; 
                    BOOL fSuccess = GetOverlappedResult(
                        _pipe,
                        &oConnect,
                        &cbRet,
                        FALSE);
                    if (!fSuccess) 
                    {
                        LOG("error(%d): ConnectNamedPipe", GetLastError()); 
                        return 0;
                    }
                } 

                /*为管道实例分配存储空间*/
                lpPipeInst = (LPPIPEINST) GlobalAlloc( GPTR, sizeof(PIPEINST)); 
                if (lpPipeInst == NULL) 
                {
                    LOG("error(%d): GlobalAlloc() failed", GetLastError()); 
                    return 0;
                }

                lpPipeInst->hPipeInst = _pipe;
                lpPipeInst->cbToWrite = 0;
                CompletedWriteRoutine(0, 0, (LPOVERLAPPED) lpPipeInst);

                /* 为下一个连接创建新的管道实例 */
                fPendingIO = CreateAndConnectInstance( &oConnect);
                break;
            }

        case WAIT_IO_COMPLETION:
            {
                LOG("WAIT_IO_COMPLETION, break;"); 
                break;
            }
        default:
            {
                LOG("error(%d): WaitForSingleObjectEx() failed.", GetLastError()); 
                return 0;
            }
        }
    }
    return 0;
}


/*
服务端进程创建命名管道并主动连接到管道。
如果客户端没有连接到管道则返回成功。
如果客户端已经连到管道上则返回失败。
*/
BOOL CmdUtil::CreateAndConnectInstance(LPOVERLAPPED lpoOverlap)
{
    LOG(">>");
    _pipe = CreateNamedPipe( 
        _piplename,
        PIPE_ACCESS_DUPLEX |FILE_FLAG_OVERLAPPED,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        _bufsize,
        _bufsize,
        _timeout,
        NULL);
    if (_pipe == INVALID_HANDLE_VALUE) 
    {
        LOG("error(%d):CreateNamedPipe() failed", GetLastError()); 
        return FALSE;
    }
    return ConnectPipe(_pipe, lpoOverlap);
}


BOOL CmdUtil::ConnectPipe(HANDLE hPipe, LPOVERLAPPED lpo)
{
    LOG(">>");
    /*
    调用ConnectNamedPipe进入等待客户端进程连接的状态。
    因为是异步操作所以ConnectNamedPipe应该立即返回0
    并且GetLastError() = ERROR_IO_PENDING.
    */
    BOOL fConnected = ConnectNamedPipe(hPipe, lpo);
    LOG("info: ConnectNamedPipe returns: %d.", fConnected);

    if (fConnected)
    {
        LOG("error(%d): ConnectNamedPipe failed", GetLastError()); 
        return 0;
    }

    BOOL fPendingIO = FALSE;
    switch (GetLastError()) 
    {
    case ERROR_IO_PENDING: 
        {
            fPendingIO = TRUE; 
            break;
        }
    case ERROR_PIPE_CONNECTED:
        {
            if (SetEvent(lpo->hEvent)) 
                break;
        }
    default:
        {
            LOG("error(%d): ConnectNamedPipe failed", GetLastError());
            return 0;
        }
    }
    return fPendingIO;
}


/*
* 当写操作完成之后或者当客户端例程连接到管道时调用本例程
*/
VOID CmdUtil::CompletedWriteRoutine(DWORD dwErr, DWORD cbWritten, 
                                           LPOVERLAPPED lpOverLap) 
{
    LOG(">>");
    BOOL fRead = FALSE;
    LPPIPEINST lpPipeInst = (LPPIPEINST) lpOverLap; 
    if ((dwErr == 0) && (cbWritten == lpPipeInst->cbToWrite))  
    {
        fRead = ReadFileEx(
            lpPipeInst->hPipeInst,
            lpPipeInst->chRequest, 
            _bufsize *sizeof(TCHAR),
            (LPOVERLAPPED) lpPipeInst,
            (LPOVERLAPPED_COMPLETION_ROUTINE) CompletedReadRoutine); 
    }

    if (! fRead)
    {
        DisconnectAndClose(lpPipeInst);
    }
}

// This routine is called as an I/O completion routine
// after reading a request from the client. 
// It gets data and writes it to the pipe. 
VOID CmdUtil::CompletedReadRoutine(DWORD dwErr, DWORD cbBytesRead,
                                          LPOVERLAPPED lpOverLap)
{
    LOG(">>");
    BOOL fWrite = FALSE;
    // lpOverlap points to storage for this instance. 
    LPPIPEINST lpPipeInst = (LPPIPEINST) lpOverLap; 

    //The read operation has finished, 
    //so write a response (if no error occurred). 
    if ((dwErr == 0) && (cbBytesRead != 0)) 
    { 
        //自己已经读完，也应该处理完毕：所以要返回处理结果。

        //返回操作的结果。也可以做下面的处理。
        //读取命令行发来的数据，并处理和返回结构。

        //规定所有的处理结果都放置到一个全局变量里面然后返回这个值。 

        //重点是改写这个函数。
        //GetAnswerToRequest(lpPipeInst); 

        fWrite = WriteFileEx(
            lpPipeInst->hPipeInst, 
            &(lpPipeInst->chReply), 
            lpPipeInst->cbToWrite,
            (LPOVERLAPPED) lpPipeInst, 
            (LPOVERLAPPED_COMPLETION_ROUTINE) CompletedWriteRoutine); 
    }
    if (! fWrite)
    {         
        DisconnectAndClose(lpPipeInst);  
    }
}




/*
发生错误或者客户端关闭管道时调用
*/
VOID CmdUtil::DisconnectAndClose(LPPIPEINST lpPipeInst)
{
    LOG(">>");
    if (!DisconnectNamedPipe(lpPipeInst->hPipeInst))
    {
        LOG("error(%d): DisconnectNamedPipe failed", GetLastError());
    }
    CloseHandle(lpPipeInst->hPipeInst);
    if (lpPipeInst != NULL)
    {
        GlobalFree(lpPipeInst); 
    }
}


void CmdUtil::Release()
{
    LOG(">>");
    delete this;
    _instance = NULL;
    _inited = false;
}
