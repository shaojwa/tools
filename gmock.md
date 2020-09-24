https://github.com/google/googletest/blob/master/googlemock/docs/cheat_sheet.md


设置特定mock对象的特定接口的默认行为用ON_CALL接口：
```
 ON_CALL(foo, GetSize())                       // #3
      .WillByDefault(Return(1));
````
和EXPECT_CALL的区别是，这是设定默认行为，不需要调用。
