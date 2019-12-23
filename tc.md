#### 怎么配置网络延时

    tc qdisc del dev ethA08-0 root netem delay 5s
    tc qdisc add dev eth1 root netem delay 3s
    tc qdisc del dev eth1 root netem delay 3s
    tc qdisc show dev eth1
