# 概念
## casperjs 作用
一个页面抓取以及测试框架。

## 步骤navigation-steps和套件suite
整个模拟浏览过程可以叫做一个套件suite。  
套件有一系列步骤navigation-steps组成。  
这些步骤一般包括一个start接口和多个then接口。  
当然并非严格的then接口，也包括类似的thenOpen等接口。  
这些接口定义流程，而触发这个流程执行需要run接口。  

step可以认为是一个js函数可以完成两件事：
* 等待前一个步骤结束
* 等待一个url请求对应的页面加载成功


## casper 实例创建
通过create接口创建一个casper实例。

    var casper = require('casper').create();

## 打开页面
页面的打开可以通过多重方式

    start/open/thenOpen

open 支持GET/POST/PUT/DELETE等常见的HTTP方法

# 应用
## cookie


## 在page中添加js代码

casperjs允许在原有的webpage上下文中天添加js代码。
常用来替换掉原有的一些接口函数。
通过evaluate接口来实现原有showModalDialog接口的替换。

     this.evaluate(function() {
        window.showModalDialog = function () {
            var url = arguments[0];
            httpGet(url);
        };
        return true;
    });

添加自定义接口：

    this.evaluate(function() {
        function httpGet(theUrl) {
            var xmlHttp = new XMLHttpRequest();
            xmlHttp.open("GET", theUrl, false);
            xmlHttp.send(null);
        }
        return true;
    });
    
    
# 调试
