```
17:47:16.098
17:47:16.098
17:47:16.101
17:47:16.101
17:47:16.101

         Data Validation error for fsd=fsd1; FSD lba: 0x4afe0000; Key block size: 4096; relative sector in data block: 0x00
         File name: /lwq/95g/vdb.1_2.dir/vdb_f0200.file; file block lba: 0x000c0000; bad sector file lba: 0x000e0000
 0x000   00000000 4afe0000 ........ ........   00000000 4afe0000 00000183 5f70d461
 0x010   25..0000 31647366 20202020 00000000   23880000 31647366 20202020 0003e168
         There are no mismatches in bytes 32-511
```

#### 几个lba
其中lba 0x4afe0000是全局fsd的地逻辑块地址。注意，这里不是块内的地址，快内地址需要tgt通过这个文件名去查看分析。

#### 数据对比
左边是期望的数据，右边是实际的数据

#### 省略号代表什么
