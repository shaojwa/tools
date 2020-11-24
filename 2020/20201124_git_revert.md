#### revert merge 的时候需要指定parent-number，怎么查看？
一般说来，merge行第一个就是first parent，第二个就是second parent
```
commit 9cce96729f2a51d166d50fbc5ce18d7f0cd1e55a
Merge: d0957d3 5da1138
```
当然，也可以通过下面的命令确认：
```
git show --stat 9cce9672^1
git show --stat 9cce9672^2
```
或者：
```
git cat-file -p 9cce9672
```
