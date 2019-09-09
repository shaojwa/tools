#### 服务重启过多导致无法再次重启

    man systemd.service
    man systemd.unit
    
* StartLimitIntervalSec 检查时间
* StartLimitBurst 启动次数
* systemctl reset-fail

案例： 

/opt/xxx/lib/systemd/system/ceph-mds@.service  

    StartLimitInterval=30min
    StartLimitBurst=3

    systemctl reset-failed ceph-mds@mds0.service
    systemctl reset-failed ceph-mds@target
