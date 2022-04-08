#### networking subsystem.
主要是针对网络子系统的工具，网络子系统，这个说法有点意思。

#### 功能类型
尽管netstat现在基本被废弃，但是我个人还是很喜欢这个工具，这个工具有非常多的特性。
而且，第一个参数是很重要的，man中写道：The type of information printed is controlled by the first argument。
有路由表显示，多播组，网卡信息统计，以及基于协议的统计。其中最后两个非常有用，特别是基于协议的统计信息，这个用的场景不多，但是信息很多。

#### 选项OPTIONS
-v，用的不多，好像意义不大。

-A， Specifies the address families。

-e，可以使用两次。

-o，这个参数也有点意思，居然有网络定时器相关信息。

-p，显示进程的pid和名字。

#### Recv-Q
还没被用户程序拷贝的数据，应该就是等待被读取的数据。

#### Send-Q
没有被远程主机ack的数据。

#### state
这个还是比较有意思的，因为一般raw，UDP，UDPLite中没有状态的概念，所以一般都是TCP中用的。
```
// 这几个就是涉及到三次我收的5个状态
CLOSE
LISTEN
SYN_SEND
SYN_RECV
ESTABLISHED

// 还有六个状态，和四次挥手相关，client
FIN_WAIT_1
FIN_WAIT_2
CLOSEING
TIME_WAIT

// server
CLOSE_WAIT
LAST_ACK
```

#### RefCnt
这个是 active UNIX domain Sockets 中的一个字段。
