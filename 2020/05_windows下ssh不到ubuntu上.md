ssh-copy-id成功之后，ssh还是不能免密登入，通过ssh -v看到：
```
OpenSSH_7.7p1, OpenSSL 1.0.2o  27 Mar 2018
debug1: Reading configuration data /etc/ssh/ssh_config
debug1: Connecting to 192.168.84.199 [192.168.84.199] port 22.
debug1: Connection established.
debug1: identity file /c/Users/w1333/.ssh/id_rsa type 0
debug1: key_load_public: No such file or directory
debug1: identity file /c/Users/w1333/.ssh/id_rsa-cert type -1
debug1: key_load_public: No such file or directory
debug1: identity file /c/Users/w1333/.ssh/id_dsa type -1
debug1: key_load_public: No such file or directory
debug1: identity file /c/Users/w1333/.ssh/id_dsa-cert type -1
debug1: key_load_public: No such file or directory
debug1: identity file /c/Users/w1333/.ssh/id_ecdsa type -1
debug1: key_load_public: No such file or directory
debug1: identity file /c/Users/w1333/.ssh/id_ecdsa-cert type -1
debug1: key_load_public: No such file or directory
debug1: identity file /c/Users/w1333/.ssh/id_ed25519 type -1
debug1: key_load_public: No such file or directory
debug1: identity file /c/Users/w1333/.ssh/id_ed25519-cert type -1
debug1: key_load_public: No such file or directory
debug1: identity file /c/Users/w1333/.ssh/id_xmss type -1
debug1: key_load_public: No such file or directory
debug1: identity file /c/Users/w1333/.ssh/id_xmss-cert type -1
debug1: Local version string SSH-2.0-OpenSSH_7.7
debug1: Remote protocol version 2.0, remote software version OpenSSH_6.6.1p1 Ubuntu-2ubuntu2.8
debug1: match: OpenSSH_6.6.1p1 Ubuntu-2ubuntu2.8 pat OpenSSH_6.6.1* compat 0x04000000
debug1: Authenticating to 192.168.84.199:22 as 'wsh'
debug1: SSH2_MSG_KEXINIT sent
debug1: SSH2_MSG_KEXINIT received
debug1: kex: algorithm: curve25519-sha256@libssh.org
debug1: kex: host key algorithm: ecdsa-sha2-nistp256
debug1: kex: server->client cipher: aes128-ctr MAC: umac-64-etm@openssh.com compression: none
debug1: kex: client->server cipher: aes128-ctr MAC: umac-64-etm@openssh.com compression: none
debug1: expecting SSH2_MSG_KEX_ECDH_REPLY
debug1: Server host key: ecdsa-sha2-nistp256 SHA256:mV+t8TnRDbYohp36InDVIMukRR3GY6n/Dudn1WweYJM
debug1: Host '192.168.84.199' is known and matches the ECDSA host key.
debug1: Found key in /c/Users/w13337/.ssh/known_hosts:14
debug1: rekey after 4294967296 blocks
debug1: SSH2_MSG_NEWKEYS sent
debug1: expecting SSH2_MSG_NEWKEYS
debug1: SSH2_MSG_NEWKEYS received
debug1: rekey after 4294967296 blocks
debug1: SSH2_MSG_SERVICE_ACCEPT received
debug1: Authentications that can continue: publickey,password
debug1: Next authentication method: publickey
debug1: Offering public key: RSA SHA256:k9GnF6J3AOGhV5i9prS561C+k9IEeb5BcDMrLbpw1tg /c/Users/w13337/.ssh/id_rsa
debug1: Authentications that can continue: publickey,password
debug1: Trying private key: /c/Users/w13337/.ssh/id_dsa
debug1: Trying private key: /c/Users/w13337/.ssh/id_ecdsa
debug1: Trying private key: /c/Users/w13337/.ssh/id_ed25519
debug1: Trying private key: /c/Users/w13337/.ssh/id_xmss
debug1: Next authentication method: password
wsh@192.168.84.199's password:
```
看起来公钥登入失败了，提示我用密码登入，为什么会失败？网纱查一下是以为内sshd_config中的StrictMode配置为yes，这时候，系统会检查登入的用户wsh的home的权限是否过大，导致对其他用户也开放写权限，如果有开放，说明这个home下的.ssh目录下的
authorized_keys文件可能被别人修改，也许就不安全。这样ssh就会拒绝链接。

man一下sshd就可以看到： If this file, the ~/.ssh directory, or the user's home directory are writable by other users, then the file could be modified or replaced by unauthorized
 users.  In this case, sshd will not allow it to be used unless the StrictModes option has been set to “no”.
