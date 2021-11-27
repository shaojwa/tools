ps中看到的进程时间，是一个相对时间。可能是相对于系统时的相对时间。
如果，如果我们把系统时间调整，那么进程的启动时间时间也会发生变化。
原先：
```
[wsh@archlinux ~]$ date
Thu Nov 25 13:41:46 CST 2021
```
此时的系统时间是：
```
[root@archlinux wsh]# dmesg -T | head -1
[Wed Nov 24 11:22:47 2021] Linux version 5.13.10-arch1-1 (linux@archlinux)
```
然后我修改系统时间：
```
[root@archlinux wsh]# date -s +1day
Fri Nov 26 13:42:56 CST 2021
```
然后再查看系统的系启动时间：
```
[root@archlinux wsh]# dmesg -T |head -1
[Thu Nov 25 11:22:47 2021] Linux version 5.13.10-arch1-1 (linux@archlinux)
12 Aug 2021 21:59:14 +0000
```
很明显，系统的启动时间已经改变。进程时间也类似：
```
[root@archlinux wsh]# ps -eo lstart,pid | grep 563
Fri Nov 26 13:42:14 2021     563
[root@archlinux wsh]# date -s -1day
Thu Nov 25 13:58:49 CST 2021
[root@archlinux wsh]# ps -eo lstart,pid | grep 563
Thu Nov 25 13:42:14 2021     563
```
