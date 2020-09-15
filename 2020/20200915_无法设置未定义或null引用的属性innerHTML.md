很多次发现，打开云桌面的时候会出现：
```
错误: 无法设置未定义或 null 引用的属性“innerHTML”
```
原因是页面中有以下几处代码：
```
function onInit()
{
    //var strIp   = getParamString("ip");
    var strType = getParamString("url_type");
    var strPlc  = getParamString("plc_name");
    
    if(strPlc.indexOf("#")>-1){
    	strPlc = strPlc.match(/(.*)#/)[1];
    }
    document.getElementById("strType").innerHTML = strType;
    document.getElementById("strPlc").innerHTML = strPlc;
}
```
记得之前IT和我说过，什么地方设置一下就好，今天就找了下在
```
Internet选项->高级->浏览->勾选【禁用脚本调试(Internet Explorer)】
```
就可以解决，原因没有完全清楚。
