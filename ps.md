```
查看线程	–Tp
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
示例：	ps xao pid
```

```
ps -L  -o  pid,lwp,start,stat,time,comm -p <pid>
ps  -lTp 1234 5678  = ps -lT p 1234 5678
```   
