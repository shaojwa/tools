v0.1@ 20131219  
v0.2@ 20141125  
v0.3@ 20151127  

### 创建项目仓库
方法1：创建崭新的git项目仓库  

    git init

方法2：克隆某个仓库自动初始化  

    git clone


### 提交修改
从untracked到tracked  

    git add

从work到index  

    git add
    git add .
    git add -u .
    git add -p <file>

从index到history  

    git commit -m <some message>

从index到history  

    git commit -a -m <some message>  

从history到remote  

    git push  https://github.com/shaojwa/leetcode.git master

### 回退
从tracked到untracked  

    git rm --cached <file>

从index到work  

    git checkout --files

从history到index  

    git reset --files

### 更新
从remote更新到本地history  

    git remote update

### 远程添加新的分支

    git remote add doc https://github.com/shaojwa/doc.git

### 其他

    git commit -m "`date`"





