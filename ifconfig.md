#### ifconfig
```
// ifconfig is used to configure the kernel-resident network interfaces.
// if no arguments are given, ifconfig displays the status of the currently active interfaces.

alias interfaces
ifconfig eth1:0 down // remove alias
ifconfig eth1:0 172.16.84.199/24
```

#### ifup 和 ifconfig <interface> up 的区别

根据redhat的解释(https://access.redhat.com/solutions/27166)：

1. ifconfig直接控制interface，而ifup/ifdown是执行network-scripts下的脚本。
1. ifconfig up eth0" 只是启用网口，但是并不设置IP地址，而ifdown一般会直接设置ip地址。
1. ifconfig 和 ip 命令通过 ioctl()去启用或者停用网口。
1. ifconfig 不会配置路由，而ifup有时候会根据配置设置静态路由。

根据man中的说明，ifup是基于接口定义文件/etc/sysconfig/network来配置网口的。
而ifconfig是用来配置驻留内核的网口，用于在需要在启动时安装接口，ifconfig <interface> up用来激活。
如果你修改是ifcfg配置文件，那么ifconfig down-up 是没用的，需要用ifdown/ifup。
