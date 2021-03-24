    iostat -c 1 2 
    iostat -x
 
使用 –x 参数时，最后一列中的 %util表示繁忙程度。

    tps: 每秒的传输数，一个传输就是一个设备的IO请求，多个逻辑请求会合并为一个设备请求。
    rrqm/s: 每秒钟读请求被merge的个数
    wrqm/s: 每秒钟写请求被merge的个数
    r/s: 每秒读请求数目数目
    w/s: 每秒写请求数目数目
    io合并一般是 IOscheduler负责的，把相邻的数据读写合并到一个来提高效率。
    rKb/s: 每秒读千字节数
    wKb/s: 每秒写千字节数
    avgrq-sz: 请求的平均的扇区大小
    avgqu-sz: 请求的平均的队列深度
    await: 每个请求平均的处理时长（单位毫秒），包括排队时间和服务时间
    svctm: 不再可信
    %util: 设备的带宽利用率，即饱和度，繁忙度。

    wait的时间需要注意，这个是磁盘处理时间加上IO排队时间,体现不了硬盘设备的速度。

    要看某一段时间的系统繁忙程度需要加上<interval>
    因为如果不加interval显示的是从系统启动开始到现在的负载
    iostat和sar都是依赖/proc/diskstats
    所以要理解iostat应该从立即/proc/diskstats开始
    注意diskstats中的rd_tick和wr_ticks和io_ticks的区别。
    查看/sys/block/sdx/queue/scheduler可以查看硬盘的调度器。
    %util因为硬盘的并行能力所以即使达到100%也不代表达到饱和。
    文章linuxperf.com/?p=156
    await其实是包括硬盘处理io时间和io请求在kernel队列中的时间。
    但是因为一般说来队列等待时间可以忽略不计。
    所以姑且可以用await来代表硬盘速度。
    一般机械硬盘await是5-10ms。
