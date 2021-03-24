#### 常用示例
  
    nmap 192.168.84.0/24        // 默认探测每个存活主机的开放端口
    nmap -sn 192.168.84.0/24    // 只探测存活主机不探测端口
    nmap -p 11000-12000 localhost  // 指定端口范围

#### 基本语法结构

    nmap [Scan Type(s)] [Options] <host or net #1 ... [#n]

#### 指定端口范围

     nmap -p 11000-12000 localhost  

#### 能探测什么

主机，端口，服务，系统  

####  默认扫描针对什么类型

针对端口，nmap是端口扫描器 


####  常用扫描类型有什么？

扫描类型并不是区别主机发现还是端口扫描，而是发送什么类型的包去探测。

有的类型的包只能用于主机探测比如-sP发送的icmp报文，而有的类型的包能用于主机的同时也使用于端口，比如-sT。

-sT 全连接tcp探测，这个选项的好处是运行不需要特殊的权限，但是缺陷是很容易被探测到，因为建立的链接会被马上关掉。

-sS:带SYN标记的TAC报文，判断是否开启  
-sA:带ACK标记的TAC报文，判断端口是否被过滤  
-sF:带FIN标记的TAC报文，判断端口是否关闭  
-sX:见手册
-sN:见手册

####  所谓的Option和ScanType是从哪个方面区分的？

ScanType 用来制定包的类型，options 通常不是必选的，那么option用来制定其余的配置，比如往哪些端口发，按什么速率。  
这就是两者从配置角度的差异，比如-PS参数会通过一个完整的TCP链接的三次握手和断开链接的四次握手。  

####  -PS 和-sS 什么区别
-PS是一个选项，表明在原有的扫描情况下，如果用户是root。就用SYN包来代替怨ACK去发现主机存活这一目的。

比如用-PS -sn 和单独的 -sn 来比较，-sS标明用户需要先发现存活主机后用SYN报文发起端口探测。

####  端口包括哪些状态

open 可以被链接  
filtered 被防火墙之类的过滤  
unfiltered 几乎等价于关闭  

####  主机的状态有哪些

up 或者 down  

####  主机发现相关报文

ARP, icmp-echo-request, icmp-timestamp-request, tcp, udp

####  如何只发现主机不扫描端口

使用参数 -sn/-sP

####  主机发现原理是什么

同一子网，用ARP报文探测。

不同网段，发送icmp-request报，以及 tcp-syn报文到443端口。

问题:发现发往443的报文有两个，其中一个报文多一个WS=4  

####  ip范围怎么灵活表示

常用的有192.168.10.10-20，有192.168.10.10/24

####  有哪链路层探测报文
####  有那些ip层探测报文
####  icmp-echo-request报文和icmp-timestamp-request报文什么区别？


####  有哪些TCP探测报文
-PS, -PA  

####  常见的TCP端口探测报文有哪些


####  有哪些UDP端口探测报文有哪些
-PU  

####  SCTP报文参数
-SCTP  


####  加快端口探测的选项有哪些
-F: 快速模式 扫描开放概率TOP100端口  
--top-ports <number>:扫描开放概率最高的number个端口  
--port-ratio <ratio>:扫描开放概率大于ratio以上的端口  


####  准确度相关的选项有哪些？
--version-intensity <level>  
--version-light  
--version-all  


####  加快系统探测的常用方法有哪些
--osscan-limit: 只对存活主机进行OS探测  
--osscan-guess: 猜测对方主机的系统类型  


####  如何隐藏自己
用 -r 来使端口随机化  
分片，将TCP拆分成多个IP包发送出去。  
MAC伪装，--spoof-mac  
nmap -D 192.168.10.1 --spoof-mac 00:50:56:c0:00:08 192.168.23.8  
ip混用，将真实IP和其他主机的IP混合使用  
nmap -D 192.168.10.1,192.168.10.2,192.168.10.3 192.168.23.8  
ip伪装，自己发送数据包中的原地址修改为其他主机地址  
nmap -e eth0 -S 192.168.10.184 192.168.23.8  


####  如何在windows下指定网卡
在windows下是用eth0指定第一张以太网卡  


####  如何查看本机可用网卡信息
使用 nmap --iflist  


####  IP伪装后统一子网为什么能收到报文？
因为同一子网的报文传输不需要ip地址  


####  如何制定端口发送报文
    -g <port>  


####  如何控制发包速度
用-T选项:
* paranoid 串行化所有扫描避开IDS，报文间隔5分钟
* Sneaky 同上，报文间隔15秒
* polite 报文间隔 0.4秒
* Normal 默认配置 适合网络状况良好的情况
* Aggressive
* Insane 


####  如何产生随机ip地址来扫描
-iR [count]


####  什么是 ping sweep，ACK sweep
####  什么是 retransmission calculations
####  linux下运行nmap进行操作系统探测告知需要root权限？
因为关键的内核接口比如raw-socket需要root权限


更多参见：
http://nmap.org/book/man-bypass-firewalls-ids.html
