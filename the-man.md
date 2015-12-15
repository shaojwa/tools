***
v0.1
@pwns
***
# index
tools  
sevices  
cmdlines  
porotls  
others  
***
# tools
***
## vim
### 设置
设置字体  

    set guifont=courier_new:h12

设置窗口显示行数  

    set lines=40

设置窗口显示列数  

    set columns=80

设置光标所在行高亮  

    set cursorline

设置底部状态栏显示信息  

    set statusline+=%F
    
自动缩进字符数  

    set shiftwidth=4
    
tab键长度  

    set tabstop=4
    
空格替换tab  

    set expandtab
    
设置显示空白字符  

    set list
    set listchars=tab:>-
    
去掉窗口工具栏  

    set guioptions-=T

设置tab页  

    set guitablabel=%N:%M:%F
    
是否折行显示  

    set wrap
    set nowrap
    
配置替换字符

    set listchars=eol:↓,tab:→→,trail:·
    set list

配置映射  

    map <M-1> 1gt
    map <M-2> 2gt
    map <M-3> 3gt
    map <M-4> 4gt
    map <M-5> 5gt
    map <M-6> 6gt
    map <M-7> 7gt
    map <M-8> 8gt
    map <M-9> 9gt
    map <M-F1> :tabclose<CR>
    map <M-F2> :tabedit<CR>

### 自动缩进格式化  
VISUAL BLOCK模式下（windows下按ctrl+q）  
选中后按=可以自动缩进  

### 左右缩进块代码  
VISUAL BLOCK模式下（windows下按ctrl+q）  
选中后按<或者>  

### 单行缩进  
正常模式下  
缩进光标所在单行可以按两次<(左缩进)或者>（右缩进）  

### 回到光标上一次位置  

反引号

    ``
或者引号

    ''

### 显示特定字符
可以在vimrc文件中用set listchar来配置用特殊字符显示不可见字符  
比如想用$先显示一行的末尾可以配置 set listchars=eol:$  
然后在命令模式下运行:set list 就可以看到  
可以用:set nolist取消显示  
对于部分特定字符  

### 自动重新加载vimrc文件

    :source $myvimrc

### 替换

    vim中的替换命令为:s
    
其中s的取意substitute  
完整语法：  

    :[range]s/search/replace/[options]

先设options为空则   
* 如果range为空，则替换光标当前行的第一个匹配项。  
* :8,10s 则替换8-10行中，每一行的提一个匹配项。  
现在option选择为g  
* :s/search/replace/g 替换每一行中出现的所有匹配项。  
* :8,10s/search/replace/g替换8-10行中每一行出现的所有匹配项。  
更多参见[这里](http://vim.wikia.com/wiki/Search_and_replace)  

### 匹配
匹配边界可以考虑用:  

    \< 和 \>  

匹配空格用斜杠转义:  

    \空格  

想用需要括号需要转义:

    \(\)

### 删除

    d$  //删除光标到行末
    d^  //删除光标到行头
    dgg //删除当前行到第一行的所有行
    dG  //删除当前行到最后一行的所有行

### 拷贝

    y   //拷贝当前行
    ygg //拷贝从当前行到第一行的所有行
    yG  //拷贝从当前行到最后一行的所有行
    y0  //拷贝从光标到行首
    y^  //拷贝从光标到非空行首
    y$  //拷贝从光标到行尾
    yg_ //拷贝从光标到非空行尾
    ye  //拷贝从当前字符到单词结束的所有字符
    yw  //拷贝从当前字符到下一个单词开始

### 查看帮助

查看普通模式命令    无前缀  

    :help x
    
查看可视模式命令    v_  

    :help v_u
    
查看命令行模式命令  :  

    :help :quit

找到标签后按CTRL-]进入选项的详细信并可以按CTRL-T或者CTRL-O返回  
进入帮助之后可以用/进行特定内容查找  

##### 输入特殊字符
在插入模式下按CTRL-K  
此时会出现一个问号  
然后直接输入表示特殊字符的符号码  
如何查看某个特殊字符的符号码？  
在命令模式下输入:digraphs就会弹出字符映射表  
然后找到你需要的特殊字符  
其中的前两个符号就是特殊字符的符号码  
中间是特殊字符的样子  
最后是对应的十进制的unicode值  
比如输入向下箭头  
就可以先按CTRL-K然后再输入-v就可以  

