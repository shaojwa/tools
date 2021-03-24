https://www.ibm.com/developerworks/cn/linux/1412_xiehy_tc/index.html

http://www.tldp.org/HOWTO/html_single/Traffic-Control-HOWTO/

####  什么是流量控制

tc， traffic control， 流量控制，简称流控，控制网卡进出流量，需要了解网卡工作原理。

#### 按照控制过程分两种

队列控制（即QOS，队列的规则控制，比如SFQ， PRIO），把请求放到队列中，

和流量控制（即带宽控制，队列的排队整形，比如TBF，HTB），

#### 按照控制算法分两种

1. 无类算法，用于树叶级无分支的队列，不对报文进行分类，如 SFQ
1. 分类算法，用于多分支的队列，对多种数据流进行分类，例如PRIO，TBF，HTB

#### 队列控制的无类算法 SFQ

把每个会话通过散列算法映射到有限的几个队列中，队列之间轮询，

#### 流量控制无类算法 TBF （token bucket filter 令牌桶过滤器）

令牌的分配速度恒定，但是用不完可以积累，所以有可能突然，然是总的平均速度是稳定的。

#### 怎么配置网络延时

    tc qdisc add dev ethA08-0 root netem loss 50
    tc qdisc del dev ethA08-0 root netem delay 5s
    tc qdisc add dev eth1 root netem delay 3s
    tc qdisc del dev eth1 root netem delay 3s
    tc qdisc show dev eth1
