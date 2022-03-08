`ethtool`可以检测，如果`ethtool <devname>`的输出中的下面三个字段有数据那就就表示有网线连接：
```
 Speed: 25000Mb/s
 Duplex: Full
 Port: FIBRE
```
如果没有那就是没有网线连接：
```
Speed: Unknown!
Duplex: Unknown! (255)
Port: None
```
有网线连接的完整信息：
```
[root@node71 network-scripts]# ethtool ethC5e-0
Settings for ethC5e-0:
        Supported ports: [ FIBRE ]
        Supported link modes:   1000baseT/Full
                                10000baseT/Full
                                25000baseCR/Full
        Supported pause frame use: Symmetric Receive-only
        Supports auto-negotiation: Yes
        Supported FEC modes: BaseR RS
        Advertised link modes:  1000baseT/Full
                                10000baseT/Full
                                25000baseCR/Full
        Advertised pause frame use: No
        Advertised auto-negotiation: Yes
        Advertised FEC modes: None
        Speed: 25000Mb/s
        Duplex: Full
        Port: FIBRE
        PHYAD: 1
        Transceiver: internal
        Auto-negotiation: on
        Supports Wake-on: d
        Wake-on: d
        Current message level: 0x00002001 (8193)
                               drv hw
        Link detected: no
```
注意，不要以为`link detected: no` 表示是否有网线连接。
stackexchange有一个有趣的[连接](https://unix.stackexchange.com/questions/407151/check-if-network-cable-is-plugged-in-given-nic)，他就是用`link detect`来判断，其实是不对的。
