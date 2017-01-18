@20151202
Iptables是绝大多数linux发行版内建的防火墙
在CentOS<7的版本中可以使用一下命令
###### 查看Iptables的状态
    # service iptables status
    # service ipv6tables status

###### 关闭iptables
    # service iptables stop
    # service ipv6tables stop

###### 启动iptables
    # service iptables start
    # service ipv6tables start

###### 从系统自启动列表中删除iptables
    # chkconfig iptables off
    # chkconfig ipv6tables off

###### 将iptables添加进系统自启动列表
    # chkconfig iptables on
    # chkconfig ipv6tables on

在CentOS7之后的版本统一用systemctl命令:  

    # systemctl [status|start|stop|restart] iptables
    # systemctl [status|start|stop|restart] ipv6tables
