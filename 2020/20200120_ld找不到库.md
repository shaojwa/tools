#### 现象

在一台机子上可以编译通过，在另外一台机子行报错：
```
/usr/bin/ld: cannot find -lrados
collect2: error: ld returned 1 exit status
```

#### 分析

这里的rados库就是librados，ld是链接器，ld说了是库文件找不到导致链接失败。
man ld里说了，编译一个程序的最后一步是运行ld，这里的程序也包括库文件。

说是找不到库文件，受限得弄清楚在什么路径下找，通过以下命令：
```
$ ld --verbose | grep SEARCH_DIR
SEARCH_DIR("=/usr/x86_64-redhat-linux/lib64");
SEARCH_DIR("=/usr/lib64");
SEARCH_DIR("=/usr/local/lib64");
SEARCH_DIR("=/lib64"); 
SEARCH_DIR("=/usr/x86_64-redhat-linux/lib");
SEARCH_DIR("=/usr/local/lib");
SEARCH_DIR("=/lib");
SEARCH_DIR("=/usr/lib");
```

在可以编译的机子上，逐个查找以上目录，我们在其中一个目录下找到了librados，删掉之后，果然也同样报错。
