```
-f 跟踪由fork调用产生的子进程
-t 开头显示时间到秒
-tt 开头显示时间精确到微秒,但秒字段显示的是时间，推荐用这个
-ttt 开头显示时间到精确微秒,但秒字段显示的是秒数
-T 显示每一条用消耗的时间
-c 统计调用次数，系统时间（CPU运行在内核态时间）
-e trace=open，close  只跟踪指定的系统调用
-o <filename> 将strace 输出到指定的文件
-p pid 跟踪制定的进程

-e trace=file
-e trace=process
-e trace=network
-e trace=signal
-e trace=ipc
-e trace=desc
```

示例：
```
// 跟踪vdbench的xfersize, 2097152 是IO大小，12582912是偏移量
$ strace -tt -T -f -e trace=pwrite64 -p 1500232
[pid 1500856] 15:45:22.077391 pwrite64(19, "\0\f\...\236I\17~"..., 2097152, 12582912 <unfinished ...>
[pid 1500879] 15:45:22.094193 <... pwrite64 resumed> ) = 2097152 <1.576809>
```
