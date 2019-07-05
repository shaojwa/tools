#### 第一课

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
  
  
C89/C90是一个很大的改进，比如增加 signed、volatile、const关键字，增加void *类型，增加预处理命令，以及定义c标准库等。  
  
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

#### 第二课 指定初始化

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
 
 #### 第三课 语句表达式
