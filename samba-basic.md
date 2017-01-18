###### samba基础  
@20151202  
本文基于CentOS-7  
[参考文档](http://www.unixmen.com/install-configure-samba-server-centos-7/)
  
  
###### 检查samba是否已经安装  
安装包检查 rpm -qa |grep samba 
或者 yum list installed | grep samba  

###### 配置一个允许所有权限的匿名共享
首先创建一个目录  
mkdir -p /home/shaojwa/work  
chmod -R 777 /home/shaojwa/work  

###### 配置samba  
samba配置文件路径/etc/samba/smb.conf  
配置前先备份 mv /etc/samba/smb.conf /etc/samba/smb.conf.bak  

在[global]下配置  
workgroup = WORKGROUP

添加一下内容  

[work]  
    path = /home/shaojwa/work  
    public = yes  
    browsable = yes  
    writable = yes  
    guest ok = yes  
    read only = no  
###### 启动samba  
systemctl start smb  
systemctl start nmb
systemctl enable smb
systemctl enable nmb

###### 用testparm 检查smb配置


###### 配置selinux

    setsebool -P samba_enable_home_dirs on
    chcon -t samba_share_t /samba/anonymous_share/
 
###### 关闭SELinux  
查看selinux状态 sestatus  
如果状态是enabled则尝试关闭selinux  
编辑/etc/selinux/config文件  
将其中的SELINUX=enforcing改为SELINUX=disabled  
重启  
此时从windows访问linux共享依然失败  


###### 关闭防火墙  
systemctl stop firewalld  //注意是firewalld
###### 或者配置防火墙
    firewall-cmd --permanent --add-port=137/tcp
    firewall-cmd --permanent --add-port=138/tcp
    firewall-cmd --permanent --add-port=139/tcp
    firewall-cmd --permanent --add-port=445/tcp
    firewall-cmd --permanent --add-port=901/tcp
    firewall-cmd --reload

此时可以看到存在word共享当时无法打开文件夹

###### 配置权限打开文件夹

此时从windows下访问linux的贡献时提示输入用户名密码  

###### 想匿名访问  
需要在conf文件中的[global]部分添加如下两行  
security = user  
map to guest = bad user  
此时从windows下访问linux已经能出现共享目录  
但是没有权限访问  
  

###### 创建安全共享
创建用户  
useradd -s /sbin/nologin smbusr  
创建组  
groupadd smbgrp  
将用户加入组  
usermod -a -G gmbgroup smbgrp  
设置密码
smbpasswd -a smbusr  
创建共享目录后设置权限  
mkdir /samba/share
chmod -R 0755 /samba/share  
chown -R smbusr:smbgrp /samba/share  
配置smb.conf  
[share]  
path = /samba/share  
writable = yes  
browsable = yes  
guest ok = no  
valid users = @smbgrp  
如果不关闭SELinux就需要添加如下配置  
chcon -t samba_share_t /samba/share/  
重启smb  
systemctl restart smb  
systemctl restart nmb  
最后提醒  
共享目录最好不要放在home下  
因为home是其中一个特殊共享  
有对应的配置

