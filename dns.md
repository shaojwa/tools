#### 查看DNS服务器ip

    cat /etc/resolve.conf
    nmcli dev show | grep DNS

#### 在虚拟机中配置DNS服务

    IPADDR=192.168.245.128
    NETMASK=255.255.255.0
    GATEWAY=192.168.245.1
    DNS1=192.168.245.2
    
#### 清空dns缓存

    /etc/init.d/dns-clean
