    通过stty，参见input setting中
    ixany 让任何字符都可以重启输出。
    ixoff 开启字符发送（启动或停止字符）
    ixon  启动XON/XOFF数据流控制
    XON为start信号，即ctrl-q
    XOFF为停止信号，即ctrl-s
    所以要关闭这个流控就可以用 –ixon
    PC机器中常用的两种串行通信流控制。
    RTS/CTS（硬件流控制）
    XON/XOFF（软件流控制）
