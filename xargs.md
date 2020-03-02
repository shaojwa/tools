#### 需要替换用-i参数

```
xargs -i cat /proc/{}/sched | grep switch
```

#### 需要用其他的替换字串用-I

```
xargs -Ixxxx cat /proc/xxxx/sched | grep switch
xargs -I{} cat /proc/{}/sched | grep switch
```
-I后面就是个替换字串，命令中查找是否有这样的字串，有的话就替换，一般都是用 -I{}。

#### 命令中有管道用 bash -c

```
sudo locate -br ^.*\\.sh$  | xargs -i bash -c 'echo {} >> total.sh; cat {} >> total.sh'
ps -Tp 201255 | awk '{print $2}' | xargs -i bash -c "cat /proc/{}/sched | grep switch"
```
