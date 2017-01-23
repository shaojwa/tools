20151202  
#### motion  
0  
^  
$  
g_  
#### normal mode  
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
#### insert mode  
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
#### 设置  
设置字体  
    set guifont=courier_new:h12  
设置窗口显示行数  
    set lines=40  
设置窗口显示列数  
    set columns=80  
设置光标所在行高亮  
    set cursorline  
设置底部状态栏显示信息  
    set statusline+=%F  
自动缩进字符数  
    set shiftwidth=4  
tab键长度  
    set tabstop=4  
空格替换tab  
    set expandtab  
设置显示空白字符  
    set list  
    set listchars=tab:>-  
去掉窗口工具栏  
    set guioptions-=T  
设置tab页  
    set guitablabel=%N:%M:%F  
是否折行显示  
    set wrap  
    set nowrap  
配置替换字符  
    set listchars=eol:↓,tab:→→,trail:·  
    set list  
设置swap和backup目录  
    set directory=$VIMRUNTIME\..\swap\\  
    set backupdir=$VIMRUNTIME\..\backup\\  
#### 键盘映射  
    map <M-1> 1gt  
    map <M-2> 2gt  
    map <M-3> 3gt  
    map <M-4> 4gt  
    map <M-5> 5gt  
    map <M-6> 6gt  
    map <M-7> 7gt  
    map <M-8> 8gt  
    map <M-9> 9gt  
    map <M-F1> :tabclose<CR>  
    map <M-F2> :tabedit<CR>  
#### 自动缩进格式化  
VISUAL BLOCK模式下（windows下按ctrl+q）  
选中后按=可以自动缩进  
#### 左右缩进块代码  
VISUAL BLOCK模式下（windows下按ctrl+q）  
选中后按<或者>  
#### 单行缩进  
正常模式下  
缩进光标所在单行可以按两次<(左缩进)或者>（右缩进）  
#### 回到光标上一次位置  
反引号  
    ``  
或者引号  
    ''  
#### 跳转到行  
三种方式:  
    42gg  
    42G  
    :42<CR>  
如果需要同时把指定行移到shell窗口顶部(中部或者底部)则需要在上述命令后添加  
    zt(z. or zb)  
#### 显示特定字符  
可以在vimrc文件中用set listchar来配置用特殊字符显示不可见字符  
比如想用$先显示一行的末尾可以配置 set listchars=eol:$  
然后在命令模式下运行:set list 就可以看到  
可以用:set nolist取消显示  
对于部分特定字符  
#### 自动重新加载vimrc文件  
    :source $myvimrc  
#### 替换  
    vim中的替换命令为:s  
其中s的取意substitute  
完整语法：  
    :[range]s/search/replace/[options]  
先设options为空则  
* 如果range为空，则替换光标当前行的第一个匹配项。  
* :8,10s 则替换8-10行中，每一行的提一个匹配项。  
现在option选择为g  
* :s/search/replace/g 替换每一行中出现的所有匹配项。  
* :8,10s/search/replace/g替换8-10行中每一行出现的所有匹配项。  
更多参见[这里](http://vim.wikia.com/wiki/Search_and_replace)  
#### 匹配  
匹配边界可以考虑用:  
    \< 和 \>  
匹配空格用斜杠转义:  
    \空格  
想用需要括号需要转义:  
    \(\)  
#### 删除  
    d$  //删除光标到行末  
    d^  //删除光标到行头  
    dgg //删除当前行到第一行的所有行  
    dG  //删除当前行到最后一行的所有行  
#### 拷贝  
    y   //拷贝当前行  
    ygg //拷贝从当前行到第一行的所有行  
    yG  //拷贝从当前行到最后一行的所有行  
    y0  //拷贝从光标到行首  
    y^  //拷贝从光标到非空行首  
    y$  //拷贝从光标到行尾  
    yg_ //拷贝从光标到非空行尾  
    ye  //拷贝从当前字符到单词结束的所有字符  
    yw  //拷贝从当前字符到下一个单词开始  
#### 查看帮助  
查看普通模式命令    无前缀  
    :help x  
查看可视模式命令    v_  
    :help v_u  
查看命令行模式命令  :  
    :help :quit  
找到标签后按CTRL-]进入选项的详细信并可以按CTRL-T或者CTRL-O返回  
进入帮助之后可以用/进行特定内容查找  
##### 输入特殊字符  
在插入模式下按CTRL-K  
此时会出现一个问号  
然后直接输入表示特殊字符的符号码  
如何查看某个特殊字符的符号码？  
在命令模式下输入:digraphs就会弹出字符映射表  
然后找到你需要的特殊字符  
其中的前两个符号就是特殊字符的符号码  
中间是特殊字符的样子  
最后是对应的十进制的unicode值  
比如输入向下箭头  
就可以先按CTRL-K然后再输入-v就可以  
