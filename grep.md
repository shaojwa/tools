###### 文件内容查找  
grep <options> <pattern> <files>  
示例  

    grep -rn "loosgood"  * 
    *  表示当前目录所有文件，也可以是某个文件名
    -r 是递归查找
    -n 是显示行号
    -R 查找所有文件包含子目录
    -i 忽略大小写
    -l 只列出匹配的文件名
    -L 列出不匹配的文件名， 
    -w 只匹配整个单词，而不是字符串的一部分

###### 查找man文档中以连字符开始的选项

    $ man chmod | grep [-]R
        -R, --recursive
 
加上-n显示行号  
    
    $ man chmod | grep [-]R
    111:  -R, --recursive

然后用more显示从某行开始
    
    $ man chmod | more +111

