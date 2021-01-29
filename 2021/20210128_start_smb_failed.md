bug:
```
$ testparm
testparm: /usr/local/lib/libldb.so.1: version `LDB_1.3.0' not found (required by /usr/lib64/samba/libldbsamba-samba4.so)
testparm: /usr/local/lib/libldb.so.1: version `LDB_1.1.30' not found (required by /usr/lib64/samba/libldbsamba-samba4.so)
```
debug，samba4中需要的libldb的版本有6个：
```
$ readelf --version-info /usr/lib64/samba/libldbsamba-samba4.so
...
...
...
0x0280: Version: 1  File: libldb.so.1  Cnt: 6
0x0290:   Name: LDB_1.1.19  Flags: none  Version: 30
0x02a0:   Name: LDB_1.1.1  Flags: none  Version: 29
0x02b0:   Name: LDB_1.3.0  Flags: none  Version: 23
0x02c0:   Name: LDB_0.9.15  Flags: none  Version: 22
0x02d0:   Name: LDB_0.9.10  Flags: none  Version: 9
0x02e0:   Name: LDB_1.1.30  Flags: none  Version: 3
```
libldb.so中确实没有 1.3.0和1.1.30，估计是libldb太久？
```
readelf --version-info /usr/local/lib/libldb.so.1
```
