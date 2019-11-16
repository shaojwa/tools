#### .bashrc 和 .bash_profile的区别

centos系统的home目录下有.bashrc 和 .bash_profile 两个文件，而且.bash_profile会包含并先执行.bashrc。
同样的，.bashrc 会先执行/etc/bashrc。interactive shell 分为 login shell 以及非 login shell， login shell自然就是等入时候的shell，而之后启动的bash就是non-login shell。
login shell 会执行.bash_profile, 而 非login-shell只会执行.bashrc, 所以不需要每次bash都运行的配置可以放到.bash_profile里。
