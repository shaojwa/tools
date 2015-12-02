@文档基于CentOS

#查看系统完整信息
	uname -a

#查看系统架构
	arch 		/* deprecated since release 2.13 */
	uname -m 	/* identical with arch */

#任务控制
	ctrl+z 	/* suspend the current job */

#查看快捷键绑定
	bind -p

#设置yum源
创建cdrom.repo文件包含如下内容： 

	[cdrom]
	name=cdrom-repo
    baseurl=file:///mnt/cdrom
    enable=1
    gpgcheck=0

#挂载
    mdir  /mnt/cdrom
    mount -t auto /dev/cdrom /mnt/cdrom

#查看当前正在使用的bash的pid
其实很简单$$命令就能显示当前进程的pid,比如我在linux terminal下运行得到：

    # echo $$
    bash: 2085: command not found
    # ps axu | grep 2085
    root 2085 0.0 0.1 5232 1664 pts/0 S 09:38 0:00 bash

#查看系统用户-who
基本功能不介绍两点说明  
（1）TTY字段下显示tty表示直连终端，pts标识虚拟终端。比如通过SecureCRT就显示pts。  
（2）这玩意居然能查看系统最后一次重启的时间（who -b）有点意外。  
（3）查看当前终端 who -m  
（4）查看对应的shell 进程id： who -u （自然可以和-m配合）  
（5）查看run-level：who -r  

#查看系统用户以及执行的命令-w
它告诉你当前系统有谁登入，从哪里登入，都在执行什么命令。
所以linux发行版都包含该命令。它差不多少是who和uptime功能的组合。


#同步系统时间-clock
同事管理linux服务器，服务器时间一直显示有问题。今天专门去看了下。系统设置时区之后，修改当前时间，重启系统又有问题。后来发现，是没有写入到硬件时钟。linux系统的两个时钟，硬件使用和系统时钟需要同步。系统启动时，系统时钟需要从硬件时钟中读取时间。查看硬件时间用clock 或者hwclock命令。和系统时间的同步用：

	clock --systohc //把系统时间同步到硬件
	clock --hctosys //把硬件时间同步到系统

#调整运行级别-init
#查看运行级别-runlevel
linux下的run-leveld的含义就好像windows下的正常模式，安全模式，命令行模式等等。以图形界面登入linux，runlevel一般是5，而字符界面登入linux，runlevel一般是3。linux一般有8个level：
 
	0 Halt the system  
	1 Single-user mode  
	2 Multi-user mode  
	3 Multi-user mode with networking
	4 Not used/user-deinable
	5 Multi-user mode with GUI  
	6 Reboot the system  

#man
linux下命令巨多，有的是所谓的内建（built-in command），比如read，有的不是比如grep。平时查命令用法用man，但是内建命令怎么查？一直不清楚，最近专门了解了下，做点记录。

#help查内建命令用法
help也是一个内建命令，查起来很方便，不需要依赖网络查用法，这是重点。

#help和man区别
这个问题不懂，只能网上找，按照自己的理解。

- help是bash内建命令，使用bash内部的数据结构获取保存信息。
而man不是。help只用来查看bash命令。所谓的内建，在我看来就是在bash进程里执行，终端是一个进程。写到这里，想到另外一个问题。如何查看当前shell的pid？

#查看一个命令是否为内建命令
using type

    # type cd
    cd is a shell buildin
    # type grep
    grep is hashed (/bin/grep)
    
##一个命令能不能同时是内建也是外部命令
 可以比如pwd，至于为什么还不清楚， 默认情况下是先使用内建命令。

#如何查询是否存在相关功能的命令
直接输入apropos [keyword], 即可查看与keyword相关功能的命令。
很强大，和好用。


##如何关闭内建命令
    
    enable -n
##查看所有激活的内建命令

    enable -a


#网络

从CentOS-7以及RHEL-7开始开始使用systemd。
这是一个系统和服务管理器。

	sudo systemctl status  network.service
    sudo systemctl status  network
	sudo systemctl start   network.service
    sudo systemctl start   network
    sudo systemctl stop    network.service
    sudo systemctl stop    network
    sudo systemctl restart network.service
    sudo systemctl restart network

在此之前的版本可以用：

    service network status
	service network stop
	service network start
	service network restart

等价于使用初始化脚本：

	/etc/init.d/network status
	/etc/init.d/network restart
	/etc/init.d/network stop
	/etc/init.d/network start


#VMware相关的虚拟网络设备
[参考这里](http://blog.csdn.net/lwbeyond/article/details/7648509)  
虚拟交换机： 
VMWare安装完成之后有三个虚拟交换机   
VMnet0：桥接模式下的虚拟交换机  
VMnet1：在host-only模式下的虚拟交换机  
VMnet8：在NAT模式下的虚拟交换机  

虚拟网卡：  
VMnet Network Adapter VMnet1：在host-only模式下，Host于Host-Only虚拟网络进行通信达呃虚拟网卡，这是在物理机的虚拟网卡，和虚拟机上的虚拟网卡不是一个概念。  
VMnet Network Adapter VMnet8：在NAT模式下，Host与NAT虚拟网络进行通信的虚拟网卡。


#虚拟机里配置CentOS为NAT模式
虚拟机安装好CentOS之后默认采用NAT模式，所以只需要在MVware中设置使用NAT模式，并在CentOS中打开开启启动开关 ONBOOT=yes就可以，默认情况下得到的IP地址是192.168.59.0/24，这个地址是VMWare配置的DHCP地址范围，可以在VMWare上修改。


#虚拟机里配置CentOS为bridged模式

#虚拟桥接网卡
在虚拟机里安装好CentOS之运行ifconfig会友现在一张虚拟网卡virbr0，要了解这方面内容，详细的可以参考[这里](http://wiki.libvirt.org/page/VirtualNetworking)。先了解几个概念：

##虚拟网络交换机
在宿主机里，虚拟网络交换机以网卡的形式显示。默认的一个交换机，在
libvirt守护进程安装并启动时创建，显示为virbr0。

可以通过通过查看libvirtd来查看该守护进程是否存在：

	$ ps -aux | grep libvirtd

你可以通过ifconfig virbr0 来查看相关的信息。
 	
	$ ifconfig virbr0

或者你使用ip命令
	
	$ip addr show virbr0

##默认模式
在默认情况下，虚拟网络交换机工作在NAT模式下。DHCP给每个虚拟网络交换机分配一个地址段。Libvirt通过dnsmasq来作为DNS和DHCP服务器。可以通过查看dnsmasq查看该守护进程：

	$ps -aux | grep dnsmasq

同时可以看到该守护进程的配置文件。	

##其他模式
还有两种模式：第一是routed模式，就是我们常说的bridged模式。第二种是Isolated模式。

##查看
 
* 运行ifconfig  
* 运行virsh net-list

结果一般是：

	Name      State     Autostart  Persistent
	-----------------------------------------
	default   active    yes        yes  

##禁用

	virsh net-destroy default

##启用

	virsh net-start default

##删除

	virsh net-undefine default

##编辑

	virsh net-edit default

##nat改为bridge
