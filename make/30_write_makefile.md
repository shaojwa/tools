1. makefile文件本身就是一个data base。
2. Makefiles包括五类元素。
3. 指令，一般使用来完成特殊工作的。
4. 注释。
5. 物理行和逻辑。
6. Makefile使用基于行的语法，也就是说，换行符是特殊的，他表示一条语句的借宿，这个和shell很类似。
7. Makefile对行的长度没有限制，但是换行符却表示语句结束，所以需要用反斜杠来转义换行符来达到对同一条语句换行。
8. backslash/newline这种用法，在recipe中和不再recipe中是不一样的，主要不是在recipe中，这个组个都会被转换为一个空格。
9. 如果换行但是不想添加功课，有一个技巧的。
10. .POSIX 是一个特殊的target。
11. 建议使用makefile，或者Makefile更好。
12. 用include指令去包含其他的makefile文件。文件名列表可以使用shell的文件扩展。
13. include前可以有空格，但是不能是Tab，因为如果是tab，这一行会被当作recipe。
14. 模式规则(pattern rules是什么)
15. make会检测makefile的更新，怎么检测？
16. MAKE_RESTARTS。
17. Double-Colon.
