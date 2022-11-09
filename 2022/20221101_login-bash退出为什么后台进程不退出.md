#### login-bash 被杀或者退出时，会往前台进程组中的每个进程发送SIGHUP信号。后台进程不再这个组中。
```
[wsh@node80 ~]$ ps -eo pid,ppid,pgid,sess,tpgid,cmd | grep bash
2872506 2872197 2872506 2872506 2872506 -bash
2873711 2872506 2873711 2872506 2872506 /bin/bash /home/SDS_Admin/test_nohup.sh
```
当前的前台进程组是2872506，而nohup所在的进程组是2873711，所以不会被杀。
