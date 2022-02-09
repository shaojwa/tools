```
# equals yes
PermitRootLogin yes
PermitRootLogin no

# equals no
PermitRootLogin no
PermitRootLogin yes
```
WHY? SEE HERE:[duplicate-setting](https://serverfault.com/questions/673013/can-i-overwrite-a-setting-within-sshd-config-with-a-duplicate-setting)
for the latest version of sshd, the manual of sshd_config saying that. to override the setting, we can use a match-block:
```
Match User root
      PermitRootLogin no
```
