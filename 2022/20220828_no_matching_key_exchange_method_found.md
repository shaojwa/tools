no matching key exchange method found
我在win中的`~/.ssh/config`中添加了以下几行配置：
```
PreferredAuthentications publickey
Host 10.165.104.246
  KexAlgorithms +diffie-hellman-group1-sha1
  PubkeyAcceptedAlgorithms +ssh-rsa
  HostKeyAlgorithms +ssh-rsa
```
