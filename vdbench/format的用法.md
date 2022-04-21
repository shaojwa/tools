#### format
这是RD中的参数，指定运行前，针对目录以及文件结构的要求。在执行每一个fwd之前都会先执行这个。

#### format=yes 
// 目录层次的完全创建以及所有文件的初始化，会先删除当前的文件结构，然后重建文件结构，之后再运行需要的RD

#### format=restart
// 只会生成缺少的文件以及扩展大小不足的文件，并不会重新创建目录结构。

#### fwd=format
这是一个特殊的fwd，如果fwd中设置了format=yes，那么，这个fwd开始前，会先执行一个workload，这个 workload就是执行format工作。
而这个工作的是可以这只一些参数的（尽管非常有限，只有threads/xfersize,openflags等等），这些参数的设置就在这个fwd中进行。
