```
sudo gzip -c dse.debug > dse.debug.gz
```
will fail because the `>`(the current bash actually) has no permission to write to current directory.
solving this problem as following:
```
sudo bash -c "gzip -c dse.debug > dse.debug.gz"
```
or
```
sudo bash -c 'gzip -c dse.debug > dse.debug.gz'
```
