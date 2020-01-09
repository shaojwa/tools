#### ps 中的TIME 字段

累积的 user + system toptop时间，MMM:SS.PP，如果超过999分钟，那么值显示MMMM:SS, 比如1488:00

#### top 中的 %CPU 和 TIME

top 中的TIME 和 PS 中的 TIME是一个值，%CPU就是平均占用多少个CPU周期，所以，进程存活时间乘CPU基本等于TIME 

####  /proc/sched 下的时间

```
se.sum_exec_runtime task的运行之间，单位是毫秒。
所以打开进程的sched也只是进程中主线程的时间，不是整个进程的。
```

```
nr_switches:              上下文切换数
nr_voluntary_switches     主动上下文切换
nr_involuntary_switches   抢占上下文切换
nr_switches = nr_voluntary_switches + nr_involuntary_switches
```
一般说来 nr_voluntary_switches 远远大于 nr_involuntary_switches
