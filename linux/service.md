@20151202
从CentOS7开始服务的操作方式发生变化

##服务操作
service 改为 systemctl
    # service <servcie> status|stop|start|restart
    # systemctl status|start|stop|restart <service>

##系统自启动列表中删除或者添加

chkconfig改为systemctl
    # chkconfig <service> off|on
    # systemctl enable|disable <service>
    # chkconfig <service>
    # systemctl is-enabled <service>
    # chkconfig -list
    # systemctl list-unit-files --type=service


