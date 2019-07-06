[GNU C语法扩展大全](http://tigcc.ticalc.org/doc/gnuexts.html)

[GCC 编译器手册](http://gcc.gnu.org/onlinedocs/gcc/)

#### 第1课 简介

linux内核中看到的一些特殊用法：

宏定义：

      #define mult_frac(x, numer, denom)(            \
      {                            \
          typeof(x) quot = (x) / (denom);         \
          typeof(x) rem  = (x) % (denom);         \
          (quot * (numer)) + ((rem * (numer)) / (denom));    \
      }                            \
      )

      #define ftrace_vprintk(fmt, vargs)                    \
      do {                                    \
          if (__builtin_constant_p(fmt)) {                \
              static const char *trace_printk_fmt __used      \
            __attribute__((section("__trace_printk_fmt"))) =  \
                  __builtin_constant_p(fmt) ? fmt : NULL;     \
                                          \
              __ftrace_vbprintk(_THIS_IP_, trace_printk_fmt, vargs);  \
          } else                              \
              __ftrace_vprintk(_THIS_IP_, fmt, vargs);        \
      } while (0)
 
 
 字符驱动填充
 
      static const struct file_operations lowpan_control_fops = {
      .open        = lowpan_control_open,
      .read        = seq_read,
      .write        = lowpan_control_write,
      .llseek        = seq_lseek,
      .release    = single_release,
      };
    
 
 打印宏定义
    
      #define pr_info(fmt, ...)    __pr(__pr_info, fmt, ##__VA_ARGS__)
      #define pr_debug(fmt, ...)    __pr(__pr_debug, fmt, ##__VA_ARGS__)
      
  
C语言在1989年出过第一个标准，一般叫C89/C90 或者叫ANSI C。在这是前是K&R C，在这之后有C99，以及C11。

我们看的k&C的《C程序设计语言》，第二版是C89，最早的一版就是K&R C。

标准中有函数嵌套层度，函数参数个数等很多规范，只是平时大家不会过多留意到。 
  
  
C89/C90是一个很大的改进，比如增加 signed、volatile、const关键字，增加void * 类型，增加预处理命令，以及定义c标准库等。  
  
C99做的改进常见的是： 

关键字和数据类型上， 添加inline，指针修饰restrict，支持long long，long double数据类型。

支持边长数组，支持对结构体特定成员赋值，支持16位浮点数等。

在语法上，变量声明可以放代码块的任何地方。源程序每行最大支持4095个字节。支持单行//注释方式。

目前据说对C99支持最好的是GUN C编译器。

C11做的常用改进是：新增文件锁功能；支持多线程；目前绝大多数编译器还不支持。

以上是标准，每个编译器厂商都还会有自己的扩展。比如GUN C编译器的扩展有：

* 零长度数组
* 语句表达式
* 内建函数
* __attribute__特殊属性声明
* 标号元素
* case 范围

#### 第2课 指定初始化

C99 标准改进了数组的初始化方式，支持指定任意元素初始化，不再按照固定的顺序初始化。

    int b[100] ={ [10] = 1, [30] = 2};
  
通过数组索引，我们可以直接给指定的数组元素赋值。这里有个细节注意一下，就是各个赋值之间用逗号 “，” 隔开，而不是使用分号“；”。
如果我们想给数组中某一个索引范围的数组元素初始化，可以采用下面的方式。

    int main(void)
    {
        int b[100] = { [10 ... 30] = 1, [50 ... 60] = 2 }；
        for(int i = 0; i < 100; i++)
        {
            printf("%d  ", a[i]);
            if( i % 10 == 0)
                printf("\n");
        }
        return 0;   
    }

GNU C 支持使用 … 表示范围扩展，这个特性不仅可以使用在数组初始化中，也可以使用在 switch-case 语句中。

除此之外，一个结构体变量的初始化，也可以通过指定某个结构体域直接赋值。
在标准 C 中，结构体变量的初始化也要按照固定的顺序。在 GNU C 中我们也可以通过结构域来初始化指定某个成员。

    struct student{
        char name[20];
        int age;
    };

    int main(void)
    {
        // 标准 C 赋值方式
        struct student stu1={ "wit",20 };
        printf("%s:%d\n",stu1.name,stu1.age);

        // GUN C 赋值方式
        struct student stu2=
        {
            .name = "wanglitao",
            .age  = 28
        };
        printf("%s:%d\n",stu2.name,stu2.age);

        return 0;
    }
 
 这是 GUN C编译器的一个扩展。
 
 #### 第3课 语句表达式
 
C语言中，语句和表达式是不一样的，表达式有两个属性，值和类型，比如 x = 1 * 2，但是后面没有结束的分号。

分号是编译器认为一条语句结束的标志，就算是bash之类的脚本语言，也是用分号而不是物理行来判断一行代码的结束。

* 代码块

在｛｝中做个语句组成，编译器以代码块来决定变量的入栈和出栈。

GNU C 对 C 标准作了扩展，允许在一个表达式里内嵌语句，允许在表达式内部使用局部变量、for 循环和 goto 跳转语句。

这样的表达式，我们称之为语句表达式。语句表达式的格式如下：

      ({ 表达式1; 表达式2; 表达式3; })
      
      
      MAX(x,y)  ({\
          auto __a = (x); \
          auto __b = (y); \
          __a > __b ? __a : __b; \
      )
      
      #define MAX(type,x,y)({     \
          type _x = x;        \
          type _y = y;        \
          _x > _y ? _x : _y; \
          })
      
      #define min_t(type, x, y) ({            \
          type __min1 = (x);          \
          type __min2 = (y);          \
          __min1 < __min2 ? __min1 : __min2; })

      #define max_t(type, x, y) ({            \
          type __max1 = (x);          \
          type __max2 = (y);          \
          __max1 > __max2 ? __max1 : __max2; })
          
          
  #### 第4课 containter_of
  
  typeof
  
      #define MAX(x,y)({     \
          typeof(x) _x = x;        \
          typeof(x) _y = y;        \
          _x > _y ? _x : _y; \
      })
      
      
      #define min(x, y) ({                \
          typeof(x) _min1 = (x);          \
          typeof(y) _min2 = (y);          \
          (void) (&_min1 == &_min2);      \
          _min1 < _min2 ? _min1 : _min2; })

      #define max(x, y) ({                \
          typeof(x) _max1 = (x);          \
          typeof(y) _max2 = (y);          \
          (void) (&_max1 == &_max2);      \
          _max1 > _max2 ? _max1 : _max2; })
          
      #define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
      #define  container_of(ptr, type, member) ({    \
          const typeof( ((type *)0)->member ) *__mptr = (ptr); \
          (type *)( (char *)__mptr - offsetof(type,member) );})


