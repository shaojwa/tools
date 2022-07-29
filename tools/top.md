#### top的能力范围
top是比较喜欢的命令之一，就像man里说的一样，这个命令主要显示的linux进程，而网络、磁盘相关的显示功能比较弱，不能查看网络，磁盘信息。

#### 关于命令参数
man中说到，传统的-和空格是可选的，我试试了下，确实`top -p 489883`和`top p 489883`以及`top p489883`功能一样。

#### 配置的持久化
这个命令支持很多关于信息类型，顺序，以及大小的显示都是可以配置的，而且这个配置可以持久化，以支持重启之后依然可用。

#### 最终要的两个key
首先是h，寻求帮助，其次是q，quit，退出top。

#### top的显示分区
汇总去，列头，任务区。

#### top的man手册
这man手册写得真好，哪些配置可以用在命令行中覆盖也写得很清楚。比如`H - Threads mode`，以及`s - Secure mode`

#### 参数和按键的同名
比如有-s设置safe mode，那么也会有s按键触发safemode，有-H设置线程显示，也有H触发线程显示，这种对应便于记忆。
当然更多的按键，是没有命令行选项对应的。也有很多命令行选项，并没有按键设置。

#### top中的统计起始点
top中的统计，需要注意一点，就是task部分的信息，都是从上一次刷新之后开始计时的，所以是几秒钟的时间间隔而已。

## 基本用法
#### top的上下左右显示
用方向键可以对top的行和列进行移动显示。让然，强大的top也只是组合键，分别是alt+hjkl

#### 查看CPU负载
按 0123 // 基于CPU显示

#### 基于CPU使用率排序process
按键 P 

#### 基于内存使用率排序process
按键 M

#### 基于内存使用率排序process
按键 N


#### 查看可以排序的列名
top -O

#### 按进程号降序（默认是降序）
top -bn1 -o PID

#### 如果要升序，那就在列名前加减号
top -bn1 -o -PID
> You can prepend a '+' or `-' to the field name to also override the sort direction.
> A leading '+' will force sorting high to low, whereas a '-' will ensure a low to high ordering.
> This option exists primarily to support automated/scripted batch mode operation.

## CPU 相关
#### 按CPU占用率排序进程
top -bn1 -o %CPU

#### 内存占用率排序进程
top -bn1 -o %MEM  # 这里使用的%MEM是RES内存，就是实际使用的物理内存。

#### 指定监控的线程
-p参数，可以多次使用，最多20次，也可以用-p后加pid-list，pid-list中用逗号分隔，详细见man手册。

#### 特定线程模式回到常规模式
从特定进程模式回到多进程模式，按=，或者u，或者U，都可以。

#### 其他不常用命令
```
x	高亮排序列
y	高亮正运行的进程
b	选中一行
```

## top 中的字段
top提供了49个字段可供显示，都是和进程相关的。

#### 如何管理字段 MANAGING Fields

#### top中的Status字段
一共有6个，R/T(stopped)/S(sleeping)/Z(zombie)/D/t(traced)，值得注意的是t状态，表示正在被调试。

#### top 中的CODE字段
Code Size (KiB)，这个好像从来没用过，有点意思。

#### top 中的 DATA字段
Data + Stack Size (KiB)

#### top 中的FLAG字段
Task Flags，标记调度标记，有时候估计很有用。

#### top 中的NI字段
nice值，值越低，越冷酷，不nice。

#### top 中的P字段
Last used CPU (SMP), A number representing the last used processor. 这个是用来干什么的，探测是否存在CPU亲和性估计是。

#### top 中的 PR字段
和NI差不多，但是是两套算法，一般可以对应起来。

#### top 中的 TTY字段
注意man中的解释：The  name  of the controlling terminal. 

#### top 中的 WCHAN 字段
Sleeping in Function

#### top中的RES字段
和%MEM区别在哪里？ %MEM是比例，RES是具体的大小。

#### line oriented input

## batch mode
top -bn1 // 所谓的batch mode，就是不会动态变化，只显示某个时间点的数据，用-b参数。常常和-n搭配使用。

## secure mode

## view display mode
