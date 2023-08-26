`reset soft`可以保持修改的文件已经added，而不需要重新add，这个是比不加soft好的地方。

reset默认的mode是mixed，就是会reset index，但是不会reset working-tree。所有的mode都会设置当前分支的head到<commit>上.
