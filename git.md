v0.1@ 20131219  
v0.2@ 20141125  
v0.3@ 20151127  
v0.4@ 20160601  

status = tracked + untracked  
tracked = work + index + history + remote  


#### add  
    git add  
    git add .  
    git add -u .  
    git add -p <file>  


#### branch  
    git branch // list create or delete branched  
    git branch -r // list the remote-tracking branches  
    git branch -a // list remote-tracking branched and local branches  


#### checkout  
    git checkout  // revert from index to working directory  
    git checkout HEAD // revert from to working directory  


#### clone  
    git clone // clone a repository  
    git clone ssh://git@github.com/shaojwa/lang.git // can not commit
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


#### reset  
    git reset --files // reset current HEAD to the specified state  


#### rm  
    git rm --cached <file> // remove file from the index only  
    git rm [-f] <file> // file from index and working directory  


#### status  
    git status  


