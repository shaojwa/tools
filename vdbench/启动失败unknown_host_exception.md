#### UnknownHostException
```
UnknownHostException: hd=hd1,system=55.55.56.223
```
在多slave模式下，需要有一个master，这个master需要明确的ip，这样slave才能和这个master通信。如果vdbench不能从hostname解析出ip，那么vdbench就无法执行多slave模式。
当出现这个错误时，我们要确保，hd中的hostname可以解析出ip。
