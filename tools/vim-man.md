@20151202  
###### 设置  
//设置字体  
set guifont=courier_new:h12  
//设置窗口显示行数  
set lines=40  
//设置窗口显示列数  
set columns=80  
//设置光标所在行高亮  
set cursorline  
//设置底部状态栏显示信息  
set statusline+=%F  
//自动缩进字符数  
set shiftwidth=4   
//tab键长度  
set tabstop=4  
//空格替换tab  
set expandtab  
//设置显示空白字符  
set list  
set listchars=tab:>-  
//去掉窗口工具栏  
:set guioptions-=T  
//设置tab页  
set guitablabel=%N:%M:%F  

//是否折行显示  
set wrap  
set nowrap 

//配置映射  
  
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
  
###### 操作  
  
//自动缩进格式化    
VISUAL BLOCK模式下（windows下按ctrl+q）    
选中后按=可以自动缩进    
  
//左右缩进块代码  
VISUAL BLOCK模式下（windows下按ctrl+q）  
选中后按<或者>  
  
//单行缩进  
正常模式：  
缩进光标所在单行可以按两次<(左缩进)或者>（右缩进）  
  
//回到光标上一次位置  
`` (反引号) 或者''（引号）  
  
###### 自动重新加载vimrc文件  
:source $myvimrc  
  
###### 替换  
vim中的替换命令为:s  
其中s的取意substitute  
完整语法：  
:[range]s/search/replace/[options]  
先设options为空则   
* 如果range为空，则替换光标当前行的第一个匹配项。  
* :8,10s则替换8-10行中，每一行的提一个匹配项。  
现在option选择为g   
* :s/search/replace/g 替换每一行中出现的所有匹配项。  
* :8,10s/search/replace/g替换8-10行中每一行出现的所有匹配项。  
更多参见[这里](http://vim.wikia.com/wiki/Search_and_replace)  
 
###### 删除  
d$  //删除光标到行末  
d^  //删除光标到行头  
dgg //删除当前行到第一行的所有行  
dG  //删除当前行到最后一行的所有行   

###### 拷贝
y   //拷贝当前行  
ygg //拷贝从当前行到第一行的所有行
yG  //拷贝从当前行到最后一行的所有行  
y0  //拷贝从光标到行首  
y^  //拷贝从光标到非空行首  
y$  //拷贝从光标到行尾  
yg_ //拷贝从光标到非空行尾  
ye  //拷贝从当前字符到单词结束的所有字符  
yw  //拷贝从当前字符到下一个单词开始
