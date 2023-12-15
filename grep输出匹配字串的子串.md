grep默认使用BRE，并且不支持非贪心匹配（non-greedy match，find the shortest match，*？操作），所以要做到这个，有两个办法：
（1）prep + awk
```
grep -o "processers_num=[0-9]\+"  ceph.conf | awk -F= '{print $NF}'
```
（2）用大P参数（注意，用大P之后，+号前的反斜杠就不需要）：
```
grep -oP "(?<=processers_num=)[0-9]+"  ceph.conf
```
