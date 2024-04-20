#### 搜索本文
快捷键ctrl+f

#### 搜索文件
快捷键ctrl+p让光标直接跳到输入框，search-files-by-name。也可以直接在命令面板里敲文件名。

#### 运行vscode管理命令
是ctrl-shift-p

#### 是否可以打开多个远程连接
可以

#### 跳转
```
ctrl + p  // go to file 
ctrl + g  // go to line
F12       // go to definiation
alt + Leftarrow // go back
alt + RightArrow // go forward
```

#### 代码编辑
```
Ctrl+K Ctrl+C // add line comment
Ctrl+K Ctrl+U // remvoe line comment
Ctrl+K Ctrl+F // format selection
Shift+Alt+F   // format selection
```

#### 文件名修改
```
F2            // rename
Ctl+F2        // change all
```

#### 窗口
```
ctrl + shift + e // explorer
ctrl + shift + f // find in file
ctrl + shift + d // debug
ctrl + shift + x // eXtension
```

#### 设置快捷键
```
Ctrl+K Ctrl+S // open keyboard shortcuts
```

####  智能感知 IntelliSense

```
IntelliSense: 智能感知，这个术语包括很多特性，比如：
code completion（代码补全）, parameter info（参数提示）, quick info（快速提示）, and member lists（成员列表）
笼统点说，就是各种提示和补全。IS基于VS中的language service（语言服务）

（1） 代码补全
代码补全就是会显示俩种，一种是VS code推断出来的，一种是全局标记。文本，字段，函数，类名等等，都会补全。

Tab completion，默认关闭，按tab键可以在备选项之间切换。通过editor.tabCompletion设置。
代码补全还可以设置，按照离光标位置出现的远近来最可选项进行排序。通过editor.suggest.localityBonus来设置。

Suggestion selection，推荐列表也可以配置（editor.suggestSelection），默认情况下是最近选择的补全排在前面。
如果选择first，那么推荐列表中的选项顺序不会变化。
还有一个比较高级的recentlyUsedByPrefix，前缀也会参与决定。
比如先输入rc，选择rcache_clear。然后输入rca，选择rcache_dump。
那么当下一次输入rc时，优先显示的是rcache_clear，如果用默认的recentlyUsed，那么优先选择的就会是rcache_dump。

Snippets 补全，就是代码片段补全。

（2）和IS相关的Key binding
修改在keybindings.json

（3）Troubleshooting问题解决
```

#### 设置 User and Workspace Settings
分两种:
```
User Settings
Workspace Settings 
```

#### 常用快捷键

显示所有的设置
```
Ctrl+,
```
选择颜色主题
```
Ctrl+K Ctrl+T
File > Preferences > Color Theme
```
