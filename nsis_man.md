
#### nsis note &copy;

#### 执行程序/命令
    nsExec::Exec '"$INSTDIR\vcredist_x86.exe" /q'


#### 释放文件

* 在实行前一般先设定释放路径  

        SetOutPath $INSTDIR

* 然后释放来源文件

        File "path/to/file"  