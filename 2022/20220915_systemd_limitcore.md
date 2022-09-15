dse@.service 查看
```
sudo systemctl show dse.service| grep Limit
```
```
LimitCORE=infinity
```
LimitCORE这个默认值显示的是18446744073709551615。配置成infinity之后，status显示的也是18446744073709551615。
```
[admin@node01 ~]$ sudo systemctl show dse.service| grep -i limitcore
LimitCORE=18446744073709551615
```
但是奇怪的是，不配置时，查看proc下的limits，soft limit 是0，而配置之后就是ulimited。
```
[root@node60 system]# cat /proc/$(pidof dse)/limits | grep core
Max core file size        0                    unlimited            bytes
```
如果配置
```
[SDS_Admin@node60 ~]$ cat /proc/$(pidof dse)/limits | grep -i core
Max core file size        unlimited            unlimited            bytes
```
我们只能这么理解，status中显示的应该是上限，是hard-limit，我们配置的LimitCORE是对soft和hard都起作用的。
