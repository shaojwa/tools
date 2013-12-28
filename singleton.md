
#### 单例类

（1）私有构造函数 确保用户无法通过 *new* 直接实例它
（2）静态私有成员变量 *instance* 与静态共有方法 *Instance()* 
（3） *Instance()* 方法负责检验并实例化自己然后存储在静态成员变量中，确保只有一个实例被创建。
    
	class Singleton
	{
	public:
	    static Singleton* GetInst(void) 
		{
			if (!_inited)
			{
           		_instance = new Singleton();
           		_inited = true;
       		}
			return _instance;
		};

	private:		
		static Singleton *_instance;
		static bool _inited;
	};