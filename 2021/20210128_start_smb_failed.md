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
看一看：
```
[root@node wsh]# readelf --version-info /usr/local/lib/libldb.so.1  | grep 1.1.30
[root@node wsh]# readelf --version-info /usr/local/lib/libldb.so.1  | grep 1.3.1
```
libldb.so中确实没有 1.3.0和1.1.30，估计是libldb太老？
```
readelf --version-info /usr/local/lib/libldb.so.1
```
continue:
```
$ yum deplist samba
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
package: samba.x86_64 4.10.16-5.el7
  dependency: /bin/sh
   provider: bash.x86_64 4.2.46-34.el7
  dependency: /usr/sbin/groupadd
   provider: shadow-utils.x86_64 2:4.6-5.el7
  dependency: libCHARSET3-samba4.so()(64bit)
...
  dependency: libldb.so.1()(64bit)
   provider: libldb.x86_64 1.5.4-1.el7
  dependency: libldbsamba-samba4.so()(64bit)
   provider: samba-client-libs.x86_64 4.10.16-5.el
...
```
这里我们知道，libldb是samba需要的，libldbsamba-samba4.so也是samba需要的，但是最开始的错误显示是，libldbsamba-samba4.so 找不到需要的libldb.so版本：
conrinue，我们继续看libldbsamba-samba4需要的libldb是什么版本：
```
$ yum deplist samba-client-libs
dependency: libldb.so.1
 provider: libldb.i686 1.5.4-1.el7
dependency: libldb.so.1(LDB_0.9.10)
 provider: libldb.i686 1.5.4-1.el7
dependency: libldb.so.1(LDB_0.9.15)
 provider: libldb.i686 1.5.4-1.el7
dependency: libldb.so.1(LDB_0.9.23)
 provider: libldb.i686 1.5.4-1.el7
dependency: libldb.so.1(LDB_1.1.1)
 provider: libldb.i686 1.5.4-1.el7
dependency: libldb.so.1(LDB_1.1.19)
 provider: libldb.i686 1.5.4-1.el7
dependency: libldb.so.1(LDB_1.1.30)
 provider: libldb.i686 1.5.4-1.el7
dependency: libldb.so.1(LDB_1.3.0)
 provider: libldb.i686 1.5.4-1.el7
```
这尴尬，libldbsamba-samba4需要但是libldb.i686，但是我们有的只是libldb.x86_64，所以还需要装32位版本的，但是报错：
```
Error:  Multilib version problems found. This often means that the root
       cause is something else and multilib version checking is just
       pointing out that there is a problem. Eg.:

         1. You have an upgrade for libtevent which is missing some
            dependency that another package requires. Yum is trying to
            solve this by installing an older version of libtevent of the
            different architecture. If you exclude the bad architecture
            yum will tell you what the root cause is (which package
            requires what). You can try redoing the upgrade with
            --exclude libtevent.otherarch ... this should give you an error
            message showing the root cause of the problem.

         2. You have multiple architectures of libtevent installed, but
            yum can only see an upgrade for one of those architectures.
            If you don't want/need both architectures anymore then you
            can remove the one with the missing update and everything
            will work.

         3. You have duplicate versions of libtevent installed already.
            You can use "yum check" to get yum show these errors.

       ...you can also use --setopt=protected_multilib=false to remove
       this checking, however this is almost never the correct thing to
       do as something else is very likely to go wrong (often causing
       much more problems).

       Protected multilib versions: libtevent-0.9.39-1.el7.i686 != libtevent-0.10.2-2.el8.x86_64
Error: Protected multilib versions: libtdb-1.3.18-1.el7.i686 != libtdb-1.4.3-1.el8.x86_64
Error: Protected multilib versions: libtalloc-2.1.16-1.el7.i686 != libtalloc-2.3.1-2.el8.x86_64
```
这其实基本是错误的，64位机子上为什么需要装32位的包，说明我们之前查的依赖信息有错。

我们应该查`yum deplist samba-client-libs.x86_64` 而不是`yum deplist samba-client-libs`

