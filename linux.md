#### install gcc g++

    yum install gcc
    yum install gcc-c++

#### yum

    yum provides ifconfig
    yum whatprovides ifconfig
    yum install net-tools

#### check DNS server in use

    cat /etc/resolve.conf
    nmcli dev show | grep DNS

#### config DNS of vm

    IPADDR=192.168.245.128
    NETMASK=255.255.255.0
    GATEWAY=192.168.245.1
    DNS1=192.168.245.2
