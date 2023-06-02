今天碰到一个问题，就是新创建的branch的HEAD的分支没设置对，因为`git branch`的时候，默认为用当前branch的head。
在这种情况下，其实只需要查询到你希望指向的commit，然后用`git reset <commit>` 就可以更改。
