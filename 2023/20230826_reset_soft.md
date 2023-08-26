`reset soft`可以保持修改的文件已经`to be committed`，而不需要重新`add`，这个是比没有`soft`好的地方。
`reset`默认的mode是mixed，就是会reset `index`，但是不会reset `working-tree`。所有的mode都会设置当前分支的head到<commit>上.
