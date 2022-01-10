#### -m parameter
the -m specify the master ip fo the slaves like:
```
19:09:08.413 Starting slave: ssh 182.200.21.61 -l root /root/wshutils/vdbench50403/vdbench SlaveJvm
  -m 172.16.21.60 -n 182.200.21.61-10-220110-19.09.08.223 -l hd1-0 -p 5570
```
now, how the `172.16.21.60` got when vdbench launched? I think it is:
```
ping $(hostname)
```
and which ip should be using in hostname if the host has multi-interfaces?

#### the /etc/nsswitch.conf
```
hosts: files dns myhostname
```
nsswitch: Name Service Switch config file is used by the GUU C library to determinie the sources from 
which to obtain name-service information in a range or catgories, adn in what order.

ref to nss-myhostname:
```
The local, configured hostname is resolved to all locally configured IP addresses ordered by their scope,
or — if none are configured — the IPv4 address 127.0.0.2 (which is on the local loopback) and the IPv6 address ::1 (which is the local host).
```
