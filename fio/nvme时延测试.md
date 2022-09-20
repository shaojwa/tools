平均时延9微妙，iops10万（104702）
```
[SDS_Admin@node80 wsh]$ sudo fio wsh_4k_randread.fio
hdd_randread_test: (g=0): rw=randread, bs=4K-4K/4K-4K/4K-4K, ioengine=libaio, iodepth=1
fio-2.2.10
Starting 1 process
Jobs: 1 (f=1): [r(1)] [100.0% done] [420.4MB/0KB/0KB /s] [108K/0/0 iops] [eta 00m:00s]
hdd_randread_test: (groupid=0, jobs=1): err= 0: pid=3287458: Tue Sep 20 21:51:44 2022
  read : io=10240MB, bw=418811KB/s, iops=104702, runt= 25037msec
    slat (usec): min=1, max=199, avg= 1.52, stdev= 0.63
    clat (usec): min=0, max=2564, avg= 7.41, stdev= 7.10
     lat (usec): min=6, max=2566, avg= 9.00, stdev= 7.12
    clat percentiles (usec):
     |  1.00th=[    6],  5.00th=[    6], 10.00th=[    6], 20.00th=[    7],
     | 30.00th=[    7], 40.00th=[    7], 50.00th=[    7], 60.00th=[    7],
     | 70.00th=[    7], 80.00th=[    7], 90.00th=[    7], 95.00th=[    8],
     | 99.00th=[   11], 99.50th=[   53], 99.90th=[  108], 99.95th=[  149],
     | 99.99th=[  151]
    bw (KB  /s): min=392216, max=439072, per=99.99%, avg=418776.80, stdev=7784.02
    lat (usec) : 2=0.01%, 4=0.01%, 10=98.79%, 20=0.54%, 50=0.09%
    lat (usec) : 100=0.35%, 250=0.21%, 500=0.01%, 750=0.01%, 1000=0.01%
    lat (msec) : 2=0.01%, 4=0.01%
  cpu          : usr=14.58%, sys=28.49%, ctx=2620894, majf=0, minf=112
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued    : total=r=2621440/w=0/d=0, short=r=0/w=0/d=0, drop=r=0/w=0/d=0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
   READ: io=10240MB, aggrb=418810KB/s, minb=418810KB/s, maxb=418810KB/s, mint=25037msec, maxt=25037msec

Disk stats (read/write):
  nvme0n1: ios=2606874/16, merge=0/0, ticks=17387/1, in_queue=17388, util=99.66%
```
