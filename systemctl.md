
#### check if the service start on boot

run the systemctl status command on your service and check for the "Loaded" line.

    [wsh@192 ~]$ systemctl status firewalld
    ● firewalld.service - firewalld - dynamic firewall daemon
       Loaded: loaded (/usr/lib/systemd/system/firewalld.service; enabled; vendor preset: enabled)
       Active: active (running) since Fri 2019-09-20 23:34:08 CST; 14min ago
       
#### Disabling a service on boot 

running systemctl disable on the desired service. 

Running systemctl disable removes the symlink to the service in /etc/systemd/system/*.


#### Enabling a service on boot

    [wsh@192 ~]$ systemctl status smb
    smb.service - Samba SMB Daemon
       Loaded: loaded (/usr/lib/systemd/system/smb.service; disabled; vendor preset: disabled)
       Active: inactive (dead)
       
    [wsh@192 ~]$ systemctl start smb    
    [wsh@192 ~]$ systemctl status smb
    smb.service - Samba SMB Daemon
       Loaded: loaded (/usr/lib/systemd/system/smb.service; disabled; vendor preset: disabled)
       Active: active (running) since Fri 2019-09-20 23:54:19 CST; 2s ago
    
    [wsh@192 ~]$ systemctl enable smb


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
