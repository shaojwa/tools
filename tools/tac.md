
######  Client端

客户端启动第一次登入流程  

* TAC第一次登入流程
        WinMain() -> CreatePipeClient() -> GetLoginRequest()

* TAC其他登入采用 LoginSecHelper() 
接口在接口内调GetLoginRequest()


######  客户端的工作线程
* 登入界面线程
* 托盘线程  


######  客户端文件说明：
* CerUI.cpp 证书相关
* ChangePwdUI.cpp  密码修改界面类
* CmdUtil.cpp 命令行处理类

######  CommonAPI.cpp 通用接口类
* code_convert：用来在utf-8和gb2312之间转换


######  连接UMC失败，请稍后再试

    RecvProcess //数据接收线程	
    RecvPacket() // 从管道内读取数据
	ClientMessageParse() //客户端代码处理
	

######  Service 端

######  登入认证流程
* 读取Client发送的命令 RecvPacket
* 解析配置 MessageParse()
* 初始化登入信息 InitLoginInfo()
* 登入 login()
* dot1x_auth_start()

	
