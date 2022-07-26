以sudo运行的脚本，会有一个root作为有效uid的进程：
```
root     1206640  0.0  0.0 113296  2992 pts/3    S+   09:00   0:00 /bin/bash sudo_run.sh
```
此时，如果按ctrl-z停止进程，那么这个进程的状态会变成`T`
```
root     1206640  0.0  0.0 113296  2992 pts/3    T    09:00   0:00 /bin/bash sudo_run.sh
```
然后用fg唤醒运行，然后按ctrl-c退出任务，进程不再继续。
