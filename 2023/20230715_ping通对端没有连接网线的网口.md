node18 可以ping通28节点上的172.16.6.128 ip，但是这个ip对应的网口，没有连接网线：
```
ib41-0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 172.16.6.28  netmask 255.255.255.0  broadcast 172.16.6.255
        ....
        ether 10:70:fd:b7:d5:be  txqueuelen 1000  (Ethernet)
        ....
```
和
```
ib41-1: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        inet 172.16.6.128  netmask 255.255.255.0  broadcast 172.16.6.255
        ether 10:70:fd:b7:d5:bf  txqueuelen 1000  (Ethernet)
```
没有网线：
```
[root@node28 ~]# ethtool ib41-1
Settings for ib41-1:
        ...
        Link detected: no (No cable)
```

我们发现：18节点上，arp显示的MAC地址是一样的
```
[SDS_Admin@node18 ~]$ arp -a | grep 172.16.6.128
? (172.16.6.128) at 10:70:fd:b7:d5:be [ether] on ib41-0
[SDS_Admin@node18 ~]$ arp -a | grep 172.16.6.28
? (172.16.6.28) at 10:70:fd:b7:d5:be [ether] on ib41-0
```
而这个MAC（`10:70:fd:b7:d5:be`）地址其实是28节点上，172.16.6.28网口的MAC地址，而不是172.16.6.128的MAC地址。

node28节点上的配置：
```
[root@node28 ~]#  sudo sysctl -a | grep ip_forward
net.ipv4.ip_forward = 0
net.ipv4.ip_forward_update_priority = 1
net.ipv4.ip_forward_use_pmtu = 0
[root@node28 ~]#  sudo sysctl -a | grep rp_filter
net.ipv4.conf.all.arp_filter = 0
net.ipv4.conf.all.rp_filter = 0
net.ipv4.conf.default.arp_filter = 0
net.ipv4.conf.default.rp_filter = 1
net.ipv4.conf.ethAe1-0.arp_filter = 0
net.ipv4.conf.ethAe1-0.rp_filter = 1
net.ipv4.conf.ethAe1-1.arp_filter = 0
net.ipv4.conf.ethAe1-1.rp_filter = 1
net.ipv4.conf.ethAe1-2.arp_filter = 0
net.ipv4.conf.ethAe1-2.rp_filter = 1
net.ipv4.conf.ethAe1-3.arp_filter = 0
net.ipv4.conf.ethAe1-3.rp_filter = 1
net.ipv4.conf.ib41-0.arp_filter = 0
net.ipv4.conf.ib41-0.rp_filter = 1
net.ipv4.conf.ib41-1.arp_filter = 0
net.ipv4.conf.ib41-1.rp_filter = 1
net.ipv4.conf.ib62-0.arp_filter = 0
net.ipv4.conf.ib62-0.rp_filter = 1
net.ipv4.conf.ib62-1.arp_filter = 0
net.ipv4.conf.ib62-1.rp_filter = 1
net.ipv4.conf.lo.arp_filter = 0
net.ipv4.conf.lo.rp_filter = 1
```
