#### 基本原则
变量可以直接用，赋值和访问都直接用变量名，只有位置变量才需要用$访问。


#### 分隔符
awk中是没有IFS的，只有FS和OFS，一般我们用FS就够。而要同时使用多个分隔符，那么用-F和在BEGIN中用FS也是一样的。
但是要注意一个规则就是，如果FS中引号内只有一个字符，那么这个字符就是分隔符，如果多个字符，那么就必须满足正则表达式规则。
如果引号内有多个字符而且不满足正则表达式那么整个行就不会分隔。所以下面这个功能你用冒号和逗号分隔，就必须写成这样：
```
cat test | awk 'BEGIN{FS="[:,]"}{print $10；}'
```
这个等价于
```
cat test | awk -F "[:,]" '{print $10;}'
```
所以感觉还是F选项简短好用。

#### 实例
```
cat timestamp.txt | awk '{print $1}' | awk -F . '{ print $2 }' |
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
