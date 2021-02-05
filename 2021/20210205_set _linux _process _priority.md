https://www.tecmint.com/set-linux-process-priority-using-nice-and-renice-commands/

#### How to Check Nice Value of Linux Processes
```
ps -eo pid,ppid,ni,comm
```
the nice value of ceph-msgr and ceph-mds-msgr is -20。

#### difference between PRI and NICE
- `NI` – is the nice value, which is a user-space concept, -20 means high priory 40, 19 mean low priority.
- `PR` or `PRI` – is the process’s actual priority, as seen by the Linux kernel.
so 19(nice) = 0(pri), -20 = 39(pri), `pri = 19 - nice` or `pri + nice = 19`。
