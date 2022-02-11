```
systemctl restart network
```
失败，应该是network device名字和启动脚本不一致。那么`ip link` 中显示的名字是从什么地方读取的？
