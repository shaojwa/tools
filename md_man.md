
## markdown manual 
#### 28/12 2013 by darktyping &copy;

## summary

markdown 语法总的说来是一区块的划分的，简单可以分为
* 引用区块
* 列表区块
* 代码区块

#### quote-block
>这是第一层的引用
>>这是第二层的引用


#### list-block
*   可以用*或者用数字，建议一共四个字符（包括*号）
*   列表项可以是一个段落或者多个段落（一个列表项下的每个段落开头都要缩进四个空格）
*   列表项也可以是引用，但是引用要间隔一行。

    > 这一行是引用  
	> 这一行也是引用


#### code-block
*   代码区块统一用四个空格或者一个制表符，同样首先要另起一段。  

这下面是一个代码区块：

    #include <stdio.h>
	int main(void)
	{
		return 0;
	}


#### 可以用三个以上的星号、减号、或者底线来画出分割线，比如
****

#### 连接：

This is [an example](http://example.com/ "Title") inline link.

[This link](http://example.net/) has no title attribute.

代码是：
 
    This is [an example](http://example.com/ "Title") inline link.
	[This link](http://example.net/) has no title attribute.

#### 强调（一颗星斜体，两颗星加粗，三颗星斜体加粗）

*这里用的就是一颗星的强调*

**这里用的是两颗星的强调**

但是如果你显示星号，那就用斜杠转义比如 \*斜杠转义\*

#### 一小段代码
用 `printf()` 来演示


#### 自动连接
<http://example.com/>

<address@example.com>

简单用法总结如上，更多信息参见: [Markdown语法说明中文版](http://wowubuntu.com/markdown/#list)