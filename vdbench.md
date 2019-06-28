
#### 常用方式
HD(host definitions)	主机定义	一般只会在多主机测试场景下才用。
  * system	主机ip或者网络主机名。
	* shell	其实就是远程主机可以提供的连接方式。一般都是ssh。
SD(storage definition)	存储定义	
WD(workload definition)	工作负载定义
FSD(filesystem definition) 	定义文件系统目录文件结构。	包括fsd_name，参数包括，路径，深度，广度，文件数，文件大小。
FWD(filesystem workload definition) 	文件系统工作负载定义。	文件系统测试一般用FWD，而不是WD。fwd依赖fsd，包括fwd_name，定义读写方式，xfersize（数据传输大小），顺序还是随机，文件选择方式等。
	* fwd=name	如果是default，那么该配置会当做默认配置被所有下面第你故意的fwd使用。
	* xfersize	读写传输文件大小，默认128k。
RD	run definitions	rd依赖fwd
	* format=yes	format=yes（目录层次的完全创建以及所有文件的初始化，会先删除当前的文件节后，然后重建文件结构，然后才会运行需要的RD）
  * format=restart（只会生成缺少的文件以及扩展大小不足的文件，但是并不会创建目录结构）
  
#### bugs	留意文件总共的大小，不能过大，否者vdbench起不来。
