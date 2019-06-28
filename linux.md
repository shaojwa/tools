#### apt search 和 apt-cache search 的区别
    
    apt search pylint
    apt-cache search pylint

#### 查看某个apt包信息

    apt show pylint

#### awk中如果分割符是[]要怎么处理

    awk –F ‘[][]’ // [is closed with ]， except when ] follows immediately the opening [

#### awk 显示最后一列

    awk '{print $(NF)}'
    
#### basename
    
#### bash 命令输入几个技巧

    !!	最后一条命令
    !n	第n条命令
    !-n	倒数第n条命令
    !string	以string开始的最近一条命令
    !^	第一个参数
    !$	最后一个参数
    !*	除第一个命令之外的所有参数
    ^s1^s2	将上一条命令中的s1切换为s2
    !!:n-m	上一条命令的n-m个参数。
 
 #### date 
 
    date -s "-5 seconds"
    date -s "+5 seconds"
    date -s "-5 mins"
    date -s "+5 mins"
    date -s "-5 hours"
    date -s "+5 hours"

#### dirname

#### 怎么挂载debugfs

    mount -t debugfs none /sys/kernel/debug

#### 提起deb包中的文件

    dpkg-deb -x package.deb extract/
   
#### 对文本折行
 
    fold –s
 
#### gcc g++ 安装

    yum install gcc
    yum install gcc-c++


#### pylint 用法
    
    pylint --rcfile=conffile module.py      // 某模块
    pylint --rcfile=conffile packagename    // 某个包

    
#### readline 相关快捷键

    ctrl-a // 光标跳转到行头
    ctrl-e // 光标跳转到行尾
    esc-b // 往后移动一个词
    esc-f // 往前移动一个字符
    ctrl-b // 往后移动一个字符
    ctrl-f // 往前移动一个字符
    ctrl-u // 从光标位置删除到行头
    ctrl-k // 从光标位置删除到行尾
    ctrl-w // 往后删一个词
    esc-d // 往前删一个词
    ctrl-h // 往后删一个字符
    ctrl-d // 往前删一个字符
    ctrl-x ctrl-u // undo 回退
    ctrl-_ // 回退
    ctrl-y // 粘贴前一次通过ctrl-w或esc-d删除的词
    ctrl-t // 互换两个字符
    esc-t // 互换两个词
    ctrl-l // 清屏
    ctrl-j
    ctrl-g
    !!:/s/--old_option/--new_option/
    ctrl-v ctrl-j 多行编辑

#### 如何分割文件

    split
    
#### 常用压缩解压命令

    tar -cf vdbench.tar vdbench/
    tar -czf vdbench.tar.gz vdbench/
    tar –xf example.tar
    
#### tcpdump常用法

    -n：不将ip解析为域名
    -m: 全部显示port
    -X: 以ASCII 和 十六进制显示
    -i: tcpdump -i eth0
    -b: ip/arp/rarp
    -t: 不显示时间

    tcpdump host 10.99.68.34
    tcpdump –i em3
    tcpdump dst port not telnet
    tcpdump src host 192.168.0.1 and dst net 192.168.0.0/24
    tcpdump -i bond1  host 172.12.15.162 and port 6800


#### 怎么配置网络延时

    tc qdisc del  dev ethA08-0 root netem delay 5s
    tc qdisc add dev eth1 root netem delay 3s
    tc qdisc del dev eth1 root netem delay 3s
    tc qdisc show dev eth1
    
 ### vimdiff 常用命令
 
    vimdiff
    diffget
    diffput
    diffu[pdate]
    do //own
    dp //put
    ]c //next diff
    [c //prev diff
    zo
    zc
    
#### xargs常用法
    
    cat hosts | xargs -I{} ssh root@{} hostname
    sudo locate -br ^.*\\.sh$  | xargs -i bash -c 'echo {} >> total.sh; cat {} >> total.sh'

#### yum

    yum provides ifconfig
    yum whatprovides ifconfig
    yum install net-tools

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
    
#### 查看内核配置 

sysctl下的很多配置的解释可以到：https://www.kernel.org/doc/Documentation/sysctl 找到。　　
sysctl 和 在proc下的操作sys是一致的，所以相比/proc/sys这么长的路径，还是用sysctl来得快：　　

#### 丢弃内核缓存 

非破坏性操作，并不会释放脏对象。官方文档已经说明，这不是一个控制内核各种缓存增长的方法。  
该操作会引起性能问题，因为他丢弃缓存对象，因此还有明显的IO以及CPU消耗来重新创建这些对象，特别是对象正在重度使用的时候。

    vm.drop_caches // 1: 释放页缓存, 2:释放可回收的slab对象包括dentries和inodes，3：页缓存和slab对象
    
#### 内核中的tcp连接保活参数

    tcp_keepalive_time: 最后一个数据包和第一次保活探测之间的时间间隔。
    tcp_keepalive_intvl: 包括探测之间报文之间的时间间隔。
    tcp_keepalive_probes: 连接被标记为dead时所需要的无返回探测报文个数。

#### 什么是slab

    slab是一种Linux内存分配算法。

#### watchdog_thresh是干什么的

    kernel.watchdog_thresh

用来控制hrtimer（高精度定时器）和NMI（不可屏蔽中断）的事件的频率。
进而也影响到softlockup 和 hardlockup的筏值，通常这个筏值是watchdog_thresh的两倍。

#### dirtytime_expire_seconds

都知道atime的改变只是文件访问引起的，但是这个inode却脏了。inode脏了是需要下刷inode到disk的。所以这个问题就有多种优化思路：  
noatime：直接干掉atime，让系统中的atime失效。  
reatime：ctime和mtime的时间晚于atime时才去更新atime。  
lazytime，控制inode下发的时间。  
后台bdi用来写回dirty inode，就是bdi_writeback->b_dirty，就看dirty 的inode什么时候放到这个队列。  
如果是i_size等关键inode属性改变，具体文件系统层会放到这个队列 ，如果是ctime等不关键属性，那么VFS层负责把inode放到这个队列中。  


#### 系统调用号在什么头文件定义？
    
    asm/unistd_64.h:190:#define __NR_gettid 186
    bits/syscall.h:577:# define SYS_gettid __NR_gettid  