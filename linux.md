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

#### yum

    yum provides ifconfig
    yum whatprovides ifconfig
    yum install net-tools

#### 在虚拟机中配置DNS服务

    cat /etc/resolve.conf
    nmcli dev show | grep DNS

#### config DNS of vm

    IPADDR=192.168.245.128
    NETMASK=255.255.255.0
    GATEWAY=192.168.245.1
    DNS1=192.168.245.2
