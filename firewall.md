#### 关闭防火墙

    firewall-cmd --state
    service firewalld status
    
    systemctl start firewalld.service
    service firewalld start
    
    systemctl stop firewalld.service
    service firewalld stop
    
    systemctl disable firewalld.service
    service firewalld disable
