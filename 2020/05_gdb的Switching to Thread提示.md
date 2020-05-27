gdb使用的时候常常会看到以下提示，特别是某个线程出现段错误或者断言的时候：
```
[Switching to Thread 0x7f51a5bff700 (LWP 121819)]
```
其实这只是gdb告诉我们，某个线程出问题之后，当前线程切换到那出问题的线程，当前线程就是出问题的线程。
而不是说因为那个线程出问题挂掉，当前线程从那个线程切换到一个新的线程，不要误解。gdb官方文档有说：

Whenever GDB stops your program, due to a breakpoint or a signal, it automatically selects the thread where that breakpoint or signal happened.
