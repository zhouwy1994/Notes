====================================================Study on Mysql====================================================
install:
sudo apt-get install mysql-server
2.modify configfile:
sudo vi /etc/mysql/my.cnf //注释bind 127.0.0.1
3.允许远程访问:
1.改表法:
1.use mysql
2.update user set host = '%' where user = 'root';
3.select host, user from user;
2.授权法:
例如，你想root使用123456从任何主机连接到mysql服务器。
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY '123456' WITH GRANT OPTION;
4.登陆数据库
mysql -h 'ipaddr' -u 'username' -p 'password'

SQL(Struction Qurey Lagunage):结构化查询语言
1.show databases;//显示系统存在的数据库
2.use basename //选择需要使用的数据库
3.show tables;//显示所有数据表
4.set names utf8;//设置字符集
查询语言:
SELECT - 从数据库中提取数据
UPDATE - 更新数据库中的数据
DELETE - 从数据库中删除数据()
INSERT INTO - 向数据库中插入新数据
CREATE DATABASE - 创建新数据库
ALTER DATABASE - 修改数据库
CREATE TABLE - 创建新表
ALTER TABLE - 变更（改变）数据库表
DROP TABLE - 删除表
CREATE INDEX - 创建索引（搜索键）
DROP INDEX - 删除索引

1.SELECT column_num, column_num from table; //提取数据，结果以行呈现
colume_num:字段名
table:数据表
2.select * from table;//查询所有字段
3.SELECT DISTINCT colume_num form table; //显示指定列的不同值

4.where 过滤语句
select * from table where colume_num = 'value';//找出colume_num字段值等于value的行记录
数值字段不用引号，字符型用单引号
WHERE 子句中的运算符
下面的运算符可以在 WHERE 子句中使用：
运算符	描述
=	等于
<>	不等于。注释：在 SQL 的一些版本中，该操作符可被写成 !=
>	大于
<	小于
>=	大于等于
<=	小于等于
BETWEEN	在某个范围内
LIKE	搜索某种模式
IN	指定针对某个列的多个可能值

5.AND , OR字句
select * from table where colume_num > 23 AMD colume_num < 34;如果结构复杂，用括号
select * from table where colume_num > 23 AMD (colume_num < 34 OR colume_num != 9);
SQL ORDER BY 关键字
ORDER BY 关键字用于对结果集按照一个列或者多个列进行排序。
ORDER BY 关键字默认按照升序对记录进行排序。如果需要按照降序对记录进行排序，您可以使用 DESC 关键字。
SELECT * FROM table WHERE colume_num > 20 ORDER BY colume_num; //针对colume_num字段排序
6.SQL INSERT INTO 语法
INSERT INTO 语句可以有两种编写形式。
第一种形式无需指定要插入数据的列名，只需提供被插入的值即可：
INSERT INTO table_name
VALUES (value1,value2,value3,...);。
第二种形式需要指定列名及被插入的值：
INSERT INTO table_name (column1,column2,column3,...)
VALUES (value1,value2,value3,...);
insert into Stati2 (First, Aug, Jul, Jun, May, Apr, Mar, Feb) values ('New insret into data', '2', '34', '09', '98', '67', '87', '6');

7.updata 
SQL UPDATE 语句
UPDATE 语句用于更新表中已存在的记录。
SQL UPDATE 语法
UPDATE table_name SET column1=value1,column2=value2,... WHERE some_column=some_value;
更新数据时要慎重，使用where进行过滤，不然整个字段都回被更新

8.delete 删除记录（一行）SQL DELETE 语法
DELETE FROM table_name
WHERE some_column=some_value;
delete * from table where colume_num = 'value';

SQl,存在很多函数来处理数据，用时查

增 （INSERT INTO） 删（delete）， 查（SELECT）， 改（UPDATE）










