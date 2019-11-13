#### gdb基本用法

远程调试

    gdbserver --attach :4444 <pid>
    gdb ceph-mds
    target remote 192.168.0.11:4444
    
搜索命令

    apropos 
    
查看线程

    info thread

切换线程

    thread <ID> 

查看所有栈帧（backtrace）

    bt      // 考虑用full 限定符
    where   // 等同于 bt 考虑用full 限定符
    
切换到指定的栈帧

    frame <frame_id>
    
查看栈帧的详细情况

    info frame

断点

    save breakpoints <filename> // 保存断点
    break file.c:100 thread all
    
符号

    maint print symbol all.sym 
    info functions C_ObjectOperation_decodevals
    set multiple-symbols // 多符号匹配时的行为


当前指令位置

    
    p $rip
    
变量类型
    
    ptype
    whatis
    
查看类
    
    p *this
    p *(C_MaybeExpiredSegment *)0x7f17d08d8560
    
查看函数

    p C_MaybeExpiredSegment::complete
    
查看虚函数

    p C_MaybeExpiredSegment::finish时报错
    Cannot reference virtual member function "finish"
    
查看虚函数表

    info vtbl this
    
反汇编函数
    
    disass /m Server::handle_client_readdir
    
显示汇编代码

    set disassemble-next-line on
    intel格式	set disassembly-flavor intel
    
查看内存内容

    x $rbp-0x18
    
单行汇编执行

    si
    
网络相关

    set tcp auto-retry on
    
调度器

    set scheduler-locking off|on|step
    
信号捕捉

    info signals // 显示所有信号以及默认的gdb处理方式
    info handle  // =  info signals
    handle signal keywords
    
指定程序启动参数

    (gdb) file /opt/bin/ceph-mds
    (gdb) set args -f --cluster ceph --id mds0 --setuser ceph --setgroup ceph
    (gdb) run
    
指定命令启动
    gdb -p 1234 -ex 'break MOSDOpReply::decode_payload'

### python debug

    tar xf centos_gdb_python_debug_mini.tgz -C debug
    debug/install.sh
    (gdb) thread apply all py-list


#### 为什么bt显示的某些栈帧看不到参数

一个软件的正式版本一般都是经过优化的，如果一个接口的参数，在调用这个接口之后不再使用，那么这个接口的参数一般会通过寄存器传入。
这个参数也就不会在栈帧中看到，除非是对内层的调用。所以如果碰到某个接口的参数无法显示，不用觉得奇怪。
