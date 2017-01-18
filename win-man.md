@20151202

## shortcuts  
## commands  
[ref1: control panel tools](https://support.microsoft.com/zh-cn/kb/192806)

##### 获取卷(分区)的序列号
vol [drive:]  
###### 获取字符映射表
charmap

###### 控制面板类
sysdm.cpl



#### 打开系统网络链接控制面板
ncpa.cpl

#### 添加删除程序
appwiz.cpl

#### 时间日期面板
timedate.cpl

#### 桌面配置面板
desk.cpl

#### 辅助功能配置 
access.cpl

#### Internet配置
inetcpl.cpl

#### 防火墙配置
firewall.cp

#### 其区域 Netcpl.cpl
#### 区域和语言
Intl.cpl

#### console 系列
control system
control admintools
control mouse
control keyboard

###### Scroll Lock
@20151202
今天早上在虚拟机里的CentOS上运行命令。发现无法输入，看了下发现ScrollLock等变量，于是按ScrollLock键使其不亮，发现就可以输入。
在物理机上不会有这个问题，在虚拟机的shell里存在。在shell里我试了下发现按下改键之后，你所有的命令都会缓存起来，等你再次按ScrollLock随时，之前的所有输入会一次性得显示出来。
