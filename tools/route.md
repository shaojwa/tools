    Destination	目标网络或者目标主机。
    Gateway	    本机某个IP地址，星号表示没有。
    Genmask	    目标掩码，255.255.255.255表示目标主机，0.0.0.0表示默认路由。
    Flags
    U：route is UP
    H：taget is a host
    G：use gatway
    Use	被路由查找的次数
    Iface	命中路由后发送报文的网口

实例：

    网络路由	route add -net 192.56.76.0 netmask 255.255.255.0 dev eth0
    默认路由	route add default gw mango-gw // 不需要 target
    删除路由	route del default
