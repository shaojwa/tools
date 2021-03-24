#### Memcheck 原理

Memcheck 能够检测出内存问题，关键在于其建立了两个全局表Valid-Address map（A表），valid-value map（V表）。 

首先是Valid-Address map，当程序往一个地址读写数据时，通过地址从A表中查找，判断那个地址是否可读写，如果不可写就报错。
其次，当内存中的一个字节被加载到真实的CPU中时，对应的V-bit也会加载到虚拟的core中，如果读写一个内存时，V表中的标记该值为未初始化时，memcheck就会报错。
