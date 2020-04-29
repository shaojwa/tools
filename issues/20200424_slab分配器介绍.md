https://www.ibm.com/developerworks/cn/linux/l-linux-slab-allocator/index.html

https://www.ibm.com/developerworks/cn/linux/l-cn-slub/index.html

## 内存管理的两个目标
1. 最小化管理内存所需要的时间。
1. 最小化管理内催所需要的空间（当可用内存尽可能大）。

内存管理实际上是一种关于权衡的零和游戏。

## 搜索可用空间的算法
1. first-fit
1. best-fit

## 内存分配策略
1. 每个内存管理器一般使用了一种基于堆（内存块）的分配策略，当然还有一种策略是 buddy memory allocation。

基于堆的分配策略的根本问题是碎片（fragmentation），基于堆的内存分配通常有比较高的内存使用率。但是管理复杂度比较高，时间消耗较大。

## 内核的内存分配机制slab

Linux 所使用的 slab 分配器的基础是 Jeff Bonwick 为 SunOS 操作系统首次引入的一种算法。以为内他注意到，为内对对象进行初始化的时间超过为对象分配和释放内存的时间，所以他觉得，让已经释放的对象保持在一个初始化的状态，而不是完全释放回全局空间是一个比较重要的事情。

例如，如果内存被分配给了一个互斥锁，那么只需在为互斥锁首次分配内存时执行一次互斥锁初始化函数（mutex_init）即可。后续的内存分配不需要执行这个初始化函数，因为从上次释放和调用析构之后，它已经处于所需的状态中了。

Linux slab 分配器使用了这种思想和其他一些思想来构建一个在空间和时间上都具有高效性的内存分配器。

## 最小单位

一个slab是slab分配器分配的最小单元，一般一个slab有多个page。

如果一个slab中已经被所有对象用完，那么这个slab就放到slab_full链表中。部分使用的slab挂在slab_partial链表中。
一个slab如果没有分配给任何对象，那就在slab_empty中，比如某个mutex已经被释放，而没有被别的进程再次申请使用。

## slab的优势

内核从业务上来说，通常频繁进行小对象的申请和释放，比如fd，比如mutex。通过slab，就对这些对象引入一个缓存机制。
用完的对象，不用马上还到全局内存，而是先在slab列表中，万一很快内核又需要申请这种对象呢。

这种缓存，一是避免频繁申请释放，二是能极大程度减少对内核对象的初始化过程。

## slab缓存链的数据结构

 kmem_cache指针，这是一条slab缓存链的头。
 
 ## kmem_cache_create 创建一个kmem_cache缓存
 
 这通常是在内核初始化时执行的，或者在首次加载内核模块时执行。构建这个缓存的时候，就指定了这个缓存中，将来每个分配的object的大小。
 
 ## kmem_cache_destroy销毁一个slab缓存
 
 ## slab的访问接口
 
 原先在/proc/slabinfo中，现在已经移动到 /sys/kernel/slab 中。
