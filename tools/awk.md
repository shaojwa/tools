#### 基本原则
变量可以直接用，赋值和访问都直接用变量名，只有位置变量才需要用$访问。

#### 实例
```
cat timestamp.txt | awk '{print $1}' | awk -F . '{ print $2 }' | \\
awk 'BEGIN {sum = 0} { if (NR % 2 == 1) t = $1; if (NR % 2 == 0) sum += $1 - t; } END {print sum}'
```

#### OFS
```
awk 'BEGIN{ OFS = "\t" }; { print $3,$6}'
```
#### awk中如果分割符是[]要怎么处理
```
awk –F ‘[][]’ // [is closed with ]， except when ] follows immediately the opening [
```
#### awk 显示最后一列
```
awk '{print $(NF)}'
```
#### awk 倒数第二列
```
awk '{print $(NF-1)}'
```
