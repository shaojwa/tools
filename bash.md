#### unset
```
$ i=1
$ echo $i
1
$ unset i
$ echo $i

$
```

#### expr
do NOT use expr any more in bash 
```
echo "lun$j+`expr \( $i + 1 \) \* 256`"
```

#### bash

bash是一个运行环境，运行环境本身有选项(OPTIONS)，参数(ARGUMENTS)，调用方式(INVOCATION)，运行环境支持自己的语言，所以有定义(DEFINITIONS)，保留字(RESERVED WORDS)，以及语法（GRAMMER），当然还有 EXIT STATUS 以及 BUILTIN COMMANDS 等等。

当看到一个用法时，可以先考虑下这是属于什么部分的内容，比如test，shopt 就是BUILTIN COMMANDS。 星号的用法属于EXPANSION 大类下的pathname expansion下小类， bash光大类就有十几个，这是最基本的分配。

## 重定向

在命令被执行前，它的输出输出就被重定向。重定向按照它们出现的顺序，从左到右处理。两大类：输入和输出，输出再细分两类：标准输出和标准错误, 统一格式是: \[n\]{oper}{word}。<和>都是oper，n被忽略时，如果oper是<，那么n=0，如果oper是>, 那么n=1。

其实stdin 和stdout 和 stderr 有这两个oper就足够，如果同时对stdout和stderr重定向，那么bash多来一点花样，我觉得不是必须的。因为如果都需要重定向到同一个文件，那么大不了>word 2>word 一起用，和 &>word 可能没什么区别， &>使命令简化而已，但也许有别的考虑。其实我个人觉得&的真正价值是在stderr和stdout之间相互重定向用的，因为直接用1>2或者2>1时，oper后的1或2会被当做文件名。

其实&>的真正语法叫 文件描述符复制（Duplicating File Descriptors），和重定向没有直接关联，可以查看man帮助。

如果是重定向标准输入和输出到文件 ，最好简单的办法就是 &> word, 等价于 >word 2>&1。

## bash option是否enable的设置

-o  optname

#### shopt 中option是否开启的测试

shopt option不是option，所以测试方式是用shopt -q ，并通过 return status来反应是否设置，如果已经设置，那么return status为0。
return status 就是 EXIT STATUS。测试方式是：

    if shopt -q dotglob; then echo yes; fi

#### 字串比较

以前很多bash中都通过一个填充字符来进行字串比较，比如：

    if [ "x$var" = "xyes" ]; then do_something; fi
    
其中的x就是一个filler character，但是现在不需要。现在bash对处理空字串已经非常智能。

所以尽量用引号，以及用-z -n等运算符来进行空串判断。

### bash 中如果没有定义 也可以在比较
参考：

    https://google.github.io/styleguide/shell.xml
    https://tiswww.case.edu/php/chet/bash/FAQ

    bash中如果一个变量没有定义，也可以在 [[ ]] 中进行比较。
    if [[ $1 != "" ]]; then cd $1; done

man bash 可以看到这个是复合命令Compound Commands， 注意这是命令，所以后面需要分号。
返回状态为0或者是1，根据里面的条件表达式，conditional expression，注意是表达式。

`[[...]]` 可以降低错误，以为该命令不会执行path expansion以及 word splitting，且允许正则表达式匹配。 `[...]` 是不允许正则的。

#### 什么是 pathname expansion

bash会扫描一个word，如果这个word中有星号，问号，左方括号，那么bash就会把这个workd当做一个pattern，并把这个word用满足这个字串的当前目录的文件名代替。这就是pathname expantsion。比如我们常用的星号。细节比较复杂，可以看man中对应的章节。

#### 什么是 word splitting

#### bash 命令输入几个技巧

    !!	最后一条命令
    !n	第n条命令
    !-n	倒数第n条命令
    !string	以string开始的最近一条命令
    !^	第一个参数
    !$	最后一个参数
    !*	除第一个命令之外的所有参数
    ^s1^s2	将上一条命令中的s1切换为s2
    !!:n-m	上一条命令的n-m个参数。
    
    history expansion: ^ $ * - %
    parameter expansion
    BRE: . * ^ $ [] \
    ERE: + ? | {} () 
    touch file{1..100}
    set –x
    set -e/-o pipefail
    trap
    ${name:?error_message}
    
## Substring Expansion
```
 ${1::-3} # 头开头到倒数第三个
 ${1:-3}  # 从倒数第三个到结尾
```

##  Parameter Expansion
bash中用来取不带扩展名的文件名和文件的扩展名
```
${parameter#word}
${parameter##word}
${parameter#%word}
${parameter%%word}
```
