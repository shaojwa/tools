bash是一个运行环境，运行环境本身有选项(OPTIONS)，参数(ARGUMENTS)，调用方式(INVOCATION)，运行环境支持自己的语言，所以有定义(DEFINITIONS)，保留字(RESERVED WORDS)，以及语法（GRAMMER），当然还有 EXIT STATUS 以及 BUILTIN COMMANDS 等等。当看到一个用法时，可以先考虑下，这是属于什么部分的内容，比如test，shopt 就是builtin command。 星号的用法属于EXPANSION 大类下的Pathname expansion下小类， bash光大类就有十几个，这是最基本的分配。

#### bash option是否enable的设置

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
