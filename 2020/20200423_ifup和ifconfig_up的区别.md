https://access.redhat.com/solutions/27166

1. ifconfig直接控制interface，而ifup/ifdown是执行network-scripts下的脚本。
1. ifconfig up eth0" 只是启用网口，但是并不设置IP地址，而ifdown一般会直接设置ip地址。
1. ifconfig 和 ip 命令通过 ioctl()去启用或者停用网口。
1. ifconfig 不会配置路由，而ifup有时候会根据配置设置静态路由。
