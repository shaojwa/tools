发现gitconfig中在[color]上diff=auto之后就有显示。

## 为什么会显示

因为color中的diff配置的是auto，那样的话，就会对根据core.whitespace的标准来显示这些字符。

## 控制哪些字符配色

这个的配置是core中的whitespace，这个用来标记哪些字符需要注意。默认情况下，很多字符都会要求提示注意。
比如，尾部的空白符要注意（blank-at-eol），默认打开）。
缩进部分中tab前的空格（space-before-tab），默认打开。
缩进部分没有用tab，而是用空格（indent-with-non-tab），默认不打开。
缩进部分没有用空格，而是用tab（tab-in-indent），默认不打开。
文件末尾的空行（blank-at-eof），默认打开。
trailing-space（=blank-at-eol + blank-at-eof），默认打开。
cr-at-eol，把行尾的cr当做行终止符的一部分，不提示，默认不开，所以diff的时候会显示。

## 如何消除
```
git config --global core.whitespace cr-at-eol
```
core.whitespace 的默认配置是 blank-at-eol，也就是说，如果行尾有空格，就会报错。
