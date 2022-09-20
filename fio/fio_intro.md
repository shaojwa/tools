
# Run fio with command line parameters

job file parameter`iodepth=2` is the same as `--iodepth 2 or --iodepth=2` in command line option.

## Basic parameters
- **global section** defining shared parameters.
- and one or more **job sections** describing the jobs involved. 

## Parmeters in details
- I/O engine
- I/O type
- I/O depth
- Block Size

## sample
```
fio --name=vol_base_test --numjobs=1 --ioengine=rbd --rw=write --direct=1 --bs=256K --iodepth=1 --size=1G
    --pool=.disk01.rbd --rbdname=vol0 --group_reporting=1
```


## --ioengine=rbd
direct access to Ceph RBD via librbd without the need to use the kernel rbd driver.
 
- rados, using librados, direct access to Ceph Reliable Autonomic Distributed Object Store.
- rbd, using librbd, direct access to Ceph Rados Block Devices whitout the need to use the kernel rbd driver. 
 




## the kernel rbd driver is placed at
```
/lib/modules/<kernel-version>/kernel/drives/block/rbd.so
```
like kernel-cephfs at
```
/lib/modules/<kernel-version>/kernel/fs/ceph/ceph.ko
```
comparing with the user-space lib at
```
/opt/xxx/lib/librdb.so
/opt/xxx/lib/libcephfs.so
```
and the rados lib at
```
/opt/xxx/lib/librados.so
```
