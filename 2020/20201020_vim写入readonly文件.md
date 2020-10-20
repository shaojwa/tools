以非root权限打开文件后，无法保存，这个时候可以用一下命令解决。
首先`:w`命令是把buffer中的数据写入文件，当然如果是readonly文件，是写不进去的。
```
E505: "/etc/samba/smb.conf" is read-only (add ! to override)
```
所以，这个时候可能会用`w!`来强制写入，但是也是没用的：
```
"/etc/samba/smb.conf" E212: Can't open file for writing
```
但是我们注意到`:w {file}`是可以写入某个特定的文件的:
```
:w %
E505: "/etc/samba/smb.conf" is read-only (add ! to override)
```
如果文件存在，也可以覆盖写入：所以，我们就可以考虑再次写入自己，但是结果显然是一样的，因为权限不够。
```
:w! %
"/etc/samba/smb.conf" E212: Can't open file for writing
```
所以，我们需要提权写入，要提权，那就需要sudo这个额外命令。vim可以额外执行命令：
```
:!sudo tee
```
结合一下，用sudo 写入一个文件，用tee来写入，那么tee的输入需要是当前的buffer，`:w !cmd`模式可以支持当前的buffer为命令的入参：
```
:w !sudo tee %
``
