

/* edit on 20131228 */

#include "logger.h"
#include "netmon.h"

bool NetMon::_inited = false;
NetMon *NetMon::_instance = NULL;
bool NetMon::_network_ok = true;
char NetMon::_adapter_name[MAX_ADAPTER_NAME_LENGTH + 4] = {0};

bool NetMon::StartMonThread(void)
{
    DWORD monNetTid = 0;
    HANDLE monNetThread = NULL;
    monNetThread = CreateThread(NULL, 0, MonNetwork, NULL, 0, &monNetTid);
    if (!monNetThread)
    {
        LOG("error(%d):create mon_network thread failed.", GetLastError());
        return false;
    }
    return true;
}


DWORD CALLBACK NetMon::MonNetwork(LPVOID arg)
{
    OVERLAPPED overlap;
    DWORD ret;
    HANDLE hand = NULL;
    overlap.hEvent = WSACreateEvent();
    bool need_reconnect = false;

    while(true)
    {
        ret = NotifyAddrChange(&hand, &overlap);
        if (ERROR_IO_PENDING != ret)
        {
            LOG("error: call NotifyAddrChange() fail.");
        }
        ret = WaitForSingleObject(overlap.hEvent, INFINITE);
        if (WAIT_OBJECT_0 == ret)
        {
            LOG("**** get addr-change notice.");
            WideCharToMultiByte(CP_ACP, 0, remeberCard, MAX_ADAPTER_NAME_LENGTH,
                _adapter_name, sizeof(_adapter_name), NULL, NULL);
            if (Check(need_reconnect) && need_reconnect && pLoginFrame)
            {
                LOG("try to login again...");
                pLoginFrame->GetLoginParse();
                need_reconnect = false;
            }
        }
    }
    return 0;
}


bool NetMon::Check(bool& need_reconnect)
{
    PIP_ADAPTER_INFO pAdapterInfo = NULL;
    PIP_ADAPTER_INFO pAdapter = NULL;
    PIP_ADDR_STRING pIpAddr;
    DWORD dwOutBufLen = 0;

    pAdapterInfo = (IP_ADAPTER_INFO *) malloc( sizeof(IP_ADAPTER_INFO) ); 
    if (NULL == pAdapterInfo)
    {
        LOG("error: malloc failed");
        need_reconnect = false;
        return false;
    }
    dwOutBufLen = sizeof(IP_ADAPTER_INFO);

    if (ERROR_BUFFER_OVERFLOW == GetAdaptersInfo(pAdapterInfo,&dwOutBufLen))
    {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *)malloc(dwOutBufLen);
        if (pAdapterInfo == NULL)
        {
            LOG("error: malloc failed");
            need_reconnect = false;
            return false;
        }
    }
    bool is_conn_ok = false;
    if (ERROR_SUCCESS == GetAdaptersInfo( pAdapterInfo, &dwOutBufLen)) 
    {
        pAdapter = pAdapterInfo;
        while (pAdapter)
        {
            if (0 == strcmp(pAdapter->AdapterName, _adapter_name))
            {
                pIpAddr = &(pAdapter->IpAddressList);
                while (pIpAddr)
                {
                    if (0 != strcmp(pIpAddr->IpAddress.String, "0.0.0.0") &&
                        0 != strcmp(pIpAddr->IpMask.String, "0.0.0.0"))
                    {
                        is_conn_ok = true;
                        break;
                    }
                    pIpAddr = pIpAddr->Next;
                }
                break;
            }
            pAdapter = pAdapter->Next;
        }
    }
    if (!is_conn_ok)
    {
        LOG("network error.");
        _network_ok = false;
    }
    if (!_network_ok && is_conn_ok)
    {
        LOG("need_reconnect.");
        need_reconnect = true;
        _network_ok = true;
    }
    free(pAdapterInfo);
    return true;
}
