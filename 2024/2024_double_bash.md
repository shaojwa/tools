because of the while-loop with sub-command to run like this:
```
#!/bin/bash
while true; do
  osd_down_list=$(ceph osd tree down | grep dcache)
done
```
