@20151221

本文是git的查看系列

## 查看本地分支

    git branch

## 查看远程分支

    git branch -r

## 查看所有分支

    git branch -a

## 查看状态

    git status

status = tracked + untracked  
tracked = work + index + history + remote  

#### 查看日志

    git log
    git log -p
    git log -2

### 查看本地clone的代码库

    git remote
    git remote -v

### 查看本地clone版本origin库的所有分支

    git remote show origin

### diff
work和index之间  

    git diff

work和history之间  

    git diff HEAD

work和remote之间  

    git diff HEAD~

index和history之间  

    git diff --cached
    git diff --staged

index和remote之间  

    git diff --cached HEAD~
