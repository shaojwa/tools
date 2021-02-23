#### info 简介

1. 大部分GNU项目通过info格式发布他们的在线文档。
1. 有两个info阅读器，其中一个是独立的程序，只用来阅读info文件。另外一个就是Emacs中的info-package，一个通用编辑器。
1. 就目前来说，只有Emacs中的info支持鼠标使用。
2. info是一个在线的，菜单驱动（menu-driven）的文档系统。

#### info 几个概念
info 浏览机制基于目录层级，所以有同一level的不同node的概念。
screen：

window:
用来显示一个node的文本。window有两部分，一个是view area，一个是mode line，这个和大多数的浏览工具是一样的。
info自然也支持一个screen下有多个window。任何时间只有一个是active window。

node：是一个文档中的概念，node有不同的层级，就类似于一棵树，node可以展开也可以聚拢。

cross reference： 这也是一个文档中的概念，如果要走到另外一个reference，可以用

#### info 常用命令

下面是info的基本命令

```
ctrl-h:get-help-window
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

#### windows内的命令
```
ctrl-a: begining-of-line
ctrl-e: end-of-line
ctrl-b: backward-char
ctrl-f: forward-char
ctrl-p: prev-line // 对应 less 中的 previous-history
ctrl-n: next-line // 对应 less 中的 next-history
ctrl-g: abort-key // 其实less中也有
```
reference相关
```
TAB: move-to-next-xref
LFD: select-reference-this-line
RET: select-reference-this-line
```
搜索相关
```
ctrl-r: isearch-backward
ctrl-s: isearch-forward
```
#### window之间
```
切换window：ctrl-x o
关闭当前window：ctrl-x 0
关闭其他window：ctrl-x 1
```
