Tab其实就是按Tab时的缩进规格，shift的本意是代码左右移动时候的规格。

#### tabstop 还是 softtabstop
```
只要softtabstop != 0, 不管expandtab什么值，按tab都是softtabstop数量的空格。
如果softtabstop == 0, 按tab对应的长度都是tabstop，是不是转为空格由expandtab决定。
```
#### smarttab
```
如果开启，一行最开始的tab的缩进按照shiftwidth来缩缩进，其他地方用tabstop和softtabstop。
如果关闭，一行中所有的tab的缩进按照softtabstop和tabstop，shiftwith只在左移或者右移代码时用。
```

#### cindent
```
这个标记用来标记缩进，关联的配置项是shiftwidth，所以只要配置这个，一行开头的缩进就是这么多。
如果 shiftwidth != 0，那么就缩进这么多空格，和tabstop和softtabstop无关。
如果 shiftwidth == 0，那么缩进的数量就由tabstop决定，和softtabstop无关，是否展开由expandtab决定
```
cindent 和smarttab并不矛盾，一开始的缩进单位都是shiftwidth，只是cindent会计算低级层，需要几次缩进。

#### 总结
```
所以一般说来，softtabstop一般为0，这样tab输入就是tab，长度有tabstop决定。
对于缩进来说，一般就是2，这样开头缩进是2，所有移动代码也以最小单位2来进行，比较方便。
所以一般设置tapstop=2，shiftwidth=2,或者shiftwidth=0，此时行首的缩进由tapstop决定。
对于写c/cpp代码来说，cindent几乎是必须的，只有smarttab帮助不大。
```
