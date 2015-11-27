# git_man

###### v0.1 on 20131219 / v0.2 on 20141125

## 配置git

    git config user.email "shaojwa@gmail.com"
    git config user.name "shaojwa"

## 创建代码仓库
### 方法1
在github网站上创建代码仓库

### 方法2

## 初始化
使用前先初始化本地仓库   
方法1：本地初始化（暂时不关联代码仓库）

    cd <dir>
    git init
方法2：从远程仓库初始化（直接关联某个代码仓库）

    cd <dir>
    git clone https://github.com/shaojwa/leetcode/git

## 修改后的撤销
放弃工作区中的所有修改：

    git reset --hard HEAD
放弃工作区中指定文件的的修改：
    
    
## 添加文件到本地缓存(index-tree)
场景1：添加某个目录下的所有文件到本地缓存 

    git add . 
    git add -u .
    
场景2：添加指定文件到本地缓存

    git add -p <file>

## 添加完后查看状态
    git status

##取消添加到缓存
场景1：取消某个文件的添加

    git rm --cached <file>
   
场景2：取消所有文件的添加


## 把更改同步到本地仓库(head-tree)
同步到远程服务器前得先同步到本地服务器

    git commit -m "some message"

## 把修改同步到远程仓库

    git push  https://github.com/shaojwa/leetcode.git maser
    
运行上条命令会提示你设置用户名和密码:

    Username for 'https://github.com':
    Password for 'https://shaojwa@github.com':
    
输入正确的用户名和密码之后提示提交成功.可以在网站上确认。

    
    
##分支操作

远程添加新的分支
 
	git remote add doc https://github.com/shaojwa/doc.git

[it switch](sw.jpg)

    git commit -m "`date`"
