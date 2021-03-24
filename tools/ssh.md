### ssh tunnel 原理

https://www.ssh.com/ssh/tunneling/

ssh tunnel 又叫做 ssh 端口转发。 ssh client监听一个端口，application 连接到ssh client。
ssh client将 app 的数据转发给ssh-server服务器。ssh-server 再把数据转给app-serve。

### ssh 调试

    ssh –v/-vv/-vvv	一个v显示debug1，两个v显示到debug2，类推，用于调试。

###  远程不允许登入问题

/etc/ssh/sshd_config同时开启：

    PermitRootLogin Without-password
    PermitRootLogin yes
    service ssh reload
    
###  登入延迟问题

    用ssh –vvv root@192.168.4.11调试查看延迟原因，
    如果是GSS失败，则设置/etc/ssh/sshd_config中的 GSSAPIAuthentication 为no，然后重启sshd

### ssh-keygen中使用passphrase

ssh-keygen时如果输入passphrase那么在使用ssh的时候就会提示你输入passphrase。比如你在：

    git clone ssh://git@github.com/shaojwa/lang.git
    
同时如果你修改主机hostname原来的public key自然就不再有效。
