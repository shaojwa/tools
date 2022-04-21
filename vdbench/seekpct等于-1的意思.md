#### seekpct=-1
seekpct=100，表示seek的位置是随机的， 就等价于seekpct=random。
seelpct=0，表示没有随机的seek，意味着完全是顺序执行。所以，如果顺序到了末尾，还会从头开始。
那么问题如果我就想顺序一遍 不想从头开始，那么可以设置，seekpct=-1（或者等价于seekpct=eof），来避免重新开始IO。
