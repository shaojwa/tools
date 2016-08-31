by shaojwa
@20151014

#### 文档顺序
基础 架构 调试  

#### 头文件中包含其他头文件的顺序
（1）包含当前工程中所需要的自定义头文件（顺序自定）  
（2）包含第三方程序库的头文件  
（3）包含标准头文件  

#### 源文件中包含头文件的顺序
（1）包含该源文件对应的头文件（如果存在）  
（2）包含当前工程中所需要的自定义头文件（顺序自定）  
（3）包含第三方程序库的头文件  
（4）包含标准头文件  

#### Windows下包含关系头文件问题
用到socket相关功能时，包含ws2tcpip.h。
如果这个头文件在windows.h之后包含就会有很多宏重定义。  
这种情况下需要把ws2tcpip.h放在windows.h之前来解决。  

#### 头文件要求
使用内部包含守哨，且要求下划线开始，下划线结束，且和头文件名一致。

    #ifndef _common_h_
    #define _common_h_
	...
    #endif

#### 错误码
Windows中常用的错误码获取接口:
（1）常用api采用getlasterror()接口获取。  
（2）注册表操作接口常为函数的返回值。  
（3）socket操作函数的返回值可用wsagetlasterror()或者getlasterror()。
（4）clib库函数接口通常用errno（出错时通常和函数返回值为同一个值）。

#### 函数返回值类型
自定义函数必须要求有返回值，自定义函数的返回值一般不会和系统接口关联，所以建议使用通用的数据类型，比如int，unsigned int等，尽量不要使用dword等平台相关的数据类型。自定义接口一般都需要返回值，出极少部分不需要返回值的接口需要讨论确定后在文档中说明。

#### 返回值不能透传
windows/linux系统函数返回值、平台返回值（如果存在）、tac返回值、层与层之间返回值不应该透传。即平台返回值以及应用软件返回值应该有独立的定义，在多层调用时，直接透传返回值会因为返回值意义不同造成功能缺陷。

#### 返回值的定义
返回值应该严格定义，返回值应该表示的是本地运行错误。项目自定义的错误码分两类（1）通用错误码（2）模块错误码。通用错误码一般定义在统一的errorcode头文件中。一般是windows api 返回值的简化以及和软件配置或者特性相冲突的错误。比如打开文件异常，windows api有很多错误原因，而项目组可以简单定义一种通用错误为“打开文件错误“而不细究具体是什么原因导致（如果细究就是和windows api一个层次）。比如tac只能运行一个实例。为了表示第二个进程实例启动时触发的错误，即可定义一个“不允许多进程实例运行”的通用错误。又或者网络数据包长度超过我们对某个字段的长度限制，可以定义一种通用错误为“网络数据长度异常”错误。模块错误码和模块关联比较密切。是和某个具体功能点相关联的错误，而之前提到的网络数据异常，打开文件错误是相对比较底层的，各个上层功能点都会用到的公共性的错误。这一点需要区别。比如要禁用guest账户，但是因为本地策略导致禁用失败。则可以定义一个模块特定错误为“guest账户禁用失败错误“。模块特定错误一般定义在模块头文件中，供其他模块引用。


#### 目代码中数据类型的选择
编写的代码应该选用通用的数据类型，比如int，unsigned int，即使编写windows代码，项目代码也尽量不要用 dword代替unsigned int，出去平台api的的返回值变量，应该一律使用通用的数据类型。
使用尽可能准确的数据类型
类似time()函数的返回值类型time_t, size_t等，对size_t来说，32位系统和64位系统上宽度不一致，所以打印时需要用%zu，%zx，%zd。


#### 初始化时机
有意见认为应该在定义时初始化。而另外一种意见认为变量的初始化应该采用就近原则，即在使用时初始化。原因有两点：
其中一个原因是：减少无谓的赋值（包括memset）操作。某个变量可能只在特定的分支流程才用到（可能只有某些特殊情况才会运行到这里），在函数入口赋值时，会使所有流程均要执行该赋值操作，影响程序效率，而有些情况下，函数接口的memset操作会成为一些性能瓶颈。另一个原因是：避免循环中标志变量遗漏初始化或多层循环中遗漏内层循环变量初始化的情况。
这里建议比较折中（1）局部指针要求在定义的时候初始化（2）简单变量建议定义时初始化，再次使用时应该注意是否需要重新赋值。（3）数组等空间较大结构可以不在定义之后立即初始化，可以在使用前或者使用的过程中显示设定，类似字串结束等标记，对不附加结束符的api来说，显示设定更有必要。

#### 句柄初始化
用invalid_handle_value初始化句柄（不是null）。
结构体初始化
结构体可使用`{0}`或者`memset()`。注意几点：（1）类实例初始化不建议用memset()。因为类实例用memset初始化可能会引入问题。类的实例有时候会有指针指向虚函数表（vtbl），用于运行时虚函数调用，所以一旦被初始化便会导致程序异常。所以，类实例用构造函数完成初始化，而不是memset()。(2)局部变量最好在函数起始处定义并初始化。
说明：可能因为代码流程导致局部变量被跳过初始化而后面直接使用，导致运行过程中debug版本assert弹框告警。（出现过socket变量初始化流程被跳过而在该变量与invalid_socket比较时出现assert弹框异常）