***
## git
v0.1@ 20131219  
v0.2@ 20141125  
v0.3@201151127  

### 创建项目仓库
方法1：创建崭新的git项目仓库  

    git init

方法2：克隆某个仓库自动初始化  

    git clone

### 查看状态

    git status

status = tracked + untracked  
tracked = work + index + history + remote  

#### 查看日志

    git log
    git log -p
    git log -2

### 查看本地clone的代码库

    git remote
    git remote -v

### 查看本地clone版本origin库的所有分支

    git remote show origin

### diff
work和index之间  

    git diff

work和history之间  

    git diff HEAD

work和remote之间  

    git diff HEAD~

index和history之间  

    git diff --cached
    git diff --staged

index和remote之间  

    git diff --cached HEAD~


### 提交修改
从untracked到tracked  

    git add

从work到index  

    git add
    git add .
    git add -u .
    git add -p <file>

从index到history  

    git commit -m <some message>

从index到history  

    git commit -a -m <some message>  

从history到remote  

    git push  https://github.com/shaojwa/leetcode.git master

### 回退
从tracked到untracked  

    git rm --cached <file>

从index到work  

    git checkout --files

从history到index  

    git reset --files

### 更新
从remote更新到本地history  

    git remote update

### 远程添加新的分支

    git remote add doc https://github.com/shaojwa/doc.git

### 其他

    git commit -m "`date`"
***
## wireshark
### http方法过滤

    http.request.method == "POST"

注意点1加引号2大写POST  

### host过滤
***
## office

### 电子表格单元格内换行

openoffice:

    ctrl+enter

msoffice:

    alt+enter

# services
***
##  ftp
@20151203  

### 主动模式
主动就是传输数据时  
客户端开启某端口并PORT命令告诉服务器  
服务器连接客户端  

### 被动模式
被动就是传输数据时  
服务器开启某端口并通过PASV命令通知客户端  
客户端连接服务器  

### 配置文件

    /usr/sbin/vsftpd            vsftpd的主程序
    /etc/vsftpd/vsftpd.conf     主配置文件
    /etc/vsftpd.ftpusers        禁止使用vsftpd的用户列表文件
    /etc/vsftpd.user_list       禁止或允许使用vsftpd的用户列表文件
    /var/ftp                    匿名用户主目录
    /var/ftp/pub                匿名用户的下载目录

### 参数含义
是否允许匿名访问

    anonymous_enable=YES

是否允许本地用户登入  

    local_enable=YES
    
允许任何形式的写操作  

    write_enable=YES

umask屏蔽权限022表示所有者群组和其他用户不能写  

    local_umask=022
    
是否允许匿名用户上传文件  

    #anon_upload_enable=YES

是否允许你您不过用户创建文件  

    #anon_mkdir_write_enable=YES

是否在进入目录是显示欢迎信息  

    dirmessage_enable=YES

上传下载文件时记录日志  

    xferlog_enable=YES

是否使用20端口传输数据即是否采用主动模式  

    connect_from_port_20=YES

是否允许匿名上传的文件改变其所有者  

    #chown_uploads=YES
    #chown_username=whoever

设置日志文件路  

    #xferlog_file=/var/log/xferlog

是否采用标准的日志文件格式  

    xferlog_std_formats=YES

空闲会话超时时间  

    #idle_session_timeout=600
    
数据链接超时时间  

    #date_connection_timeout=120

是否采用非特权用户  

    #nopriv_user=ftpsecure

是否识别匿名用户的ABOR请求  
不建议开启但不开启可能使老的ftp客户端混乱  

    #async_abor_enable=YES

ASCII模式下的上传和下载  

    #ascii_upload_enable=YES
    #ascii_download_enable=YES

欢迎提示语句  

    #ftpd_banner=Welcome to blah FTP service

拒绝登入邮件列表  

    #deny_email_enables=YES
    #banned_email_file=/etc/vsftpd/banned_emails

