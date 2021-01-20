#### 按CPU占用率排序进程
```
ps aux --sort -pcpu 
top -bn1 -o %CPU
```

#### 查看线程
```
查看线程	–Tp
```
#### 指定字段
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
```

这是一个而比较有意思的问题，以下三种方式的输出都不一样：
```
ps -T -l -p 1827654
ps -T -l p 1827654
ps -T l -p 1827654
```
其中 `ps -T l -p 1827654` 和 ps `-T l p 1827654` 输出一样。
我们能总结出来的规律是，如果-l还是l决定了输出字段的名称：
比如-l输出的是：
```
F S   UID     PID    SPID    PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
```
而l输出的是：
```
F   UID     PID    SPID    PPID PRI  NI    VSZ   RSS WCHAN  STAT TTY        TIME COMMAND
```
如果是l时，-p和p已经没有区别，但是在-l的情况下：-p 和 p 又不一样，-l p 中的CMD字段是执行文件路径和参数。
-l -p输出的也不一定是线程名，-T是线程名，H 就不是，不知道是不是和H是unix-style有关系。
所以，准确原因估计只能看ps的源代码了，因为proc文件系统中，有comm文件，也有cmdline文件，内容是不一样的。

查看procps-ng-3.3.10的源代码：
```
/* SysV options */ 对 -p会设置：
```
