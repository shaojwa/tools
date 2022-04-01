#### 查看丢包

netstat 是在查看网络延时问题是首先想到的命令，因为 man netstat 说就有 inferface statistics信息。但是这个命令已经被废弃，建议使用ss。
但是用netstat 实在是成习惯。

#### 查看网卡统计信息
```
// Replacement for netstat -i is ip -s link.
netstat -i
netstat -I=ethA3d-0
```

#### 查看链接
    -t，-u分别表示tcp，udp的socket。
    -l，显示listening 的socket，默认情况下是忽略的。
    -n，主机和端口都显示数字，默认情况下会把部分ip和端口转为主机和服务。
    -p，显示进程号以及进程名。
    netstat 如果要查看listen，需要用-a，因为默认选项不包含listen
