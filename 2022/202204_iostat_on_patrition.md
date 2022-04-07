iostat man页面看完。

#### 显示磁盘的各个分区信息
using iostat -p, The -p option displays statistics for block devices and all their partitions that are used by the system.
```
$ iostat -p ALL
$ iostat -p nvme4n1
```
-p参数是ALL 或者是 device，不能加分区，添加device之后，就会显示device下所有的分区的统计。

#### 同时显示时间戳
用-t参数。
