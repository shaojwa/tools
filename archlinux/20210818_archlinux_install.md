
#### VirtualBox 
采用桥接模式：Bridged Adapter

#### partition
用parted进行分区，分成三个分区，采用MBR分区表（partition table）。
boot-partition, swap-partition，root-partition。

#### 格式化文件系统以及挂载
```
mkfs.ext4 /dev/sda3
mount /dev/sda3 /mnt
```

#### 格式化swap分区并启用
```
mkswap /dev/sda2
swapon /dev/sda2
```

#### export http_proxy
```
export http_proxy=http://13333:ws1234@proxy.hccc.com:8080
export https_proxy=https://13333:ws1234@proxy.hccc.com:8080
```
#### modify mirrorlist
```
vim /etc/pacman.d/mirrorlist
```

#### mkfs 
```
mkfs.ext4 /dev/sda
mount /dev/dsa /mnt
```

#### install linux
```
pacstrap /mnt base linux linux-firmware
```

#### Generate an fstab file
```
# genfstab -U /mnt >> /mnt/etc/fstab
```

#### install grub
```
pacman -S grub
```

#### generate gurb config file

#### why there is no DHCP after installation but in it exist in live-installation
because we have not make some script in `/etc/systemd/network/`


#### install ssh
```
pacman -S openssh
```
