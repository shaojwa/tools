#### 问题
最近碰到一个问题，用wsh账户登入集群后，每次`ll`命令，都提示我敲入password。
```
[sudo] password for wsh:
```
我猜测这个和pam有关系。linux中的pam主要就是干认证工作的。

#### 解决方案
用visudo中加上如下一行：
```
wsh ALL=(ALL)       NOPASSWD:ALL
```
或者更加暴力一点：
```
wsh     ALL=(ALL)       ALL
```
都可以解决这个问题。
