
#### top的能力范围
主要是解决进程相关统计信息，不能查看网络，磁盘信息。
  
#### 查看CPU负载
按 0123 // 基于CPU显示

#### 基于CPU使用率排序process
按键 P 

#### 基于内存使用率排序process
按键 M

#### 基于内存使用率排序process
按键 N

#### 其他不常用命令
```
x	高亮排序列
y	高亮正运行的进程
b	选中一行
```

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
