```
[SDS_Admin@node0 /]$ sudo rpm -qa > /package.log
-bash: /package.log: Permission denied

[SDS_Admin@node0 /]$ ll package.log
-rw-r--r-- 1 root root 23004 Sep  6 15:26 package.log
```

#### 可能的原因
sudo 命令创建的文件，uid还是原来的uid，而不是root：// 并不是，sudo创建的文件的uid和gid都是root
```
-rw-r--r--   1 SDS_Admin root      23355 Sep 18 13:14 package.out
```
如果是sudo su之后，创建的文件的uid就是root:
```
[root@node80 SDS_Admin]# rpm -qa > package.log
rw-r--r--   1 root      root      23355 Sep 18 13:15 package.log
```
而/目录默认是没有其他账户的写入权限的：
```
[root@node80 /]# ll -d /
drwxr-xr-x. 18 root root 277 Sep 18 13:16 /
```
