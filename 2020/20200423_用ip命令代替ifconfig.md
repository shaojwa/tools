## show
```
ifconfig
ip addr show = ip a sh
ip link show = ip l sh
```

## enable network interface
```
ifconfig eth0 up
ip link set eth0 up = ip l set eth0 up
```
## set ip address
```
ifconfig eth0 192.168.0.3
ip address add 192.168.0.3 dev eth0

ifconfig eth0 192.168.0.3 netmask 255.255.255.0 broadcast 192.168.0.255
ip addr add 192.168.0.3/24 broadcast 192.168.0.255 dev eth0
```

## del ip address
```
ip addr del 192.168.0.3/24 dev eth0
```

## Add alias interface
```
ifconfig eth0:1 10.0.0.1/8
ip addr add 10.0.0.1/8 dev eth0 label eth0:1
```

## route 命令也应该用 ip route 代替
```
ip route show
ip route get 192.168.88.33
```
