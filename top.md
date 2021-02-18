#### 按进程号升序排列
如果要从小到大，那么需要这样：
```
top -bn1 -o -PID
```
因为：
```
You can prepend a `+' or `-' to the field name to also override the sort direction.
A leading `+' will force sorting high to low, whereas a `-' will ensure a low to high ordering.

This option exists primarily to support automated/scripted batch mode operation.
``` 
#### 按进程号排序
默认是降序
```
top -bn1 -o PID
```

#### 分批模式
所谓的batch mode，就是不会动态变化，只显示某个时间点的数据，用-b参数。常常和-n搭配使用。
```
top -bn1
```

#### 按CPU占用率排序进程
```
top -bn1 -o %CPU
```   

#### 内存占用率排序进程

```
top -bn1 -o %MEM
```
   
#### 备注
```
M	按内存排序
N	按pid排序
P	按cpu排序
x	高亮排序列
y	高亮正运行的进程
b	选中一行
```
