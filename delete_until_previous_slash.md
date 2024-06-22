## 先查询一下
```
bind -P |grep unix-filename-rubout
```
发现没有bound，单后绑定一个。

## 选用一个bind
发现只有ctrl-c和ctrl-z没有被默认绑定，选用ctrl-c和ctrl-z不能用。那就用alt：
```
"\ew":unix-filename-rubout
```

## 发现已经有相关命令
比如`alt-ctrl-h`就可以backward-kill-word
```
"\e\C-h": backward-kill-word
```
还比如同样的功能，用 `alt+backspace`, // 往左删除一个语义上的单词(以斜杠为分隔符)
```
"\e\C-?": backward-kill-word
```
因为backspace一般是用ctrl-?来表示。
