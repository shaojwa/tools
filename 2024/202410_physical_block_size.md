```
[wsh]$ cat /sys/block/nvme0n1/queue/physical_block_size
512
[wsh]$ sudo blockdev --getpbsz /dev/nvme0n1
512
[wsh]$  lsblk -o NAME,PHY-SEC | grep nvme0n1
nvme0n1          512
```
