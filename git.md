gitav0.1@ 20131219  
v0.2@ 20141125  
v0.3@ 20151127  
v0.4@ 20160601

## create a new branch and push
```
git checkout -b t14_storepool_usage
git push origin t14_storepool_usage:t14_storepool_usage
```

## merge branch
```
git merge br1 br2 br3
```

## show parent relationship of commits in log
```
git log –pretty=raw
```

## git
https://stackoverflow.com/questions/1404796/how-can-i-get-the-latest-tag-name-in-current-branch-in-git
```
git describe --tags 
git describe --tags --abbrev=0
```
To get the most recent annotated tag:
```
git describe --abbrev=0
```

## add index
```
git add  <pathspec>
git add -u  # add all update tracked files
git add .   # all files include untracked files
```

## reset index
```
git reset HEAD code/global_instance_construct.s
// same as reset --
git reset -- src/test/dse/dcache/dm/dcache_dm_test.cc
```

## delete index
```
git rm src/test/dse/dcache/dm/dcache_dm_test.cc   # delete file from index and working directory 
git rm --cached <file_name>                       # delete file from the index only, not working directory
```

## reset working
```
git checkout src/test/dse/dcache/dm/dcache_dm_test.cc
```

## delete working
```
rm src/test/dse/dcache/dm/dcache_dm_test.cc
```


## git basics
- object: blobs, trees, commits
- references

##  HEAD^ or  HEAD~ 
there are 2 commits after merge, first-parent is the prevous commit of the branch, is also called merged-in commit.
the second-parent is the commit of from which the patches are merged. in git doc,
`<rev>~<n>` to a revision parameter means the commit object that is the <n>th genetation ancestor of the named commit object,
 following only the first parnets, but `<rev>^n` measn the <n>th parnet. so

```
HEAD~ is equivalent to HEAD~1, HEAD~2 equivalent to HEAD~1~1
HEAD^ is same as HEAD^1, HEAD^^ is same as HEAD~2 but NOT equivalent to HEAD^2
```
 
## three tree
```
HEAD
index
working
```

## repo
#### default repo name and branch name
```
origin     # repo name
master     # branch name
```

## remote
```
git remote [-v]
git remote set-url origin https://github.com/shaojwa/man.git   #  rename remote repository  
git remote show origin   # query all branches in remote repository named origin  
git remote update  # update from remote repository to local repository  
git remote add doc https://github.com/shaojwa/doc.git  # add remote repository  
```

## stash
#### show the changes recorded in the stash as a diff 
```
git show stash@{n}
git stash show stash@{1}
git stash show -p stash@{1} # in patch form
git stash list --date=local # show stash timestamp
git stash list # stashing changes in Working Directroy
```

## branch
#### list branches
```
git branch     # list create or delete branched  
git branch -r  # list the remote-tracking branches  
git branch -a  # list remote-tracking branched and local branches
```

#### get the upstream info of the local branch
```
git branch -vv
```

#### local branches
```
.git/refs/heads
```

####  remote-tracking branches
```
.git/refs/remotes/<remote>/.
```

#### local branshs VS remote-tracking branches VS  remote branches
```
git branch -r # List the remote-tracking branches.
git branch -a # List both remote-tracking branches and local branches.
```

## log basic
```
git log  
git log -p  
git log -2  
```

## oneline log
```
git log --oneline
```

## only the specified dir logs
```
git log --name-only .
```

##  log graph
```
git log --graph  # draw graphical commit history
```

## get the log of the specified file
```
git log src/test/dse/dcache/CMakeLists.txt
```

## git show
## get the change of the particular file on the specified commit
https://stackoverflow.com/questions/44245286/git-see-changes-to-a-specific-file-by-a-commit
```
git show <commit> -- <file>
```
 
## status 
```
git status  
```

## diff
```
git diff                # diff between work and index  
git diff HEAD           # diff between workspace and HEAD  
git diff HEAD~          # diff between workspace and remote  
git diff --cached       # diff between index and head  
git diff --staged       # same to above  
git diff --cached HEAD~ # diff between index and remote  
git diff --stat 47f5af # list file of the commit
```

#### reset 
```
git reset -- <filename>   # reset current HEAD to the specified state  
git reset -- src/test/dse/dcache/dm/dcache_dm_test.cc
```

####  restore the addition of modified files (tracked files) or added files (untracked files)
```
git reset HEAD <file_name>
git reset HEAD # restore all added files to unstaged
```

## restore one directory
```
git checkout -f dse/dcache/
```

## other checkouts
```
git checkout  # revert from index to working directory  
git checkout HEAD
get checkout <tag>
```

## checkout 
when run `git checkout branch_name`, if `branch_name` exists in local branches, then will checkout the branch. 
```
git checkout <new_branch>    # To prepare for working on <branch>
```
 
if not, and the name match the one of branch in the remote, then a local branch will be created with the same name with setting the upstream
```
git checkout -b <branch> --track <remote>/<branch>
```

## cherry-pick
```
git cherry-pick e0e56
```

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
after resolving every conflicts，git add each file， run git cherry-pick --continue to commit.

## commit 
```
git commit -m <message>       # from index to HEAD  
git commit -a -m <message>    # from working directory to HEAD  
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
```
 
## merge
```
git merge hot-fix  # merge hot-fix to the current branch
```
branch-name is just the branch pointer, commit is the element of the list.
1. fast-forward: the branch is in the same list of another.
1. three-way merge: it has more than one parent.

#### rebase
```
# current branch is "topic"
git rebase master # replay the changes of master to topic
```
 
## init
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

## settings
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

## create a new branch and specify the up-stream
```
git branch b01_engine_readonly
get branch b01_engine_readonly -u origin/unistor_vrb01_engine_readonly
```
