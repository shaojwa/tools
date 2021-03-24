@20151202

    service 可以操作 SysV的 init 脚本或者 upstart 的job。
    所以service 是可以同时操作 System V init script和 upstart。
    upstart 和sysvinit脚本如果同名，则upstart优先。
    sysvinit 脚本在 /etc/init.d/下
    upstart脚本在 /etc/init/ 下    
    service –status-all 只调用sysvinit job，而不调用 upstart job。

从CentOS7开始服务的操作方式发生变化

#### 服务操作

    service 改为 systemctl
    # service <servcie> status|stop|start|restart
    # systemctl status|start|stop|restart <service>

#### 系统自启动列表中删除或者添加

    chkconfig改为systemctl
    # chkconfig <service> off|on
    # systemctl enable|disable <service>
    # chkconfig <service>
    # systemctl is-enabled <service>
    # chkconfig -list
    # systemctl list-unit-files --type=service
