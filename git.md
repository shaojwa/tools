v0.1@ 20131219  
v0.2@ 20141125  
v0.3@ 20151127  
v0.4@ 20160601

#### three tree
```
HEAD
Index
Working Directory
```

#### default repo-name and branch-name
```
origin // repo name
master // branch name
```

#### init  
```
git init // create empty repository  
```

#### clone
```
git clone // clone a repository
git clone ssh://git@github.com/shaojwa/lang.git // can not commit
```

#### status 
```
git status  
```

#### add to Index
```
git add  <pathspec>
git add -u  # add all update tracked files
git add .   # all files include untracked files
```

#### delete from Index
```
git rm src/test/dse/dcache/dm/dcache_dm_test.cc   # delete file from index and working directory 
git rm --cached <file_name>                       # delete file from the index only, not working directory
```

#### delete from Working Direcory
```
rm src/test/dse/dcache/dm/dcache_dm_test.cc
```

#### reset 
```
git reset --files // reset current HEAD to the specified state  
```

#### restore the delete of Index
```
git reset src/test/dse/dcache/dm/dcache_dm_test.cc
```
####  restore the addition of modified files (tracked files) or added files (untracked files)
```
git reset HEAD <file_name>
git reset HEAD // restore all added files to unstaged
```

#### restore the delete of Working Directory
```
git checkout src/test/dse/dcache/dm/dcache_dm_test.cc
```

#### restore one directory
```
git checkout -f dse/dcache/
```

#### other checkouts
```
git checkout  # revert from index to working directory  
git checkout HEAD
get checkout <tag>
```

#### commit  
```
git commit -m <message>       # from index to HEAD  
git commit -a -m <message>    # from working directory to HEAD  
```

#### stashing changes in Working Directroy
```
git stash list
```

####  ssh clone
```
git clone git@github.com:ceph/ceph.git
```

#### push
```
git push <repos> <refspec> // <refspec>=<src>:<dst>
```
repos是远程仓库，不是远程主机，默认是origin

```
git push https://github.com/shaojwa/leetcode.git master  
git push origin master
git push origin HEAD:refs/for/UniStorOS_V100R001B01

HEAD:refs/for/UniStorOS_V100R001B01是refspec，HEAD是refspec中的src-ref，refs/for/UniStorOS_V100R001B01是dst-ref
```

#### list file of the commit
```
git diff --stat 47f5af
```

#### checkout 

* git checkout <new_branch>

```
执行git checkout <branch_name>时，如果branch_name在本地分支中存在，那么就会签出这个本地分支的代码。 
如果不存在而且，这个分支名匹配到远程库origin中的一个分支，那么将在本地创建一个同名的分支名，跟踪远程的分支。
所以这种情况就相当于新建一个本地分支（-b）参数，然后这个本地分支跟踪远程的的同名分支。
即 man git checkout里说的，等同于：git checkout -b <branch> --track <remote>/<branch>
```
* git checkout -b <new_branch>
而如果用 git checkout -b <new_branch>时，branch 就是新的分支名，没有指定源分支，所以默认是当前分支。

#### cherry pick

* 在分支b上运行cherry-pick，commit号是分支a上的一个commit(将分支a上的某个提交应用到b上)

```
get cherry-pick e0e56
```

* 此时在分支b上运行git status 就可以看到有文件在"Unmerged paths"下：

```   
$ git status
# Unmerged paths:
#   (use "git add <file>..." to mark resolution)
#
#       both modified:      src/a.h
#       both modified:      src/b.cc
#       both modified:      src/c.cc
#       both modified:      src/d.cc
```

* 手动解决每一个冲突的文件后，git add每一个文件。
* 最后运行git cherry-pick --continue 来添加提交。
 
#### 分支管理 
```
git branch // list create or delete branched  
git branch -r // list the remote-tracking branches  
git branch -a // list remote-tracking branched and local branches
```

* 查看本地 branch 对应的的 远程库的upsteam分支信息
```
git config -l
git branch -vv
```

* 创建一个和远程跟踪分支同名的本地分支
```
git checkout V100R001 # 本地没有这个分支且远程有这个分支
```

#### diff
```
git diff // diff between work and index  
git diff HEAD  // diff between workspace and HEAD  
git diff HEAD~ // diff between workspace and remote  
git diff --cached // diff between index and head  
git diff --staged // same to above  
git diff --cached HEAD~ // diff between index and remote  
```

#### log
```
git log  
git log -p  
git log -2  
```

#### remote
```
git remote [-v]  
// rename remote repository  
git remote set-url origin https://github.com/shaojwa/man.git  
// query all branches in remote repository named origin  
git remote show origin  
git remote update // update from remote repository to local repository  
git remote add doc https://github.com/shaojwa/doc.git // add remote repository  
```

#### HEAD^ 和 HEAD~ 的区别
一个merge之后的commit就会有两个父提交，first-parent是merged-in的commit，second-parent是被合入的commit。
 
~是纵向第几层父节点
```
HEAD~ == HEAD~1: HEAD的第一个parent
HEAD~2 == HEAD~1~1: HEAD的第一个parent的第一个parent
```
^ 横向第几个父节点
```
HEAD^ == HEAD^1：HEAD的第一个parent
HEAD^2：HEAD的第2个parent

HEAD^2 != HEAD^1^1
HEAD~2 == HEAD^1^1
```
#### 如何使用分支来修问题单
```
git branch bugfix01
```  
git会创建一个指针，指向当前的提交（commit），怎么找到当前的提交？通过HEAD，HEAD是一个指向分支的指针（可以理解为指针的指针）。  
创建完成之后，HEAD还在原来的分支（指向原来的分支），并没有指向新创建的bugfix14。  
此时，可以查看各个本地分支所指向的commit对象：git log --oneline --decorate，创建完成之后，需要checkout：
```
git checkout bugfix01
```  
这样HEAD就指向bugfix01分支。以上两条命令可以通过 git checkout -b bugfix01 等价完成。
创建分支之后，有时候需要切换回master，切换之前最好保证修改已经提交到bugfix01上（即bugxi01已经干净，尽管可以通过stash等命令来绕过）
如果你想将bugfix01上的修改合并到master上，那么需要先checkout到master分支：
```
$ git checkout master
$ git merge bugfix01
``` 
完成之后，需要删除bugfix01分支：
```
$ git branch -d bugfix01
```
#### pretty-format
```
[format]
pretty = format:"%C(yellow)%h %C(red)%ad %C(green)%<(8)%an %C(cyan)%s"
```
#### set vim as default-editor
```
[core]
    editor = vim
```
