#### using UTC time as default
```
[wsh@localhost ~]$ date -u
Mon Mar  8 00:50:41 UTC 2021
[wsh@localhost ~]$ date
Sun Mar  7 19:50:44 EST 2021
[wsh@localhost ~]$ man date
```
sol
```
[wsh@localhost ~]$ date
Sun Mar  7 19:55:28 EST 2021
[wsh@localhost ~]$ sudo timedatectl set-timezone UTC
[sudo] password for wsh:
[wsh@localhost ~]$ date
Mon Mar  8 00:55:35 UTC 2021
```
check
```
[wsh@localhost etc]$ ll /etc/localtime
lrwxrwxrwx. 1 root root 25 Mar  8 00:55 /etc/localtime -> ../usr/share/zoneinfo/UTC
```
