#### 了解vm.vfs_cache_pressure对内核内存回收的影响？

根据 /usr/src/kernel4.4.0/Documentation/sysctl/vm.txt原文的描述（This percentage value controls the tendency of the kernel to reclaim
the memory which is used for caching of directory and inode objects），这是一个百分比值，用来控制内核回收内存的倾向。
这个倾向所针对的内存是目录和inode对象。

默认值是100，表示的意思是采取和pagecache与swapcache同样的回收倾向，也不是说就只回收directory和inode对象。
如果是0，那么内核绝不会因为内存压力而回收dentries和inode。所以这就很容易导致out-of-memory问题。

这个值也可以超过100，这样就会当内核倾向于优先回收dentries和inode。但是对性能好就可能有负面影响，因为缓存功能削弱。
而且释放denties和inode的时候，也会拿很多的锁，对性能也有影响。
