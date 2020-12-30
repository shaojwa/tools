```
objdump -lS --start-address=0x16812a --stop-address=0x168200 bin/dcache-dm-test | c++filt
objdump -lS --start-address=0x96dea0 --stop-address=0x96dfa0 libdcache.so  | c++filt
```
1. -l很重要，不然不会有对应的文件行号输出。
1. shift-s，而不是s，shift-s 才会有源代码输出，否者没有源代码。
1. 如果不是代码段那么-S命令无法输出，有且仅有以下提示：bin/dcache-dm-test: file format elf64-x86-64
1. 不用c++filt问题也没什么关系，只是函数符号是编码过的。
