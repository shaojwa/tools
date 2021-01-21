#### 用 ifup eth0 还是 ifconfig up eth0
1. ifup 是通过network-scripts下的脚本配置网络，最终是用ip命令。
1. ifconfig 是和 ip同一层次的命令， ifconfig本身只是配置网络接口，本身不会up网口，ifconfig up才会up。
1. ifup通过运行脚本，所以可以在脚本里配置静态路由等，而ifconfig 不配置。


#### ifconfig

#### 用ifconfig 还是 ip
当然来用ip，ip是新的网络管理命令，man ifconfig 已经明确说这个命令已经obsolete。
