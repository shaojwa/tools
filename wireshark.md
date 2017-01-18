# 过滤
## 协议类型过滤
tcp || udp  
!tcp  
## 链路层过滤

## 网络层过滤
eth.addr == e0:3f:49:eb:2e:d2  

## 传输层过滤
### tcp
* tcp的flag字段
tcp.flags.syn == 1
tcp.flags.reset == 1

## 应用层过滤
### http
* method 过滤
http.request.method == "POST"  
注意大写POST
* host 过滤
http.host == “www.zhihu.com”  
http.host contains “www.zhihu.com”  
为什么不像method一样http.request.host  
可能是因为host不是rfc协议里的定义的Request-Line部分  
而是request-header部分。  
而http.request仅仅是指Request中的Request-Line部分。  
