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


#### session related
    tmux new-session -s session_name
    tmux attach-session -t session_name
