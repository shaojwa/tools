第一反应是:
```
gti branch -u <upstream> <branchname>
```
但是这个命令只是设置branchname的 up-stream branch，并不会创建branch，所以如果branch那么不存在，那么就会报错：
```
fatal: branch `snap_assert` does not exist.
```
所以先create branch：
```
git branch snap_assert
```
然后再设置  tracking branch（upstream branch）
```
git branch snap_assert -u origin/UniStorOS_V100R001B01_multi_programgroup
```
当然，用checkout也是可以的，checkout 有`-b`参数用来创建branch，所以，可以是这样的：
```
git checkout -b snap_assert --track origin/UniStorOS_V100R001B01_multi_programgroup
```
