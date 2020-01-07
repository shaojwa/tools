#### 开启16个bc进程进行pi的计算，好像并不会提高mpstat中的%user指标

```
echo "scale=100000;4.0*a(1.0);" | bc -l > /dev/nul &
```
