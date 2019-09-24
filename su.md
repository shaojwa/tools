1. su 会新起一个bash进程
2. su 使用PAM进行认证，账户，会话管理。
3. 会终重置 HOME, SHELL, USER，LOGNAME 的环境变量
4. su 的配置在/etc/default/su 和 /etc/login.defs 
5. PAM的配置在 /etc/pam.d/su 和 /etc/pam.d/su-l（如果指定选项 --login）
