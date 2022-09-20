## 几个基本概念
* work load  
我一般习惯于翻译为负载，一个IO的负载的定义其实没有那么简单。比如，涉及的进程或者线程数，IO的产生方式等等。

* job  
一个负载，一个job的方式进行，job就是对一个负载的标识。个人认为，这个类似于vdbench中的RD(run definition)

* global parameters  
fio中有所谓的全局参数，这些配置参数会被每个thread继承，除非为线程独立指定特定的配置参数。

* type of I/O  
读，写，顺序还是随机，同步还是异步等。这是IO负载的重要组成部分。

* engine  
engine有多种，比如libaio，而且有的是平台特定的，比如splice engine只有在Linux上有。

## 几个注意点
* fio使用pthread的mutex来主持signalling和locking，但是很显然，很多平台并不支持进程间共享pthread mutex。
* fio命令行参数格式和job文件中使用的参数格式，略有区别，比如，job文件中是iodepth=2, 命令行是 --iodepth 2 or --iodepth=2。

## 参数的使用可能受限，需要注意一下几个方面
* memory locking.
* I/O scheduler switching.
* decreasing the nice value.

## 运行FIO (1.8)
* 直接指定job文件即可，可以接收多个job文件，默认会依次串行执行这些job。
* 在job文件中，fio通过`[]`来识别一个新的job，在命令行下，通过`--name`选项类区分不同的job。

## FIO 如何工作 (1.9)
定义一个job文件，其中参数分为两部分：
* global section 
* job section
* global 中的参数是所有job共享的参数，job部分指定该job特定的参数。

Fio的参数的几个比较
* IO type中的buffered  IO/direct IO/row IO 和 IO engine有什么关联？
* block size 和 IO size 的区别？
* I/O depth 只在 async engine 中生效。

## 几个比较有趣的命令行参数 (1.10)
* --debug  
debug可以跟踪job运行的不同侧面，非常有意思，比较典型的比如。
* --output=filename  
这个不是有趣，只是比较有用，在刚开始用fio的时候，我是将输出 tee到一个文件。
* --cmdhelp=command  
这个可以查看指定的配置命令的用法，比如thread，还可以列出所有的可用command。
* --enghelp  
列出所有支持的engine，现在支持有将近20个。
* --showcmd  
这个也很有意思，可以把job中的选项转为命令行选项。
* --trigger=command  
可以用一个命令来触发fio的执行，有点意思。

* --idle-prof=option
上报CPU空闲率

## 参数
#### time_based
一直持续这么久，即使文件已经完成读写，也会重复执行。要是无法估计运行时长，那就不要设置该选项，比如预埋数据时。

#### thread
感觉是并发模式，是线程模式，还是进程模式，用pthread_create创建线程，而不是fork来创建进程。

#### numjobs
任务数量，默认数量是1。从进程内的线程上看，fio，log，service，admin_socket等线程都翻倍。

#### iodepth
队列深度

#### direct
相当于打开文件时添加O_DIRECT选项，不适用缓冲。在linux下比较常用，支持比较好。

#### buffered
相对direct，使用缓存。

## 输出
|输出字段参数|含义|
|:-|:-|
|slat|submit latency，提交时延，从创建到提交，其中stdev表示标准差|
|clat|完成时延，从提交到完成，对于同步IO来说，政治几乎为0|
|lat|从IO创建到完成，整个事件|
