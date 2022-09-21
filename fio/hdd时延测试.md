用4k随机读测硬盘的响应时延
```
[SDS_Admin@node61 wsh]$ sudo fio fio.wsh
hdd_randread_test: (g=0): rw=randread, bs=4K-4K/4K-4K/4K-4K, ioengine=libaio, iodepth=1
fio-2.2.10
Starting 1 process
Jobs: 1 (f=1): [r(1)] [99.6% done] [6268KB/0KB/0KB /s] [1567/0/0 iops] [eta 00m:04s]
hdd_randread_test: (groupid=0, jobs=1): err= 0: pid=1487324: Tue Sep 20 17:15:50 2022
  read : io=1024.0MB, bw=1063.9KB/s, iops=265, runt=985640msec
    slat (usec): min=4, max=231, avg=13.67, stdev= 4.75
    clat (usec): min=28, max=33730, avg=3742.16, stdev=2240.90
     lat (usec): min=33, max=33741, avg=3756.14, stdev=2241.16
    clat percentiles (usec):
     |  1.00th=[  137],  5.00th=[  828], 10.00th=[ 1160], 20.00th=[ 1752],
     | 30.00th=[ 2352], 40.00th=[ 2992], 50.00th=[ 3568], 60.00th=[ 4192],
     | 70.00th=[ 4832], 80.00th=[ 5472], 90.00th=[ 6112], 95.00th=[ 6432],
     | 99.00th=[11328], 99.50th=[11712], 99.90th=[15040], 99.95th=[17024],
     | 99.99th=[22912]
    bw (KB  /s): min=  712, max=11224, per=100.00%, avg=1064.39, stdev=327.43
    lat (usec) : 50=0.21%, 100=0.01%, 250=3.46%, 500=0.07%, 750=0.58%
    lat (usec) : 1000=3.16%
    lat (msec) : 2=16.45%, 4=32.95%, 10=40.20%, 20=2.88%, 50=0.02%
  cpu          : usr=0.19%, sys=0.47%, ctx=262159, majf=0, minf=55
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued    : total=r=262144/w=0/d=0, short=r=0/w=0/d=0, drop=r=0/w=0/d=0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
   READ: io=1024.0MB, aggrb=1063KB/s, minb=1063KB/s, maxb=1063KB/s, mint=985640msec, maxt=985640msec

Disk stats (read/write):
  sdb: ios=261419/429, merge=0/197, ticks=957237/2509, in_queue=959747, util=98.14%
```
从这个输出，我们可以得到以下结论：

#### 带宽的计算
带宽的bw=1063.9KB/s 就是4k乘iops 265，这个都是成立的。

#### 我们怎么从数据角度看到iodepth是1
一共下发的io是1G/4k=256K(262144)个，运行了985640（ms），所以如果是串行执行，那么一个op的时间是3.76ms（985640/262144）
如果一个op实际的实行时间约等于这个值，那么就是串行的，如果大于这个值，就说明是异步并发的，但是我们看到总的平均时延是3756us，所以是串行的。
```
lat (usec): min=33, max=33741, avg=3756.14, stdev=2241.16
```
#### HDD的磁盘io时延
平均3毫秒，最大33毫秒

