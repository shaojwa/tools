#### 现象

运行一个脚本报错：line 1: #!/bin/bash: No such file or directory

#### 分析

首先运行 which bash 就是这个路径。
自己手写一个测试脚本，发现不会报这个错误。
所以怀疑是编码问题，通过xxd发现问题脚本文件最开始有三个字节 efbbbf。
网上查下发现，EF BB BF 是UTF-8字节序问题。
