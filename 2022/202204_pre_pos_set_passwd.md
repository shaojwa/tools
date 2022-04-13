```
[root@node80 yum.repos.d]# passwd -S wsh
wsh LK 2022-04-13 0 99999 7 -1 (Password locked.)
[root@node80 yum.repos.d]# passwd wsh
Changing password for user wsh.
New password:
Retype new password:
passwd: all authentication tokens updated successfully.
[root@node80 yum.repos.d]# passwd -S wsh
wsh PS 2022-04-13 0 99999 7 -1 (Password set, SHA512 crypt.)
[root@node80 yum.repos.d]#
```
