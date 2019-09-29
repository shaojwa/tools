162 上打开了防火墙，需要关闭firewalld： systemctl stop firewalld。因为firewalld服务默认是启动的（可以通过 systemctl status firewalld 看到 enabled）。要关闭服务自动启动，可以运行 systemctl disable firewalld
