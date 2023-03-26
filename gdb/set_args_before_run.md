```
(gdb) file /opt/bin/ceph-mds
(gdb) set args -f --cluster ceph --id mds0 --setuser ceph --setgroup ceph
(gdb) run
```
