因为/etc/pam.d/su文件下有这一行，去掉就可以解决问题：

    account         requisite       pam_deny.so
