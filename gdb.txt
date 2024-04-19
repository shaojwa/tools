https://sourceware.org/gdb/current/onlinedocs/gdb.html/
https://sourceware.org/gdb/current/onlinedocs/gdb.html/Machine-Code.html
https://sourceware.org/gdb/5.1.1/onlinedocs/gdbint.html
https://cs.baylor.edu/~donahoo/tools/gdb/gdb.html
#### 显示一个子串
```
(gdb) x /s 0x43a58
```

#### p显示16/8/10/2进制
(gdb) p sizeof(co::Task)
(gdb) p /x sizeof(co::Task)
(gdb) p /o sizeof(co::Task)
(gdb) p /t sizeof(co::Task)
help x 就可以看到

#### so可以直接调试
在/store/wsh/b01/libgo/build下可以直接 gdbliblibgo.so
(gdb) ptype co::Task

#### run core in gdb
(gdb) target core /corefile/dse.core

####  show target arch
(gdb) show arch
The target architecture is set to "auto" (currently "i386").

#### set arch
(gdb) set arch

#### load debuginfo file

#### load symbols from file
symbol-file dpe.debug
add-symbol-file dpe.debug
symbol-file // no args to clear the symbols

#### hex to dec 
p/x 0x2aa
p/d 0x2aa
p/t 0x2aa

#### show all types 
info types
info types raw_combined

#### query type by regexp
info types dcache
info types bufferlist

####  show types
ptype ceph::buffer::list
ptype ceph::buffer::ptr
ptype ceph::buffer::raw // after run
ptype ceph::buffer::raow_combined // after run

#### query functions
info func <regexp>
info func opproc

#### get function address 
p dm_hash_node_t::hn_get_object
info line dm_hash_node_t::hn_get_object
info line *0xcbd710
info line *(0xcbd710+0x2aa)
// After info line, the default address for the x command is changed to the starting address of the line.
// After info line, using info line again without specifying a location will display information about the next source line.

#### disass function
disass /m DCacheOPProc::opproc_destroy,+100
disass 'foo.c'::bar // not disass foo.c:bar

#### show class-instance
p *this
p *(C_MaybeExpiredSegment *)0x7f17d08d8560

#### show virtual-table
info vtbl this

#### examine mem
x $rbp-0x18

#### set start-args
(gdb) file /opt/bin/ceph-mds
(gdb) set args -f --cluster ceph --id mds0 --setuser ceph --setgroup ceph
(gdb) run

#### enable non-stop mode
// in `~/.gdbinit` 
set target-async on
set pagination off
set non-stop on

#### attach the thread
gdb attach <pid_of_thread>

#### attach and detach
gdb attach 
gdb detach

#### remote debug
gdbserver --attach :4444 <pid>
gdb ceph-mds
target remote 192.168.0.11:4444

#### signal capture
info signals // show the default handle of each signal
info handle  // = info signals
handle signal keywords

### python debug
tar xf centos_gdb_python_debug_mini.tgz -C debug
debug/install.sh
(gdb) thread apply all py-list

#### multi-thread debug state
(1) attach // all-t
(2) continue // all-S

// pagination off
(1) attach // all-t
(2) continue // all-S

// target-async on
(1) attach // all-t
(2) continue // all-S

// non-stop on
(1) attach // all-t
(2) continue // one-S

// target-async on, non-stop on
(1) attach // all-t
(2) continue // one-S 

#### break point
save breakpoints <filename>
break file.c:100 thread all

#### tcp usage ????
set tcp auto-retry on

#### scheduler
set scheduler-locking off|on|step 

#### todo
break 25 thread 4
b func if arg1->foo().bar().c_str() == "xxxx"
interrupt
thread apply 4 bt
thread apply all continue
gdb --command=gdbcmd1 routine

#### how to display virtual-function ????
p C_MaybeExpiredSegment::finish
Cannot reference virtual member function "finish"

#### why we need maint ???
maint print symbol all.sym 
set multiple-symbols
