#### 常用选项
```
-e trace    // 跟踪的系统调用，默认是所有
-tt         // 推荐使用的时间戳使用方式，时间格式为秒格式，时间精度为微秒
-T          // 显示每一调用消耗的时间
-f          // 跟踪由fork调用产生的子进程
-o filename // strace的输出写入filename文件
```

#### 其他选项

```
-t 开头显示时间到秒
-ttt 开头显示时间到精确微秒,但秒字段显示的是秒数
-T 显示每一调用消耗的时间
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


#### 示例
用例1
```
strace -o dd.strace -T -e all -tt dd if=/dev/zeof of=ddfile bs=4k count=1024
strace -o dd.strace -T -e all -c dd if=/dev/zeof of=ddfile bs=4k count=1024
```

用例2：
```
// 跟踪vdbench的xfersize, 2097152 是IO大小，12582912是偏移量
$ strace -tt -T -f -e trace=pwrite64 -p 1500232
[pid 1500856] 15:45:22.077391 pwrite64(19, "\0\f\...\236I\17~"..., 2097152, 12582912 <unfinished ...>
[pid 1500879] 15:45:22.094193 <... pwrite64 resumed> ) = 2097152 <1.576809>
```

#### 注意点

用-c参数，-c和-t/-tt/-ttt/-T不能同时使用。
