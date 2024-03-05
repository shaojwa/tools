CPU的使用率在ps中和top并不一样，比如：
```
[root@node155 ~]#  ps -o pid,pcpu,comm -p $(pidof dpe)
    PID %CPU COMMAND
   5524  169 dpe
```
top的输出
```
[root@node155 ~]# top -bn1 -p $(pidof dpe)
top - 19:37:16 up 2 days, 17 min,  5 users,  load average: 4.47, 14.49, 41.24
...
    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
   5524 ceph      20   0  131.3g  95.6g  54352 S 153.3  38.1     81,45 dpe
[root@node155 ~]#
```
为什么会这样？ 因为ps的使用率的计算，是从进程启动的时间点开始计算的。
