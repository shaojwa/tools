```
[wsh@li984-80 ~]$ k=v time echo "hello"
hello
0.00user 0.00system 0:00.00elapsed 0%CPU (0avgtext+0avgdata 1900maxresident)k
80inputs+0outputs (1major+81minor)pagefaults 0swaps
[wsh@li984-80 ~]$ time echo "hello"
hello

real    0m0.000s
user    0m0.000s
sys     0m0.000s
```
`k=v` makes the execution of time runing with the binary of `/usr/bin/time`
it looks that `k=v` make the implicit execution of `env` ?
