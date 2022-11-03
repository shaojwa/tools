## Node
#### 什么是一个 Node
一个iSCSI initiator或者iSCSI target (a single iSCSI initiator or iSCSI target.) 

#### Initiator
iSCSI client

#### Target
iSCSI Server provide several Targets

#### 先去发现一个Node
去发现一个之后，注意，需要指定一个 type，st就是SendTargets
```
$ sudo iscsiadm -m discovery -p 172.16.21.70 -t st
172.16.21.70:3260,1 iqn.2018-01.com.h3c.onestor:09502dd08f414d779e79ae23c901c411
```

#### 显示发现的Node
多了一个Node，是一种iSCSI-Target类型的Node
```
$ sudo iscsiadm -m node
172.16.21.70:3260,1 iqn.2018-01.com.h3c.onestor:09502dd08f414d779e79ae23c901c411
```

#### 登入Node
we can be login in node, or discovery mode：
```
sudo iscsiadm -m node -p 172.16.21.82 -l
sudo iscsiadm -m node -T iqn.2018-01.com.h3c.onestor:1f370e6107474f82a56d7810199c1f50 -l
```

#### 退出Node
```
sudo iscsiadm -m node -p 172.16.21.80 -u
sudo iscsiadm -m node -T iqn.2018-01.com.h3c.onestor:20c5611213f64c0d9500f7096d9f390e -u
sudo iscsiadm -m session -u
sudo iscsiadm -m node -u
sudo iscsiadm -m node --logoutall=all
sudo iscsiadm -m node -U all
```

## session
#### 什么是session
就是和Target的个链接，The group of TCP connections that link an initiator with a target form a session

####  显示所有session
```
$ sudo iscsiadm -m session
tcp: [12] 172.16.21.70:3260,1 iqn.2018-01.com.h3c.onestor:09502dd08f414d779e79ae23c901c411 (non-flash)
```

#### rescan
```
sudo iscsiadm -m session -R // rescan all running session
```
