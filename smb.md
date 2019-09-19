####  配置

     [shaojwa]
        path = /home/shaojwa
        valid users = shaojwa
        public = yes
        browseable = yes
        writeable = yes
        create mask = 0644

#### 列出某个ip所提供的共享文件夹

     smbclient -L 192.168.0.1 -U username[%password]
