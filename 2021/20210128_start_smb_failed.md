```
$ systemctl status smb.service
● smb.service - Samba SMB Daemon
   Loaded: loaded (/usr/lib/systemd/system/smb.service; enabled; vendor preset: disabled)
   Active: failed (Result: exit-code) since Thu 2021-01-28 22:27:45 CST; 22s ago
     Docs: man:smbd(8)
           man:samba(7)
           man:smb.conf(5)
  Process: 206274 ExecStart=/usr/sbin/smbd --foreground --no-process-group $SMBDOPTIONS (code=exited, status=1/FAILURE)
 Main PID: 206274 (code=exited, status=1/FAILURE)

Jan 28 22:27:45 node32 systemd[1]: Starting Samba SMB Daemon...
Jan 28 22:27:45 node32 smbd[206274]: /usr/sbin/smbd: /usr/local/lib/libldb.so.1: version `LDB_1.3.0' not found (required by /usr/li...mba4.so)
Jan 28 22:27:45 node32 smbd[206274]: /usr/sbin/smbd: /usr/local/lib/libldb.so.1: version `LDB_1.1.30' not found (required by /usr/l...mba4.so)
Jan 28 22:27:45 node32 systemd[1]: smb.service: main process exited, code=exited, status=1/FAILURE
Jan 28 22:27:45 node32 systemd[1]: Failed to start Samba SMB Daemon.
Jan 28 22:27:45 node32 systemd[1]: Unit smb.service entered failed state.
Jan 28 22:27:45 node32 systemd[1]: smb.service failed.
Hint: Some lines were ellipsized, use -l to show in full.
```
