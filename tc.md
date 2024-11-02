https://cloud.tencent.com/developer/article/2298332

##  whats qdisc
qdisc = queueing discipline, the layer between the kernel and interface driver.
the kernel enqueue the pacakges to qdisc and get the packages from the qdisc, then gives the packages to the driver.
the qdisc is associated to one of interfaces.
there are two kinds of qdisc, the classless qdisc and classful qdisc. the commonly-used qdisc 'netem' is one of the classless qdisc.

## tc qdisc netem
one of the classless qdisc.


## show the current  queue discipline
```
tc qdisc show dev  <iface> 
tc qdisc show dev ib41-0

setting delays for  the interface：
tc qdisc add dev  <iface> root netem delay <interval>
tc qdisc add dev ens19 root netem delay 6000ms
after setting we can see the  pcko is 0 by atop, but  non-zero in pcki, why?
because tc can not control the incomming packages.

why we cannot find the drops in atop when using command tc to do the dropping?


cancel the delays
tc qdisc del dev  <iface> root 
tc qdisc del dev ens19 root

dropping packages by tc (control the transmit queue，so it works on for sending)
tc qdisc add dev  <iface> root netem loss <percent>
tc qdisc add dev  <iface> root netem drop <percent>
tc qdisc add dev ens19 root netem loss 10%


netem is  one type of  queuing discipline used for network emulation

interface contol
disable the interface：
sudo ip link set <iface> down
sudo ip link set ib41-0 down
atop will not show the interface stats after we disable the interface.
 
 enable the interface：
sudo ip link set <iface> up


the reason of package drop


rx_dropped and tx_dropped
network driver is in the layer of Data link, eg L2 for the node-to-node data transfer.
driver works between the NIC(network interface card) and the operating system. 
https://www.kernel.org/doc/html/v6.1/networking/statistics.html


tc qdisc add dev ib41-0 ingress
tc filter add dev ib41-0 parent ffff: protocol ip u32 match ip src 172.16.25.85 action drop
tc filter del dev ib41-0 parent ffff:0
```
![image](https://github.com/user-attachments/assets/0f67eff9-8e86-4530-9a7f-4f34faddebbe)

## algo
TBF 

## Stochastic Fireness Queuing
Round Robin Dqueuing Algorithm

