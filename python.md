#### 一个类不继承自其他类，就显式从object继承，嵌套也一样。

继承自object是为了使属性（properties）正常工作，并且这样可以保护你的代码。  
这样做也定义了一些特殊的方法，这些方法实现了对象的默认语义，包括： 

    __new__,__init__, __delattr__,__getattribute__,__setattr__,__hash__,__repr__


#### 访问控制
