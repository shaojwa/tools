gnu find
#### 搜索模式
find默认就是递归搜索一个start-point下的所有子目录。

#### 超过100天的文件
```
find . -mtime +100
```

#### 超过100K的文件
```
find . -size +100k
```

#### -name 匹配
find中的-name，针对的是文件的basename，会忽略pattern中的路径。
同时，用的是shell模式，好像并不是正则匹配，man中说用的是fnmatch库函数的：
有一点要注意，如果用了`*`那么需要把pattern字串用引号包含起来，不然`*`会被shell展开。
```
$ find . -name "*.cmake"
$ find . -name \*.cmake
```
