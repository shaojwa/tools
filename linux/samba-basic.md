###### samba基础  
@20151202  
本文基于CentOS-7  
  
  
###### 检查samba是否已经安装  
安装包检查 rpm -qa |grep samba   
###### 查看samba状态  
systemctl status smb  
###### 配置samba  
samba配置文件路径/etc/samba/smb.conf  
配置前先备份 mv /etc/samba/smb.conf /etc/samba/smb.conf.bak  
[work]  
path = /home/shaojwa/work  
public = yes  
browsable = yes  
writable = yes  
guest ok = yes  
read only = no  
###### 启动samba  
systemctl start smb  
此时从windows下访问linux的samba目录失败  
###### 关闭SELinux  
查看selinux状态 sestatus  
如果状态是enabled则尝试关闭selinux  
编辑/etc/selinux/config文件  
将其中的SELINUX=enforcing改为SELINUX=disabled  
重启  
此时从windows访问linux共享依然失败  
###### 关闭防火墙  
systemctl stop firewalld  
此时从windows下访问linux的贡献时提示输入用户名密码  
###### 想匿名访问  
需要在conf文件中的[global]部分添加如下两行  
security = user  
map to guest = bad user  
此时从windows下访问linux已经能出现共享目录  
但是没有权限访问  
  
***  
  
  
