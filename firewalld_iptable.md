firewalld blocked 'wwssh.net', so have a look. 
#### firewall-cmd
```
[wsh@li984-80 ~]$ sudo firewall-cmd --zone=public --add-port=11280 --permanent
Error: INVALID_PORT: bad port (most likely missing protocol), correct syntax is portid[-portid]/protocol
[wsh@li984-80 ~]$ sudo firewall-cmd --zone=public --add-port=11280/tcp --permanent
Error: INVALID_PORT: 110280
[wsh@li984-80 ~]$ sudo firewall-cmd --zone=public --add-port=11280/tcp --permanent
success
```

#### netfilter
#### nftables