#### 字符串处理
#### 明确长度
在定义字串数组长度时，应该明确是字符个数还是字节个数，比如在定义用户名和密码长度时，应该明确使用字符个数。而在定义网络数据包缓冲区大小时，定义字节个数。
字符串字符集转换
在windows下采用widechartomultibyte 以及multibytetowidechar字串格式转换。转换时必须明确多字节字符的转换类型（通常都为cp_utf8）

#### 字串拷贝
任何字串的拷贝都应该明确该拷贝是否允许截断，在绝大多数场景下截断处理不能被接受。此时必须对源字串长度和目标缓存长度进行比较，并作异常处理（至少应该打印错误信息）。在正常分支中进行字串拷贝。

#### 代码流程
防止嵌套过深, 如果if-else嵌套过多，且if和else部分逻辑处理量相差较大，可以优先处理特殊情况（逻辑处理量较少的先处理）后退出函数。随后跟进逻辑处理量较多的代码，这样可以使得代码扁平化，防止嵌套太多。


#### 日志语言
日志要求用英文，如果找不到合适的单词，可以直接用函数名，变量名来标记。
#### 日志分级
fatal：表示需要立即被处理的系统级错误。当该错误发生时，表示服务已经出现了某种程度的不可用，系统管理员需要立即介入。这属于最严重的日志级别，因此该日志级别必须慎用，如果这种级别的日志经常出现，则该日志也失去了意义。通常情况下，一个进程的生命周期中应该只记录一次fatal级别的日志，即该进程遇到无法恢复的错误而退出时。当然，如果某个系统的子系统遇到了不可恢复的错误，那该子系统的调用方也可以记入fatal级别日志，以便通过日志报警提醒系统管理员修复；
error： 该级别的错误也需要马上被处理，但是紧急程度要低于fatal级别。当error错误发生时，已经影响了用户的正常访问。从该意义上来说，实际上error错误和fatal错误对用户的影响是相当的。fatal相当于服务已经挂了，而error表示然而活着却无法提供正常的服务，只能不断地打印error日志。特别需要注意的是，error和fatal都属于服务器自己的异常，是需要马上得到人工介入并处理的。而对于用户自己操作不当，如请求参数错误等等，是绝对不应该记为error日志的；
warn：该日志表示系统可能出现问题，也可能没有，这种情况如网络的波动等。对于那些目前还不是错误，然而不及时处理也会变为错误的情况，也可以记为warn日志，例如一个存储系统的磁盘使用量超过阀值，或者系统中某个用户的存储配额快用完等等。对于warn级别的日志，虽然不需要系统管理员马上处理，也是需要即使查看并处理的。因此此种级别的日志也不应太多，能不打warn级别的日志，就尽量不要打；
info：该种日志记录系统的正常运行状态，例如某个子系统的初始化，某个请求的成功执行等等。通过查看info级别的日志，可以很快地对系统中出现的warn,error,fatal错误进行定位。info日志不宜过多，通常情况下，info级别的日志应该不大于trace日志的10%；
debug：这两种日志具体的规范应该由项目组自己定义，该级别日志的主要作用是对系统每一步的运行状态进行精确的记录。通过该种日志，可以查看某一个操作每一步的执行过程，可以准确定位是何种操作，何种参数，何种顺序导致了某种错误的发生。可以保证在不重现错误的情况下，也可以通过debug（或trace）级别的日志对问题进行诊断。需要注意的是，debug日志也需要规范日志格式，应该保证除了记录日志的开发人员自己外，其他的如运维，测试人员等也可以通过debug（或trace）日志来定位问题；
日志格式
{timestamp} {error_level } {error_type（error_code）:}{msg}
timestamp：时间戳，中括号分隔，例如 [2015-06-17 08:59:10]
error_level：严重等级，中括号分隔，枚举 [fatal|error|warn|info|debug]
error_type：错误类型，无中括号分隔，当前两种：win_error和tac_error，可选
error_code：错误码，十六进制显示，0x开头，无宽度要求。
msg：错误信息，尽量避免显示函数名或者变量名。需要答应的值用逗号(,)隔开。最后一个打印值没有标点，如果是语句以点号结尾(.)。
[2015-06-17 08:59:10][debug] user count = 1， group count = 2
[2015-06-17 08:59:20][error]win_error(0x2)： config file not found.
bool/bool逻辑运算。
类型变量不建议和ture/false比较，类似，bool类型变量也不建议和true/false直接比较。if (b_secauth_pass == true）应为：if（b_secauth_pass）函数命名。
命名
goto标签命名
全部小写，下划线连接格式，如label_out, label_ret, label_err等；
函数命名
c代码中的函数命名建议按照<module>_<action>的格式命名，模块名建议为简短的一个单词，或缩写组合，不建议有下划线分割，比如用portal替换access_portal。<action>部分建议以动词开始，且要用最能代表函数功能的动词。比如如果是重置登入信息的接口，不建议用portal_login_reset（），应该使用portal_reset_login（），甚至只用portal_reset。 在cpp代码中，portal这一模块名可以在类名中体现，直接用<action>开始，比如portal::reset（）。不建议在函数中加入过的信息，比如：
portal::login_failed_reset（）；reset就是重置，和登入失败没有直接关联。这个函数什么功能就描述什么，不用加入类似函数被调用的原因，条件，或者环境信息。
函数命名中，采用linux风格，单建议单个函数中分隔用的下划线不要过多，建议不超过3个。
变量命名
变量的命名在cpp中比较突出，成员变量建议以m_开头，涉及控件相关的，建议控件类型放在前面，比如取消按钮，为m_btn_cancel。控件类型建议采用简写，能缩短变量长度，比如标签用lbl等，那些控件名较长可以组内讨论再确定。
宏命名
宏定义是命名中比较重要的一块，建议命名时能尽量一眼看出宏所属的模块以及定义的功能点。通常有如下几点可以参考：
可以分为2类宏：固定前缀宏（错误码，消息码，以及文本宏）和非固定前缀宏。（1）错误码，用于定义产品可能出现的错误。命名通常为<产品名>_errcode_<错误类型>，比如tac_errcode_username_invalid。（2）消息码，格式类似错误码，如tac_msgcode_login_start（3）文本宏，建议以txt开头，标识该宏对应一个文本字串。形如txt_<大模块>_<子模块>_<标识>，例子：txt_secpol_av_need_check _t(“不要求检测杀毒软件”)。
另一类宏定义不固定前缀，根据宏对应的功能命名。如两个模块之间进行的消息传递，除定义消息的类别，以及对应的模块功能外，还可以标记消息传递的方向。例如tac项目中server和ui之间需要信息交互，根据大类可以分为 auth（认证），seccheck（安全监测）等，认证模块中的用户信息相关操作就可以定义为ot_auth_user_get_username_s2u。ot代表这一类宏是操作类型宏（ot=operationtype）。又比如项目通常用tlv结构发送存储数据，type的宏定义，就可以以dt为前缀（dt=datatype），格式可以dt_<模块>_<数据名>，比如dt_auth_username, dt_auth_pwd。以上仅作参考，不一定很合理。

2接口使用
文件系统
路径相关操作
使用pathappend()函数完成路径拼接。通过使用shgetfolderpath等系列函数获取。通过pathfileexists判断文件或者目录路径是否存在。
文件目录操作
通过removedirectory删除已经存在的空目录，如果目录非空可以使用shfileoperation进行递归的删除。
shfileopstruct fileop; 

        zeromemory((void*)&fileop, sizeof(shfileopstruct));
        fileop.fflags = fof_noconfirmation | fof_noerrorui | fof_silent; 
        fileop.hnamemappings = null; 
        fileop.hwnd = null; 
        fileop.lpszprogresstitle = null; 
        fileop.pfrom = szdir; 
        fileop.pto = null; 
        fileop.wfunc = fo_delete;
        int err = shfileoperation(&fileop);
		
线程进程操作
线程的创建
使用_beginthreadex()创建线程，不能使用createthread()或者_beginthread()创建线程。
线程退出
线程自然返回，不使用 _endthread，_endthreadex，exitthread，terminatethread退出线程。
线程存活判断
使用getexitcodethread()检查返回参数lpexitcode是否为still_active。不能以用户态句柄是否为invalid_handle_value来判断。
网络
判断是否有可用网卡
可以调用getadaptersinfo()判断返回值是否为error_no_data

3接口隐患
文件系统接口
getmodulefilename（）的返回值
该接口调用时注意两点（1）返回值大于0有可能存在截断的情况。如果入参数组大小不够，那么返回的文件路径将截断，这是一个隐患（2）如果被截断，目标系统不懂，返回值不一样，如果是xp系统，截断之后last error code 还是error_success，如果是nt6以上系统，last error code 为error_insufficient_buffer。
4架构设计
消息处理
应用程序中的消息多数为通知消息，应该用postmessage发到主消息循环，由消息循环响应。很多实现中用sendmessage先发往主窗口消息处理过程，由主窗口来处理，类似这样的设计不合理。

5调试相关
vs中查看错误码以及对应解释
在vs的watch窗口中，name列添加“$err,hr“来查看上一个错误码以及对应的解释。
6系统运维
查询某个进程的父进程
wmic process  get  processid, parentprocessid | findstr <pid>
wmic process where (processid=<pid>) get parentprocessid
7实际案例
文件系统
正在io时发生系统断电或者强制重启
在一些极端测试情况下，进程正在io操作时触发断电或者系统强制重启。此时因为系统缓存可能会把部分数据丢弃，没有及时写入到磁盘中。在linux下，可以通过sync/fsync等系统调用实现。windows下通过库函数_commit()实现。
网络编程
多线程对同一个socket进行同类型操作
多个线程对同一个socket进行send操作在极端情况下会引发缓冲器数据重叠。就算send操作是线程安全的，但并不能保证是原子操作，所以多线程往一个socket发送数据时，务必进行同步。
ui编程
shell_notifyicon使用问题
用shell_notifyicon函数通知explorer替换托盘图标的过程中，第二个参数lpdata指向的结构notifyicondata中的uid为之前的图标对应的uid,两者必须一致，否则无法替换。


#### dll 导入导出
在windows下使用
__declspec(dllexport)，可以用在类名上，也可以用在类的某个方法上。比如：

	#define DllExport __declspec( dllexport )
	class DllExport Log
	{	
	}
	
	
***
v0.1
@pwns
***
# index
tools  
sevices  
cmdlines  
porotls  
others  
***
# tools
***
## vim
### 设置
设置字体  

    set guifont=courier_new:h12

设置窗口显示行数  

    set lines=40

设置窗口显示列数  

    set columns=80

设置光标所在行高亮  

    set cursorline

设置底部状态栏显示信息  

    set statusline+=%f
    
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

    set guioptions-=t

设置tab页  

    set guitablabel=%n:%m:%f
    
是否折行显示  

    set wrap
    set nowrap
    
配置替换字符

    set listchars=eol:↓,tab:→→,trail:·
    set list

配置映射  

    map <m-1> 1gt
    map <m-2> 2gt
    map <m-3> 3gt
    map <m-4> 4gt
    map <m-5> 5gt
    map <m-6> 6gt
    map <m-7> 7gt
    map <m-8> 8gt
    map <m-9> 9gt
    map <m-f1> :tabclose<cr>
    map <m-f2> :tabedit<cr>

### 自动缩进格式化  
visual block模式下（windows下按ctrl+q）  
选中后按=可以自动缩进  

### 左右缩进块代码  
visual block模式下（windows下按ctrl+q）  
选中后按<或者>  

### 单行缩进  
正常模式下  
缩进光标所在单行可以按两次<(左缩进)或者>（右缩进）  

### 回到光标上一次位置  

反引号

    ``
或者引号

    ''

### 显示特定字符
可以在vimrc文件中用set listchar来配置用特殊字符显示不可见字符  
比如想用$先显示一行的末尾可以配置 set listchars=eol:$  
然后在命令模式下运行:set list 就可以看到  
可以用:set nolist取消显示  
对于部分特定字符  

### 自动重新加载vimrc文件

    :source $myvimrc

### 替换

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
更多参见[这里](http://vim.wikia.com/wiki/search_and_replace)  

### 匹配
匹配边界可以考虑用:  

    \< 和 \>  

匹配空格用斜杠转义:  

    \空格  

想用需要括号需要转义:

    \(\)

### 删除

    d$  //删除光标到行末
    d^  //删除光标到行头
    dgg //删除当前行到第一行的所有行
    dg  //删除当前行到最后一行的所有行

### 拷贝

    y   //拷贝当前行
    ygg //拷贝从当前行到第一行的所有行
    yg  //拷贝从当前行到最后一行的所有行
    y0  //拷贝从光标到行首
    y^  //拷贝从光标到非空行首
    y$  //拷贝从光标到行尾
    yg_ //拷贝从光标到非空行尾
    ye  //拷贝从当前字符到单词结束的所有字符
    yw  //拷贝从当前字符到下一个单词开始

### 查看帮助

查看普通模式命令    无前缀  

    :help x
    
查看可视模式命令    v_  

    :help v_u
    
查看命令行模式命令  :  

    :help :quit

找到标签后按ctrl-]进入选项的详细信并可以按ctrl-t或者ctrl-o返回  
进入帮助之后可以用/进行特定内容查找  

##### 输入特殊字符
在插入模式下按ctrl-k  
此时会出现一个问号  
然后直接输入表示特殊字符的符号码  
如何查看某个特殊字符的符号码？  
在命令模式下输入:digraphs就会弹出字符映射表  
然后找到你需要的特殊字符  
其中的前两个符号就是特殊字符的符号码  
中间是特殊字符的样子  
最后是对应的十进制的unicode值  
比如输入向下箭头  
就可以先按ctrl-k然后再输入-v就可以  

***
## git
v0.1@ 20131219  
v0.2@ 20141125  
v0.3@201151127  

### 创建项目仓库
方法1：创建崭新的git项目仓库  

    git init

方法2：克隆某个仓库自动初始化  

    git clone

### 查看状态

    git status

status = tracked + untracked  
tracked = work + index + history + remote  

#### 查看日志

    git log
    git log -p
    git log -2

### 查看本地clone的代码库

    git remote
    git remote -v

### 查看本地clone版本origin库的所有分支

    git remote show origin

### diff
work和index之间  

    git diff

work和history之间  

    git diff head

work和remote之间  

    git diff head~

index和history之间  

    git diff --cached
    git diff --staged

index和remote之间  

    git diff --cached head~


### 提交修改
从untracked到tracked  

    git add

从work到index  

    git add
    git add .
    git add -u .
    git add -p <file>

从index到history  

    git commit -m <some message>

从index到history  

    git commit -a -m <some message>  

从history到remote  

    git push  https://github.com/shaojwa/leetcode.git master

### 回退
从tracked到untracked  

    git rm --cached <file>

从index到work  

    git checkout --files

从history到index  

    git reset --files

### 更新
从remote更新到本地history  

    git remote update

### 远程添加新的分支

    git remote add doc https://github.com/shaojwa/doc.git

### 其他

    git commit -m "`date`"
***
## wireshark
### http方法过滤

    http.request.method == "post"

注意点1加引号2大写post  

### host过滤
***
## office

### 电子表格单元格内换行

openoffice:

    ctrl+enter

msoffice:

    alt+enter

# services
***
##  ftp
@20151203  

### 主动模式
主动就是传输数据时  
客户端开启某端口并port命令告诉服务器  
服务器连接客户端  

### 被动模式
被动就是传输数据时  
服务器开启某端口并通过pasv命令通知客户端  
客户端连接服务器  

### 配置文件

    /usr/sbin/vsftpd            vsftpd的主程序
    /etc/vsftpd/vsftpd.conf     主配置文件
    /etc/vsftpd.ftpusers        禁止使用vsftpd的用户列表文件
    /etc/vsftpd.user_list       禁止或允许使用vsftpd的用户列表文件
    /var/ftp                    匿名用户主目录
    /var/ftp/pub                匿名用户的下载目录

### 参数含义
是否允许匿名访问

    anonymous_enable=yes

是否允许本地用户登入  

    local_enable=yes
    
允许任何形式的写操作  

    write_enable=yes

umask屏蔽权限022表示所有者群组和其他用户不能写  

    local_umask=022
    
是否允许匿名用户上传文件  

    #anon_upload_enable=yes

是否允许你您不过用户创建文件  

    #anon_mkdir_write_enable=yes

是否在进入目录是显示欢迎信息  

    dirmessage_enable=yes

上传下载文件时记录日志  

    xferlog_enable=yes

是否使用20端口传输数据即是否采用主动模式  

    connect_from_port_20=yes

是否允许匿名上传的文件改变其所有者  

    #chown_uploads=yes
    #chown_username=whoever

设置日志文件路  

    #xferlog_file=/var/log/xferlog

是否采用标准的日志文件格式  

    xferlog_std_formats=yes

空闲会话超时时间  

    #idle_session_timeout=600
    
数据链接超时时间  

    #date_connection_timeout=120

是否采用非特权用户  

    #nopriv_user=ftpsecure

是否识别匿名用户的abor请求  
不建议开启但不开启可能使老的ftp客户端混乱  

    #async_abor_enable=yes

ascii模式下的上传和下载  

    #ascii_upload_enable=yes
    #ascii_download_enable=yes

欢迎提示语句  

    #ftpd_banner=welcome to blah ftp service

拒绝登入邮件列表  

    #deny_email_enables=yes
    #banned_email_file=/etc/vsftpd/banned_emails

chroot用户使能  

    #chroot_local_user=yes
    #chroot_list_enable=yes
    #chroot_list_file=/etc/vsftpd/chroot_list

是否开启递归  

    #ls_recurse_enable=yes

是否监听ipv4端口  

    #listen=yes

是否监听ipv6端口  
默认情况下开启该选项能同时监听v4和v6端口  

    listen_ipv6=yes

服务名  

    pam_service_name=vsftpd

用户列表使能  

    userlist_enable=no

tcp  

    tcp_wrappers=yes

最后需要关闭防火墙或者开放ftp服务  

    firewall-cmd --permanent --add-service=ftp

最重要一点 firewall-cmd --reload  
所谓的允许匿名登入不是不使用用户名  
而是可以用ftp或anonymous和空密码登入  
更多选项[参见这里][0]  
[0]:https://www.centos.org/docs/5/html/deployment_guide-en-us/s1-ftp-vsftpd-conf.html

***
## service-control
@20151202
从centos7开始服务的操作方式发生变化

### 服务操作
service 改为 systemctl

    # service <servcie> status|stop|start|restart
    # systemctl status|start|stop|restart <service>

### 系统自启动列表中删除或者添加

    chkconfig改为systemctl
    # chkconfig <service> off|on
    # systemctl enable|disable <service>
    # chkconfig <service>
    # systemctl is-enabled <service>
    # chkconfig -list
    # systemctl list-unit-files --type=service


### samba
@20151202  
本文基于centos-7  
[参考文档](http://www.unixmen.com/install-configure-samba-server-centos-7/)


### 检查samba是否已经安装

    rpm -qa |grep samba
    或者 yum list installed | grep samba

### 配置一个允许所有权限的匿名共享
首先创建一个目录  

    mkdir -p /home/shaojwa/work
    chmod -r 777 /home/shaojwa/work

### 配置samba
配置前先备份

    mv /etc/samba/smb.conf /etc/samba/smb.conf.bak

在[global]下配置  

    workgroup = workgroup

添加以下内容  

    [work]
    path = /home/shaojwa/work
    public = yes
    browsable = yes
    writable = yes
    guest ok = yes
    read only = no

### 启动samba  

    systemctl start smb
    systemctl start nmb
    systemctl enable smb
    systemctl enable nmb

### 用testparm 检查smb配置

### 配置selinux

    setsebool -p samba_enable_home_dirs on
    chcon -t samba_share_t /samba/anonymous_share/

### 关闭selinux
查看selinux状态  

    sestatus

如果状态是enabled则尝试关闭selinux  
编辑/etc/selinux/config文件  
将其中的  

    selinux=enforcing
改为

    selinux=disabled

重启  
此时从windows访问linux共享依然失败  


### 关闭防火墙

    systemctl stop firewalld

注意是firewalld
### 或者配置防火墙

    firewall-cmd --permanent --add-port=137/tcp
    firewall-cmd --permanent --add-port=138/tcp
    firewall-cmd --permanent --add-port=139/tcp
    firewall-cmd --permanent --add-port=445/tcp
    firewall-cmd --permanent --add-port=901/tcp
    firewall-cmd --reload

此时可以看到存在word共享当时无法打开文件夹

### 配置权限打开文件夹

此时从windows下访问linux的贡献时提示输入用户名密码  

### 想匿名访问
需要在conf文件中的[global]部分添加如下两行  

    security = user
    map to guest = bad user

此时从windows下访问linux已经能出现共享目录  
但是没有权限访问  


### 创建安全共享

创建用户  

    useradd -s /sbin/nologin smbusr

创建组  

    groupadd smbgrp

将用户加入组  

    usermod -a -g gmbgroup smbgrp

设置密码

    smbpasswd -a smbusr

创建共享目录后设置权限  

    mkdir /samba/share
    chmod -r 0755 /samba/share
    chown -r smbusr:smbgrp /samba/share
    
配置smb.conf  

    [share]
    path = /samba/share
    writable = yes
    browsable = yes
    guest ok = no
    valid users = @smbgrp

如果不关闭selinux就需要添加如下配置  

    chcon -t samba_share_t /samba/share/

重启smb  

    systemctl restart smb
    systemctl restart nmb

最后提醒  
共享目录最好不要放在home下  
因为home是其中一个特殊共享  
有对应的配置  
***
## net-config
@20151202

从centos-7以及rhel-7开始开始使用systemd。这是一个系统和服务管理器。

    sudo systemctl status  network.service
    sudo systemctl status  network
    sudo systemctl start   network.service
    sudo systemctl start   network
    sudo systemctl stop    network.service
    sudo systemctl stop    network
    sudo systemctl restart network.service
    sudo systemctl restart network

在此之前的版本可以用：

    service network status
    service network stop
    service network start
    service network restart

等价于使用初始化脚本：

    /etc/init.d/network status
    /etc/init.d/network restart
    /etc/init.d/network stop
    /etc/init.d/network start

### vmware相关的虚拟网络设备

[参考这里](http://blog.csdn.net/lwbeyond/article/details/7648509)  
vmware安装完成之后有三个虚拟交换机：  
vmnet0：桥接模式下的虚拟交换机  
vmnet1：在host-only模式下的虚拟交换机  
vmnet8：在nat模式下的虚拟交换机  

虚拟网卡：  
vmnet network adapter vmnet1：在host-only模式下，host与host-only虚拟网络进行通信，这是在物理机的虚拟网卡，和虚拟机上的虚拟网卡不是一个概念。vmnet network adapter vmnet8：在nat模式下，host与nat虚拟网络进行通信的虚拟网卡。  

### 虚拟机里配置centos为nat模式

虚拟机安装好centos之后默认采用nat模式, 所以只需要在mvware中设置使用nat模式，并在centos中打开开启启动开关 onboot=yes就可以，默认情况下得到的ip地址是192.168.59.0/24，这个地址是vmware配置的dhcp地址范围，可以在vmware上修改。

### 虚拟机里配置centos为bridged模式

### 虚拟桥接网卡

在虚拟机里安装好centos之运行ifconfig会友现在一张虚拟网卡virbr0，要了解这方面内容，详细的可以参考[这里](http://wiki.libvirt.org/page/virtualnetworking)。先了解几个概念：

### 虚拟网络交换机

在宿主机里，虚拟网络交换机以网卡的形式显示。默认的一个交换机，在libvirt守护进程安装并启动时创建，显示为virbr0。可以通过通过查看libvirtd来查看该守护进程是否存在：

    $ ps -aux | grep libvirtd

你可以通过ifconfig virbr0 来查看相关的信息。

    $ ifconfig virbr0

或者你使用ip命令

    $ip addr show virbr0

### 默认模式

在默认情况下，虚拟网络交换机工作在nat模式下。dhcp给每个虚拟网络交换机分配一个地址段。libvirt通过dnsmasq来作为dns和dhcp服务器。可以通过查看dnsmasq查看该守护进程：

    $ps -aux | grep dnsmasq

同时可以看到该守护进程的配置文件。	

### 其他模式

还有两种模式：第一是routed模式，就是我们常说的bridged模式。第二种是isolated模式。

### 查看

    ifconfig
    virsh net-list

结果一般是：

    name      state     autostart  persistent
    -----------------------------------------
    default   active    yes        yes  

### 禁用

    virsh net-destroy default

### 启用

    virsh net-start default

### 删除

    virsh net-undefine default

### 编辑

    virsh net-edit default

### nat改为bridge
***
## ip-tables
@20151202

iptables是绝大多数linux发行版内建的防火墙
在centos<7的版本中可以使用一下命令

### 查看iptables的状态

    # service iptables status
    # service ipv6tables status

### 关闭iptables

    # service iptables stop
    # service ipv6tables stop

### 启动iptables

    # service iptables start
    # service ipv6tables start

### 从系统自启动列表中删除iptables

    # chkconfig iptables off
    # chkconfig ipv6tables off

### 将iptables添加进系统自启动列表

    # chkconfig iptables on
    # chkconfig ipv6tables on

在centos7之后的版本统一用systemctl命令:  

    # systemctl [status|start|stop|restart] iptables
    # systemctl [status|start|stop|restart] ipv6tables

***
# cmdlines
其实所谓的复用技巧也只是我看网上的资料汇总出来的东西。
只是很多没有单独拿出来介绍，总是和其他的一些技巧一并介绍。
而我写的这篇只关注怎么用最简单的命令复用之前输入过的命令。

***
## command reuse

### ！系列
网上的说法是，这些以！开始的标记（暂且就用标记来称呼吧）都是一些列特殊的环境变量。

### 上一条命令的全部内容

    !!

示例

    $cd test
    $echo !!
    cd test

### 上条命令的第一个参数

    !^

示例
    $cd test
    $echo !^
    test
    
注意不是cd

### 上条命令的最后一个参数

    !$

    $cd first second last
    $echo !$
    last
    
### 上条命令的所有参数

    !*

    $cd first second last
    $echo !$
    first second last

### 最近一条以prefix开始的命令

    !prefix

注意这里的prefix可以是一个或者多个字母表。
看了以上几条命令我只有感慨正则表达无处不在。

### 打印但不执行最近一条以prefix开始的命令

    !prefix:p

### ^系列

    ^foo        //上一条命令中去掉foo之后的命令
    ^foo bar    //上一条命令中去掉foo和bar之后的命令
    ^foo^bar    //上一条命令中把foo换成bar之后的命令

### 最后再说说其他的几个常用的：
回到最近一次目录  

    cd - 

回到登入用户的home目录  

    cd ~

***
##  command edit

linux下命令操作是我最喜欢的方式。
但是编辑命令本身也有一些小技巧值得学习。
因为这样可以让你更快得编辑命令进而节省时间。

### 先说一个有意思的命令
依次显示之前命令的最后一个参数  

    alt+.

这个还是很有用的，比如本来打算输入cat xxx，结果输入 cd xxx。那么你只需要输入cat之后按 alt + .就可以自动补全，如果最后一个参数比较长就很有用。作为对比 ctrl+alt+y 只会记住上一条命令的第一个参数

### 查询命令
进入查询模式  

    ctrl+r  

撤销查询  

    ctrl+g

### 撤销修改

    ctrl+/

### 互换

光标所在位置和行首之间互换

    ctrl+xx

### 移动光标

光标的移动分三种: 行移动，单词移动，字母移动。

    ctrl+a     //移到行首
    ctrl+e     //移到行尾
    alt+f      //以单词为单位向前移动
    atl+b      //以单词为单位向后移动
    ctrl+f     //以字母为单位向前移动
    ctrl+b     //以字母为单位向后移动

### 删除命令  

    ctrl+u    //删除光标后的所有内容
    ctrl+k    //删除光标前的所有内容
    ctrl+w    //删除光标后面的一个单词
    alt+d     //删除光标前面的一个单词
    ctrl+h    //删除光标后面的一个字母
    ctrl+d    //删除光标前面的一个字母

#### 字母互换

    ctrl+t     //互换光标左右字母后光标移到后一个位置

### 单词互换

    alt+t     //互换光标左右两边的单词后移到下个单词位置

### 大小写转换

    alt+c //把光标所在出的字符改为大写然后跳到下一个单词词首
    alt+l //把光标所在处的字符到单词结尾都改为小写
    alt+u //把光标所在处的字符到单词结尾都改为大写

### 查看前后命令
查看之前命令  

    ctrl+p 

查看之后命令  

    ctrl+n

***
## grep

### 文件内容查找

    grep <options> <pattern> <files>

示例  

    grep -rn "loosgood"  * 
    *  表示当前目录所有文件，也可以是某个文件名
    -r 是递归查找
    -n 是显示行号
    -r 查找所有文件包含子目录
    -i 忽略大小写
    -l 只列出匹配的文件名
    -l 列出不匹配的文件名， 
    -w 只匹配整个单词，而不是字符串的一部分


### 查找某个目录信息
使用$来定位  

    ll root | grep roor$

查找man文档中以连字符开始的选项

    $ man chmod | grep [-]r
        -r, --recursive

加上-n显示行号  

    $ man chmod | grep [-]r
    111:  -r, --recursive

最后用more显示从某行开始

    $ man chmod | more +111

***
## man
linux下命令巨多，有的是所谓的内建（built-in command），比如read，有的不是比如grep。平时查命令用法用man，但是内建命令怎么查？一直不清楚，最近专门了解了下，做点记录。

### help查内建命令用法
help也是一个内建命令，查起来很方便，不需要依赖网络查用法，这是重点。

### help和man区别

这个问题不懂，只能网上找，按照自己的理解。help是bash内建命令，使用bash内部的数据结构获取保存信息。
而man不是。help只用来查看bash命令。所谓的内建，在我看来就是在bash进程里执行，终端是一个进程。写到这里，想到另外一个问题。如何查看当前shell的pid？

### 查看一个命令是否为内建命令

    type

    # type cd
    cd is a shell buildin
    # type grep
    grep is hashed (/bin/grep)
    
### 一个命令能不能同时是内建也是外部命令

可以比如pwd，至于为什么还不清楚，默认情况下是先使用内建命令。

### 如何查询是否存在相关功能的命令
直接输入

    apropos [keyword]

即可查看与keyword相关功能的命令。


### 如何关闭内建命令

    enable -n
### 查看所有激活的内建命令

    enable -a

### 查看所有用户

    $ cat /etc/passwd
    $ awk -f':' '{ print $1}' /etc/passwd

### 所有组

    $ cat /etc/group

### 查看组内所有成员

    lid group_name|user_name

### 查看系统完整信息

    uname -a

### 查看系统架构

    arch         /* deprecated since release 2.13 */
    uname -m     /* identical with arch */

### 查看快捷键绑定

    bind -p

### 查看当前正在使用的bash的pid
其实很简单$$命令就能显示当前进程的pid，比如我在linux terminal下运行得到

    # echo $$
    bash: 2085: command not found
    # ps axu | grep 2085
    root 2085 0.0 0.1 5232 1664 pts/0 s 09:38 0:00 bash

### 查看系统用户-who
基本功能不介绍两点说明  
（1）tty字段下显示tty表示直连终端，pts标识虚拟终端。比如通过securecrt就显示pts。  
（2）这玩意居然能查看系统最后一次重启的时间（who -b）有点意外。  
（3）查看当前终端 who -m  
（4）查看对应的shell 进程id： who -u （自然可以和-m配合）  
（5）查看run-level：who -r  

### 查看系统用户以及执行的命令-w
它告诉你当前系统有谁登入，从哪里登入，都在执行什么命令。
所以linux发行版都包含该命令。它差不多少是who和uptime功能的组合。

### 同步系统时间-clock
同事管理linux服务器，服务器时间一直显示有问题。今天专门去看了下。系统设置时区之后，修改当前时间，重启系统又有问题。后来发现，是没有写入到硬件时钟。linux系统的两个时钟，硬件使用和系统时钟需要同步。系统启动时，系统时钟需要从硬件时钟中读取时间。查看硬件时间用clock 或者hwclock命令。和系统时间的同步用：

    clock --systohc //把系统时间同步到硬件
    clock --hctosys //把硬件时间同步到系统

### 调整运行级别-init

### 查看运行级别-runlevel
linux下的run-leveld的含义就好像windows下的正常模式，安全模式，命令行模式等等。以图形界面登入linux，runlevel一般是5，而字符界面登入linux，runlevel一般是3。linux一般有8个level：

    0 halt the system
    1 single-user mode
    2 multi-user mode
    3 multi-user mode with networking
    4 not used/user-deinable
    5 multi-user mode with gui
    6 reboot the system


### 设置yum源
创建cdrom.repo文件包含如下内容

    [cdrom]
    name=cdrom-repo
    baseurl=file:///mnt/cdrom
    enable=1
    gpgcheck=0

### 挂载  

    mdir  /mnt/cdrom
    mount -t auto /dev/cdrom /mnt/cdrom


### 任务控制

    ctrl+z/

### 添加用户

    useradd shaojwa

### 文件操作系列

### 拷贝文件夹
cp -r /root/test /root/user/test  #注意-r

***
## windows管理命令
@20151202

### 获取卷(分区)的序列号

    vol [drive:]

### 获取字符映射表

    charmap

### 控制面板类  
winnt 5.0和6.0以上都可用，打开系统属性对话框。在6.0以后还有另一个系统配置对话框可以通过control system打开。

    sysdm.cpl

打开系统网络链接控制面板  

    ncpa.cpl

添加删除程序  

    appwiz.cpl

时间日期面板  

    timedate.cpl

桌面配置面板  

    desk.cpl

辅助功能配置：鼠标，鼠标，声音等

    access.cpl

internet配置  

    inetcpl.cpl

防火墙配置  

    firewall.cpl

区域和语言设置  

    netcpl.cpl
    intl.cpl

其他  

    control admintools
    control mouse
    control keyboard

***
# others
***
## scroll lock
@20151202  

今天早上在虚拟机里的centos上运行命令。发现无法输入，看了下发现scrolllock等变量，于是按scrolllock键使其不亮，发现就可以输入。
在物理机上不会有这个问题，在虚拟机的shell里存在。在shell里我试了下发现按下改键之后，你所有的命令都会缓存起来，等你再次按scrolllock随时，之前的所有输入会一次性得显示出来。
