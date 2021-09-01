#### 主要步骤
1. 基础安装
2. WIKI实例创建
3. 让WEB服务器服务静态网址
4. 让WEB服务器在我们访问wiki页面时执行moin的代码。

#### 在你的主机上进行moin的基本安装
1. 检查python是否可以工作
```
> python -V
```
2. 下载Moin
3. 安装Moin
建议选择系统路径安装，因为这样会更加方便。我们选择的前缀安装路径(PREFIX) 是`/usr/local`.
这样共享文件会在`'/usr/local/share/moin`, moin的代码路径在：`/usr/local/lib/python2.x/site-packages/MoinMoin/`

#### 测试安装结果
```
python
>>> import MoinMoin
```
没有输出就是成功。

#### 了解下Moin的主要目录
1. MoinMoin目录: `/usr/local/lib/python2.x/site-packages/MoinMoin/` # Moin的源代码路径
2. share directory: `/usr/local/share/moin` #　模板存放位置
  1. data目录，wiki页面，用户等。只有MoinMoin可以访问。
  2. underlay目录，wiki页面。
  3. htdocs，html支持页面，比如存放各种主题的图片文件。
  4. server，Moin示例的建立（startup）文件。
  5. config，Moin示例的配置文件（比如：like wikiconfig.py）

#### 什么是wiki实例
1. 在`/usr/local/share/moin`下创建`onestor_perf_team`。
2. 拷贝`data`和`underlay`到`onestor_perf_team`下。
3. 拷贝`config/wikiconfig.py`到`onestor_perf_team`下。
