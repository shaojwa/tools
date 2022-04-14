1. GNU make Version 4.3
2. This file documents the GNU make utility.
3. issues the commands to recompile them.
4. Permission is granted to copy, distribute or modify this document under the terms of the GNU Free Documentation License.
5. GNU make conforms to section 6.2 of IEEE Standard 1003.2-1992 (POSIX.2).
6. Our examples show C programs, since they are most common.
7. Indeed, make is not limited to programs.

#### How To
The make program uses the makefile data base and the last-modification times of the files to decide which of the files need to be updated.

### report bug
Before reporting a bug or trying to fix it yourself, try to isolate it to the smallest possible makefile that reproduces the problem.

#### check version
```
[wsh@node80 timus]$ make --version
GNU Make 3.82
Built for x86_64-redhat-linux-gnu
Copyright (C) 2010  Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```

#### check os version
```
[wsh@node80 timus]$ make --help
...
This program built for x86_64-redhat-linux-gnu
Report bugs to <bug-make@gnu.org>
```

#### recipe
A recipe is a list of ingredients and a set of instructions that tell you how to cook something.

#### data base
make has a data base to record the recipes.

