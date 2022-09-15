dse@.service 查看
```
sudo systemctl show dse.service| grep Limit
```
```
LimitCORE=infinity
```
LimitCORE 这个默认值是 -1
