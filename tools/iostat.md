- [linuxperf参考](linuxperf.com/?p=156)
- [内核中的diskstats](https://www.kernel.org/doc/Documentation/iostats.txt)
- [ykrocku](http://ykrocku.github.io/blog/2014/04/11/diskstats/)
- [bean-li](https://bean-li.github.io/dive-into-iostat/)


#### iostat所依赖的diskstats
`/proc/diskstats`中的字段在4.18之前，有14个，分别是：
```
==  ===================================
 1  major number
 2  minor mumber
 3  device name
 4  reads completed successfully
 5  reads merged
 6  sectors read
 7  time spent reading (ms)
 8  writes completed
 9  writes merged
10  sectors written
11  time spent writing (ms)
12  I/Os currently in progress
13  time spent doing I/Os (ms)
14  weighted time spent doing I/Os (ms)
==  ===================================
```
从4.18开始，增加了4个字段：
```
Kernel 4.18+ appends four more fields for discard tracking putting the total at 18:
==  ===================================
15  discards completed successfully
16  discards merged
17  sectors discarded
18  time spent discarding
==  ===================================
```
而从5.5开始，又增加2个字段
```
Kernel 5.5+ appends two more fields for flush requests:
==  =====================================
19  flush requests completed successfully
20  time spent flushing
==  =====================================

For more details refer to Documentation/admin-guide/iostats.rst
```

在我们环境的版本中，一般是20个字段，我们需要理解每一个字段的含义：

#### 为什么read会merge
io到大disk之后，相邻的IO会merge，这个在什么环节完成？排队时计算的IO个数是merge之后的。

#### 用时的统计
as measured from __make_request() to end_that_request_last()

#### milliseconds spent doing I/Os
这个不是等于  milliseconds_spent_reading + milliseconds_spent_writing，而是表示有IO需要处理的时间，磁盘非空闲时间。

#### 什么叫weighted
好像就是 milliseconds_spent_reading + milliseconds_spent_writing。

#### 什么叫discards completed


## iostat

#### 每个io的平均耗时
这可能是我们最新关心的性能数据，在Linux中，一个io的耗时包括queuing-time以及servicing-time。
这个时间是await，因为他包括排队时间，所以这个指标不能反映硬盘的性能。

#### iostat 中的svctm
#### 为什么svctm 不再可信
svctm本来表示的意思是，一个IO请求发送给设备得到处理的平均时间，现在的IO统计是在block层，我们并不知道磁盘驱动什么时候开始处理这个请求。
看起来意思是，IO发送到block队列后返回，磁盘驱动的处理是异步的。


#### 基本用法
注意：iostat 的默认输出是从系统启动之后的数据，如果设置interval，那么从第二组数据开始，后续的每次都是增量。
```
iostat -x       // Display extended statistics
iostat -p sda   // specify the devices and all their partitions
iostat -c 1 2   // display the CPU utilization in <interval> second by <n> times
```

#### CPU利用率输出字段
- %iowait
CPU因为正在等待磁盘IO而空闲的时间比例，一般说来，这个比例都极低。
- %steal
基本都为0，因为这个只有在CPU是虚拟CPU时，宿主机正在模拟其他CPU执行，而当前CPU没有被模拟的情况。
- %idle
空闲时间，排除掉正在运行，以及正在等待IO的CPU时间，是真正的空闲时间。

#### Device利用率输出字段
- tps
每秒钟发送到设备上的传输数（number of transfers per second），一个传输就是发给设备的一次IO，上层的多次逻辑IO会合并成一个Device IO 请求。
所以这种transfer的大小并不是固定的。

- rrqm/wrqm
这是所谓的合并的请求数，这些请求会放入设备的队列，io合并一般是 IOscheduler负责的，把相邻的数据读写合并到一个来提高效率。

- await
单位毫秒，是包括硬盘处理io时间和io请求在kernel队列中的时间，但是因为一般说来队列等待时间可以忽略不计。
所以姑且可以用await来代表硬盘速度，一般机械硬盘await是5-10ms。



#### 输出字段
使用 –x 参数时，最后一列中的 %util表示繁忙程度。
```
tps: 每秒的传输数，一个传输就是一个设备IO请求，多个逻辑请求会合并为一个设备IO请求。
rrqm/s: 每秒钟读请求被merge的个数
wrqm/s: 每秒钟写请求被merge的个数
r/s: 每秒读请求数目数目
w/s: 每秒写请求数目数目
rKb/s: 每秒读千字节数
wKb/s: 每秒写千字节数
avgrq-sz: 请求的平均的扇区大小
avgqu-sz: 请求的平均的队列深度
await: 每个请求平均的处理时长（单位毫秒），包括排队时间和服务时间
%util: 设备的带宽利用率，即饱和度，繁忙度。
```

#### 注意点
1. wait的时间需要注意，这个是磁盘处理时间加上IO排队时间,体现不了硬盘设备的速度。
2. 要看某一段时间的系统繁忙程度需要加上`interval`，因为否者显示的是从系统启动开始到现在的负载。
3. iostat和sar都是依赖/proc/diskstats，所以要理解iostat应该从立即/proc/diskstats开始
4. 注意/proc/diskstats中的rd_tick和wr_ticks和io_ticks的区别。
5. 查看/sys/block/sdx/queue/scheduler可以查看硬盘的调度器。
6. %util因为硬盘的并行能力所以即使达到100%也不代表达到饱和。

#### 遗留问题
1. 硬盘IO有返回时间么？
