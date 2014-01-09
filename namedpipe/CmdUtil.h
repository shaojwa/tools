

/* edited on 20140101*/

#ifndef _TAC_CMD_UTIIL_H_
#define _TAC_CMD_UTIIL_H_


#define PIPE_BUFSIZE 32 

typedef struct {
    OVERLAPPED oOverlap;
    HANDLE hPipeInst;
    TCHAR chRequest[PIPE_BUFSIZE];
    DWORD cbRead;
    TCHAR chReply[PIPE_BUFSIZE];
    DWORD cbToWrite; 
} PIPEINST, *LPPIPEINST; 

typedef enum {
    NS_NONE        = 0,
    NS_EXIT        = 1,
    NS_CONTINUE    = 2
} NEXT_STEP;

class CmdUtil
{
public:
    /*处理命令进程调用借口(服务端进程)*/
    static CmdUtil& GetInst();
    static BOOL StartListenThread(LPCTSTR pipename);
    static NEXT_STEP ParseCmd(LPCTSTR pipename);

    /*发送命令进程调用接口(客户端进程)*/
    static HANDLE OpenPipe(LPCTSTR pipename);
    static BOOL SendCmdRequest(LPCTSTR cmd);
    static BOOL ClosePipe();

private:
    CmdUtil() {}
    ~CmdUtil() {}
    void Release();

    static DWORD WINAPI ListenCmdProc(LPVOID lpParam);
    static BOOL CreateAndConnectInstance(LPOVERLAPPED lpoOverlap);
    static BOOL ConnectPipe(HANDLE hPipe, LPOVERLAPPED lpo);
    static VOID WINAPI CompletedWriteRoutine(
        DWORD dwErr, DWORD cbWritten, LPOVERLAPPED lpOverLap);
    static VOID WINAPI CompletedReadRoutine(
        DWORD dwErr, DWORD cbBytesRead, LPOVERLAPPED lpOverLap);
    static VOID DisconnectAndClose(LPPIPEINST lpPipeInst);

    static HANDLE _pipe;
    static bool _inited;
    static CmdUtil* _instance;
    static DWORD _result;
    static TCHAR _pipename[256];
    static DWORD _timeout;
};

#endif 