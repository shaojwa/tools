v0.1@ 20131219
v0.2@ 20141125
v0.3@ 20151127
v0.4@ 20160601

status = tracked + untracked  
tracked = work + index + history + remot

#### create empry repository
    git init
#### clone a repository
    git clone

#### from workspace to index
    git add
    git add
    git add .
    git add -u .
    git add -p <file>

#### from index to local repository
    git commit -m <some message>

#### from worksapce to local repository
    git commit -a -m <some message>  

#### from local repository to remote repository
    git push  https://github.com/shaojwa/leetcode.git master

#### revert from index to workspace
    git checkout

#### revert from local repository to workspace
    git checkout HEAD

#### remove file from the index only
    git rm --cached <file>

#### remove file from index and working tree
    git rm [-f] <file>

#### reset current HEAD to the specified state
    git reset --files

#### update from remote repository to local repository
    git remote update

#### add remote repository
    git remote add doc https://github.com/shaojwa/doc.git

#### list create or delete branched
    git branch

#### list the remote-tracking branches
    git branch -r

#### list remote-tracking branched and local branches
    git branch -a

#### show working tree status
    git status

#### show commit logs
    git log
    git log -p
    git log -2

#### query remote repository name
    git remote [-v]

#### query all  branches in remote repository named origin

    git remote show origin

#### diff between work and index

    git diff

#### diff between workspace and local repository

    git diff HEAD

#### diff between workspace and remote repository

    git diff HEAD~

#### diff between index and local repository
    git diff --cached
    git diff --staged

#### diff between index and remote repository
    git diff --cached HEAD~

#### rename remote repository
    git remote -v
    git remote set-url origin https://github.com/shaojwa/man.git
