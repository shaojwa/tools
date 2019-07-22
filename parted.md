#### 将一块硬盘自动挂载为xfs系统

* 查看硬盘是否已经有文件系统

    $ sudo parted /dev/sdp
    (parted) print
    Number  Start   End    Size   File system  Name  Flags
     1      1049kB  480GB  480GB  ext4         gpt
    select /dev/sdq1
    (parted) print 
    Number  Start   End    Size   File system  Name  Flags
     1      1049kB  480GB  480GB  xfs          gpt

* 选一个没用过的硬盘，先创建分区表

    (parted) select /dev/sdd
    Using /dev/sdd
    (parted) mklabel gpt
    (parted) print
    Model: PM8060- DefaultValue3 (scsi)
    Disk /dev/sdd: 1997GB
    Sector size (logical/physical): 512B/512B
    Partition Table: gpt
    Disk Flags:

    Number  Start  End  Size  File system  Name  Flags

*　看一下可用情况

  (parted) print free
  Model: PM8060- DefaultValue3 (scsi)
  Disk /dev/sdd: 1997GB
  Sector size (logical/physical): 512B/512B
  Partition Table: gpt
  Disk Flags:

  Number  Start   End     Size    File system  Name  Flags
          17.4kB  1997GB  1997GB  Free Space

* 然后创建一个分区（可以直接指定xfs）

  (parted) mkpart primary
  File system type?  [ext2]? xfs
  Start? 17.4kB
  End? 1997G
  Warning: You requested a partition from 16.9kB to 1997GB (sectors 33..3900390625).
  The closest location we can manage is 17.4kB to 1997GB (sectors 34..3900680158).
  Is this still acceptable to you?
  Yes/No? y
  Warning: The resulting partition is not properly aligned for best performance.
  Ignore/Cancel? i
  (parted) print
  
* 在次查看后退出

  Model: PM8060- DefaultValue3 (scsi)
  Disk /dev/sdd: 1997GB
  Sector size (logical/physical): 512B/512B
  Partition Table: gpt
  Disk Flags:

  Number  Start   End     Size    File system  Name     Flags
   1      17.4kB  1997GB  1997GB               primary
  (parted) quit




