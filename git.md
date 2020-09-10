v0.1@ 20131219  
v0.2@ 20141125  
v0.3@ 20151127  
v0.4@ 20160601

#### default repo-name and branch-name
```
origin     # repo name
master     # branch name
```

#### remote branch
远程分支，不再本地厂库，是远程服务器上的某个分支，名字常常和本地的一样，只是仓库是远程的。

#### Remote-tracking branches
这是一种本地分支，类似本地的书签，用来跟踪远程分支，一般以origin/master类似的名字命名，但是一般也会叫成远程分支。
```
git branch -r  # List the remote-tracking branches.
````

#### both remote-tracking branches and local branches
```
git branch -a # List both remote-tracking branches and local branches.
```

#### three tree
```
HEAD
Index
Working Directory
```

#### init  
```
git init  # reate empty repository  
```

#### clone
```
git clone  # clone a repository
git clone ssh://git@github.com/shaojwa/lang.git  # cannot commit
```

#### ssh clone
```
git clone git@github.com:ceph/ceph.git
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
git reset -- <filename>   # reset current HEAD to the specified state  
```

#### restore the delete of Index
```
git reset -- src/test/dse/dcache/dm/dcache_dm_test.cc
```
####  restore the addition of modified files (tracked files) or added files (untracked files)
```
git reset HEAD <file_name>
git reset HEAD   # restore all added files to unstaged
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

#### checkout 
```
git checkout <new_branch>    # To prepare for working on <branch>
```

执行git checkout branch_name时，如果branch_name在本地分支中存在，那么就会签出这个本地分支的代码。 
如果不存在，而且这个分支名匹配到远程库origin中的一个分支，那么将在本地创建一个同名的本地分支名，并设置这个本地分支的upstream为对应的远程分支。
```
git checkout -b <branch> --track <remote>/<branch>
```

#### cherry pick

在check pick的目的分支上运行cherry-pick，commit号是源分支上的一个commit。
```
get cherry-pick e0e56
```
 此时在当前分支上运行git status 就可以看到有文件在Unmerged paths下：

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
手动解决每一个冲突的文件后，git add每一个文件，最后运行git cherry-pick --continue 来添加提交。

#### commit  
```
git commit -m <message>       # from index to HEAD  
git commit -a -m <message>    # from working directory to HEAD  
```

#### stashing changes in Working Directroy
```
git stash list
```

#### merge
```
git merge hot-fix  # merge hot-fix to the current branch
```
branch-name is just the branch pointer, commit is the element of the list.
1. fast-forward: the branch is in the same list of another.
1. three-way merge: it has more than one parent.

#### rebase
```
git checkout experiment
git rebase master # replay the changes of experiment on master
git checkout master
```

#### push
```
git push <repos> <refspec>  # <refspec>=<src>:<dst>
```
repos is the remote-repo, not remote-host, default-name is origin

```
git push https://github.com/shaojwa/leetcode.git master  
git push origin master
git push origin HEAD:refs/for/UniStorOS_V100R001B01

HEAD:refs/for/UniStorOS_V100R001B01是refspec，HEAD是refspec中的src-ref，refs/for/UniStorOS_V100R001B01是dst-ref
```

#### branch management
```
git branch     # list create or delete branched  
git branch -r  # list the remote-tracking branches  
git branch -a  # list remote-tracking branched and local branches
```

get the upstream info of the local branch
```
git branch -vv
```

#### list file of the commit
```
git diff --stat 47f5af
```

#### diff
```
git diff                # diff between work and index  
git diff HEAD           # diff between workspace and HEAD  
git diff HEAD~          # diff between workspace and remote  
git diff --cached       # diff between index and head  
git diff --staged       # same to above  
git diff --cached HEAD~ # diff between index and remote  
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
git remote set-url origin https://github.com/shaojwa/man.git   #  rename remote repository  
git remote show origin   # query all branches in remote repository named origin  
git remote update  # update from remote repository to local repository  
git remote add doc https://github.com/shaojwa/doc.git  # add remote repository  
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

#### difference of HEAD^ and  HEAD~ 
merge之后的commit就会有两个父提交，first-parent是merged-in的commit，second-parent是被合入的commit。
```
~是纵向第几层父节点，HEAD~ == HEAD~1: HEAD的第一个parent，HEAD~2 == HEAD~1~1: HEAD的第一个parent的第一个parent
^ 横向第几个父节点,  HEAD^ == HEAD^1：HEAD的第一个parent, HEAD^2：HEAD的第2个parent
所以，HEAD^2 != HEAD^1^1，HEAD~2 == HEAD^1^1
```
