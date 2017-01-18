###### 注意点
- index不能做列名。
- 列和索引名不区分大小写。

###### 显示当前基本配置信息
`status;`

###### 显示所有数据库
`show databases;`

###### 显示某个数据库中所有表
 `show tables [from dbname];`

###### 显示表中的列信息
`show columns from tbname [from dbname ] ; `

###### 显示表结构信息
`desc tbname`

###### 显示表的索引
`show index from tbname;`

###### 显示存储过程状态
`show procedure status`

###### 显示某用户权限
`show grants for user_name;`
例：`show grants for root@localhost;`

###### 删除database
`drop database dbname;`

###### 删除table
`drop table tbname;`

###### 添加列
`alter table tbname add(tage int(3));`

######  设置主键
在创建表时加上主键  
`CREATE TABLE tbl_name (PRIMARY KEY(index_col_name));`

更新表结构时加上主键  
`ALTER TABLE tbl_name ADD PRIMARY KEY (index_col_name);`
