CPU的使用率在ps中和top并不一样，比如：
```
[root@node155 ~]#  ps -o pid,pcpu,comm -p $(pidof dpe)
    PID %CPU COMMAND
   5524  169 dpe
[root@node155 ~]# top -bn1 -p $(pidof dpe)
top - 19:37:16 up 2 days, 17 min,  5 users,  load average: 4.47, 14.49, 41.24
Tasks:   1 total,   0 running,   1 sleeping,   0 stopped,   0 zombie
%Cpu(s): 15.0 us,  5.0 sy,  0.0 ni, 70.0 id,  0.0 wa,  5.0 hi,  5.0 si,  0.0 st
MiB Mem : 257249.9 total, 127258.0 free, 122809.8 used,   7182.0 buff/cache
MiB Swap:      0.0 total,      0.0 free,      0.0 used. 128692.0 avail Mem

    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
   5524 ceph      20   0  131.3g  95.6g  54352 S 153.3  38.1     81,45 dpe
[root@node155 ~]#
```