#### 第5课 零长数组

C99 允许边长数组，即编译时长度不确定的数组。
GNU C在C99 的基础上新增零长数组，目的是为了支持边长结构体。

#### 第6课 GNU C 的扩展关键字：__attribute__

声明这个特殊属性有什么用呢？主要用途就是指导编译器在编译程序时进行特定方面的优化或代码检查。

      __atttribute__((ATTRIBUTE))
 
现在 __attribute__ 支持十几种属性：

* section
* aligned
* packed
* format
* weak
* alias
* noinline
* always_inline

我们先讲一下 section 这个属性。使用__atttribute__ 来声明一个 section 属性，主要用途是在程序编译时，将一个函数或变量放到指定的段，即 section 中。
我们可以使用下面的 readelf 命令，去查看一个可执行文件中各个 section 的信息。

      $ ld --verbose
      
我们使用上面命令，就可以查看编译当前程序时，链接器使用的默认链接脚本。在 Linux 内核中，同样会有 vmlinux.lds 这样一个链接脚本。

《C 语言嵌入式 Linux 高级编程》：程序的编译、链接和运行。

#### 第7课 地址对齐那些事

GNU C 通过 __attribute__ 来声明 aligned 和 packed 属性，指定一个变量或类型的对齐方式。
这两个属性用来告诉编译器：在给变量分配存储空间时，要按指定的地址对齐方式给变量分配地址。

结构体的整体对齐就是结构体总长度的对齐，就好像基本数据类型只有1字节（char），2字节（short），4字节（int）一样。
结构体如果其中一个成员是4字节，那么一般情况下不允许出现10字节的情况，末尾也要补充进2字节，让结构体的大小达到12字节。

      struct data{
          char a;
          short b;
          int c ;
      }__attribute__((aligned(16)));
      
  起始这里要除以 aligned是同时指定对齐和分配大小的，看gnu官网的解释：
  > aligned
  force the compiler to insure (as far as it can) that each variable whose type is struct S or more_aligned_int will be allocated and aligned at least
  
  > packed
This attribute, attached to an enum, struct, or union type definition, specified that the minimum required memory be used to represent the type.

#### 第8课 变参函数的格式检查format

既然地址对齐会造成一定的内存空洞，那我们为什么还要按照这种对齐方式去存储数据呢？
一个主要原因就是，这种对齐设置可以简化 CPU 和内存 RAM 之间的接口和硬件设计。
在 Linux 内核中，我们经常看到 aligned 和 packed 一起使用，即对一个变量或类型同时使用 aligned 和 packed 属性声明。
这样做的好处是，既避免了结构体内因地址对齐产生的内存空洞，又指定了整个结构体的对齐方式。
