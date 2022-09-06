因为operation这个目录有append属性：
```
[root@node1 log]# lsattr -d operation/
-----a---------- operation/
```
修改：
```
[root@node1 log]# chattr +a operation
[root@node1 log]# lsattr -d operation
-----a---------- operation
[root@node1 log]# chattr -a operation
[root@node1 log]# lsattr -d operation
---------------- operation
```
