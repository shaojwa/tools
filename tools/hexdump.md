#### 最常见用法，一行显示16 字节，每个字节用16进制显示，但是这个是两个字节一组
```
sudo hexdump -x -s 249159680 -n 32 /dev/mapper/mpathfp
```

#### 如果你想还想显示字符，那就用-C参数
```
sudo hexdump -C -s 249159680 -n 32 /dev/mapper/mpathfp
```

#### 如果都不满意，是可以自己定义格式的：
format string 可以包含人一个格式单元，空格分割。每个格式单元分成三部分：iteration_count, bytes_count, format。
```
iteration_count： 迭代次数
bytes_count：每次迭代解析的字节数
format：
```
比如:
```
hexdump -e '"0x%8.8_ax " 4/4 "%08x " "\n"'   -n 32 /dev/mapper/mpathfp
// 第一个8，表示预留宽度
// 第二个8，表示显示宽度
// _a，表示显示地址
// x，表示以16进制显示地址
// 4/4 表示显示4次，每次以4字节
// %08x，每次显示的宽度
// "\n"，最后换行一下
```
还可以：
```
hexdump -e '"0x%8.8_ax " 16/1 "%02x " "\n"' -n 1k /dev/mapper/mpathfp
hexdump -e '"0x%8.8_ax " 8/2 "%04x " "\n"' -n 1k /dev/mapper/mpathfp
hexdump -e '"0x%8.8_ax " 4/4 "%08x " "\n"' -n 1k /dev/mapper/mpathfp
```

