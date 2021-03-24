https://www.ibm.com/developerworks/cn/linux/l-vimdiff/

## 算法
基于左边，匹配右边，如果左边的行右边没出现，则左边的行显示红色，后边没有则显示了绿色。

## 开启
```
$ vimdiff    FILE_LEFT  FILE_RIGHT
$ vimdiff -d FILE_LEFT  FILE_RIGHT
```

## 查看
1. 相同的部分会被折叠起来
1.



## 两个文件间跳转
```
Ctrl-w, w
```

## 修改配色
.vimrc 中
```
if &diff
  colorscheme blue
endif
```

## 其他常用命令
```
vimdiff
diffget
diffput
diffu[pdate]
do //own
dp //put
]c //next diff
[c //prev diff
zo
zc
```
