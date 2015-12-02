#### git_man
#### v0.1@ 20131219 
#### v0.2@ 20141125
#### v0.3@201151127

####1.创建项目仓库
####方法1：创建崭新的git项目仓库：  
`git init`

####方法2：克隆某个仓库自动初始化：
 
`git clone`


####查看

####查看状态
`git status`  
status = tracked + untracked  
tracked = work + index + history + remote

####查看日志
`git log`  
`git log -p`  
`git log -2`

####查看diff

####work和index之间
`git diff`

####work和history之间
`git diff HEAD`

####work和remote之间
`git diff HEAD~`

####index和history之间
`git diff --cached`  
`git diff --staged`

####index和remote之间
`git diff --cached HEAD~`


####提交修改
####从untracked到tracked  
`git add`  

####从work到index
`git add`  
`git add . `   
`git add -u . `   
`git add -p <file>`  

####从index到history 
//from index to history  
`git commit -m <some message>`   
//from work to history  
`git commit -a -m <some message>` 

#### 从history到remote
`git push  https://github.com/shaojwa/leetcode.git master`  

####回退
####从tracked到untracked  
`git rm --cached <file>`


####从index到work
`git checkout --files`

####从history到index
`git reset --files`  

   
####分支
####远程添加新的分支
`git remote add doc https://github.com/shaojwa/doc.git`

![it switch](sw.jpg)
```git commit -m "`date`"```
