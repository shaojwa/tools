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
#### iodepth = 10, iops提高 3倍
```
[SDS_Admin@node80 wsh]$ sudo fio wsh_4k_randread.fio
hdd_randread_test: (g=0): rw=randread, bs=4K-4K/4K-4K/4K-4K, ioengine=libaio, iodepth=10
fio-2.2.10
Starting 1 process
Jobs: 1 (f=1): [r(1)] [100.0% done] [1240MB/0KB/0KB /s] [317K/0/0 iops] [eta 00m:00s]
hdd_randread_test: (groupid=0, jobs=1): err= 0: pid=3376004: Tue Sep 20 21:56:27 2022
  read : io=10240MB, bw=1254.7MB/s, iops=321176, runt=  8162msec
    slat (usec): min=1, max=114, avg= 2.08, stdev= 0.91
    clat (usec): min=6, max=2623, avg=28.42, stdev= 7.87
     lat (usec): min=8, max=2626, avg=30.60, stdev= 7.94
    clat percentiles (usec):
     |  1.00th=[   23],  5.00th=[   24], 10.00th=[   25], 20.00th=[   27],
     | 30.00th=[   27], 40.00th=[   27], 50.00th=[   28], 60.00th=[   28],
     | 70.00th=[   28], 80.00th=[   29], 90.00th=[   29], 95.00th=[   32],
     | 99.00th=[   44], 99.50th=[   75], 99.90th=[  139], 99.95th=[  169],
     | 99.99th=[  175]
    bw (MB  /s): min= 1169, max= 1281, per=100.00%, avg=1254.69, stdev=33.66
    lat (usec) : 10=0.01%, 20=0.06%, 50=99.25%, 100=0.39%, 250=0.29%
    lat (usec) : 500=0.01%, 1000=0.01%
    lat (msec) : 2=0.01%, 4=0.01%
  cpu          : usr=32.68%, sys=67.32%, ctx=42, majf=0, minf=24
  IO depths    : 1=0.1%, 2=0.1%, 4=0.1%, 8=100.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.1%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued    : total=r=2621440/w=0/d=0, short=r=0/w=0/d=0, drop=r=0/w=0/d=0
     latency   : target=0, window=0, percentile=100.00%, depth=10

Run status group 0 (all jobs):
   READ: io=10240MB, aggrb=1254.7MB/s, minb=1254.7MB/s, maxb=1254.7MB/s, mint=8162msec, maxt=8162msec

Disk stats (read/write):
  nvme0n1: ios=2618202/6, merge=0/0, ticks=18199/0, in_queue=18200, util=99.03%
```

#### numjobs为10时，iops提高7倍，时延从9涨到12
```
[SDS_Admin@node80 wsh]$ sudo fio wsh_4k_randread.fio
hdd_randread_test: (g=0): rw=randread, bs=4K-4K/4K-4K/4K-4K, ioengine=libaio, iodepth=1
...
fio-2.2.10
Starting 10 processes
Jobs: 1 (f=1): [_(8),r(1),_(1)] [100.0% done] [1912MB/0KB/0KB /s] [489K/0/0 iops] [eta 00m:00s]
hdd_randread_test: (groupid=0, jobs=10): err= 0: pid=3425834: Tue Sep 20 21:59:43 2022
  read : io=102400MB, bw=2848.1MB/s, iops=729332, runt= 35943msec
    slat (usec): min=1, max=277, avg= 1.70, stdev= 0.71
    clat (usec): min=0, max=4075, avg=11.12, stdev= 7.91
     lat (usec): min=7, max=4077, avg=12.91, stdev= 7.95
    clat percentiles (usec):
     |  1.00th=[    7],  5.00th=[    8], 10.00th=[    9], 20.00th=[    9],
     | 30.00th=[   10], 40.00th=[   10], 50.00th=[   11], 60.00th=[   11],
     | 70.00th=[   11], 80.00th=[   12], 90.00th=[   12], 95.00th=[   13],
     | 99.00th=[   16], 99.50th=[   61], 99.90th=[  129], 99.95th=[  157],
     | 99.99th=[  165]
    bw (KB  /s): min=253936, max=316288, per=10.10%, avg=294573.36, stdev=13438.59
    lat (usec) : 2=0.01%, 4=0.01%, 10=21.62%, 20=77.65%, 50=0.10%
    lat (usec) : 100=0.41%, 250=0.23%, 500=0.01%, 750=0.01%, 1000=0.01%
    lat (msec) : 2=0.01%, 4=0.01%, 10=0.01%
  cpu          : usr=11.69%, sys=22.17%, ctx=26213158, majf=0, minf=990
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued    : total=r=26214400/w=0/d=0, short=r=0/w=0/d=0, drop=r=0/w=0/d=0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
   READ: io=102400MB, aggrb=2848.1MB/s, minb=2848.1MB/s, maxb=2848.1MB/s, mint=35943msec, maxt=35943msec

Disk stats (read/write):
  nvme0n1: ios=26210593/23, merge=0/0, ticks=271650/1, in_queue=271650, util=99.85%
```
