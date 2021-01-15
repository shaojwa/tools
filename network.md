#### route print
```
On-link:
Inferface: local netcard ip
```
after adding 2 default-gateway 172.16.84.1 and 192.168.84.1
```
Active Routes:
Network Destination     Netmask     Gateway     Interface       Metric
            0.0.0.0     0.0.0.0     10.99.68.1  10.99.68.176    10
            0.0.0.0     0.0.0.0     172.16.84.1 172.16.84.141   266
            
Persistent Routes:
Network Destination     Netmask     Gateway                 Metric
            0.0.0.0     0.0.0.0     172.16.84.1             Default
            0.0.0.0     0.0.0.0     192.168.84.1            Default  
```

#### bnet
```
10.99.68.176
255.255.254.0
10.99.68.1
```

#### snet
```
172.16.84.141
255.255.255.0
172.16.84.1
```

#### to local cluster
should config the local ip: 192.168.84.141/255.255.255.0
```
tracert 192.168.84.199
  1    <1 ms    <1 ms    <1 ms  192.168.84.199
```

#### to workspace net
```
10.99.190.158
```
tracert, goto gateway 10.99.68.1, because the first route
```
> 10.99.190.158
1.          10.99.68.2
2.          Request timed out
3.          172.23.6.66
4.          10.99.190.158
```


#### to chengdu
```
10.132.32.201
```
tracert, goto gateway 10.99.68.1, because the first route
```
> tracert 10.132.32.201
1.          10.99.68.2
2.          Request timed out
3.          172.23.7.218
4.          172.23.14.61
5.          Request timed out
6.          10.132.32.201
```


#### 刷缓存
net cache flush
