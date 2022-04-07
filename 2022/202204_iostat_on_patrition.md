using iostat -p
```
$ iostat -p ALL
$ iostat -p nvme4n1
```
-p参数是ALL 或者是 device，不能加分区，添加device之后，就会显示device下所有的分区的统计。
