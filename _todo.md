#### done
```
网络丢包模拟工具tc(done)
logrotate基本用法(done)
excel锁定一行(done)
快排实现(done)
线程有创建它的父线程么？(done） 没有，ppid只显示父进程的pid 
什么是 UP Machine (done) UP = uniprocessor, 单处理器
进程的状态和它的线程的状态什么关系？(done)
```

#### todo
 
```
命令ipcs了解一下
strace man 手册
自动补全的原理
std::unordered_map;
std::unordered_multimap;
当进程文件删除之后，gdb挂载之后，为什么无法查看线程？
kill -kill 一个线程后为什么会把这个线程所在的进程中的所有线程杀掉？
红黑树实现
task需要TASK_UNINTERRUPTABLE状态的原因
IO 时为什么处理信号非常困难
semaphore和mutex的区别（https://www.zhihu.com/question/47704079）
fork出来的子进程不能继承的资源到底是什么
pthread_cond_wait 为什么需要传递 mutex 参数？(https://www.zhihu.com/question/24116967)
Goodbye semaphores?（https://lwn.net/Articles/166195/）
https://stackoverflow.com/questions/4764945/difference-between-completion-variables-and-semaphores
c++ 的线程库以及同步库提供的接口和pthread接口的对应关系是什么？
linux存在强制锁（mandatory lock）和劝告锁（advisory lock），使用场景是什么？

5.5.4 Thread-Specific Breakpoints
https://sourceware.org/gdb/onlinedocs/gdb/Non_002dStop-Mode.html
https://sourceware.org/gdb/onlinedocs/gdb/Asynchronous-and-non_002dstop-modes.html
https://stackoverflow.com/questions/19181834/what-is-the-concept-of-vruntime-in-cfs
tmux卡死问题，client和server都只有一个线程，用tmux kill-window -t 1 终止该window。
https://chortle.ccsu.edu/AssemblyTutorial/   
http://kerneltrap.org/node/517    
对目录调用 stat 系统调用时的返回值是什么意思？
sync，syncfs，fsync，fdatasync 等系统调用的区别和注意点？
lock_gettime() 接口中，CLOCK_REALTIME and CLOCK_MONOTONIC 区别以及适用场景？
正常TCP会话会保持多久？
TCP/IP重传超时RTO是什么意思？
优先级倒置是什么意思？
fork创建的子进程不会继承父进程挂起的信号，而exec创建的进程会继承父进程挂起的信号，为什么？
进程中的信号相关配置存储在哪里？
chroot 的适用场景是什么？
select微秒级精读是什么意思？
poll毫秒精度是什么意思？
pselect/ppoll纳秒级精但毫秒级已经不可靠
    
深入linux PAM体系结构    
EINTER系统调用被中断    
ctrl+\终止前台进程组中进程并产生core
linux 系统编程p55
原生编程规范 是什么意思？    
    
看一下 ld 的man手册
sshpass 做什么用的？
添加sudo权限通过wheel方式和编辑sudoers的方式哪个更好？
shutdown命令的halt是什么意思？
the /run/nologin file is created to ensure that further logins shall not be allowed. (ref shutdown)
https://www.ibm.com/developerworks/cn/linux/l-bash-test.html
windows10 下有ubuntu子系统，可以试用下，尽管据说有不少命令可能还不能用。

xfs 文件系统写数据有journal么？
lowest priority APIC routing
如果查看占用CPU高的程序？
进程以及线程对不同信号的处理方式？
linux 内核中的三个 tcp keepalive参数是什么含义？

cat /sys/block/sda/queue/read_ahead_kb
echo c > /proc/sysrq-trigger
/proc/locks 什么作用
/proc/net/dev
/proc/net/snmp    
ifdown和ifconfig区别？
iopath结合图理解
内存泄露工具Valgrind了解
 
信心上限树是什么(UCT) 是什么东西？
std::hash (std::bitset)
https://stackoverflow.com/questions/12600330/pop-back-return-value
http://www.gotw.ca/gotw/008.htm
https://stackoverflow.com/questions/596162/can-you-remove-elements-from-a-stdlist-while-iterating-through-it
https://stackoverflow.com/questions/799314/difference-between-erase-and-remove
move也会抛出异常，所以不是所有的类型都是movable
1234b2有其他算法需要了解下
```
