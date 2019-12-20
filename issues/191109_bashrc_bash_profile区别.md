
#### shell 分类

四类:

```
interactive login shell
// 用户登入时

interactive not-login shell
// su 用户
// 登入后运行bash


non-interactively with --login
//

non-interactively
// 比如执行脚本时

```

#### .bashrc 还是 .bash_profile


```
//
interactive login shell
/etc/profile
~/.bash_profile
~/.bash_login
~/.profile


//
interactive not-login shell
~/.bashrc


// 
non-interactively with --login
/etc/profile
~/.bash_profile
~/.bash_login
~/.profile

non-interactively

```

#### 脚本包含关系

```
.bash_profile
-> .bashrc
-> /etc/bashrc
```

#### 实例

* wsh 登入：

```
run /home/wsh/.bash_profile
run /home/wsh/.bashrc
run /etc/bashrc
```

* wsh 登入后 su

```
run /root/.bashrc
run /etc/bashrc
```


* root 登入：
```
run /root/.bash_profile
run /root/.bashrc
run /etc/bashrc
```

* root 登入后 su wsh

```
run /home/wsh/.bashrc
run /etc/bashrc
```
