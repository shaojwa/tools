```
clang -S -emit-llvm -c const.cc
```
或者先生成字节码const.bc
```
clang -emit-llvm -o const.bc -c const.cc
```
然后用llvm-dis生成llvm汇编：
```
llvm-dis const.bc
```
