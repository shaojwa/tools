#### smarttab
```
如果开启，一行最开始时tab的缩进按照shiftwidth来缩缩进，其他地方用tabstop和softtabstop。
如果关闭，一行最开始时tab的缩进按照tabstop和softtabstop来用，shiftwith只在左移或者又移代码时用。
```

#### tabstop 还是 softtabstop
```
只要softtabstop!=0, 不关expandtab什么值，tab都是softtabstop数量的空格。
如果softtabstop == 0, tab对应的长度都是tabstop，是不是转为空格由expandtab决定。
```
