1. install server

```
bash <(curl -L -s https://install.direct/go.sh)
```

2. check service status

```
[root@li984-80 ~]# systemctl status v2ray
● v2ray.service - V2Ray Service
   Loaded: loaded (/etc/systemd/system/v2ray.service; enabled; vendor preset: disabled)
   Active: inactive (dead)
```

3. start service
```
[root@li984-80 ~]# systemctl status v2ray
● v2ray.service - V2Ray Service
   Loaded: loaded (/etc/systemd/system/v2ray.service; enabled; vendor preset: disabled)
   Active: active (running) since Mon 2020-03-16 14:31:49 UTC; 7s ago
 Main PID: 11406 (v2ray)
   CGroup: /system.slice/v2ray.service
           └─11406 /usr/bin/v2ray/v2ray -config /etc/v2ray/config.json
```
