4k随机读，iops是15365，hdd是265，差不多50倍，平均时延是：63微妙，是HDD的1/50
```
[SDS_Admin@node61 wsh]$ sudo fio wsh_4k_randread.fio
hdd_randread_test: (g=0): rw=randread, bs=4K-4K/4K-4K/4K-4K, ioengine=libaio, iodepth=1
fio-2.2.10
Starting 1 process
Jobs: 1 (f=1): [r(1)] [100.0% done] [63272KB/0KB/0KB /s] [15.9K/0/0 iops] [eta 00m:00s]
hdd_randread_test: (groupid=0, jobs=1): err= 0: pid=1715567: Tue Sep 20 22:00:38 2022
  read : io=1024.0MB, bw=61460KB/s, iops=15365, runt= 17061msec
    slat (usec): min=4, max=218, avg= 6.24, stdev= 2.61
    clat (usec): min=3, max=10994, avg=57.33, stdev=151.94
     lat (usec): min=47, max=10999, avg=63.70, stdev=152.00
    clat percentiles (usec):
     |  1.00th=[   44],  5.00th=[   45], 10.00th=[   46], 20.00th=[   47],
     | 30.00th=[   48], 40.00th=[   48], 50.00th=[   49], 60.00th=[   49],
     | 70.00th=[   50], 80.00th=[   51], 90.00th=[   55], 95.00th=[   68],
     | 99.00th=[  177], 99.50th=[  209], 99.90th=[  940], 99.95th=[ 2640],
     | 99.99th=[ 8384]
    bw (KB  /s): min=55728, max=65880, per=100.00%, avg=61459.71, stdev=2937.87
    lat (usec) : 4=0.01%, 10=0.01%, 20=0.01%, 50=62.23%, 100=34.42%
    lat (usec) : 250=3.15%, 500=0.06%, 750=0.02%, 1000=0.03%
    lat (msec) : 2=0.03%, 4=0.02%, 10=0.03%, 20=0.01%
  cpu          : usr=4.31%, sys=13.62%, ctx=262146, majf=0, minf=34
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued    : total=r=262144/w=0/d=0, short=r=0/w=0/d=0, drop=r=0/w=0/d=0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
   READ: io=1024.0MB, aggrb=61460KB/s, minb=61460KB/s, maxb=61460KB/s, mint=17061msec, maxt=17061msec

Disk stats (read/write):
  sdt: ios=259385/23, merge=0/4, ticks=14323/2, in_queue=14325, util=97.16%
```
17061 ms 和 16698ms（ = 262144 * 63.70）相差不多
