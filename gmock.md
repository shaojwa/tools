https://github.com/google/googletest/blob/master/googlemock/docs/cheat_sheet.md

#### 什么是Mock
mock一般称为模拟，对待测对象行为（也就是接口）的模拟。

#### 使用的三个步骤

1. 用一些宏描述你想要模拟的接口，扩展为你的mock类。
1. 使用模拟类对应的对象，并制定这些对象对应接口的行为。
1. 使用模拟对象，编写测试代码。


#### 宏
宏会帮你实现mock函数的定义，而不是指申明。

 

#### ON_CALL

设置特定mock对象的特定接口的默认行为用ON_CALL接口：

```
 ON_CALL(foo, GetSize()).WillByDefault(Return(1));
````
和EXPECT_CALL的区别是，这是设定默认行为，不需要调用。

#### EXPECT_CALL

EXPECT_CALL(turtle, PenDown()).Times(AtLeast(1));

#### Matchers

#### cardinality

#### Sticky


