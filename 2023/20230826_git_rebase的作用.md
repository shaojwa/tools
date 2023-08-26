本意上来说，是设计到两个分分支，分支a和分支b，把分支a上的几个提交，commit1，commit2直接移到分支b上，而没有分支a和分支b的合并过程。
默认会在当前分支上执行，并且，前提条件是当前branch需要有一个upstream（上游）。
在当前分支上完成了，但在upstream中没有做的修改（多个commit），会保存到一个临时区域，这些修改可以通过`git log <upstream>..HEAD` 看到。

rebase的步骤是（1）先保修当前分支和upstream上的区别（2）单后将当前分支的HEAD指向upstream（3）将刚才保存的修改在当前分支上（HEAD已经更新）重应用一遍。
就类似重新回放一遍，逐个的，按顺序。当然，这个rebase的过程，可能会因为一些合并失败（merge-failure）而不能自动完成。

例如,假设当前分支是topic，如果git rebase的命令格式是`git rebase master`或者`git rebase master topic`那么，会将topic上的独有commit，移植到master的后面。

所以，git rebase的直接操作branch是当前分支，可以省。而rebase的目标branch是需要指定的，因为你不知道需要rebase去哪里。
