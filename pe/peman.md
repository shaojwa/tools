说明：文档以实际项目中生成64位版本的操作为准
//
//安装基础PE版本
//
1. 安装 Windows ADK
2. 开始-[Windows Kits]->[Windows ADK]->[Deployment and Imaging Tools Environment]
注意：以管理员权限运行
3. 安装PE: copype amd64 g:\WinPEa64 
注意：不要预先创建WinPEa64目录
4. 制作USB启动盘：MakeWinPEMedia /UFD g:\WinPEa64 h:
注意: h就是U盘在电脑上的盘符


//
// 添加定制应用
//
1. cd到指定版本的pe目录
注意：需要明确指定WinPE.wim是x86还是amd64版本
所以先从[Deployment Tools]目录cd到对应的目录中。
cd "..\Windows Preinstallation Environment\amd64"
2. 加载PE镜像
Dism /Mount-Image /ImageFile:"g:\WinPEa64\media\sources\boot.wim" /index:1 /MountDir:"g:\WinPEa64\mount"
3. 添加可选组件
在mount目录下创建定制程序的存放目录tools并将对应的程序拷贝进去
4.添加自启动脚本
修改mount\Windows\System32\Startnet.cmd
添加启动代码：%SYSTEMDRIVE%\tools\fuzz.exe
5. 卸载PE
Dism /Unmount-Image /MountDir:"g:\WinPa64\mount" /commit
6.创建启动盘
MakeWinPEMedia /UFD C:\WinPEa64 F:

在我们当前使用的PE5.0 从3.0中已经没有peimg
参考连接
[1. PE5.0 添加定制应用](https://msdn.microsoft.com/zh-cn/library/hh824926.aspx)
[2. PE < 3.0参考](https://technet.microsoft.com/en-us/library/cc749312(v=ws.10).aspx)
[1](https://msdn.microsoft.com/en-us/windows/hardware/commercialize/manufacture/desktop/winpe-create-usb-bootable-drive)


