## 查看线程
```
查看线程	–Tp
```
## 指定字段
```
进程命令行	cmd
父进程id	ppid
进程组id	pgid
会话id	sid/sess
前台进程组id	tpgid
进程分配的处理器	psr
命令启动时间	lstart
cpu运行时间	bsdtime
cpu运行时间	time
cpu运行时间	cputime
ps -L  -o  pid,lwp,start,stat,time,comm -p <pid>
```

#### 其他示例
```
示例：	ps xao pid
```

#### 两个进程号导致输出结果不符合预期

用以下命令发现显示的进程线程名不符合预期
```
ps -lTp 1827654 4022
```
```
单pid的时候，输出结果的TIME字段是时分秒三段式，两个pid会导致TIME字段只有分和秒。
单pid的时候，输出结果的CMD字段是线程名，两个pid会导致CMD字段只输出执行文件和参数。
我们发现，后面这种格式是p参数而不是-p参数的输出。所以我们先了解p和-p的区别。
man ps告诉我们p和-p是一样的，那是什么原因？这分两部分：
(1)-p和p的区别，p和-p的中针对CMD的字段应该本来就不一样，所以只要是p，不管是 ps -T -l p 还是 ps l p，都不会输出线程名。
(2)-l和l也有区别，从输出结果上看，这是应该和两种不同的long-format有关系，一种叫BSD-long-format。
那为什么 ps -T l -p也不会输出线程，因为l是BSD-style，所以会把-p也转成p。
ps -Tl p 1827654 变成 ps -T -l p 1827654 再变成 ps -T l p 1827654 效果等价。
```
