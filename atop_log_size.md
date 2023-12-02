服务器上每天的atop文件大概是200M，如果采样周期改成1分钟，就会扩大10倍，这个感觉不太行不行。
```
[root@ft2500-node125 atop]$ ll
total 2018384
-rw-r--r-- 1 root root  68039410 Nov 23 00:00 atop_20231122
-rw-r--r-- 1 root root 217232595 Nov 24 00:00 atop_20231123
-rw-r--r-- 1 root root 204729186 Nov 25 00:00 atop_20231124
-rw-r--r-- 1 root root 219991070 Nov 26 00:00 atop_20231125
-rw-r--r-- 1 root root 227901989 Nov 27 00:00 atop_20231126
-rw-r--r-- 1 root root 238907258 Nov 28 00:00 atop_20231127
-rw-r--r-- 1 root root 201329604 Nov 29 00:00 atop_20231128
-rw-r--r-- 1 root root 196180823 Nov 30 00:00 atop_20231129
-rw-r--r-- 1 root root 206687060 Dec  1 00:00 atop_20231130
-rw-r--r-- 1 root root 202882279 Dec  2 00:00 atop_20231201
```
