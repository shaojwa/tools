https://github.com/google/googletest/blob/master/googlemock/docs/cheat_sheet.md

#### 什么是Mock
mock一般称为模拟，对待测对象行为（也就是接口）的模拟。

#### 使用的三个步骤

1. 用一些宏描述你想要模拟的接口，扩展为你的mock类。
1. 使用模拟类对应的对象，并制定这些对象对应接口的行为。
1. 使用模拟对象，编写测试代码。

#### 创建Mock类

#### 宏
1. 宏会帮你生成模拟方法，前三个参数是方法的申明，第四个参数是方法修饰符的集合。
1. 类型复杂时注意对逗号的保护， 建议用using 来alias一个复杂类型，比如`using BoolAndInt = std::pair<bool, int>;`。
1. mock的方法必须在public分段中定义，不管是被mock的在基类中是public，还是protectd，还是private。
1. 在mock类的外面，允许通过ON_CALL和EXPECT_CALL来引用mock方法。
1. gMock可以覆盖virtual方法。
1. gMock也可以模拟non-virtual方法，这种情况下，不需要继承基类，定义两个不相关的类。
1. gMock可以模拟free-function，就是c-style function，或者 static method。

####  Nice, Strict, Naggy
没有指定EXPECT_CALL的模拟方法被调用，被称为uninteresting call。那么这个mock方法将会调用ON_CALL指定的行为。


#### 一条重要的C++ rule
C++'s general rule: if a constructor or destructor calls a virtual method of this object, that method is treated as non-virtual. 
In other words, to the base class's constructor or destructor, this object behaves like an instance of the base class, not the derived class.
This rule is required for safety.

#### 在不破坏原有代码的前提下简化接口

#### 把一个non-virtual接口变成virtual接口是一个很重大的决定

建议引入接口类。

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
