#### sample1
```
# step 1: Host Definition
# hd is used in multi-vdbench instance
# hd=default,vdbench=./vdbench,user=root,shell=ssh
# hd=hd1,system=192.169.84.11
# hd=hd2,system=192.169.84.12

# step 2: FileSystem Definition, non-default fsd is required.
fsd=fsd1,anchor=/mnt/vdbench,depth=1,width=100,files=50,size=64k,shared=yes

# step 3: Filesytem Workload Definition, non-default fwd is required.
#fwd=format,xfersize=(32k,30,8k,30,4k,40),threads=64
#fwd=default,xfersize=(32k,30,8k,30,4k,40),fileio=random,fileselect=random,rdpct=60,threads=64
#fwd=fwd1,fsd=fsd1
#fwd=fwd1,fsd=fsd1,host=hd1
#fwd=fwd2,fsd=fsd1,host=hd2
fwd=fwd1,fsd=fsd1,xfersize=(32k,30,8k,30,4k,40),fileio=random,fileselect=random,rdpct=60,threads=64

# step 4: Run Definition
rd=rd1,fwd=fwd*,fwdrate=max,format=restart,elapsed=600,interval=1
```

#### sample2
```
messagescan=no
hd=default,vdbench=/root/vdbench50406,user=root,shell=ssh
hd=hd1,system=55.55.56.223
hd=hd2,system=55.55.56.224
hd=hd3,system=55.55.56.43
hd=hd4,system=55.55.56.44
hd=hd5,system=55.55.56.88

fsd=fsd1,anchor=/mnt/opm,depth=1,width=1000,files=2000,size=32k,shared=yes
fwd=fwd1,fsd=fsd1,xfersize=32k,operation=create,threads=1
rd=rd1,fwd=fwd*,fwdrate=max,format=(restart,only),elapsed=10,interval=1
```
