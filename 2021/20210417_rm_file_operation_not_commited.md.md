## description
```
[root@syy125 operation]# pwd
/var/log/operation
[root@syy125 operation]# rm test
rm: remove regular file ‘test’? y
rm: cannot remove ‘test’: Operation not permitted
[root@syy125 operation]#
```

## examine the attribute of file
```
[root@syy125 operation]# lsattr test
---------------- test
```
16 fields

## examine the directory contains the file
```
[root@syy125 log]# lsattr -d operation
-----a---------- operation
```
a means ** append only**

## fields of the lsattr output
**man chattr** shows the attrs which can be changed:
```
[aAcCdDeijsStTu]
```
attrs cannot be change by attrs:
```
[EhINXZ]
```
