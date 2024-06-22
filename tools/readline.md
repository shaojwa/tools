```
alt+backspace // 往左删除一个语义上的单词(以斜杠为分隔符)
```

## word 和 unix-word
word一般就是单词，不包括slash，如果是包含slash的，以空格作为分隔的，就得用unix-word。
比如 ctrl-w就会往前删除到前一个空格为止，而不是停在下划线。

##  backward 就是往左
一般没有这个前缀的kill，delete都是往右删除，右边是光标的forward，所以默认没有forward这个前缀。


#### readline 相关快捷键
```
ctrl-a // 光标跳转到行头
ctrl-e // 光标跳转到行尾
ctrl-u // 光标删除到行头
ctrl-k // 光标删除到行尾

alt-b esc-b // 往后移动一个词
alt-f esc-f // 往前移动一个词
ctrl-w // 往左删一个词
alt-d  // 往右删一个词 (= esc-d)

ctrl-b // 往后移动一个字符
ctrl-f // 往前移动一个字符
ctrl-h // 往后删一个字符
ctrl-d // 往前删一个字符

ctrl-x ctrl-u // undo 回退
ctrl-_ // 回退
ctrl-y // 粘贴前一次通过ctrl-w或alt-d删除的词
ctrl-t // 互换两个字符 (transpose char)
esc-t  // 互换两个词 (transpose word)
ctrl-l // 清屏
ctrl-j
ctrl-g
!!:/s/--old_option/--new_option/
ctrl-v ctrl-j 多行编辑
```   

#### 替换多次 
```
twice:
^string1^string2^:&
all:
!!:gs/string1/string2
^string1^string2^:g&
```
