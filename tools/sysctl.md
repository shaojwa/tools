sysctl下的很多配置的解释可以在两个地方查看

1. https://www.kernel.org/doc/Documentation/sysctl
1. /usr/src/kernel4.4.0/Documentation/sysctl

sysctl 和 在proc下的操作sys是一致的，所以相比/proc/sys这么长的路径，还是用sysctl来得快。


#### vm.drop_caches 

    1: 释放页缓存, 2:释放可回收的slab对象包括dentries和inodes，3：页缓存和slab对象
    
    slab是一种Linux内存分配算法。
    这是非破坏性操作，并不会释放脏对象。官方文档已经说明，这不是一个控制内核各种缓存增长的方法。
    该操作会引起性能问题。
    因为他丢弃缓存对象，因此还有一个明显的IO以及CPU消耗来重新创建这些对象，特别是对象正在重度使用的时候。

#### kernel.watchdog_thresh

    用来控制hrtimer（高精度定时器）和NMI（不可屏蔽中断）的事件的频率。
    进而也影响到softlockup 和 hardlockup的筏值，通常这个筏值是watchdog_thresh的两倍。



#### tcp_keepalive_time

    最后一个数据包和第一次保活探测之间的时间间隔。
    
#### tcp_keepalive_intvl
    
    包括探测之间报文之间的时间间隔。
    
#### tcp_keepalive_probes

    连接被标记为dead时所需要的无返回探测报文个数。


#### dirtytime_expire_seconds
    
    都知道atime的改变只是文件访问引起的，但是这个inode却脏了。
    inode脏了是需要下刷inode到disk的。
    所以这个问题就有多种优化思路：
    noatime：直接干掉atime，让系统中的atime失效
    reatime：ctime和mtime的时间晚于atime时才去更新atime
    lazytime，控制inode下发的时间
    后台bdi用来写回dirty inode，就是bdi_writeback->b_dirty
    就看dirty 的inode什么时候放到这个队列。
    如果是i_size等关键inode属性改变，具体文件系统层会放到这个队列
    如果是ctime等不关键属性，那么VFS层负责把inode放到这个队列中
