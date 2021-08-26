#### 安装包
```
[root@archlinux ~]# pacman -Q lsb-release
error: package 'lsb-release' was not found
[root@archlinux ~]# pacman -S lsb-release
resolving dependencies...
looking for conflicting packages...

Packages (1) lsb-release-1.4-18

Total Download Size:   0.01 MiB
Total Installed Size:  0.02 MiB

:: Proceed with installation? [Y/n] y
:: Retrieving packages...
 lsb-release-1.4-18-any  
(1/1) checking keys in keyring       
(1/1) checking package integrity     
(1/1) loading package files          
(1/1) checking for file conflicts    
(1/1) checking available disk space  
:: Processing package changes...
(1/1) installing lsb-release         
:: Running post-transaction hooks...
(1/1) Arming ConditionNeedsUpdate...

[root@archlinux ~]# lsb_release -a
LSB Version:    1.4
Distributor ID: Arch
Description:    Arch Linux
Release:        rolling
Codename:       n/a
```
