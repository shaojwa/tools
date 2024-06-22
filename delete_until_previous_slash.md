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
