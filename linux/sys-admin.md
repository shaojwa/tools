@文档基于CentOS
@20151202

###### 查看系统完整信息
	uname -a

###### 查看系统架构
	arch 		/* deprecated since release 2.13 */
	uname -m 	/* identical with arch */

###### 任务控制
	ctrl+z 	/* suspend the current job */

###### 查看快捷键绑定
	bind -p


###### 设置yum源
创建cdrom.repo文件包含如下内容： 

	[cdrom]
	name=cdrom-repo
    baseurl=file:///mnt/cdrom
    enable=1
    gpgcheck=0

###### 挂载
    mdir  /mnt/cdrom
    mount -t auto /dev/cdrom /mnt/cdrom

###### 查看当前正在使用的bash的pid
其实很简单$$命令就能显示当前进程的pid,比如我在linux terminal下运行得到：

    # echo $$
    bash: 2085: command not found
    # ps axu | grep 2085
    root 2085 0.0 0.1 5232 1664 pts/0 S 09:38 0:00 bash

###### 查看系统用户-who
基本功能不介绍两点说明  
（1）TTY字段下显示tty表示直连终端，pts标识虚拟终端。比如通过SecureCRT就显示pts。  
（2）这玩意居然能查看系统最后一次重启的时间（who -b）有点意外。  
（3）查看当前终端 who -m  
（4）查看对应的shell 进程id： who -u （自然可以和-m配合）  
（5）查看run-level：who -r  

###### 查看系统用户以及执行的命令-w
它告诉你当前系统有谁登入，从哪里登入，都在执行什么命令。
所以linux发行版都包含该命令。它差不多少是who和uptime功能的组合。


###### 同步系统时间-clock
同事管理linux服务器，服务器时间一直显示有问题。今天专门去看了下。系统设置时区之后，修改当前时间，重启系统又有问题。后来发现，是没有写入到硬件时钟。linux系统的两个时钟，硬件使用和系统时钟需要同步。系统启动时，系统时钟需要从硬件时钟中读取时间。查看硬件时间用clock 或者hwclock命令。和系统时间的同步用：

	clock --systohc //把系统时间同步到硬件
	clock --hctosys //把硬件时间同步到系统

###### 调整运行级别-init
###### 查看运行级别-runlevel
linux下的run-leveld的含义就好像windows下的正常模式，安全模式，命令行模式等等。以图形界面登入linux，runlevel一般是5，而字符界面登入linux，runlevel一般是3。linux一般有8个level：
 
	0 Halt the system  
	1 Single-user mode  
	2 Multi-user mode  
	3 Multi-user mode with networking
	4 Not used/user-deinable
	5 Multi-user mode with GUI  
	6 Reboot the system  
