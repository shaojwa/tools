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


* 看一下可用情况

      (parted) print free
      Model: PM8060- DefaultValue3 (scsi)
      Disk /dev/sdd: 1997GB
      Sector size (logical/physical): 512B/512B
      Partition Table: gpt
      Disk Flags:

      Number  Start   End     Size    File system  Name  Flags
              17.4kB  1997GB  1997GB  Free Space

*  然后创建一个分区（可以直接指定xfs）

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
  

  
*  在次查看后退出

        Model: PM8060- DefaultValue3 (scsi)
        Disk /dev/sdd: 1997GB
        Sector size (logical/physical): 512B/512B
        Partition Table: gpt
        Disk Flags:

        Number  Start   End     Size    File system  Name     Flags
        1      17.4kB  1997GB  1997GB               primary
        (parted) quit

以上在创建分区的时候指定文件类型，但是创建完成print，如上所示，FileSytem 并没有看到 xfs，过 mount -t xfs 尝试挂载也会报错，暂时不清楚原因，但是此时分区已经建立。

* 此时已经存在分区，通过mkfs.xfs 命令来唉创建xfs文件系统

        $ sudo mkfs.xfs -f /dev/sdp
        meta-data=/dev/sdp               isize=512    agcount=4, agsize=29293888 blks
                 =                       sectsz=512   attr=2, projid32bit=1
                 =                       crc=1        finobt=0, sparse=0
        data     =                       bsize=4096   blocks=117175552, imaxpct=25
                 =                       sunit=0      swidth=0 blks
        naming   =version 2              bsize=4096   ascii-ci=0 ftype=1
        log      =internal log           bsize=4096   blocks=57214, version=2
                 =                       sectsz=512   sunit=0 blks, lazy-count=1
        realtime =none                   extsz=4096   blocks=0, rtextents=0
        
        $ sudo parted /dev/sdp
        GNU Parted 3.1
        Using /dev/sdp
        Welcome to GNU Parted! Type 'help' to view a list of commands.
        (parted) print
        Model: PM8060- DefaultValue15 (scsi)
        Disk /dev/sdp: 480GB
        Sector size (logical/physical): 512B/512B
        Partition Table: loop
        Disk Flags:

        Number  Start  End    Size   File system  Flags
         1      0.00B  480GB  480GB  xfs
    
    可以看到此时的print打印的字段比用mkfs命令前print显示的少，没有Name字段，不清楚原因，网上都是通过mkfs.xfs的方式来格式化。

* 通过 mount -t /dev/sdp1 /home/wsh 来挂载，注意sdp1中的1不能省略。

* 最后如果想开机挂载，需要编辑/etc/fstab 文件。

