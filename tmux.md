#### tmux attch

#### 光标上下移动
```
ctrl-b [ 之后可以 Up/PgUp/Down/PgDown
```

#### 进入 copy模式之后用vi的快捷键
in .tmux.conf
```
set-window-option -g mode-keys vi # works in tmux 2.1 and above.
setw -g mode-keys vi              # works in tmux 1.8
```


#### key bindings

     C-b    prefix key
     
     // panes
     %           Split the current pane into two, left and right.
     "           Split the current pane into two, top and bottom.
     x           Kill the current pane. (same with: exit command)
     o           Select the next pane in the current window.
     C-o         Rotate the panes in the current window 
     
     
     // windows     
     c           Create a new window.
     &           Kill the current window. (same with: exit command)
     n           Change to the next window.
     p           Change to the previous window.
     l           Move to the previously selected window.
     w           Choose the current window interactively.
     
     
     // session     
     s           Select a new session for the attached client interactively.
     d           Detach the current client.
     
     // command
     :

#### tmux conf
 
     set -g prefix C-a
     unbind C-b
     
     // like vim
     // pane
     #up
     bind-key k select-pane -U
     #down
     bind-key j select-pane -D
     #left
     bind-key h select-pane -L
     #right
     bind-key l select-pane -R
     
     // window
     #select last window
     bind-key C-l select-window -l


#### session related

    tmux new -s session_name
    tmux attach -t session_name

#### 对窗口重编号

     // then using movew -r to renumbered  all windows in sequential order in the session
     :movew -r
     // without parameters will move the current to the first free position
     :movewwindows


     // then using movew -r to renumbered  all windows in sequential order in the session
     :movew -r
     // without parameters will move the current to the first free position
     :movew
