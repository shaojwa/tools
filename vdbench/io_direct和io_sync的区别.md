#### io_direct 的含义
其实这个参数值对应的就是glibc中的open接口的IO_DIRECT选项，在Linux中，这个选项是从2.4.10开始有的。

这个选项的意思是，需要最小化cache的影响。在Linux中，这个参数会对user-space的buffer进行长度和地址的限制，以及文件中偏移量offset的对齐限制。
但是，Linux中，这种限制又因为文件系统的不同，以及内核版本的不同，而有所变化，甚至，也可能完全不存在这种限制。

现在，有没有和文件系统不相关的接口函数，来判断这个文件系统或者其中的文件在这方面的限制到底如何。
尽管有的文件系统会提供他们自己的判断接口，比如XFS中的，但是统一的，和文件系统无关的接口好像没有。

在Linux的2.4以下版本，传输长度，缓冲区大小，文件偏移，都有要求，必须是文件系统逻辑块（logical block size of the filesystem）大小的倍数。
但是，Linux 2.6.0，这个对齐的对象只要是底层存储的逻辑块大小就可以，而不需要是文件系统的LBS，这个底层LBS通常是512，这个可以通过命令
`blockdev --getss /dev/sda`来找到。

但是IO_DIRECT的用法似乎比较混乱，语义感觉不太清晰。

#### IO_DIRECT到底跳过什么
跳过了buffer subsystem，也叫缓冲子系统。这是内核的主要子系统之一。这是Linux内核提升写性能的主要手段。

#### 和io_sync的区别是什么？
IO_SYNC是保证，这个文件的每个IO操作都是同步的，从语义上来说，这个选项并没有说在写操作时没有回写，也就是说 buffer-subsystem可能还是会用的。
只是，内核做了优化，让每个IO都能很快落盘。具体怎么优化，暂时不清楚，但是和IO_DIRECT的区别还是明显的，IO_SYNC还是会走buffer-subsystem。
