@20151202

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


####VMware相关的虚拟网络设备
[参考这里](http://blog.csdn.net/lwbeyond/article/details/7648509)  
虚拟交换机： 
VMWare安装完成之后有三个虚拟交换机   
VMnet0：桥接模式下的虚拟交换机  
VMnet1：在host-only模式下的虚拟交换机  
VMnet8：在NAT模式下的虚拟交换机  

虚拟网卡：  
VMnet Network Adapter VMnet1：在host-only模式下，Host于Host-Only虚拟网络进行通信达呃虚拟网卡，这是在物理机的虚拟网卡，和虚拟机上的虚拟网卡不是一个概念。  
VMnet Network Adapter VMnet8：在NAT模式下，Host与NAT虚拟网络进行通信的虚拟网卡。


####虚拟机里配置CentOS为NAT模式
虚拟机安装好CentOS之后默认采用NAT模式，所以只需要在MVware中设置使用NAT模式，并在CentOS中打开开启启动开关 ONBOOT=yes就可以，默认情况下得到的IP地址是192.168.59.0/24，这个地址是VMWare配置的DHCP地址范围，可以在VMWare上修改。


####虚拟机里配置CentOS为bridged模式

####虚拟桥接网卡
在虚拟机里安装好CentOS之运行ifconfig会友现在一张虚拟网卡virbr0，要了解这方面内容，详细的可以参考[这里](http://wiki.libvirt.org/page/VirtualNetworking)。先了解几个概念：

####虚拟网络交换机
在宿主机里，虚拟网络交换机以网卡的形式显示。默认的一个交换机，在
libvirt守护进程安装并启动时创建，显示为virbr0。

可以通过通过查看libvirtd来查看该守护进程是否存在：

	$ ps -aux | grep libvirtd

你可以通过ifconfig virbr0 来查看相关的信息。
 	
	$ ifconfig virbr0

或者你使用ip命令
	
	$ip addr show virbr0

####默认模式
在默认情况下，虚拟网络交换机工作在NAT模式下。DHCP给每个虚拟网络交换机分配一个地址段。Libvirt通过dnsmasq来作为DNS和DHCP服务器。可以通过查看dnsmasq查看该守护进程：

	$ps -aux | grep dnsmasq

同时可以看到该守护进程的配置文件。	

####其他模式
还有两种模式：第一是routed模式，就是我们常说的bridged模式。第二种是Isolated模式。

####查看
 
* 运行ifconfig  
* 运行virsh net-list

结果一般是：

	Name      State     Autostart  Persistent
	-----------------------------------------
	default   active    yes        yes  

####禁用

	virsh net-destroy default

####启用

	virsh net-start default

####删除

	virsh net-undefine default

####编辑

	virsh net-edit default

####nat改为bridge
