#### 线程有父线程么？怎么查看？
进程的ppid可以通过 ```cat /proc/<pid>/status``` 中的PPid字段查看到，所以我们也用同样的方法去查发现，所有的线程的ppid和主线程的ppid相同，也就是进程的ppid相同。
