###### ftp基础    
@20151203   
###### 主动模式  
主动就是传输数据时  
客户端开启某端口并PORT命令告诉服务器  
服务器连接客户端  
  
###### 被动模式  
被动就是传输数据时  
服务器开启某端口并通过PASV命令通知客户端  
客户端连接服务器  
  
  
###### 配置文件  
/usr/sbin/vsftpd            vsftpd的主程序  
/etc/vsftpd/vsftpd.conf     主配置文件  
/etc/vsftpd.ftpusers        禁止使用vsftpd的用户列表文件  
/etc/vsftpd.user_list       禁止或允许使用vsftpd的用户列表文件  
/var/ftp                    匿名用户主目录  
/var/ftp/pub                匿名用户的下载目录  
  

#### 参数含义  
//是否允许匿名访问
`anonymous_enable=YES`  
//是否允许本地用户登入  
`local_enable=YES`  
//允许任何形式的写操作  
`write_enable=YES`  
//umask屏蔽权限022表示所有者群组和其他用户不能写  
`local_umask=022`  
//是否允许匿名用户上传文件  
`#anon_upload_enable=YES`  
//是否允许你您不过用户创建文件  
`#anon_mkdir_write_enable=YES`  
//是否在进入目录是显示欢迎信息  
`dirmessage_enable=YES`  
//上传下载文件时记录日志  
`xferlog_enable=YES`  
//是否使用20端口传输数据即是否采用主动模式  
`connect_from_port_20=YES`  
//是否允许匿名上传的文件改变其所有者  
`#chown_uploads=YES`  
`#chown_username=whoever`  
//设置日志文件路  
`#xferlog_file=/var/log/xferlog`  
//是否采用标准的日志文件格式  
`xferlog_std_formats=YES`  
//空闲会话超时时间  
`#idle_session_timeout=600`  
//数据链接超时时间  
`#date_connection_timeout=120`  
//是否采用非特权用户  
`#nopriv_user=ftpsecure`  
//是否识别匿名用户的ABOR请求  
//不建议开启但不开启可能使老的ftp客户端混乱  
`#async_abor_enable=YES`  
//ASCII模式下的上传和下载  
`#ascii_upload_enable=YES`  
`#ascii_download_enable=YES`  
//欢迎提示语句  
`#ftpd_banner=Welcome to blah FTP service`  
//拒绝登入邮件列表  
`#deny_email_enables=YES`  
`#banned_email_file=/etc/vsftpd/banned_emails`  
//chroot用户使能  
`#chroot_local_user=YES`  
`#chroot_list_enable=YES`  
`#chroot_list_file=/etc/vsftpd/chroot_list`  
//是否开启递归  
`#ls_recurse_enable=YES`  
//是否监听ipv4端口  
`#listen=YES`  
//是否监听ipv6端口  
//默认情况下开启该选项能同时监听v4和v6端口  
`listen_ipv6=YES`  
//服务名  
`pam_service_name=vsftpd`  
//用户列表使能  
`userlist_enable=NO`  
//tcp  
`tcp_wrappers=YES`  
  
###### 最后注意一点  
需要关闭防火墙或者开放ftp服务  
firewall-cmd --permanent --add-service=ftp  
最重要一点 firewall-cmd --reload  
所谓的允许匿名登入不是不使用用户名  
而是可以用ftp或anonymous和空密码登入  
更多选项[参见这里][0]  

[0]:https://www.centos.org/docs/5/html/Deployment_Guide-en-US/s1-ftp-vsftpd-conf.html
