#### ssh 常见登入问题

    ssh –v/-vv/-vvv	一个v显示debug1，两个v显示到debug2，类推，用于调试。

远程不允许登入问题

    /etc/ssh/sshd_config同时开启：    
    PermitRootLogn Without-password
    PermitRootLogn yes
    service ssh reload
    
登入延迟问题

    用ssh –vvv root@192.168.4.11调试查看延迟原因，
    如果是GSS失败，则设置/etc/ssh/sshd_config中的 GSSAPIAuthentication 为no，然后重启sshd

#### ssh-keygen中使用passphrase

ssh-keygen时如果输入passphrase那么在使用ssh的时候就会提示你输入passphrase。比如你在：

    git clone ssh://git@github.com/shaojwa/lang.git
    
同时如果你修改主机hostname原来的public key自然就不再有效。
