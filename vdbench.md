## master 和 slave
master解析配置，实际执行负载的是slave，master的ip从hostname解析出来。slave的ip我们在配置文件中设置。

## 配置
#### HD 
host definitions，主机定义，一般只会在多主机测试场景下用。
  * system	主机ip或者网络主机名。
  * shell	其实就是远程主机可以提供的连接方式。一般都是ssh。
	
#### SD
storage definition，存储定义

#### WD
workload definition，工作负载定义 

#### FSD
filesystem definition，文件件系统定义

* 括fsd_name，参数包括，路径，深度，广度，文件数，文件大小。

#### FWD
filelesystem workload definition，文件系统工作负载定义，文件系统测试用fwd，不是wd，fwd依赖fsd。
* fwd=name，如果是default，那么该配置会当做默认配置被所有下面第你故意的fwd使用。
* operation
	one of mkdir, rmdir, create, delete, open, close, read, write, access, getattr and setattr
	
* fileio 在文件内怎么IO
	random: 在一个文件内随机IO，不是随机选文件，一个文件只有一个线程访问
	sequential: 在一个文件内顺序IO

* fileselect 怎么选择文件
* xfersize 读写传输文件大小，默认128k。
	
#### RD
run definitions，rd依赖fwd。

* format 格式化

```
format=yes // 目录层次的完全创建以及所有文件的初始化，会先删除当前的文件节后，然后重建文件结构，然后才会运行需要的RD
format=restart // 只会生成缺少的文件以及扩展大小不足的文件，但是并不会创建目录结构
```

#### 样例

```
# step 1: Host Definition
# hd is used in multi-vdbench instance
# hd=default,vdbench=./vdbench,user=root,shell=ssh
# hd=hd1,system=192.169.84.11
# hd=hd2,system=192.169.84.12

# step 2: FileSystem Definition, non-default fsd is required.
fsd=fsd1,anchor=/mnt/vdbench,depth=1,width=100,files=50,size=64k,shared=yes

# step 3: Filesytem Workload Definition, non-default fwd is required.
#fwd=format,xfersize=(32k,30,8k,30,4k,40),threads=64
#fwd=default,xfersize=(32k,30,8k,30,4k,40),fileio=random,fileselect=random,rdpct=60,threads=64
#fwd=fwd1,fsd=fsd1
#fwd=fwd1,fsd=fsd1,host=hd1
#fwd=fwd2,fsd=fsd1,host=hd2
fwd=fwd1,fsd=fsd1,xfersize=(32k,30,8k,30,4k,40),fileio=random,fileselect=random,rdpct=60,threads=64

# step 4: Run Definition
rd=rd1,fwd=fwd*,fwdrate=max,format=restart,elapsed=600,interval=1
```

样例二：
```
messagescan=no
hd=default,vdbench=/root/vdbench50406,user=root,shell=ssh
hd=hd1,system=55.55.56.223
hd=hd2,system=55.55.56.224
hd=hd3,system=55.55.56.43
hd=hd4,system=55.55.56.44
hd=hd5,system=55.55.56.88

fsd=fsd1,anchor=/mnt/opm,depth=1,width=1000,files=2000,size=32k,shared=yes
fwd=fwd1,fsd=fsd1,xfersize=32k,operation=create,threads=1
rd=rd1,fwd=fwd*,fwdrate=max,format=(restart,only),elapsed=10,interval=1
```

## 常见启动失败原因

1. 总文件容量过大，空间不足
2. vdbench脚本中的java路径错误
3. 集群模式，免密没有配置
4. 集群模式，host不通，记得配/etc/hosts文件
