bug现象
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
[root@node32 wsh]# readelf --version-info /usr/local/lib/libldb.so.1  | grep 1.1.30
[root@node32 wsh]# readelf --version-info /usr/local/lib/libldb.so.1  | grep 1.3.1
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
[root@node32 wsh]# yum info libldb.x86_64
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
$[root@node32 ~] cd /mnt/cdrom/Packages
[root@node Packages]# ll | grep libldb
-rw-rw-r--  6 root root    153488 Apr  4  2020 libldb-1.5.4-1.el7.i686.rpm
-rw-rw-r--  3 root root    152376 Apr  4  2020 libldb-1.5.4-1.el7.x86_64.rpm
-rw-rw-r--  6 root root     76844 Apr  4  2020 libldb-devel-1.5.4-1.el7.i686.rpm
-rw-rw-r--  3 root root     76804 Apr  4  2020 libldb-devel-1.5.4-1.el7.x86_64.rpm
[root@node32 Packages]# rpm -q libldb
libldb-1.5.4-1.el7.x86_64
[root@node32 Packages]# rpm -e libldb-1.5.4-1.el7.x86_64
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
没办法，网上找找：`https://bugzilla.redhat.com/show_bug.cgi?id=1736013`，换成其他的包安装都类似。然后想看看，samba卸载之后，库还在不在，结果发现libldb下载之后，libldb还有一个文件：
```
drwxr-xr-x  2 root root     31 Jan  7 20:30 ldb
lrwxrwxrwx  1 root root     16 Jan  7 20:30 libldb.so -> libldb.so.1.1.29
lrwxrwxrwx  1 root root     16 Jan  7 20:30 libldb.so.1 -> libldb.so.1.1.29
-rwxr-xr-x  1 root root 261120 Jan  7 20:30 libldb.so.1.1.29
```
然后重新安装samba，查看libldbsamba-samba4.so的 rpath：
```
[root@node32 lib]# readelf -d /usr/lib64/samba/libldbsamba-samba4.so | grep rpath
0x000000000000000f (RPATH)              Library rpath: [/usr/lib64/samba]
```
此时的libldb有两个：
```
[root@node32 lib]# pwd
/usr/local/lib
[root@node32 lib]# ll | grep ldb
drwxr-xr-x  2 root root     31 Jan  7 20:30 ldb
lrwxrwxrwx  1 root root     16 Jan  7 20:30 libldb.so -> libldb.so.1.1.29
lrwxrwxrwx  1 root root     16 Jan  7 20:30 libldb.so.1 -> libldb.so.1.1.29
-rwxr-xr-x  1 root root      0 Jan 29 23:11 libldb.so.1.1.29
lrwxrwxrwx  1 root root     23 Jan  7 20:30 libpyldb-util.so -> libpyldb-util.so.1.1.29
lrwxrwxrwx  1 root root     23 Jan  7 20:30 libpyldb-util.so.1 -> libpyldb-util.so.1.1.29
-rwxr-xr-x  1 root root  14048 Jan  7 20:30 libpyldb-util.so.1.1.29
```
和
```
[root@node32 lib64]# pwd
/usr/lib64
[root@node32 lib64]# ll | grep ldb
drwxr-xr-x   3 root root       102 Jan 29 23:11 ldb
lrwxrwxrwx   1 root root        15 Jan 29 23:11 libldb.so.1 -> libldb.so.1.5.4
-rwxr-xr-x   1 root root    208424 Apr  2  2020 libldb.so.1.5.4
lrwxrwxrwx.  1 root root        19 Jan  6 22:18 libleveldb.so -> libleveldb.so.1.0.7
lrwxrwxrwx.  1 root root        19 Jan  6 22:17 libleveldb.so.1 -> libleveldb.so.1.0.7
-rwxr-xr-x.  1 root root    348928 May 18  2016 libleveldb.so.1.0.7
lrwxrwxrwx   1 root root        22 Jan 29 23:11 libpyldb-util.so.1 -> libpyldb-util.so.1.5.4
-rwxr-xr-x   1 root root     15672 Apr  2  2020 libpyldb-util.so.1.5.4
```
而我们看smbd或者testparm找的libldb文件可以看到,正常的是加载`/lib64`目录（这个是目录软链接，指向`/usr/lib64`）。
而问题版本并不是指向这个，而是指向 `/usr/loca/lib`, 这样，基本就确定原因，是加载的路径不对。
现在的问题是：为什么libldbsamba-samba4.so选择的是`/usr/local/lib` 而不是`/usr/lib64`
原因是：在node32节点上的`/etc/ld.so.conf`下的内容是
```
include ld.so.conf.d/*.conf
```
最终, `ld.so.conf.d`下的所有conf包含的的一个有效目录是:
```
/usr/lib64/atlas
/usr/lib64//bind9-export/
/usr/lib64/mysql
/usr/local/lib
```
也就是有一个路径指向 `/usr/local/lib`， 而这个路径下，确实有libldb库文件(1.1.29文件):
```
libldb.so -> libldb.so.1.1.29
libldb.so.1 -> libldb.so.1.1.29
libldb.so.1.1.29
```
而正确环境下,`/etc/ld.so.conf`文件的内容是：
```
include ld.so.conf.d/*.conf
/usr/local/lib
```
其实内容一样，但是`/usr/local/lib`下并没有`libldb.so`可以加载。
所以，最终找到了`/lib64下`(最终指向`/usr/lib64`)下的正确库文件。
现在还剩最后一个问题，系统是如何找到`/lib64`的，是系统内置的么？
