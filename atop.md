## atop-explained
https://linuxwheel.com/atop-explained/
lower case key can be used to show other informations.
and upper case keys can be used to influence the order.

#### 系统信息行控制
key l, Limit the number of system level lines

#### 选定进程
shift+p

#### 显示进程内线程
y

#### 显示内存相关输出
m

#### 显示磁盘相关输出
d

#### key b
viewing raw file, go to a certain timestamp, b meas begin

#### key t/T
show previous/next sample from the file

#### key s
show scheduling characteristics

## read atop file
atop -r atop_20210601

## MISC commands
#### key z
freeze the current situation

#### key i
trigger a new sample manually

#### key r
reset

#### 1st line: System Level Information
```
PRC line: Process level totals
#sys: Total CPU time consumed in system mode
#user: Total CPU time consumed in user mode
#proc: Total number of processes present at this moment
#trun: Total number of running threads present at this moment
#tslpi: Total number of sleeping threads present at this moment
#tslpu: Total number of sleeping uninterruptible threads present at this moment
#zombie: Total number of zombie processes
#clones: Number of clone system calls
#exit: Number of processes that ended during this interval
#exit: Number of processes that ended during this interval
```
