https://cloud.tencent.com/developer/article/2298332

## tc
tc linux的网络流量控制工具，控制带宽，时延，丢包。

## tc qdisc
队列和排队规则，qdisc=queueing discipline。

## tc qdisc netem
主机内模拟网络延时，重复，丢包，乱序，网络损坏，网络中断，端口占用。

## classless queueing discipline
无分类排队规则，最常用的CQD 是 pfifo_fast，这是默认的排队规则，先来先处理。p是优先级的意思。

## 数据跑的TOS字段
这是报文中的标记字段，type of service， 8比特标记，准确说是8bit中的其中4个bit，在IP报文中，准确说是IP头。

#### TBF
令牌桶过滤去
