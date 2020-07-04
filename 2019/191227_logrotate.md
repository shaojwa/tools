#### 执行顺序

```
/etc/cron.d/publog
-> /var/lib/publog/logrotate_ceph.sh
-> /usr/sbin/logrotate  /var/lib/publog/logrotate_ceph

/var/lib/publog/logrotate_ceph 中描述把 /var/log/ceph/*.log的日志替换到 /var/log/storage/backup/
```

####　man logrotate

* logrotate 设计的目的就是为了更好的管理系统产生的大量日志。
* log允许自动的轮换，压缩，删除，邮递。
* 没一个日志文件都可能按照每天，每周，每月或者当它增长到一定大小时进行处理。
* 正常情况下，logrotate会被当做一个每日定时任务执行。

#### 使用

logrotate的运行脚本在/etc/cron.daily/logrotate，注意这个文件没有后缀，一般表示这是一个当做工具的。

```
20,50 *    * * *   root   /var/lib/publog/logrotate_ceph.sh
```

#### 配置参数

```
rotate // 转储文件保留多少份
```
