#### 问题
最近碰到一个问题，用wsh账户登入集群后，每次ll命令，都提示我敲入password。
```
[sudo] password for wsh:
```
我猜测这个和pam有关系。linux中的pam主要就是干认证工作的。
