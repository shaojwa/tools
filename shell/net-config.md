**本文基于CentOS**  
@20151201

##网络服务管理

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


##虚拟桥接网卡

在虚拟机里安装好CentOS之运行ifconfig会友现在一张虚拟网卡virbr0
**查看virbr0状态** 
 
* 运行ifconfig  
* 运行virsh net-list

结果一般是：

	Name      State     Autostart  Persistent
	-----------------------------------------
	default   active    yes        yes  
**禁用virbr0**
如果你想禁用就运行如下命令

	virsh net-destroy default

**启用virbr0**

	virsh net-start default

**编辑virbr**

	virsh net-edit default

**nat改为bridge**
