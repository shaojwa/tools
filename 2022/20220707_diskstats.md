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

#### 什么是weighted
好像就是 milliseconds_spent_reading + milliseconds_spent_writing。

#### 什么是discards
Linux 操作系统支持发送 discard 请求来通知存储器哪些 page 不再使用,一般只在SSD上有用。

#### 什么是flush time spent
