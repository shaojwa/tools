

/* edit on 20131228 */

#ifndef _WS_NETMON_H_
#define _WS_NETMON_H_

#include <windows.h>
#include <Iphlpapi.h>

class NetMon
{
public:
    static NetMon* GetInst(void) 
    {
        if (!_inited) 
        {
            _instance = new NetMon();
            _inited = true;
        }
        return _instance;
    };
    bool StartMonThread();
    static bool Check(bool& need_reconnect);

private:
    static DWORD CALLBACK MonNetwork(LPVOID arg);

    static NetMon *_instance;
    static bool _inited;
    static bool _network_ok;
    static char _adapter_name[MAX_ADAPTER_NAME_LENGTH + 4];
};

#endif
