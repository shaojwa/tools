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
    
####　查看内核配置

sysctl下的很多配置的解释可以到：https://www.kernel.org/doc/Documentation/sysctl 找到。　　
sysctl 和 在proc下的操作sys是一致的，所以相比/proc/sys这么长的路径，还是用sysctl来得快：　　

#### 放弃缓存 vm.drop_caches 

非破坏性操作，并不会释放脏对象。官方文档已经说明，这不是一个控制内核各种缓存增长的方法。  
该操作会引起性能问题，因为他丢弃缓存对象，因此还有明显的IO以及CPU消耗来重新创建这些对象，特别是对象正在重度使用的时候。

    vm.drop_caches // 1: 释放页缓存, 2:释放可回收的slab对象包括dentries和inodes，3：页缓存和slab对象

#### 什么时slab

    slab是一种Linux内存分配算法。

#### watchdog_thresh是干什么的

    kernel.watchdog_thresh

用来控制hrtimer（高精度定时器）和NMI（不可屏蔽中断）的事件的频率。
进而也影响到softlockup 和 hardlockup的筏值，通常这个筏值是watchdog_thresh的两倍。


#### 常用压缩解压命令

    tar -cf vdbench.tar vdbench/
    tar -czf vdbench.tar.gz vdbench/
    tar –xf example.tar

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
    
    
