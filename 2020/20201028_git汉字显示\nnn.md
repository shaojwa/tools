git status 的时候显示：
```
modified:   "\345\277\253\347\205\247\347\232\204\350\256\276\350\256\241.md"
```
so上说，git一致都是用的八进制uft8显示：https://github.com/msysgit/msysgit/wiki/Git-for-Windows-Unicode-Support

> Disable quoted file names
> By default, git will print non-ASCII file names in quoted octal notation, i.e. "\nnn\nnn...". This can be disabled with
>     git config [--global] core.quotepath off

所以，也就知道怎么解决。
