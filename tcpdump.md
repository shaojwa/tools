#### tcpdump常用法

    tcpdump [ -i interface ] [ -w file] expression  
    exression = host { and | or } port { and | or } protocol

    -b: ip/arp/rarp
    -n：不将ip解析为域名
    -t: 不显示时间
    -X: 以ASCII 和 十六进制显示   
    
    -i: interface

    tcpdump host 10.99.68.34
    tcpdump –i em3
    tcpdump -i bond1 host 172.12.15.162 and port 6800
    tcpdump -i ethB02-0 -w nfs.cap port 2049 and tcp
    tcpdump dst port not telnet
    tcpdump src host 192.168.0.1 and dst net 192.168.0.0/24
  
   
### capture ICMP

    tcpdump -i ethA01-0 host 10.99.68.235 and icmp