```
dependency: libldb.so.1()(64bit)
   provider: libldb.x86_64 1.5.4-1.el7
  dependency: libldb.so.1(LDB_0.9.10)(64bit)
   provider: libldb.x86_64 1.5.4-1.el7
  dependency: libldb.so.1(LDB_0.9.15)(64bit)
   provider: libldb.x86_64 1.5.4-1.el7
  dependency: libldb.so.1(LDB_0.9.23)(64bit)
   provider: libldb.x86_64 1.5.4-1.el7
  dependency: libldb.so.1(LDB_1.1.1)(64bit)
   provider: libldb.x86_64 1.5.4-1.el7
  dependency: libldb.so.1(LDB_1.1.19)(64bit)
   provider: libldb.x86_64 1.5.4-1.el7
  dependency: libldb.so.1(LDB_1.1.30)(64bit)
   provider: libldb.x86_64 1.5.4-1.el7
  dependency: libldb.so.1(LDB_1.3.0)(64bit)
   provider: libldb.x86_64 1.5.4-1.el7
```
其实是一样的，也是说1.5.4-1.el7会提供这些版本的libldb，然后，事实是并没有提供：

```
[root@node wsh]# yum info libldb.x86_64
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
Installed Packages
Name        : libldb
Arch        : x86_64
Version     : 1.5.4
Release     : 1.el7
Size        : 416 k
Repo        : installed
From repo   : base
Summary     : A schema-less, ldap like, API and database
URL         : http://ldb.samba.org/
License     : LGPLv3+
Description : An extensible library that implements an LDAP like API to access remote LDAP
            : servers, or use local tdb databases.
```
怎么解决, 我决定在iso中找到安装包，重新安装试试：
```
$[root@node ~] cd /mnt/cdrom/Packages
[root@node Packages]# ll | grep libldb
-rw-rw-r--  6 root root    153488 Apr  4  2020 libldb-1.5.4-1.el7.i686.rpm
-rw-rw-r--  3 root root    152376 Apr  4  2020 libldb-1.5.4-1.el7.x86_64.rpm
-rw-rw-r--  6 root root     76844 Apr  4  2020 libldb-devel-1.5.4-1.el7.i686.rpm
-rw-rw-r--  3 root root     76804 Apr  4  2020 libldb-devel-1.5.4-1.el7.x86_64.rpm
[root@node Packages]# rpm -q libldb
libldb-1.5.4-1.el7.x86_64
[root@node Packages]# rpm -e libldb-1.5.4-1.el7.x86_64
error: Failed dependencies:
        libldb(x86-64) = 1.5.4-1.el7 is needed by (installed) pyldb-1.5.4-1.el7.x86_64
        libldb.so.1()(64bit) is needed by (installed) pyldb-1.5.4-1.el7.x86_64
        libldb.so.1()(64bit) is needed by (installed) samba-common-libs-0:4.10.16-5.el7.x86_64
        libldb.so.1()(64bit) is needed by (installed) samba-client-libs-0:4.10.16-5.el7.x86_64
        libldb.so.1()(64bit) is needed by (installed) samba-libs-0:4.10.16-5.el7.x86_64
        libldb.so.1()(64bit) is needed by (installed) samba-common-tools-0:4.10.16-5.el7.x86_64
        libldb.so.1()(64bit) is needed by (installed) samba-0:4.10.16-5.el7.x86_64
        libldb.so.1(LDB_0.9.10)(64bit) is needed by (installed) pyldb-1.5.4-1.el7.x86_64
        libldb.so.1(LDB_0.9.10)(64bit) is needed by (installed) samba-client-libs-0:4.10.16-5.el7.x86_64
        libldb.so.1(LDB_0.9.10)(64bit) is needed by (installed) samba-libs-0:4.10.16-5.el7.x86_64
        libldb.so.1(LDB_0.9.15)(64bit) is needed by (installed) pyldb-1.5.4-1.el7.x86_64
        libldb.so.1(LDB_0.9.15)(64bit) is needed by (installed) samba-client-libs-0:4.10.16-5.el7.x86_64
        libldb.so.1(LDB_0.9.23)(64bit) is needed by (installed) samba-client-libs-0:4.10.16-5.el7.x86_64
        libldb.so.1(LDB_1.0.2)(64bit) is needed by (installed) pyldb-1.5.4-1.el7.x86_64
        libldb.so.1(LDB_1.1.1)(64bit) is needed by (installed) samba-client-libs-0:4.10.16-5.el7.x86_64
        libldb.so.1(LDB_1.1.19)(64bit) is needed by (installed) samba-client-libs-0:4.10.16-5.el7.x86_64
        libldb.so.1(LDB_1.1.22)(64bit) is needed by (installed) pyldb-1.5.4-1.el7.x86_64
        libldb.so.1(LDB_1.1.30)(64bit) is needed by (installed) samba-client-libs-0:4.10.16-5.el7.x86_64
        libldb.so.1(LDB_1.3.0)(64bit) is needed by (installed) samba-client-libs-0:4.10.16-5.el7.x86_64
```
