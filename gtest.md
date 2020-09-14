参考文档： https://github.com/google/googletest/blob/master/googletest/docs/primer.md

----
#### 基本概念
01. https://github.com/google/googletest
1. 它支持任何类型的测试而不只是单元测试。
1. 分TEST和TEST_F测试，TEST是针对静态或者全局对象的测试的，TEST_F是专门用来访问对象和子例程的测试模式。
1. TEST_P就是参数化测试，原先针对不同的值，需要写多个测试用例，现在一个用例就搞定，这个用例里面用到的多个值用参数来指定。

----
#### TEST基本用法
```
TEST(TestSuiteName, TestName) {
  ... test body ...
}
```
1. TestSuiteName 和 TestName 都必须是可用的c++标识符并且不能包含下划线。
1. 一个测试用例的全名（fullname）包括TestSuiteName.TestName。
1. 不同的TestSuitName下可以有相同的TestName。
1. 逻辑相关的测试用例应该在一个TestSuite中。


#### TEST_F: Test Fixture
1. 什么时候需要？ 当你发现有好几个测试用例针对的都是类似的数据时，也就是当有重用数据的需要时，可以考虑。
1. 先要派生出一个类，testing::Test，因为我们需要从子类中访问特定的成员。
```
TEST_F(TestFixtureName, TestName) {
  ... test body ...
}
```
#### TEST 和 TEST_F 的区别是

TestSuite，一般翻译为测试套件，是一系列测试用例的集合，TestName就是测试用例名。

----
#### 事件机制：目的是在一些时间点执行一些操作。分三种，1.全局，1.TestSuite 级别，3.TestCase 级别。
```
// 全局
class FooEnvironment : public testing::Environment
{
public:
    virtual void SetUp()
    {
        std::cout << "Foo FooEnvironment SetUP" << std::endl;
    }
    virtual void TearDown()
    {
        std::cout << "Foo FooEnvironment TearDown" << std::endl;
    }
};

// TestSuite 级别
class FooTest : public testing::Test {
 protected:
  static void SetUpTestCase()
  {
    shared_resource_ = new ;
  }
  static void TearDownTestCase()
  {
    delete shared_resource_;
    shared_resource_ = NULL;
  }
};

// TestCase 级别
class FooCalcTest:public testing::Test
{
protected:
    virtual void SetUp()
    {
        m_foo.Init();
    }
    virtual void TearDown()
    {
        m_foo.Finalize();
    }
};
```

----
#### 参数化
```
你必须添加一个类，继承testing::TestWithParam<T>
class IsPrimeParamTest : public::testing::TestWithParam<int>
{
};
```

----
#### 死亡测试：专门针对程序的预期崩溃进行测试。
```
ASSERT_DEATH(statement, regex`);
EXPECT_DEATH(statement, regex`);
ASSERT_EXIT(statement, predicate, regex`);
EXPECT_EXIT(statement, predicate, regex`);	
```
编写死亡测试案例时，TEST的第一个参数，即testcase_name，请使用DeathTest后缀。原因是gtest会优先运行死亡测试案例，应该是为线程安全考虑。
```
// 常见的predicate
testing::ExitedWithCode(exit_code)      # 如果程序正常退出并且退出码与exit_code相同则返回true
testing::KilledBySignal(signal_number)  # 如果程序被signal_number信号kill的话就返回true
```
死亡测试有两种方式：
```
testing::FLAGS_gtest_death_test_style = "threadsafe";
testing::FLAGS_gtest_death_test_style = "fast";
```
用法
```
TEST(ExitDeathTest, Demo)
{
    EXPECT_EXIT(_exit(1),  testing::ExitedWithCode(1),  "");
}
```


----
#### 运行参数
这里说的运行参数，是测试套件（TestSuite）编译后的可执行文件运行时的参数，所以我们可以直接传入在运行命令行传入。
```
// --gtest_list_tests 罗列测试用例
bin/dcache-dm-test --gtest_list_tests
```
运行参数建议有三个优先级：命令行参数 > 代码中指定FLAG > 系统环境变量。 

```
// 代码中用FLAG建议放在testing::InitGoogleTest(&argc, argv) 之前。
int _tmain(int argc, _TCHAR* argv[])
{
    testing::GTEST_FLAG(output) = "xml:";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

----
#### 其他
1. 其他的宏
```
SUCCEED();                       # 测试用例直接返回成功
EXPECT_ANY_THROW(Foo(10, 0));    # 期望得到任何的异常
EXPECT_THROW(Foo(0, 5), char*);  # 期望得到char* 类型的异常
ASSERT_PRED1(pred1, val1);       # pred1(val1) returns true
ASSERT_PRED2(pred2, val1, val2); # pred2(val1, val2) returns true
EXPECT_PRED1(pred1, val1);       # pred1(val1) returns true
EXPECT_PRED2(pred2, val1, val2); # pred2(val1, val2) returns true
```
