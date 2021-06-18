https://www.gnu.org/software/coreutils/manual/html_node/sort-invocation.html
--numeric-sort 排序
```
sort -k2 lsl.txt # 第9列字符串顺序
sort -nk2 lsl.txt # 第9列数字顺序
sort -nk2, -nk5  lsl.txt # 先按照第二列，然后第五列排序
```
sort中的key最好不好跨列，比如以下的操作常常不是你想要的结果：
```
sort -nk2,5  lsl.txt
```
