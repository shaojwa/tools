1. install server

```
bash <(curl -L -s https://install.direct/go.sh)
```

2. check service status

```
[root@li984-80 ~]# systemctl status v2ray
v2ray.service - V2Ray Service
   Loaded: loaded (/etc/systemd/system/v2ray.service; enabled; vendor preset: disabled)
   Active: inactive (dead)
```

3. start service
```
[root@li984-80 ~]# systemctl status v2ray
v2ray.service - V2Ray Service
   Loaded: loaded (/etc/systemd/system/v2ray.service; enabled; vendor preset: disabled)
   Active: active (running) since Mon 2020-03-16 14:31:49 UTC; 7s ago
 Main PID: 11406 (v2ray)
   CGroup: /system.slice/v2ray.service
           └─11406 /usr/bin/v2ray/v2ray -config /etc/v2ray/config.json
```

4. check firewall

```
$ service firewalld status
firewalld.service - firewalld - dynamic firewall daemon
   Loaded: loaded (/usr/lib/systemd/system/firewalld.service; enabled; vendor preset: enabled)
   Active: active (running) since Mon 2019-10-21 08:21:37 UTC; 4 months 25 days ago
     Docs: man:firewalld(1)
 Main PID: 549 (firewalld)
   CGroup: /system.slice/firewalld.service
           └─549 /usr/bin/python -Es /usr/sbin/firewalld --nofork --nopid
```

5. allow port

```
firewall-cmd  --add-port=46600/tcp --permanent
```

