

#ifndef _TAC_CMD_UTIIL_H_
#define _TAC_CMD_UTIIL_H_


#define BUFSIZE 10

typedef struct
{
    OVERLAPPED oOverlap;
    HANDLE hPipeInst;
    TCHAR chRequest[BUFSIZE];
    DWORD cbRead;
    TCHAR chReply[BUFSIZE]; 
    DWORD cbToWrite; 
} PIPEINST, *LPPIPEINST; 

class CmdUtil
{
public:
    static CmdUtil* GetInst();
    void Release();
    static BOOL StartListenThread(void);

    //static void ParseCmd(void);


private:
    CmdUtil() {}
    ~CmdUtil() {}

    //static bool GetCmdLen(LPTSTR *lpvMessage, DWORD * cbToWrite);
    //static DWORD SendAndReceive();

    //static VOID DisconnectAndClose(LPPIPEINST lpPipeInst);
    //static VOID GetAnswerToRequest(LPPIPEINST pipe);
    //static VOID WINAPI CompletedReadRoutine(DWORD dwErr, 
    //    DWORD cbBytesRead, LPOVERLAPPED lpOverLap);
    //static VOID WINAPI CompletedWriteRoutine(DWORD dwErr, 
    //    DWORD cbWritten, LPOVERLAPPED lpOverLap);

    //static BOOL ConnectToNewClient(HANDLE hPipe, LPOVERLAPPED lpo);
    //static BOOL CreateAndConnectInstance(LPOVERLAPPED lpoOverlap);

    /*服务端进程功能代码*/
    static DWORD WINAPI ListenCmdProc(LPVOID lpParam);
    static BOOL CreateAndConnectInstance(LPOVERLAPPED lpoOverlap);
    static BOOL ConnectPipe(HANDLE hPipe, LPOVERLAPPED lpo);
    static VOID CompletedWriteRoutine(
        DWORD dwErr, DWORD cbWritten, LPOVERLAPPED lpOverLap);
    static VOID CompletedReadRoutine(
        DWORD dwErr, DWORD cbBytesRead, LPOVERLAPPED lpOverLap);
    static VOID DisconnectAndClose(LPPIPEINST lpPipeInst);

    static HANDLE _pipe;
    static bool _inited;
    static CmdUtil* _instance;
    static DWORD _result;
    static LPCTSTR _piplename;
    static DWORD _bufsize;
    static DWORD _timeout;
};

#endif 