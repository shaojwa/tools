####  配置为windows可访问

* 配置smb
     [shaojwa]
        path = /home/shaojwa
        valid users = shaojwa
        public = yes
        browseable = yes
        writeable = yes
        create mask = 0644
        
* centos关掉selinux
     
      setenforce 0
      
* centos 关掉 firewalld 或者放行 samba

      systemctl stop firewalld
      firewall-cmd --permanent --zone=public --add-service=samba

#### 列出某个ip所提供的共享文件夹

     smbclient -L 192.168.0.1 -U username[%password]
