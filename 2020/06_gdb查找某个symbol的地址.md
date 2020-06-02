#### 显示某个symbol地址
```
(gdb) p MDLog::try_expire
$1 = {void (MDLog * const, LogSegment *, int)} 0x55dec3b8a6a0 <MDLog::try_expire(LogSegment*, int)>
(gdb) p LogSegment::try_to_expire
$2 = {void (LogSegment * const, MDSRank *, MDSGatherBuilder &,
    int)} 0x55dec3be8ce0 <LogSegment::try_to_expire(
    MDSRank*, C_GatherBuilderBase<MDSInternalContextBase, MDSGather>&, int)>
(gdb)
```
两个地址相差  0x55dec3be8ce0 - 0x55dec3b8a6a0 = 0x5e640

堆栈显示：
```
(LogSegment::try_to_expire(
MDSRank*, C_GatherBuilderBase<MDSInternalContextBase, MDSGather>&, int)+0x899) [0x55b28b1e9579]
(MDLog::try_expire(LogSegment*, int)+0x6b) [0x55b28b18a70b]
```
try_to_expire = 0x55b28b1e9579 - 0x899 = 0x55b28b1e8ce0
try_expire = 0x55b28b18a70b - 0x6b = 0x55b28b18a6a0
相差 = 0x55b28b1e8ce0 - 0x55b28b18a6a0 = 0x5e640
