```
sudo gzip -c dse.debug > dse.debug.gz
```
will fail because the `>`(actully is the current bash) has no permission of writting current directory.
we can solve this problem like this:
```
sudo bash -c "gzip -c dse.debug > dse.debug.gz"
```
