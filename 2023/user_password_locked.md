```
[root@node80 wsh]# passwd -S wsh
wsh PS 2022-04-13 0 99999 7 -1 (Password set, SHA512 crypt.)

[root@node80 wsh]# passwd -l wsh
Locking password for user wsh.
passwd: Success

[root@node80 wsh]# passwd -S wsh
wsh LK 2022-04-13 0 99999 7 -1 (Password locked.)
[root@node80 wsh]#
```
