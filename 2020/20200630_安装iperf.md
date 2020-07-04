## yum install iperf 失败
```
$ yum install iperf
Loaded plugins: fastestmirror, langpacks
Loading mirror speeds from cached hostfile
No package iperf available.
Error: Nothing to do
```

## 查看 repo列表

```
$ yum repolist
Loaded plugins: fastestmirror, langpacks
Loading mirror speeds from cached hostfile
repo id        repo name             status
base           CentOS-7 - Base      4,022+1
extras         CentOS-7 - Extras    4,022+1
updates        CentOS-7 - Updates   4,022+1
repolist: 12,066
```

## 查看iperf的 repo
```
yum provides iperf
```
发现iperf需要的是epel库（Extra Package for Enterprise Linux）, 可以先安装epel-release包，这个包在 CentOS Extras repository中。

## 可以直接下载iperf包

https://iperf.fr/iperf-download.php
