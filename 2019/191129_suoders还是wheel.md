参考：https://access.redhat.com/discussions/1392033

* redhat系统下有/var/log/secure系列日志，每周日归档。在sudoers下的用户，可以通过该日志进行跟踪事务。
* wheel下的用户并不是自动就能运行/bin/su (和/usr/bin/su是同一个文件，互为硬链接)
