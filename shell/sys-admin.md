#clock
同事管理linux服务器，服务器时间一直显示有问题。今天专门去看了下。
系统设置时区之后，修改当前时间，重启系统又有问题。后来发现，是没有写入到硬件时钟。linux系统的两个时钟，硬件使用和系统时钟需要同步。
系统启动时，系统时钟需要从硬件时钟中读取时间。查看硬件时间用clock 或者hwclock命令。和系统时间的同步用：

clock --systohc //把系统时间同步到硬件
clock --hctosys //把硬件时间同步到系统


#init

linux下的run-leveld的含义就好像windows下的正常模式，安全模式，命令行模式等等。以图形界面登入linux，runlevel一般是5，而字符界面登入linux，runlevel一般是3。linux一般有8个level：

Runlevel System State  
0 Halt the system  
1 Single user mode  
2 Basic multi user mode  
3 Multi user mode  
5 Multi user mode with GUI  
6 Reboot the system  
S, s Single user mode 

#man
linux下命令巨多，有的是所谓的内建（built-in command），比如read，有的不是比如grep。平时查命令用法用man，但是内建命令怎么查？一直不清楚，最近专门了解了下，做点记录。
## 如何查内建命令用法
用help，其中help也是一个内建命令，查起来很方便，不需要依赖网络查用法，这是重点。
## 和man区别
这个问题不懂，只能网上找，按照自己的理解。

- help是bash内建命令，使用bash内部的数据结构获取保存信息。
而man不是。help只用来查看bash命令。所谓的内建，在我看来就是在bash进程里执行，终端是一个进程。写到这里，想到另外一个问题。如何查看当前shell的pid？

## 怎么看一个命令是不是内建命令
用type，比如：

    # type cd
    cd is a shell buildin
    # type grep
    grep is hashed (/bin/grep)
    
## 一个命令能不能同时是内建也是外部命令
 能，比如pwd，至于为什么还不清楚， 默认情况下是先使用内建命令。

## 如何查询是否存在相关功能的命令？
直接输入apropos [keyword], 即可查看与keyword相关功能的命令。
很强大，和好用。

## 如何查看当前正在使用的bash的pid
其实很简单$$命令就能显示当前进程的pid
比如我在linux terminal下运行得到：

    # echo $$
    bash: 2085: command not found
    # ps axu | grep 2085
    root 2085 0.0 0.1 5232 1664 pts/0 S 09:38 0:00 bash

## 如何关闭内建命令
    
    enable -n
## 查看所有激活的内建命令

    enable -a

#who命令
基本功能不介绍两点说明  
（1）TTY字段下显示tty表示直连终端，pts标识虚拟终端。比如通过SecureCRT就显示pts。  
（2）这玩意居然能查看系统最后一次重启的时间（who -b）有点意外。  
（3）查看当前终端 who -m  
（4）查看对应的shell 进程id： who -u （自然可以和-m配合）  
（5）查看run-level：who -r  


#w命令
它告诉你当前系统有谁登入，从哪里登入，都在执行什么命令。
所以linux发行版都包含该命令。它差不多少是who和uptime功能的组合。