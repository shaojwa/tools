```
grep notify_release_check ceph-dse.engine.20.3.log-2021-01-20-102729
Binary file ceph-dse.engine.20.3.log-2021-01-20-102729 matches
```

```
ceph-dse.engine.20.3.log-2021-01-20-102729: data
```
Presumably the file .bash_history starts with non-text data, hence grep is treating the file as binary. 

###  solution
use grep -a 'pattern'.
