

#include "logger.h"
#include "cmdutil.h"

int _tmain(int argc, TCHAR *argv[])
{
	HANDLE hPipe;
	LPTSTR msg = _T("default message");
	TCHAR chBuf[BUFSIZE];
	BOOL   fSuccess = FALSE; 
	DWORD  cbRead, cbToWrite, cbWritten, dwMode; 

	Logger::Instance().Open(_T("pipe.log"));
	hPipe = CmdUtil::OpenPipe();
	if(hPipe != INVALID_HANDLE_VALUE)
	{		
		LOG("---- hPipe = 0x%p ----", hPipe);
		LPCTSTR cmd = _T("hahaha");
		LOGT(_T("ok: OpenPipe(), to send cmd: [%s]."), cmd);
		CmdUtil::SendCmd(cmd);
		CmdUtil::ClosePipe();
		return 0;
	}	
	CmdUtil::StartListenThread();
	int cmd = 0;
	while(true)
	{		
		printf("please input a number: ");
		scanf("%d", &cmd);
		if (0 == cmd)break;
	}
}