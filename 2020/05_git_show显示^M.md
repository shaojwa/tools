发现gitconfig中在[color]上diff=auto之后就有显示。

## 为什么会显示

因为 color.diff.whitespace 会显示

## 如何消除
```
git config --global core.whitespace cr-at-eol
```
core.whitespace 的默认配置是 blank-at-eol，也就是说，如果行尾有空格，就会报错。