#### iodepth = 10， iops = 816, 大概是iodepth=1的3倍
```
[SDS_Admin@node61 wsh]$ sudo fio wsh_4k_randread.fio
hdd_randread_test: (g=0): rw=randread, bs=4K-4K/4K-4K/4K-4K, ioengine=libaio, iodepth=10
fio-2.2.10
Starting 1 process
Jobs: 1 (f=1): [r(1)] [99.4% done] [7060KB/0KB/0KB /s] [1765/0/0 iops] [eta 00m:02s]
hdd_randread_test: (groupid=0, jobs=1): err= 0: pid=943716: Tue Sep 20 21:58:51 2022
  read : io=1024.0MB, bw=3265.8KB/s, iops=816, runt=321087msec
    slat (usec): min=3, max=244, avg=10.99, stdev= 4.61
    clat (usec): min=98, max=325347, avg=12234.38, stdev=13500.72
     lat (usec): min=103, max=325364, avg=12245.61, stdev=13500.75
    clat percentiles (usec):
     |  1.00th=[  207],  5.00th=[ 1304], 10.00th=[ 1944], 20.00th=[ 3152],
     | 30.00th=[ 4384], 40.00th=[ 5664], 50.00th=[ 7328], 60.00th=[10176],
     | 70.00th=[13376], 80.00th=[18560], 90.00th=[28544], 95.00th=[39168],
     | 99.00th=[65280], 99.50th=[76288], 99.90th=[103936], 99.95th=[118272],
     | 99.99th=[146432]
    bw (KB  /s): min= 1872, max= 9457, per=99.74%, avg=3256.46, stdev=411.28
    lat (usec) : 100=0.01%, 250=1.24%, 500=0.41%, 750=0.27%, 1000=0.98%
    lat (msec) : 2=7.53%, 4=16.38%, 10=32.51%, 20=22.49%, 50=15.66%
    lat (msec) : 100=2.40%, 250=0.12%, 500=0.01%
  cpu          : usr=0.47%, sys=1.22%, ctx=252579, majf=0, minf=85
  IO depths    : 1=0.1%, 2=0.1%, 4=0.1%, 8=100.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.1%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued    : total=r=262144/w=0/d=0, short=r=0/w=0/d=0, drop=r=0/w=0/d=0
     latency   : target=0, window=0, percentile=100.00%, depth=10

Run status group 0 (all jobs):
   READ: io=1024.0MB, aggrb=3265KB/s, minb=3265KB/s, maxb=3265KB/s, mint=321087msec, maxt=321087msec

Disk stats (read/write):
  sdc: ios=261919/136, merge=0/63, ticks=3163503/5252, in_queue=3168755, util=99.64%
```


#### numjobs = 10, iops = 825, 大概是numjobs=1的3倍
```
hdd_randread_test: (g=0): rw=randread, bs=4K-4K/4K-4K/4K-4K, ioengine=libaio, iodepth=1
...
fio-2.2.10
Starting 10 processes
Jobs: 1 (f=1): [_(1),r(1),_(8)] [99.7% done] [5272KB/0KB/0KB /s] [1318/0/0 iops] [eta 00m:09s]
hdd_randread_test: (groupid=0, jobs=10): err= 0: pid=3467143: Tue Sep 20 23:08:55 2022
  read : io=10240MB, bw=3297.8KB/s, iops=824, runt=3179734msec
    slat (usec): min=4, max=1699, avg=13.97, stdev= 4.97
    clat (usec): min=3, max=264506, avg=12088.42, stdev=13493.10
     lat (usec): min=33, max=264521, avg=12102.69, stdev=13493.14
    clat percentiles (usec):
     |  1.00th=[  149],  5.00th=[ 1304], 10.00th=[ 1928], 20.00th=[ 3120],
     | 30.00th=[ 4320], 40.00th=[ 5536], 50.00th=[ 7072], 60.00th=[ 9920],
     | 70.00th=[12992], 80.00th=[18304], 90.00th=[28288], 95.00th=[39168],
     | 99.00th=[65280], 99.50th=[77312], 99.90th=[105984], 99.95th=[118272],
     | 99.99th=[148480]
    bw (KB  /s): min=  111, max= 5184, per=10.02%, avg=330.27, stdev=77.57
    lat (usec) : 4=0.01%, 10=0.01%, 50=0.01%, 100=0.01%, 250=1.60%
    lat (usec) : 500=0.15%, 750=0.18%, 1000=0.97%
    lat (msec) : 2=7.67%, 4=16.70%, 10=33.00%, 20=21.82%, 50=15.38%
    lat (msec) : 100=2.38%, 250=0.14%, 500=0.01%
  cpu          : usr=0.07%, sys=0.15%, ctx=2621630, majf=0, minf=390
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued    : total=r=2621440/w=0/d=0, short=r=0/w=0/d=0, drop=r=0/w=0/d=0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
   READ: io=10240MB, aggrb=3297KB/s, minb=3297KB/s, maxb=3297KB/s, mint=3179734msec, maxt=3179734msec

Disk stats (read/write):
  sdb: ios=2621164/1357, merge=0/627, ticks=31451149/52276, in_queue=31503425, util=99.69%
```

