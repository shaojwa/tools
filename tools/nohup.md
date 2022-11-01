#### 传递给谁
如何终端连接断开，这个nohup会发送到回话的首进程。如果会话首进程终止，那么这个信号会发送到前台进程组中的每一个进程。

#### nohup的作用
就是对hangup信号免疫（immune），主要是用来避免控制终端退出时，前台进程组的进程受到这个信号的影响。

#### SIGHUP的信号如何产生
一般来说，一个会话session的中断断开时，内核回给这个会话的首进程发送这个信号。
当会话的首进程终止时，内核也会给前台进程组的每个进程发送这个信号。
```
[SDS_Admin@node80 ~]$ cat test_nohup.sh
#!/bin/bash

i=0
while true; do
  echo $i
  sleep 1
  ((i++))
done
```

#### 测试场景
所以，当我把bash进程杀死时，从bash中启动的执行脚本的bash也会退出。
```
[SDS_Admin@node80 ~]$ ps -eo pid,ppid,pgid,sid,cmd | grep bash
 907175  907090  907175  907175 -bash
1083566  907175 1083566  907175 /bin/bash ./test_nohup.sh  # ./test_nohup.sh
1124494  907175 1124494  907175 /bin/bash ./test_nohup.sh  # ./test_nohup.sh &
```
执行test_nohup.sh 的bash的sid是和log-in bash相同的，都是907175，但是pgid是自己。当kill log-in bash时, 有一个bash还在：
```
1124494       1 1124494  907175 /bin/bash ./test_nohup.sh
```
`nohup`会修改前台进程组，而`&`运行并不会，`nohup+&`也不会修改。一个回话有很多进程组，而前台进程组之后一个。
