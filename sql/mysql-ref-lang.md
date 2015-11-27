[0]:https://docs.oracle.com/javadb/10.8.3.0/ref/
看sql文档觉得很多地方需要自己弄弄清楚。
可以参考[oracle的参考文档][0]。
***
**statements**
sql语法结构从最上层的应该就是这个
从参考文档上来说**statements**可以分为15个大类。
常见的有
CREATE statement
INSERTstatement
SELECTstatemetn
等等
中文一般好像翻译成**语句**
***
**clause **
第二层结构，一般翻译成子句。
尽管中文很多地方也翻译成语句，但这显然不合理。
clause 和statement在英文原义上就不一样。
子句也有很多：
CONSTRAINT clause
FOR UPDATE clause
FROM clause
GROUP BY clause
HAVING clause
ORDER BY clause
USING clause
WHERE clause
WHERE CURRENT OF clause
***
**expression**
这个怎么翻译我也不知道。
反正中文翻译的里也很蛋疼得翻译成语句的。
这个和上两个是否有严格的层级关心我不确定。
需要查资料看看。
（续）