chroot用户使能  

    #chroot_local_user=YES
    #chroot_list_enable=YES
    #chroot_list_file=/etc/vsftpd/chroot_list

是否开启递归  

    #ls_recurse_enable=YES

是否监听ipv4端口  

    #listen=YES

是否监听ipv6端口  
默认情况下开启该选项能同时监听v4和v6端口  

    listen_ipv6=YES

服务名  

    pam_service_name=vsftpd

用户列表使能  

    userlist_enable=NO

tcp  

    tcp_wrappers=YES

最后需要关闭防火墙或者开放ftp服务  

    firewall-cmd --permanent --add-service=ftp

最重要一点 firewall-cmd --reload  
所谓的允许匿名登入不是不使用用户名  
而是可以用ftp或anonymous和空密码登入  
更多选项[参见这里][0]  
[0]:https://www.centos.org/docs/5/html/Deployment_Guide-en-US/s1-ftp-vsftpd-conf.html

***
## service-control
@20151202
从CentOS7开始服务的操作方式发生变化

### 服务操作
service 改为 systemctl

    # service <servcie> status|stop|start|restart
    # systemctl status|start|stop|restart <service>

### 系统自启动列表中删除或者添加

    chkconfig改为systemctl
    # chkconfig <service> off|on
    # systemctl enable|disable <service>
    # chkconfig <service>
    # systemctl is-enabled <service>
    # chkconfig -list
    # systemctl list-unit-files --type=service


