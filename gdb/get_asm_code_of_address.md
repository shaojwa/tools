```
(gdb) disass 0x400c5d
Dump of assembler code for function pchar_add_str(char const*, std::string):
   0x0000000000400c5d <+0>:     push   %rbp
   0x0000000000400c5e <+1>:     mov    %rsp,%rbp
   0x0000000000400c61 <+4>:     sub    $0x20,%rsp
   0x0000000000400c65 <+8>:     mov    %rdi,-0x8(%rbp)
   0x0000000000400c69 <+12>:    mov    %rsi,-0x10(%rbp)
   0x0000000000400c6d <+16>:    mov    %rdx,-0x18(%rbp)
   0x0000000000400c71 <+20>:    mov    -0x8(%rbp),%rax
   0x0000000000400c75 <+24>:    mov    -0x18(%rbp),%rdx
   0x0000000000400c79 <+28>:    mov    -0x10(%rbp),%rcx
   0x0000000000400c7d <+32>:    mov    %rcx,%rsi
   0x0000000000400c80 <+35>:    mov    %rax,%rdi
   0x0000000000400c83 <+38>:    callq  0x400e33 <std::operator+<char, std::char_traits<char>, std::allocator<char> >(
                                       char const*, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)>
   0x0000000000400c88 <+43>:    mov    -0x8(%rbp),%rax
   0x0000000000400c8c <+47>:    leaveq
   0x0000000000400c8d <+48>:    retq
```
