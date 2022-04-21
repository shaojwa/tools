#### openflags
这个参数可以用在很多定义中，包括SD/FSD/WD/FWD/RD中。

如果是在FSD中使用，就是在创建文件结构时，设置如何打开文件，这对于写入有明显的影响。

如果是在FWD中定义，openflags=o_direct，那就是在跑负载的时候，比如写入的时候IO的模式。
其实就算在WD或者FSD中使用，这个参数也是在 打开文件的时候设置，write本身没有这个选项。
vdbench的手册也说明，这个只是open和close接口调用时的参数。
