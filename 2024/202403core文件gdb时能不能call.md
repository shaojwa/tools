如果只是gdb打开core文件，而没有运行的进程，无法用call去执行命令，会显示：
```
You can't do that without a process to debug.
```
而且要注意使用call的时候，后面一定要加小括号，而且用p命令也可以。
```
(gdb) call add()
add
$1 = 1
(gdb) call add()
add
$2 = 2
(gdb) call add
$3 = {int (void)} 0x401182 <add()>
(gdb) p add()
add
$4 = 3
(gdb) p add()
add
$5 = 4
```
