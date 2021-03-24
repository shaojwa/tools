 ```
// centos
[root@node11 etc]# free -h
              total        used        free      shared  buff/cache   available
Mem:            62G        5.8G         37G        3.2G         18G         51G
Swap:            0B          0B          0B
```
   
   
```
// ubuntu
[quorm 20:09:22 ~ ]$ free -h
             total       used       free     shared    buffers     cached
Mem:           62G       4.6G        58G       2.3M       661M       3.2G
-/+ buffers/cache:       777M        62G
Swap:          14G         0B        14G

[@quorm 10:54:43 ~ ]$ free -k
             total       used       free     shared    buffers     cached
Mem:      65850628    4831356   61019272       2360     677696    3355628
-/+ buffers/cache:     798032   65052596
Swap:     15624700          0   15624700

Mem一行操作系统视角的占用: total = used + free. 是包含 buffers 和cached

-/+ buffers/cache 是应用程序角度看到的内存占用：
total = used + free
used = userd(Mem) - buffers  - cached
free = free (Mem) + buffers  + cached
```
