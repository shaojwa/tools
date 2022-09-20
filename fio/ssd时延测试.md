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

#### iodepth调整为10，iops提高到47387, 提高3倍
```
[SDS_Admin@node61 wsh]$ sudo fio wsh_4k_randread.fio
hdd_randread_test: (g=0): rw=randread, bs=4K-4K/4K-4K/4K-4K, ioengine=libaio, iodepth=10
fio-2.2.10
Starting 1 process
Jobs: 1 (f=1): [r(1)] [100.0% done] [184.3MB/0KB/0KB /s] [47.2K/0/0 iops] [eta 00m:00s]
hdd_randread_test: (groupid=0, jobs=1): err= 0: pid=2410045: Tue Sep 20 22:06:37 2022
  read : io=1024.0MB, bw=189513KB/s, iops=47378, runt=  5533msec
    slat (usec): min=3, max=277, avg= 5.30, stdev= 2.40
    clat (usec): min=41, max=11249, avg=204.64, stdev=260.70
     lat (usec): min=48, max=11254, avg=210.06, stdev=260.69
    clat percentiles (usec):
     |  1.00th=[   71],  5.00th=[  151], 10.00th=[  171], 20.00th=[  183],
     | 30.00th=[  187], 40.00th=[  193], 50.00th=[  195], 60.00th=[  197],
     | 70.00th=[  199], 80.00th=[  201], 90.00th=[  207], 95.00th=[  225],
     | 99.00th=[  354], 99.50th=[  458], 99.90th=[ 4768], 99.95th=[ 6240],
     | 99.99th=[10560]
    bw (KB  /s): min=174840, max=196424, per=100.00%, avg=189529.91, stdev=6696.77
    lat (usec) : 50=0.24%, 100=1.83%, 250=94.05%, 500=3.40%, 750=0.07%
    lat (usec) : 1000=0.05%
    lat (msec) : 2=0.13%, 4=0.08%, 10=0.11%, 20=0.02%
  cpu          : usr=10.27%, sys=35.00%, ctx=209839, majf=0, minf=77
  IO depths    : 1=0.1%, 2=0.1%, 4=0.1%, 8=100.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.1%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued    : total=r=262144/w=0/d=0, short=r=0/w=0/d=0, drop=r=0/w=0/d=0
     latency   : target=0, window=0, percentile=100.00%, depth=10

Run status group 0 (all jobs):
   READ: io=1024.0MB, aggrb=189513KB/s, minb=189513KB/s, maxb=189513KB/s, mint=5533msec, maxt=5533msec

Disk stats (read/write):
  sdt: ios=255037/13, merge=0/2, ticks=49967/3, in_queue=49970, util=96.08%
```
#### numjobs设置为10,iops和iodepth=10上差不多
```
[SDS_Admin@node61 wsh]$ sudo fio wsh_4k_randread.fio
hdd_randread_test: (g=0): rw=randread, bs=4K-4K/4K-4K/4K-4K, ioengine=libaio, iodepth=1
...
fio-2.2.10
Starting 10 processes
Jobs: 6 (f=6): [r(3),_(2),r(1),_(2),r(2)] [100.0% done] [192.6MB/0KB/0KB /s] [49.3K/0/0 iops] [eta 00m:00s]
hdd_randread_test: (groupid=0, jobs=10): err= 0: pid=2812665: Tue Sep 20 22:11:00 2022
  read : io=10240MB, bw=196683KB/s, iops=49170, runt= 53313msec
    slat (usec): min=4, max=264, avg= 7.64, stdev= 3.08
    clat (usec): min=1, max=29629, avg=192.71, stdev=410.84
     lat (usec): min=48, max=29637, avg=200.48, stdev=410.90
    clat percentiles (usec):
     |  1.00th=[   62],  5.00th=[   96], 10.00th=[  115], 20.00th=[  143],
     | 30.00th=[  155], 40.00th=[  167], 50.00th=[  175], 60.00th=[  181],
     | 70.00th=[  189], 80.00th=[  193], 90.00th=[  199], 95.00th=[  211],
     | 99.00th=[  350], 99.50th=[ 1080], 99.90th=[ 8160], 99.95th=[10304],
     | 99.99th=[10944]
    bw (KB  /s): min=10344, max=29896, per=10.03%, avg=19730.85, stdev=1583.97
    lat (usec) : 2=0.01%, 10=0.01%, 20=0.01%, 50=0.21%, 100=5.45%
    lat (usec) : 250=90.98%, 500=2.69%, 750=0.09%, 1000=0.07%
    lat (msec) : 2=0.14%, 4=0.13%, 10=0.19%, 20=0.06%, 50=0.01%
  cpu          : usr=1.75%, sys=5.22%, ctx=2621655, majf=0, minf=266
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued    : total=r=2621440/w=0/d=0, short=r=0/w=0/d=0, drop=r=0/w=0/d=0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
   READ: io=10240MB, aggrb=196682KB/s, minb=196682KB/s, maxb=196682KB/s, mint=53313msec, maxt=53313msec

Disk stats (read/write):
  sdt: ios=2618552/47, merge=0/11, ticks=450239/9, in_queue=450248, util=99.87%
```
