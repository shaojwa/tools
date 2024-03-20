#### 这种用法在当前目录下有.log文件的时候有问题
```
find /path/ -name *.log
```
因为`*.log`会展开，所以应该写成
```
find /path/ -name '*.log'
```
或者
```
find /path/ -name "*.log"
```
或者
```
find /path/ -name \*.log
```
