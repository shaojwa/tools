    system call
    exception
    trap
    far fewer system calls than most systems
    Provide mechanism, not policy
    SYSCALL_DEFINE0中的0代表参数个数
    系统调用bar在内核中实现的函数名是sys_bar
    系统调用在sys.c中
    SYSCALL_DEFINEX 的宏在include/linux/syscalls.h中
    process does not refer to the syscall by name
    架构相关的系统调用表存放系统调用号
    x86-64架构定义在arch/i386/kernel/syscall_64.c
    linux的系统调用比一般的系统快是因为它上下文切换快
    system call  handler
    signal the kernel to have the system switch to kernel mode
    exception handler is the system call handler here.
    int $0x80
    It triggers a switch to kernel mode and the execution of exception vector 128
    这个handler也恰恰就命名为system_call()
    在arch/x86/entry/entry_64.S文件中的ENTRY(entry_SYSCALL_64)
    其中有一行是call    *sys_call_table(, %rax, 8)
    the important notion is that somehow user-space causes an exception or trap to enter the kernel
