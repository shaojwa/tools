###### man
linux下命令巨多，有的是所谓的内建（built-in command），比如read，有的不是比如grep。平时查命令用法用man，但是内建命令怎么查？一直不清楚，最近专门了解了下，做点记录。

###### help查内建命令用法
help也是一个内建命令，查起来很方便，不需要依赖网络查用法，这是重点。

###### help和man区别
这个问题不懂，只能网上找，按照自己的理解。

- help是bash内建命令，使用bash内部的数据结构获取保存信息。
而man不是。help只用来查看bash命令。所谓的内建，在我看来就是在bash进程里执行，终端是一个进程。写到这里，想到另外一个问题。如何查看当前shell的pid？

###### 查看一个命令是否为内建命令
using type

    # type cd
    cd is a shell buildin
    # type grep
    grep is hashed (/bin/grep)
    
###### 一个命令能不能同时是内建也是外部命令
 可以比如pwd，至于为什么还不清楚， 默认情况下是先使用内建命令。

###### 如何查询是否存在相关功能的命令
直接输入apropos [keyword], 即可查看与keyword相关功能的命令。
很强大，和好用。


###### 如何关闭内建命令
    
    enable -n
###### 查看所有激活的内建命令

    enable -a

