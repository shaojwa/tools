20151202

#### 跳转列表跳转

跳转列表中较新的光标位置
```
ctrl+i
```
    
跳转列表中较老的光标位置
```
ctrl+o
```

#### 搜索到的匹配项高亮
```
:set hls
```

####  配色
```
industry
blue
```

## ## 将已经存在的tab转换为空格

在已经打开
```
:set expandtab
```
开关的基础上，执行
```
:retab
````
意思就是重新输入tab

#### modeline

a number of lines at the beginning and end of the file are checked for modelines. 

#### insert 多次

输入10个abc
```
10iabcEsc
```

#### 建议配色
```
slate
darkblue
industry
elflord
ron
```

#### vim 升级后的问题

通过在.vimrc文件的第一行加入syntax enable来解决

#### 复制到行尾用
```
y$
```
   
#### 复制到行头用
```
y^
```

#### 搜索
```
tTfF;, 
```

#### motion  
```
0  
^  
$  
g_  
```   

#### normal mode  
```
u/CTRL-R  
CTRL-N/CTRL-P  
CTRL-I/CTRl-O  
CTRL-]/CTRL-T  
CTRL-G  
#  
*  
g#  
g*  
=  
=%  
gd  
```
#### insert mode  
```
i_CTRL-H  
i_CTRL-W  
i_CTRL-U  
i_CTRL-J  
i_CTRL-I  
i_CTRL-T  
i_CTRL-D  
i_CTRL-N  
i_CTRL-P  
i_CTRL-[  
i_CTRL-C  
i_<Esc>  
```
#### 自动缩进格式化  

VISUAL BLOCK模式下（windows下按ctrl+q） 选中后按等号=可以自动缩进  

#### 块缩进 

VISUAL BLOCK模式下（windows下按ctrl+q）选中后按<或者>  

#### 单行缩进  

正常模式下，缩进光标所在单行可以按两次<(左缩进)或者>（右缩进）  

#### 回到光标上一次位置  

跳转：单引号或者反引号，两个单引号或者两个反引号表示跳转到最近一次跳转之前的位置。

#### 跳转到行  

三种方式:
```
42gg
42G
:42<CR>  
```
    
如果需要同时把指定行移到shell窗口顶部(中部或者底部)则需要在上述命令后添加 zt(z. or zb)  
    
#### 显示特定字符  

可以在vimrc文件中用set list来上显示不可打印字符，set listchar来配置用特殊字符显示不可打印字符，默认是 eol:$

#### 自动重新加载vimrc文件  
```
:source $myvimrc
```

#### 替换

vim中的替换命令为:s, 其中s的取意substitute： 
```
:[range]s/search/replace/[options]  
```

先设options为空则，如果range为空，则替换光标当前行的第一个匹配项，比如则替换8-10行中，每一行的第一个匹配项：
```
:8,10s
```
现在option选择为g，替换每一行中出现的所有匹配项：
```
:s/search/replace/g
```   
替换8-10行中每一行出现的所有匹配项：
```
:8,10s/search/replace/g
```   
更多参见[这里](http://vim.wikia.com/wiki/Search_and_replace)  

#### 匹配  
```
匹配边界可以考虑用: \< 和 \>  
匹配空格用斜杠转义:  \空格  
想用需要括号需要转义: \(\)  
```

#### 删除  
```
d$  //删除光标到行末  
d^  //删除光标到行头  
dgg //删除当前行到第一行的所有行  
dG  //删除当前行到最后一行的所有行  
```
#### 拷贝  
```
y   //拷贝当前行  
ygg //拷贝从当前行到第一行的所有行  
yG  //拷贝从当前行到最后一行的所有行  
y0  //拷贝从光标到行首  
y^  //拷贝从光标到非空行首  
y$  //拷贝从光标到行尾  
yg_ //拷贝从光标到非空行尾  
ye  //拷贝从当前字符到单词结束的所有字符  
yw  //拷贝从当前字符到下一个单词开始  
```   
#### 查看帮助  
```
查看普通模式命令  :help x  
查看可视模式命令  :help v_u  
查看命令行模式命令:help :quit  
找到标签后按CTRL-]进入选项的详细信并可以按CTRL-T或者CTRL-O返回  
进入帮助之后可以用/进行特定内容查找  
```

#### 输入特殊字符  
```
在插入模式下按CTRL-K  
此时会出现一个问号  
然后直接输入表示特殊字符的符号码
```
#### 如何查看某个特殊字符的符号码
```
在命令模式下输入:digraphs就会弹出字符映射表  
然后找到你需要的特殊字符  
其中的前两个符号就是特殊字符的符号码  
中间是特殊字符的样子  
最后是对应的十进制的unicode值  
比如输入向下箭头  
就可以先按CTRL-K然后再输入-v就可以  
```    
#### pattern
```
:%s/^\[^#]/####\1/gc
```

#### 设置 colo default无效

原因是vimrc文件开头需要syntax enable，否则无效，这个和版本有关系，在8.1版本下，必须有这个要求。

#### vim 中insert模式下backspace无效

搜一下看到说是backspace为空导致，正常情况下是backspace=indent,eol,start，表示可以删除indent，eol
  
8.0以后，如果没有user vimrc，才会把backspace设置为indent,eol,start，否则为空。

查看版本为 version 8.1.1777，将 .vimrc文件改名后，backspac而恢复正常。
