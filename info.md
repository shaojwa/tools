### info 的大概介绍

1. 大部分GNU项目通过info格式发布他们的在线文档。
1. 有两个info阅读器，其中一个是独立的程序，只用来阅读info文件。另外一个就是Emacs中的info-package，一个通用编辑器。
1. 就目前来说，只有Emacs中的info支持鼠标使用。

#### info 的使用入门的几个概念
可以通过按h键来打开入门文档，如果要查看高级文档，可以按两次n键，直接跳过入门文档。
```
info windows
cross reference
manu item
node
```

#### info常用命令
案件和readline挺像的，emacs风格，首先是查看帮助
```
ctrl-h:get-help-window
```
然后是文档内的光标定位：
```
DEL: scroll backward
SPACE :scrol forward
Home: go to the begining of this node
End: to to the end of this node
TAB: Skip to the next hypertext link
RET: Follow the hypertext link under the cursor
l
[
]
p：当前level的前一个node
n: 当前level的后一个node
t: 当前文档的topnode
```

然后是基本的光标移动，
```
ctrl-a: begining-of-line
ctrl-e: end-of-line
ctrl-b: backward-char
ctrl-f: forward-char
ctrl-p: prev-line // 对应 less 中的 previous-history
ctrl-n: next-line // 对应 less 中的 next-history
ctrl-g: abort-key // 其实less中也有
```
特定的几个键
```
TAB: move-to-next-xref
LFD: select-reference-this-line
RET: select-reference-this-line
ctrl-l: redraw the display
```
来几个搜索
```
ctrl-r: isearch-backward
ctrl-s: isearch-forward
```
