#### iops只有150左右，fio有260
```
messagescan=no
hd=default,user=root,shell=ssh,vdbench=/home/SDS_Admin/wsh/vdbench50403,user=root
hd=hd1,system=182.200.67.61
sd=default,threads=1
sd=sd1,hd=hd1,lun=/dev/sdk,openflags=o_direct
wd=wd1,sd=sd*,seekpct=100,rdpct=100,xfersize=4K
rd=rd1,wd=wd1,iorate=max,elapse=600,maxdata=64M,interval=1
```
threads=1为串行io
```
Sep 21, 2022  interval        i/o   MB/sec   bytes   read     resp     read    write     resp     resp queue  cpu%  cpu%
                             rate  1024**2     i/o    pct     time     resp     resp      max   stddev depth sys+u   sys
23:45:52.077         1      88.00     0.34    4096 100.00    6.255    6.255    0.000   14.493    2.032   0.6  55.5  23.4
23:45:53.008         2     151.00     0.59    4096 100.00    6.484    6.484    0.000   18.441    2.212   1.0  50.4  19.3
23:45:54.011         3     143.00     0.56    4096 100.00    6.947    6.947    0.000   11.271    2.129   1.0  40.5  16.3
23:45:55.006         4     154.00     0.60    4096 100.00    6.484    6.484    0.000   17.057    2.541   1.0  43.1  21.6
23:45:56.048         5     149.00     0.58    4096 100.00    6.725    6.725    0.000   16.053    2.213   1.0  46.7  21.9
23:45:57.011         6     153.00     0.60    4096 100.00    6.557    6.557    0.000   13.278    2.202   1.0  49.8  20.6
23:45:58.006         7     143.00     0.56    4096 100.00    6.939    6.939    0.000   15.224    2.340   1.0  47.3  19.6
23:45:59.047         8     149.00     0.58    4096 100.00    6.698    6.698    0.000   15.668    2.148   1.0  31.7  15.4
23:46:00.005         9     149.00     0.58    4096 100.00    6.666    6.666    0.000   11.334    2.227   1.0  30.9  15.1
23:46:01.005        10     155.00     0.61    4096 100.00    6.475    6.475    0.000   16.490    2.321   1.0  46.1  16.6
```
我们注意到，vdbench的时延有6.ms，fio的话，只有3.5ms。vdbench 的cpu也没满
