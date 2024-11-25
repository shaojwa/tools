正常来说，dash，或者double-dash，都会传到命令行中。之所以有的命令不接受dash或者double-dash之后的参数，那一般是因为这些命令可以执行其他命令。
他所执行的命令也需要参数。所以，比如bash和perf record，当这些命令可能执行其他命令时，一般用double-dash来分割。
