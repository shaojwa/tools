it cannot work to use gitignore file to ignore the tacked files in git. *but*, we can use  follows:
```
git update-index --assume-unchanged <path-to-file>
git update-index --no-assume-unchanged <path-to-file>
```
