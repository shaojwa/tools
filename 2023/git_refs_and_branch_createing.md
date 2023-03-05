####  update the ref
using the git built-in command like this:
```
git update-ref refs/heads/master 1a410ef
```

#### using in creating a branch
creating a branch is doing something like create a ref of commit:
```
git update-ref refs/heads/wsh_branch 1a410ef
```

#### symbolic reference
`HEAD` is the symbolic reference  to the branch you are currently on. symbolic reference is a point to a reference.
