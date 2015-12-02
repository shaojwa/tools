
######  20140108 by shaojwa

######  Ch2
######  2.2
* nsis 把每一行都当作命令

######  2.3
* OutFile 指令指明生成的安装文件路径

######  2.3.1 属性指令（多种）
* 属性指令决定安装行为以及外观

######  2.3.2 页面指令（Page）
* 安装页设置使用Page命令
    Page license
	Page components
	Page directory
	Page instfiles
	UninstallPage uninstConfirm
	UninstallPage instfiles

######  2.3.3  片段指令(Section)
* 常用法

        Section "Installer section"
	    SectionEnd
	    //卸载片段以"un." 开头
	    Section "un.Uninstaller Section"
	    SectionEnd

在片段中使用的指令和属性指令非常不同，他们运行在用户的电脑上。
最常见用的就是 `SetOutPath` //把文件释放到哪里) 以及 `File` //释放哪些文件

* 执行  

        nsExec::Exec '"$INSTDIR\vcredist_x86.exe" /q'


* 释放文件

        // 在实行前一般先设定释放路径
	    SetOutPath $INSTDIR
	    // 释放文件
	    File "path/to/file"  


######  2.3.4 函数 Functions

函数和片段的区别是他们被调用的方式.  
函数有两类 1. *用户函数*  2. *回调函数*
* 用户函数  
在片段或者函数中通过Call指令调用，用户函数不会被调用除非你使用Call指令调用。
* 回调函数  
在某个事件触发时被安装程序调用，比如安装程序运行时。回调函数是可选的。
比如.onInit函数会因为函数名而被NSIS编译器识别为一个回调函数，并在安装开始时调用。



######  2.3.5 使用脚本
######  2.3.5.1 代码的逻辑结构
* 常见的条件指令(为了方便各种比较运算一般都会添加 `LogicLib.nsh`)

        StrCmp IntCmp, IfErrors, Goto 
######  2.3.5.2 变量
    * Var 指令定义变量，并且变量是全局的。
	* 注意使用寄存器变量和栈

######  2.3.5.3 调试脚本
    MessageBoxes/DetailPrint

######  2.3.6 脚本的执行

(1) 定义的页面依次显示，直到instfiles页面
(2) 在instfiles页面，各个section按照定义的顺序依次执行。
(3) 如果components页面没有显示，所有的section都会执行。
(4) 如果有回调函数，回调函数可能会先于任何section被执行，
比如.onInit回调函数会先于任何其他代码执行。
(5) 也有页面回调函数(page-callback function)会在页面显示的某个阶段执行。

######  2.3.7 编辑器命令
编译器命令在编译的时候执行  

1. 条件编译
2. 头文件包含
3. 执行应用程序
4. 改变工作目录
5. 其他

最常见的是define。 Defines是编译时常量
	
