最直接的办法是grep config文件：
```
cat .git/config | grep wsh_branch
```
如果这个branch没有设置upstream，那么是不会搜到的。
