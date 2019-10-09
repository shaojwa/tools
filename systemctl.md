
    man systemctl
    man systemd.service
    man systemd.unit

#### sub commands of systemctl

* unit command
* unit file command 


#### disable 

just remove the  symlink to  the specified unit file from the unit configuration directory.

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


#### service are not permitted to start any more by too many restarts
    
* StartLimitInterval    // checking interval
* StartLimitBurst       // how many starts per interval are allowed
* systemctl reset-fail

eg： 

/opt/xxx/lib/systemd/system/ceph-mds@.service  

    StartLimitInterval=30min
    StartLimitBurst=3

    systemctl reset-failed ceph-mds@mds0.service
    systemctl reset-failed ceph-mds@target
