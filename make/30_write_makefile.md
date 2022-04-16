1. makefile文件本身就是一个data base。
2. Makefiles包括五类元素: explicit rules, implicit rules, variable definitions, directives, and comments.
3. 指令，A directive is an instruction for make to do something special while reading the makefile.
4. 注释，# in a line of a makefile starts a comment.
5. 物理行和逻辑
6. Makefile使用基于行的语法，也就是说，换行符是特殊的，他表示一条语句的借宿，这个和shell很类似。
7. Makefile对行的长度没有限制，但是换行符却表示语句结束，所以需要用反斜杠来转义换行符来达到对同一条语句换行。
8. backslash/newline这种用法，在recipe中和不再recipe中是不一样的，主要不是在recipe中，这个组个都会被转换为一个空格。
9. .POSIX 是一个特殊的target。
