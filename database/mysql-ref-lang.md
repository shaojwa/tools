[0]:https://docs.oracle.com/javadb/10.8.3.0/ref/
本文参考[oracle的参考文档][0]。

##statements
sql语法结构上最上层的应该就是这个，中文一般好像翻译成语句，从参考文档上来说statements可以分为15个大类，常见的有：  
CREATE statement  
INSERTstatement  
SELECTstatemetn  

##clause
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

##expression
这个怎么翻译我也不知道。反正中文翻译的里也很蛋疼得翻译成语句的。
这个和上两个是否有严格的层级关心我不确定。感觉这个不是特指某种结构。
（续）