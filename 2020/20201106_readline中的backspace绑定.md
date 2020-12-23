bash中，`alt+backspace`会往左删除一个语义上的单词，比如会删除路径中的一段，和`ctrl-w`按空格删除一个单词不同。
但是看`bind-p`，我们发现按键的写法是`\e\C-h`，这是什么意思？

`\C-h`是按住Ctrl的同时按h，这其实是对应一个特殊字符，叫`backspace`。
因为`backspace`的ascii码是0x8，h是字母表的第8个数字，所以`ctrl-h`对应`backspace`。
所以`ctrl-a`其实也对应一个特殊字符，其实就是`NUL`，只是键盘上没有对应的按键而已。
其实`backspace`本身是可以用`ctrl-h`来模拟的，所以bash中，先按alt，然后按ctrl-h，也是能删除语义上的单词的。
但readline中的很多ctrl命令，也许按照ctrl之后的字母去理更好，比如`ctrl-a`中的a表示ahead，`ctrl-e`中的e表示end。
