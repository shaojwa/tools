```
(gdb) disass __erasure_code_version
Dump of assembler code for function __erasure_code_version:
   0x0000000000033cc0 <+0>:     lea    0xfd91(%rip),%rax        # 0x43a58
   0x0000000000033cc7 <+7>:     ret
End of assembler dump.
(gdb) p /10s 0x43a58
Item count other than 1 is meaningless in "print" command.
(gdb) x /10s 0x43a58
0x43a58:        "854b9ee5"
0x43a61:        "technique"
0x43a6b:        "reed_sol_van"
0x43a78:        "reed_sol_r6_op"
0x43a87:        "cauchy_orig"
0x43a93:        "cauchy_good"
0x43a9f:        "liberation"
0x43aaa:        "blaum_roth"
0x43ab5:        "liber8tion"
0x43ac0:        "ErasureCodePluginJerasure: "
(gdb) x /s 0x43a58
0x43a58:        "854b9ee5"
```
