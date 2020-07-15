
#### tabstop 还是 softtabstop
```
只要softtabstop != 0, 不管expandtab什么值，tab都是softtabstop数量的空格。
如果softtabstop == 0, tab对应的长度都是tabstop，是不是转为空格由expandtab决定。
```
#### smarttab
```
如果开启，一行最开始时tab的缩进按照shiftwidth来缩缩进，其他地方用tabstop和softtabstop。
如果关闭，一行中所有的tab的缩进按照softtabstop和tabstop，shiftwith只在左移或者又移代码时用。
```

#### cindent
```
这个标记用来标记缩进，关联的配置项是shiftwidth，所以只要配置这个，一行开头的缩进就是这么多。
如果 shiftwidth != 0，那么就缩进这么多空格，和tabstop和softtabstop无关。
如果 shiftwidth == 0，那么缩进的数量就由softtabstop决定，如果softtabstop为0，那么由tabstop决定
```