### samba
@20151202  
本文基于CentOS-7  
[参考文档](http://www.unixmen.com/install-configure-samba-server-centos-7/)


### 检查samba是否已经安装

    rpm -qa |grep samba
    或者 yum list installed | grep samba

### 配置一个允许所有权限的匿名共享
首先创建一个目录  

    mkdir -p /home/shaojwa/work
    chmod -R 777 /home/shaojwa/work

### 配置samba
配置前先备份

    mv /etc/samba/smb.conf /etc/samba/smb.conf.bak

在[global]下配置  

    workgroup = WORKGROUP

添加以下内容  

    [work]
    path = /home/shaojwa/work
    public = yes
    browsable = yes
    writable = yes
    guest ok = yes
    read only = no

### 启动samba  

    systemctl start smb
    systemctl start nmb
    systemctl enable smb
    systemctl enable nmb

### 用testparm 检查smb配置

### 配置selinux

    setsebool -P samba_enable_home_dirs on
    chcon -t samba_share_t /samba/anonymous_share/

### 关闭SELinux
查看selinux状态  

    sestatus

如果状态是enabled则尝试关闭selinux  
编辑/etc/selinux/config文件  
将其中的  

    SELINUX=enforcing
改为

    SELINUX=disabled

重启  
此时从windows访问linux共享依然失败  


### 关闭防火墙

    systemctl stop firewalld

注意是firewalld
### 或者配置防火墙

    firewall-cmd --permanent --add-port=137/tcp
    firewall-cmd --permanent --add-port=138/tcp
    firewall-cmd --permanent --add-port=139/tcp
    firewall-cmd --permanent --add-port=445/tcp
    firewall-cmd --permanent --add-port=901/tcp
    firewall-cmd --reload

此时可以看到存在word共享当时无法打开文件夹

### 配置权限打开文件夹

此时从windows下访问linux的贡献时提示输入用户名密码  

### 想匿名访问
需要在conf文件中的[global]部分添加如下两行  

    security = user
    map to guest = bad user

此时从windows下访问linux已经能出现共享目录  
但是没有权限访问  


### 创建安全共享

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
***
## net-config
@20151202

从CentOS-7以及RHEL-7开始开始使用systemd。这是一个系统和服务管理器。

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

### VMware相关的虚拟网络设备

[参考这里](http://blog.csdn.net/lwbeyond/article/details/7648509)  
VMWare安装完成之后有三个虚拟交换机：  
VMnet0：桥接模式下的虚拟交换机  
VMnet1：在host-only模式下的虚拟交换机  
VMnet8：在NAT模式下的虚拟交换机  

虚拟网卡：  
VMnet Network Adapter VMnet1：在host-only模式下，Host与Host-Only虚拟网络进行通信，这是在物理机的虚拟网卡，和虚拟机上的虚拟网卡不是一个概念。VMnet Network Adapter VMnet8：在NAT模式下，Host与NAT虚拟网络进行通信的虚拟网卡。  

### 虚拟机里配置CentOS为NAT模式

虚拟机安装好CentOS之后默认采用NAT模式, 所以只需要在MVware中设置使用NAT模式，并在CentOS中打开开启启动开关 ONBOOT=yes就可以，默认情况下得到的IP地址是192.168.59.0/24，这个地址是VMWare配置的DHCP地址范围，可以在VMWare上修改。

### 虚拟机里配置CentOS为bridged模式

### 虚拟桥接网卡

在虚拟机里安装好CentOS之运行ifconfig会友现在一张虚拟网卡virbr0，要了解这方面内容，详细的可以参考[这里](http://wiki.libvirt.org/page/VirtualNetworking)。先了解几个概念：

### 虚拟网络交换机

在宿主机里，虚拟网络交换机以网卡的形式显示。默认的一个交换机，在libvirt守护进程安装并启动时创建，显示为virbr0。可以通过通过查看libvirtd来查看该守护进程是否存在：

    $ ps -aux | grep libvirtd

你可以通过ifconfig virbr0 来查看相关的信息。

    $ ifconfig virbr0

或者你使用ip命令

    $ip addr show virbr0

### 默认模式

在默认情况下，虚拟网络交换机工作在NAT模式下。DHCP给每个虚拟网络交换机分配一个地址段。Libvirt通过dnsmasq来作为DNS和DHCP服务器。可以通过查看dnsmasq查看该守护进程：

    $ps -aux | grep dnsmasq

同时可以看到该守护进程的配置文件。	

### 其他模式

还有两种模式：第一是routed模式，就是我们常说的bridged模式。第二种是Isolated模式。

### 查看

    ifconfig
    virsh net-list

结果一般是：

    Name      State     Autostart  Persistent
    -----------------------------------------
    default   active    yes        yes  

### 禁用

    virsh net-destroy default

### 启用

    virsh net-start default

### 删除

    virsh net-undefine default

### 编辑

    virsh net-edit default

### nat改为bridge
***
## ip-tables
@20151202

Iptables是绝大多数linux发行版内建的防火墙
在CentOS<7的版本中可以使用一下命令

### 查看Iptables的状态

    # service iptables status
    # service ipv6tables status

### 关闭iptables

    # service iptables stop
    # service ipv6tables stop

### 启动iptables

    # service iptables start
    # service ipv6tables start

### 从系统自启动列表中删除iptables

    # chkconfig iptables off
    # chkconfig ipv6tables off

### 将iptables添加进系统自启动列表

    # chkconfig iptables on
    # chkconfig ipv6tables on

在CentOS7之后的版本统一用systemctl命令:  

    # systemctl [status|start|stop|restart] iptables
    # systemctl [status|start|stop|restart] ipv6tables

***
# cmdlines
其实所谓的复用技巧也只是我看网上的资料汇总出来的东西。
只是很多没有单独拿出来介绍，总是和其他的一些技巧一并介绍。
而我写的这篇只关注怎么用最简单的命令复用之前输入过的命令。

***
## command reuse

### ！系列
网上的说法是，这些以！开始的标记（暂且就用标记来称呼吧）都是一些列特殊的环境变量。

### 上一条命令的全部内容

    !!

示例

    $cd test
    $echo !!
    cd test

### 上条命令的第一个参数

    !^

示例
    $cd test
    $echo !^
    test
    
注意不是cd

### 上条命令的最后一个参数

    !$

    $cd first second last
    $echo !$
    last
    
### 上条命令的所有参数

    !*

    $cd first second last
    $echo !$
    first second last

### 最近一条以prefix开始的命令

    !prefix

注意这里的prefix可以是一个或者多个字母表。
看了以上几条命令我只有感慨正则表达无处不在。

### 打印但不执行最近一条以prefix开始的命令

    !prefix:p

### ^系列

    ^foo        //上一条命令中去掉foo之后的命令
    ^foo bar    //上一条命令中去掉foo和bar之后的命令
    ^foo^bar    //上一条命令中把foo换成bar之后的命令

### 最后再说说其他的几个常用的：
回到最近一次目录  

    cd - 

回到登入用户的home目录  

    cd ~

***
##  command edit

linux下命令操作是我最喜欢的方式。
但是编辑命令本身也有一些小技巧值得学习。
因为这样可以让你更快得编辑命令进而节省时间。

### 先说一个有意思的命令
依次显示之前命令的最后一个参数  

    alt+.

这个还是很有用的，比如本来打算输入cat xxx，结果输入 cd xxx。那么你只需要输入cat之后按 alt + .就可以自动补全，如果最后一个参数比较长就很有用。作为对比 ctrl+alt+y 只会记住上一条命令的第一个参数

### 查询命令
进入查询模式  

    ctrl+r  

撤销查询  

    ctrl+g

### 撤销修改

    ctrl+/

### 互换

光标所在位置和行首之间互换

    ctrl+xx

### 移动光标

光标的移动分三种: 行移动，单词移动，字母移动。

    ctrl+a     //移到行首
    ctrl+e     //移到行尾
    alt+f      //以单词为单位向前移动
    atl+b      //以单词为单位向后移动
    ctrl+f     //以字母为单位向前移动
    ctrl+b     //以字母为单位向后移动

### 删除命令  

    ctrl+u    //删除光标后的所有内容
    ctrl+k    //删除光标前的所有内容
    ctrl+w    //删除光标后面的一个单词
    alt+d     //删除光标前面的一个单词
    ctrl+h    //删除光标后面的一个字母
    ctrl+d    //删除光标前面的一个字母

#### 字母互换

    ctrl+t     //互换光标左右字母后光标移到后一个位置

### 单词互换

    alt+t     //互换光标左右两边的单词后移到下个单词位置

### 大小写转换

    alt+c //把光标所在出的字符改为大写然后跳到下一个单词词首
    alt+l //把光标所在处的字符到单词结尾都改为小写
    alt+u //把光标所在处的字符到单词结尾都改为大写

### 查看前后命令
查看之前命令  

    ctrl+p 

查看之后命令  

    ctrl+n

***
## grep

### 文件内容查找

    grep <options> <pattern> <files>

示例  

    grep -rn "loosgood"  * 
    *  表示当前目录所有文件，也可以是某个文件名
    -r 是递归查找
    -n 是显示行号
    -R 查找所有文件包含子目录
    -i 忽略大小写
    -l 只列出匹配的文件名
    -L 列出不匹配的文件名， 
    -w 只匹配整个单词，而不是字符串的一部分


### 查找某个目录信息
使用$来定位  

    ll root | grep roor$

查找man文档中以连字符开始的选项

    $ man chmod | grep [-]R
        -R, --recursive

加上-n显示行号  

    $ man chmod | grep [-]R
    111:  -R, --recursive

最后用more显示从某行开始

    $ man chmod | more +111

***
## man
linux下命令巨多，有的是所谓的内建（built-in command），比如read，有的不是比如grep。平时查命令用法用man，但是内建命令怎么查？一直不清楚，最近专门了解了下，做点记录。

### help查内建命令用法
help也是一个内建命令，查起来很方便，不需要依赖网络查用法，这是重点。

### help和man区别

这个问题不懂，只能网上找，按照自己的理解。help是bash内建命令，使用bash内部的数据结构获取保存信息。
而man不是。help只用来查看bash命令。所谓的内建，在我看来就是在bash进程里执行，终端是一个进程。写到这里，想到另外一个问题。如何查看当前shell的pid？

### 查看一个命令是否为内建命令

    type

    # type cd
    cd is a shell buildin
    # type grep
    grep is hashed (/bin/grep)
    
### 一个命令能不能同时是内建也是外部命令

可以比如pwd，至于为什么还不清楚，默认情况下是先使用内建命令。

### 如何查询是否存在相关功能的命令
直接输入

    apropos [keyword]

即可查看与keyword相关功能的命令。


### 如何关闭内建命令

    enable -n
### 查看所有激活的内建命令

    enable -a

### 查看所有用户

    $ cat /etc/passwd
    $ awk -F':' '{ print $1}' /etc/passwd

### 所有组

    $ cat /etc/group

### 查看组内所有成员

    lid group_name|user_name

### 查看系统完整信息

    uname -a

### 查看系统架构

    arch         /* deprecated since release 2.13 */
    uname -m     /* identical with arch */

### 查看快捷键绑定

    bind -p

### 查看当前正在使用的bash的pid
其实很简单$$命令就能显示当前进程的pid，比如我在linux terminal下运行得到

    # echo $$
    bash: 2085: command not found
    # ps axu | grep 2085
    root 2085 0.0 0.1 5232 1664 pts/0 S 09:38 0:00 bash

### 查看系统用户-who
基本功能不介绍两点说明  
（1）TTY字段下显示tty表示直连终端，pts标识虚拟终端。比如通过SecureCRT就显示pts。  
（2）这玩意居然能查看系统最后一次重启的时间（who -b）有点意外。  
（3）查看当前终端 who -m  
（4）查看对应的shell 进程id： who -u （自然可以和-m配合）  
（5）查看run-level：who -r  

### 查看系统用户以及执行的命令-w
它告诉你当前系统有谁登入，从哪里登入，都在执行什么命令。
所以linux发行版都包含该命令。它差不多少是who和uptime功能的组合。

### 同步系统时间-clock
同事管理linux服务器，服务器时间一直显示有问题。今天专门去看了下。系统设置时区之后，修改当前时间，重启系统又有问题。后来发现，是没有写入到硬件时钟。linux系统的两个时钟，硬件使用和系统时钟需要同步。系统启动时，系统时钟需要从硬件时钟中读取时间。查看硬件时间用clock 或者hwclock命令。和系统时间的同步用：

    clock --systohc //把系统时间同步到硬件
    clock --hctosys //把硬件时间同步到系统

### 调整运行级别-init

### 查看运行级别-runlevel
linux下的run-leveld的含义就好像windows下的正常模式，安全模式，命令行模式等等。以图形界面登入linux，runlevel一般是5，而字符界面登入linux，runlevel一般是3。linux一般有8个level：

    0 Halt the system
    1 Single-user mode
    2 Multi-user mode
    3 Multi-user mode with networking
    4 Not used/user-deinable
    5 Multi-user mode with GUI
    6 Reboot the system


### 设置yum源
创建cdrom.repo文件包含如下内容

    [cdrom]
    name=cdrom-repo
    baseurl=file:///mnt/cdrom
    enable=1
    gpgcheck=0

### 挂载  

    mdir  /mnt/cdrom
    mount -t auto /dev/cdrom /mnt/cdrom


### 任务控制

    ctrl+z/

### 添加用户

    useradd shaojwa

### 文件操作系列

### 拷贝文件夹
cp -r /root/test /root/user/test  #注意-r

***
## windows管理命令
@20151202

### 获取卷(分区)的序列号

    vol [drive:]

### 获取字符映射表

    charmap

### 控制面板类  
WinNT 5.0和6.0以上都可用，打开系统属性对话框。在6.0以后还有另一个系统配置对话框可以通过control system打开。

    sysdm.cpl

打开系统网络链接控制面板  

    ncpa.cpl

添加删除程序  

    appwiz.cpl

时间日期面板  

    timedate.cpl

桌面配置面板  

    desk.cpl

辅助功能配置：鼠标，鼠标，声音等

    access.cpl

Internet配置  

    inetcpl.cpl

防火墙配置  

    firewall.cpl

区域和语言设置  

    Netcpl.cpl
    Intl.cpl

其他  

    control admintools
    control mouse
    control keyboard

***
# others
***
## Scroll Lock
@20151202  

今天早上在虚拟机里的CentOS上运行命令。发现无法输入，看了下发现ScrollLock等变量，于是按ScrollLock键使其不亮，发现就可以输入。
在物理机上不会有这个问题，在虚拟机的shell里存在。在shell里我试了下发现按下改键之后，你所有的命令都会缓存起来，等你再次按ScrollLock随时，之前的所有输入会一次性得显示出来。
