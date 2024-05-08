https://www.kernel.org/doc/Documentation/networking/ip-sysctl.txt

现象是message日志中会有答应：
```
cat /proc/sys/net/ipv6/neigh/default/gc_thresh3
```
涉及到邻居表象的回收，有三个，分别是gc_thresh1，最小保留项，小于这个数量不回收。
gc_thresh2，当缓存大于这个值时，会清空大于5秒的arp表象，gc_thresh3，硬性最大阈值。
