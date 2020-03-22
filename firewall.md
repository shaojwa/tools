#### 关闭防火墙

```
firewall-cmd --state
firewall-cmd --list-all
firewall-cmd --get-services  // Print predefined services
firewall-cmd --list-services // List services added for a zone 
firewall-cmd --list-ports    // List ports added for a zone
```
```
systemctl status firewalld.service
systemctl start firewalld.service
systemctl stop firewalld.service
systemctl disable firewalld.service

service firewalld status
service firewalld start    
service firewalld stop    
service firewalld disable
```

#### Add service
```
edit v2ray.xml in /usr/lib/firewalld/services

// 永久添加一个服务到zone
firewall-cmd --permanent --zone=public --add-service=v2ray

// 重新加载
firewall-cmd --reload

// 确认已经添加到zone
firewall-cmd --list-services
```
