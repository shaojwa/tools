#注意点
- index不能做列名。
- sql关键字和函数名不区分大小写但是数据库和表名是否区分和安装系统有关。
- 列和索引名不区分大小写。

#显示
##显示当前基本配置信息
`status;`
##显示所有数据库
`show databases;`
##显示某个数据库中所有表
 `show tables [from db_name];`
##显示表中的列信息
`show columns from tbl_name [from db_name ] ; `
`show columns from db_name.tbl_name;`
##显示表的索引
`show index from tbl_name;`
##显示存储过程状态
`show procedure status`
##显示某用户权限
`show grants for user_name;`
例：`show grants for root@localhost;`


#删除
##删除table
`drop table tbl_name;`

#设置
##设置主键
可以在创建表的时候就为表加上主键：
`CREATE TABLE tbl_name (PRIMARY KEY(index_col_name));`
可以更新表结构时为表加上主键：
`ALTER TABLE tbl_name ADD PRIMARY KEY (index_col_name);`