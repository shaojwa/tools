#### 显示完整符号用-W 
```
[root@host50 erasure-code]# readelf -sW libec_jerasure.so | c++filt| grep erasure_code_version
   361: 0000000000033cc0     8 FUNC    GLOBAL DEFAULT   13 __erasure_code_version
```
