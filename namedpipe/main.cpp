

#include "logger.h"
#include "cmdutil.h"

const LPCTSTR pipename = _T("\\\\.\\pipe\\namedpipe_cmdutil");
const LPCTSTR logname = _T("namedpipe.log");

int _tmain(int argc, TCHAR *argv[])
{
    Logger::Instance().Open(logname);
    NEXT_STEP next = CmdUtil::ParseCmd(pipename);
    if (NS_EXIT == next)
    {
        Logger::Instance().Close();
        exit(0);
    }
    if (!CmdUtil::StartListenThread(pipename))
    {
        LOG("start listen-thread fail");
        Logger::Instance().Close();
    }
    int cmd = 0;
    while(true)
    {
        printf("please input a number: ");
        scanf("%d", &cmd);
        if (0 == cmd)break;
    }
    Logger::Instance().Close();
    return 0;
}