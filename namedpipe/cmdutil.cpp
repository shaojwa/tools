

// ref1 : http://msdn.microsoft.com/en-us/library/windows/desktop/aa365601(v=vs.85).aspx
// ref2 : http://msdn.microsoft.com/en-us/library/windows/desktop/aa365592(v=vs.85).aspx

#include "logger.h"
#include "cmdutil.h"


HANDLE CmdUtil::_pipe = NULL;
bool CmdUtil::_inited = false;
CmdUtil* CmdUtil::_instance = NULL;
DWORD CmdUtil::_result  = 0;
DWORD CmdUtil::_bufsize = 16;
DWORD CmdUtil::_timeout = 1000;
LPCTSTR CmdUtil::_pipename = _T("\\\\.\\pipe\\namedpipe_cmdutil");

CmdUtil& CmdUtil::Instance()
{
    if (!_inited)
    {
        _instance = new CmdUtil();
        _inited = true;
    }
    return *_instance;
}

/************************************************************************/
/* 以下是服务端功能代码                                               */
/************************************************************************/

BOOL CmdUtil::StartListenThread()
{
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
    LPPIPEINST lpPipeInst;

    /*创建一个事件用来通知*/
    HANDLE hConnectEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
    if (NULL == hConnectEvent)
    {
        LOG("error(%d): create connect-event fail.", GetLastError()); 
        return 0;
    }
	else
	{
		LOG("ok: create connect-event."); 
	}

    OVERLAPPED oConnect;
    oConnect.hEvent = hConnectEvent;
    BOOL fPendingIO = CreateAndConnectInstance(&oConnect);

    while (true)
    {
        /*
        当有客户端连接时或者读写操作完成wait函数返回 
        */
		LOG("waiting for event...");
        DWORD dwWait = WaitForSingleObjectEx(hConnectEvent, INFINITE, TRUE);
		LOG("dwWait = %d", dwWait); 
        switch (dwWait)
        {
        case 0:
            {
                if (fPendingIO) 
                {
                    DWORD cbRet; 
                    BOOL fSuccess = GetOverlappedResult(
						_pipe, &oConnect, &cbRet, FALSE);

					LOG("fSuccess = %d", fSuccess); 
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
    _pipe = CreateNamedPipe( 
        _pipename,
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
	else
	{
		LOG("ok: CreateNamedPipe().");
		LOG("**** _pipe = 0x%p ****", _pipe);
		return ConnectPipe(_pipe, lpoOverlap);
	}
}


BOOL CmdUtil::ConnectPipe(HANDLE hPipe, LPOVERLAPPED lpo)
{
    /*
    调用ConnectNamedPipe进入等待客户端进程连接的状态。
    因为是异步操作所以ConnectNamedPipe应该立即返回0
    并且GetLastError() = ERROR_IO_PENDING.
    */
    BOOL fConnected = ConnectNamedPipe(hPipe, lpo);
    LOG("info: ConnectNamedPipe() returns: %d.", fConnected);

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
	LOG("dwErr = %d, cdWritten = %d", dwErr, cbWritten);
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
	LOG("ReadFileEx() returns %d", fRead);
    if (!fRead)
    {
        DisconnectAndClose(lpPipeInst);
    }
}


VOID CmdUtil::CompletedReadRoutine(DWORD dwErr, DWORD cbBytesRead,
                                          LPOVERLAPPED lpOverLap)
{
    BOOL fWrite = FALSE;
    LPPIPEINST lpPipeInst = (LPPIPEINST) lpOverLap; 
    if ((dwErr == 0) && (cbBytesRead != 0)) 
    {
		*((DWORD *)(lpPipeInst->chReply)) = 0;
		lpPipeInst->cbToWrite = sizeof(DWORD);

        fWrite = WriteFileEx(
            lpPipeInst->hPipeInst, 
            &(lpPipeInst->chReply), 
            lpPipeInst->cbToWrite,
            (LPOVERLAPPED) lpPipeInst, 
            (LPOVERLAPPED_COMPLETION_ROUTINE) CompletedWriteRoutine); 
    }
	LOG("WriteFileEx() returns %d", fWrite);
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


/************************************************************************/
/* 客户端例程
/************************************************************************/

HANDLE CmdUtil::OpenPipe()
{
	_pipe = CreateFile(_pipename, GENERIC_READ | GENERIC_WRITE, 
		0, NULL, OPEN_EXISTING, 0, NULL); 
	return _pipe;
}

BOOL CmdUtil::SendCmd(LPCTSTR cmd)
{
	DWORD  cbRead, cbToWrite, cbWritten, dwMode; 
	dwMode = PIPE_READMODE_MESSAGE; 
	BOOL fSuccess = SetNamedPipeHandleState(_pipe, &dwMode, NULL, NULL);  
	if ( !fSuccess) 
	{
		LOG("error(%d): SetNamedPipeHandleState() failed", GetLastError());
		return FALSE;
	}

	/*向管道的服务端发送命令 */
	cbToWrite = (lstrlen(cmd) + 1) * sizeof(TCHAR);
	LOGT(_T("Sending %d byte message: [%s]"), cbToWrite, cmd); 

	fSuccess = WriteFile(_pipe, cmd, cbToWrite, &cbWritten, NULL);
	if ( !fSuccess) 
	{ 
		LOG("WriteFile to pipe failed. GLE = %d", GetLastError()); 
		return FALSE;
	}
	LOG("send cmd done");
	return TRUE;
}

BOOL CmdUtil::ClosePipe(void)
{
	return CloseHandle(_pipe); 
}

