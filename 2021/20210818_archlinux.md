
#### VirtualBox 
Bridged Adapter

#### partition
parted
boot-partition, swap-partition，root-partition，
```
```

#### mount
···
mkfs.ext4 /dev/sda3
mount /dev/sda3 /mnt
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

####　install grub
```
pacman -S grub
```

#### 
