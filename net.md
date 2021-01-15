#### route print
```
O-link:
Inferface: local netcard ip
```
```
Active Routes:
Network Destination         Netmask         Gateway        Interface       Metric
            0.0.0.0         0.0.0.0         10.99.68.1     10.99.68.176    10
            0.0.0.0         0.0.0.0         172.16.84.1    172.16.84.141   266
            
Default Gateway:
Network Destination         Netmask         Gateway        Interface       Metric
```

#### bnet
```
10.99.68.176
255.255.254.0
10.99.68.1
```
#### to workspace net
```
10.99.190.158
```
tracert, goto gateway 10.99.68.1 first:
```
1. 10.99.68.2
2. timeout
3. 172.23.6.66
10.99.190.158
```

#### snet
```
172.16.84.141
255.255.255.0
172.16.84.1
```





#### to chengdu


#### 刷缓存
net cache flush
