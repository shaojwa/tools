#### 基本原理
`-v`参数表示激活 data validation，每一个block的写入都会记录，然后下次针对这个block的read时，就会去校验这个block中的内容。
而针对这个block的写入会导致，写入前的读取并数据校验。所以，不管读还是写，都会触发校验，如果是写么，就会插入一个读操作，因为这个是数据校验需要的。

#### `-vr`参数
这个参数的意思是，每次写入之后，马上进行读取，正常情况下（`-v`参数都是等待下次读写才会触发数据校验）。

比如，是针对大卷的IO场景，那么一个block再次被引用的时间可能需要很久，这个时候就会常常用`-vr`参数来进行快速校验。

#### `-vt`参数
除了`vr`参数之外，还有一个参数是`vt`参数，这个参数的有点是，会在内存中记录最后一次成功读写的时间戳。
这样的好处是，当校验失败的时候就会显示出这个时间，这就有助于我们定位出是什么事件导致的问题。

#### validate的开启方式
还可以用`validate=yes`的方式打开。

#### `-j`参数
这个参数的作用是，让一致性校验过程可以继续下去，即使vdbench或者OS操作系统挂掉。这个参数会创建出一个新的日志对象，

#### 注意事项
`vr`参数的马上读取，可能会有这种问题，数据只是到了存储控制器缓存（storage controller cache），而并没有落盘。

#### 我们要注意data_errors的错误值

#### 每个扇区的第0x1c-0x1f
这是当时写入这个扇区的Process-id，这个才某些情况下非常有用。

#### 什么是data block 和 key block
Data block，就是一个xfersize大小的数据块，key block就是用户指定的最小的xfersize单元，这个是data validate真正跟踪的单元。

#### 错误信息理解
```
Block lba: 0xa7d8bfd000; sector lba: 0xa7d8c00000; Key block size: 17408; 
        relative sector in data block: 0x18 (24); current pid: 3677954 (0x381f02)
        ===> Compression pattern miscompare.
0x000   000000a7 d8c00000 ........ ........   000000a7 d8c00000 00000180 c142f8df
0x010   01..0000 20316473 20202020 00000000   015b0000 20316473 20202020 00381f02
```
针对这个错误，我们看到这里一共是32字节的数据，每一排16个字节，每一段4个字节。左边是个字节是，希望读取到的数据，后面是实际读取到的数据。
我们逐个说明下：
````
00-07字节：000000a7 d8c00000 这两个字节是磁盘块的字节偏移，所以可以知道是0xa7d8c00000, 这个就是sector lba，及时扇区的起始地址。
08-15字节：这部分在实际情况下写的时间搓，所以无法预期，显示........，实际值是 00000180 c142f8df，就是0xc142f8df，从1970年1月1日开始的微秒数。
计算得到是1652509833439所以是2022年5月14日 14:30:33.439(`date --date @1652509833`)，这个是没什么疑问。
10-1b字节：01是date validation key， ..是时间搓的checksum， 0000是保留字节。实际情况是015b0000。
20316473是 "空格1ds空格空格空格"，这个是vdbench脚本中sd的名字，实际运行的sd名称是sd1，到这里也没问题。
1c-3f字节：写入的进程号，实际情况是0x00381f02=3677954，这些信息在errorlog中其实都有。
```

#### 使用场景
首先数据校验是不应该在性能测试中使用的，因为数据校验的CPU开销会影响到性能结果。

#### 为什么要数据，我可以对整个文件进行md5或者类似的校验和进行校验？
首先，用校验和的方式，从某种意义上是顺序的数据传输（复制文件是顺序写入）。如果针对随机IO的情况是否一定正确呢？不一定。

其次，校验和的方式是事后的，整个写完了之后进行整体读取计算，但是我们不知道错在什么位置。我们也不知道错误的数据的最后正确的时间是什么。


#### 校验数据是在什么位置记录的
校验数据是记录在什么位置的，比如我写入的数据是7k，校验数据加上之后就会超过7k，如果输随机写入，这个校验数据记录在什么为地方？
每次写的数据都会记录在内存表中，每一个扇区都会有一个把8字节的lba，和一个1字节的data-validation-key。
这个data-validation-key是一个从1-126的值，每次写同一个block就会增加1，达到126之后，这个值就会回到1。而0是表示，这个block没有被写过。

这种key的方案，开发出来是为了定位数据丢失，如果一个block被多次写入，但是却没有修改内容。我们没法知道其中一次或者多次write丢失。

当一个block写入一次之后，那么后续的read操作就会进行数据校验，而这一次write之前，也一定会有一次read操作。

从版本50407开始，这个key不再总是从1开始，

内存中会有记录，正对每个xfersize，会有一个one-byte项，所以800G的空间，对于17k的数据块来说，会有800/17=47.059M的校验数据会被分配在内存中。
类似的信息如下：
```
Allocating Data Validation map: 49,344,752 one-byte entries for each 17,408-byte block.
```
或者对于xfersize为4M的总容量为1T的数据来说是：
```
17:26:14.841 localhost-0: Created new mmap file: /tmp/vdbench.pid1745048.sd1.mmap.0 mmap size: 256k
17:26:14.842 localhost-0: Allocating Data Validation map: 262,144 one-byte entries for each 4,194,304-byte block.
17:26:14.842 localhost-0: Created new DV map: sd1 size: 1,099,511,627,776 bytes; key block size: 4194304; entries: 262,144
```
对于xfersize为8K的总容量为900G的数据来说是：
```
17:26:02.036 localhost-0: Created new mmap file: /tmp/vdbench.pid1743770.sd1.mmap.0 mmap size: 112.500m
17:26:02.037 localhost-0: Allocating Data Validation map: 117,964,800 one-byte entries for each 8,192-byte block.
17:26:02.037 localhost-0: Created new DV map: sd1 size: 966,367,641,600 bytes; key block size: 8192; entries: 117,964,800
```
