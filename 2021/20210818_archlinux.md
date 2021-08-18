
#### VirtualBox 
Bridged Adapter

#### export http_proxy
```
```
#### modify mirrorlist
```
vim /etc/pacman.d/mirrorlist
```

#### mkfs 
```
mkfs.ext4 /dev/sda
mountn /dev/dsa /mnt
```

####
```
pacstrap /mnt base linux linux-firmware
```
