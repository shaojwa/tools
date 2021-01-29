#### update

update的是包，包更新。更新包的时候，yum会保证包所有的依赖都要已经满足。如果匹配到的包没有安装，那么yum并不会安装这个包。这是很重要的一点。

#### upgrade

upgrade = update --obsoletes, 也就是upgrade会把旧的包丢弃，而update不会（其实默认配置下，update也会丢弃，因为/etc/yum/yum.conf中的配置项obsoletes=1）
