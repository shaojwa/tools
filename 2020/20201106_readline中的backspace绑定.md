bash中，alt+backspace会往左删除一个语义上的单词，比如会删除路径中的一段，和ctrl-w按空格删除一个单词不同。
但是看bind-p，我们发现按键的写法是\e\C-h，这是什么意思？C-h是按住Ctrl的同时按h，这其实是对应一个特殊字符，叫backspace。
因为backspace的ascii码是0x8，h是字母表的第8个数字，所以ctrl-h对应backspace。所以ctrl-a其实也对应一个特殊字符，其实就是NUL，只是键盘上没有而已。
