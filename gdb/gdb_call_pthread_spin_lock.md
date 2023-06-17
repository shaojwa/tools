we can run `call` command in gdb, the value of pthread_spinlock_t is 1  after inited
```
(gdb) info thread
  Id   Target Id         Frame
  3    Thread 0x7f6053c8c700 (LWP 3319311) "out" 0x00007f6053d52a8d in nanosleep () from /lib64/libc.so.6
  2    Thread 0x7f605348b700 (LWP 3319312) "out" 0x00007f6054886582 in pthread_spin_lock () from /lib64/libpthread.so.0
* 1    Thread 0x7f6054ca7740 (LWP 3319310) "out" 0x00007f6054883017 in pthread_join () from /lib64/libpthread.so.0
(gdb) t 3
[Switching to thread 3 (Thread 0x7f6053c8c700 (LWP 3319311))]
#0  0x00007f6053d52a8d in nanosleep () from /lib64/libc.so.6
(gdb) bt
#0  0x00007f6053d52a8d in nanosleep () from /lib64/libc.so.6
#1  0x00007f6053d52924 in sleep () from /lib64/libc.so.6
#2  0x000000000040092a in routine1 (ptr=0x7ffedb49db2c) at spinlock_gdbcall.cc:21
#3  0x00007f6054881ea5 in start_thread () from /lib64/libpthread.so.0
#4  0x00007f6053d8bb8d in clone () from /lib64/libc.so.6
(gdb) f 2
#2  0x000000000040092a in routine1 (ptr=0x7ffedb49db2c) at spinlock_gdbcall.cc:21
21          sleep(100);
(gdb) p *spl
$1 = -1
(gdb) call pthread_spin_unlock(spl)
$2 = 0
(gdb) bt
#0  0x00007f6053d52a8d in nanosleep () from /lib64/libc.so.6
#1  0x00007f6053d52924 in sleep () from /lib64/libc.so.6
#2  0x000000000040092a in routine1 (ptr=0x7ffedb49db2c) at spinlock_gdbcall.cc:21
#3  0x00007f6054881ea5 in start_thread () from /lib64/libpthread.so.0
#4  0x00007f6053d8bb8d in clone () from /lib64/libc.so.6
(gdb) info thread
  Id   Target Id         Frame
* 3    Thread 0x7f6053c8c700 (LWP 3319311) "out" 0x000000000040092a
                                                 in routine1 (ptr=0x7ffedb49db2c) at spinlock_gdbcall.cc:21
  2    Thread 0x7f605348b700 (LWP 3319312) "out" 0x00007f6053d7cc3d
                                                 in write () from /lib64/libc.so.6
  1    Thread 0x7f6054ca7740 (LWP 3319310) "out" 0x00007f6054883017
                                                 in pthread_join () from /lib64/libpthread.so.0
(gdb) c
Continuing.
```

if we call `pthread_spin_lock(spl)`
```
(gdb) bt
#0  0x00007f34c7146585 in pthread_spin_lock () from /lib64/libpthread.so.0
#1  <function called from gdb>
#2  0x00007f34c6612a8d in nanosleep () from /lib64/libc.so.6
#3  0x00007f34c6612924 in sleep () from /lib64/libc.so.6
#4  0x000000000040091d in routine1 (ptr=0x7ffe80fed56c) at spinlock_gdbcall.cc:21
#5  0x00007f34c7141ea5 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f34c664bb8d in clone () from /lib64/libc.so.6
```
