v0.1@ 20131219  
v0.2@ 20141125  
v0.3@ 20151127  
v0.4@ 20160601  

#### 克隆一个库

    git clone ssh://git@github.com/shaojwa/lang.git
    
#### clone  

    git clone // clone a repository  
    git clone ssh://git@github.com/shaojwa/lang.git // can not commit

#### add 文件到index暂存

    git add  <pathspec>
    
##### 添加所有修改过的tracked files

    git add -u
    
#### 添加当前目录所有的文件到index包括untracked的文件
  
     git add .      
   
#### 把某个added的文件恢复到unstaged
      
      git reset HEAD <file_name>
      
#### 把所有added的文件恢复到unstaged

     git reset HEAD
 
#### 把文件从index中的移出（即不再track，提交后这个文件自然就不在库中）
    
      git rm --cached <file_name>
 
#### branch  

    git branch // list create or delete branched  
    git branch -r // list the remote-tracking branches  
    git branch -a // list remote-tracking branched and local branches 

#### checkout 把working tree中的文件更新为index tree中的文件

    git checkout  // revert from index to working directory  
    git checkout HEAD // revert from to working directory
    get checkout <tag>

#### reset 

    git reset --files // reset current HEAD to the specified state  

#### commit  

    git commit -m <message> // from index to HEAD  
    git commit -a -m <message> // from working directory to HEAD  

#### diff  
    git diff // diff between work and index  
    git diff HEAD  // diff between workspace and HEAD  
    git diff HEAD~ // diff between workspace and remote  
    git diff --cached // diff between index and head  
    git diff --staged // same to above  
    git diff --cached HEAD~ // diff between index and remote  

#### init  

    git init // create empty repository  

#### log  
    git log  
    git log -p  
    git log -2  

#### push  
    git push https://github.com/shaojwa/leetcode.git master  
    git push origin master  

#### remote  
    git remote [-v]  
    // rename remote repository  
    git remote set-url origin https://github.com/shaojwa/man.git  
    // query all branches in remote repository named origin  
    git remote show origin  
    git remote update // update from remote repository to local repository  
    git remote add doc https://github.com/shaojwa/doc.git // add remote repository  


#### rm  
    git rm --cached <file> // remove file from the index only  
    git rm [-f] <file> // file from index and working directory  


#### status  
    git status  


#### 怎么使用cherry pick

* 在分支b上运行cherry-pick，commit号是分支a上的一个commit(将分支a上的某个提交应用到b上)

    get cherry-pick e0e56

* 此时在分支b上运行git status 就可以看到有文件在"Unmerged paths"下：

    
       $ git status
       # Unmerged paths:
       #   (use "git add <file>..." to mark resolution)
       #
       #       both modified:      src/a.h
       #       both modified:      src/b.cc
       #       both modified:      src/c.cc
       #       both modified:      src/d.cc


* 手动解决每一个冲突的文件后，git add每一个文件。
* 最后运行git cherry-pick --continue 来添加提交。
    
 
 #### HEAD^ 和 HEAD~ 的区别
 
 一个merge之后的commit就会有两个父提交，first-parent是merged-in的commit，second-parent是被合入的commit。
 
 ~是纵向第几层父节点
 
    HEAD~ == HEAD~1: HEAD的第一个parent
    HEAD~2 == HEAD~1~1: HEAD的第一个parent的第一个parent
    
 ^ 横向第几个父节点
 
    HEAD^ == HEAD^1：HEAD的第一个parent
    HEAD^2：HEAD的第2个parent
   
    HEAD^2 != HEAD^1^1
    HEAD~2 == HEAD^1^1
    
  
#### 设置单行 pretty-format

    [format]
    pretty = format:"%C(yellow)%h %C(red)%ad %C(green)%<(8)%an %C(cyan)%s"
    
#### 设置vim为默认编辑器

    [core]
        editor = vim
