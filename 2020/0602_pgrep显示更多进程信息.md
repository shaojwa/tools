pgrep的参数非常有限，网上建议用这种方式：
```
function ppgrep() { pgrep "$@" | xargs --no-run-if-empty ps fp; }
```
