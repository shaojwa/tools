#### make的两阶段处理
a read-in phase and a target-update phase。

#### gnu make 可以开启二级扩展
通过定义 .SECONDEXPANSION这个特殊的target。

#### 二级扩展的工作时间
在第一阶段完成后，这个特殊的target之后的prerequisites都会进行二级扩展。

#### 二级扩展的影响
大部分时候都没有影响，因为大部分的变量和函数都已经在第一阶段中完成扩展。

#### 二级扩展的真正用处
automatic variables

#### 隐式规则
隐式规则（implicit rules）也叫模式规则 （pattern rules）

#### 函数使用
```
main lib: $$(patsubst %.c,%.o,$$($$@_SRCS))
```
#### 模式主干
pattern stem.
