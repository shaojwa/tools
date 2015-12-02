## 创建repo文件
创建cdrom.repo文件包含如下内容： 

	[cdrom]
	name=cdrom-repo
    baseurl=file:///mnt/cdrom
    enable=1
    gpgcheck=0

#挂载cdrom
    mdir  /mnt/cdrom
    mount -t auto /dev/cdrom /mnt/cdrom