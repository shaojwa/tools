出现了报错：
```
$ ssh-copy-id SDS_Admin@182.100.6.28
SDS_Admin@182.100.6.28's password:
sh: line 1: .ssh/authorized_keys: Permission denied
```
然后发现28上的authorized_keys的所有者是root：
```
[SDS_Admin@node28 ~]$ ll ~/.ssh/authorized_keys
-rw-r--r-- 1 root root 565 Apr 15 16:39 /home/SDS_Admin/.ssh/authorized_keys
```
更改权限：
```
[SDS_Admin@node28 ~]$ sudo chown SDS_Admin:SDS_Admin /home/SDS_Admin/.ssh/authorized_keys
[SDS_Admin@node28 ~]$ ll ~/.ssh/authorized_keys
-rw-r--r-- 1 SDS_Admin SDS_Admin 565 Apr 15 16:39 /home/SDS_Admin/.ssh/authorized_keys
```
然后再添加免密就可以：
```
$ ssh-copy-id SDS_Admin@182.100.6.28
SDS_Admin@182.100.6.28's password:
Number of key(s) added: 1
Now try logging into the machine, with:   "ssh 'SDS_Admin@182.100.6.28'"
and check to make sure that only the key(s) you wanted were added.
```
