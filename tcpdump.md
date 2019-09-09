#### tcpdump常用法

    -n：不将ip解析为域名
    -m: 全部显示port
    -X: 以ASCII 和 十六进制显示
    -i: tcpdump -i eth0
    -b: ip/arp/rarp
    -t: 不显示时间

    tcpdump host 10.99.68.34
    tcpdump –i em3
    tcpdump dst port not telnet
    tcpdump src host 192.168.0.1 and dst net 192.168.0.0/24
    tcpdump -i bond1  host 172.12.15.162 and port 6800
