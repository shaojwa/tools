原因是root账户下没有.bashrc文件，使得新的shell没有配置环境变量。
好像su的时候，不会自动去执行/etc/bashrc文件，只会执行的 /root/下的.bashrc文件。
