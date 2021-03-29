#### basic commands

Cursor commands
```
ctrl-p    // prev-line
ctrl-n    // next-line
ctrl-a    // begining-of-line
ctrl-e    // end-of-line
ctrl-f    // forward-char
ctrl-b    // backward-char
alt-f
alt-b
```
Scrolling command: Moving text within a window
```
SPACE     // scrol forward
DEL       // scroll backward
```

Node commands
```
t   // goto the top node
u   // goto up level node
p   // previous node in current level
n   // next node in current level
[   // global-prev-node
]   // global-next-node
l   // history node
```

Searching commands
```
ctrl + s  // isearch-forward 
ctrl + r  // isearch-backward
} = ctrl-x n  // search-next
{ = ctrl-x N  // search-previous
```

Xref commands
```
TAB     // Skip to the next hypertext link
RET     // Follow the hypertext link under the cursor
LFD     // select-reference-this-line
```

## others commands
```
Home    // go to the begining of this node
End     // to to the end of this node
ctrl-h  // get-help-window
ctrl-g    // abort-key
```

#### Info intro

- 大部分GNU项目通过info格式发布他们的在线文档。
- 有两个info阅读器，其中一个是独立的程序，只用来阅读info文件。另外一个就是Emacs中的info-package，一个通用编辑器。
- 就目前来说，只有Emacs中的info支持鼠标使用。
- info是一个在线的，菜单驱动（menu-driven）的文档系统。

#### basic concept 
info browse doc based on the concept of **level**, and **nodes** in the same level.
- screen, screen  = some windows, only one active window
- window, window = view area + mode line
- node，是一个文档中的概念，node有不同的层级，就类似于一棵树，node可以展开也可以聚拢。

## terms
-cross reference： 这也是一个文档中的概念，如果要走到另外一个reference，可以用


#### window
```
siwtch window：ctrl-x o
close current window：ctrl-x 0
close other window：ctrl-x 1
```
