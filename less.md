https://www.thegeekstuff.com/2010/02/unix-less-command-10-tips-for-effective-navigation/
https://www.thegeekstuff.com/2009/04/linux-less-command-open-view-different-files-less-is-more/

#### 10 tips
1. I personally prefer to use less command to view files.
1. less allows both forward and backward movements.
1. less donot require to load the whole file before viewing. 
1. The navigation keys in less command are similar to Vim editor.
1. it will make you a better command line warrior.
1.  use backward search(?pattern) to search directory or path.

#### jump
```
[N]g          // goto line N
[n]p          // go to N percent
less +10      // 10 is a command of less
less -j 
```
#### search
```
less -ppattern
/
?           // good for searching directory which includes slashes
```

#### filter
```
&pattern      //display only the matching lines, not all.
```

#### Screen Navigation
```
ctrl+f or f   // forward one windows
ctrl+b or b   // backward one windows
ctrl+d or d   // forward half windows (d is down)
ctrl+u or u   // backward half windows (u is up)
G             // go to the end of file
g             // go to the start of file
q or ZZ       // exit the less pager
10j           // 10 lines forward.
10k           // 10 lines backward.
```

#### Marked navigation
```
ma            // mark the current position with the letter ‘a’,
a             // go to the marked position ‘a’.
```
#### Multiple file paging
```
:n            // go to the next file.
:p            // go to the previous file
```

#### info
```
-N <RETURN>   // show line numbers
-S            // chop-long-lines
=             // print current file name
ctrl + g      // print current file name
:f            // print current file name
```

#### edit
```
v             // sing the configured editor edit the current file.
```
less 之后用按v来编辑，:wq之后回到less。

#### others
  
```
:e nonexistentfile  // to reload the opened file
:n                  // go to the next file
:p                  // go to the previous file
<n>RIGHTARROW
<n>LEFTARROW
ctrl+leftarrow
ctrl+rightarrow
```
