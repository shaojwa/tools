sudoers文件的编辑需要 visudo 命令，这个默认会使用vim来标记sudoers文件，且在保存时检查sudoers的语法。

    wwssh    ALL=(ALL)    ALL  
    // no password required
    wwssh    ALL=(ALL)    NOPASSWD:ALL  
    // only du and ping can be run with sudo
    wwssh    ALL=(ALL)    NOPASSWD:/usr/bin/du,/usr/bin/ping 
