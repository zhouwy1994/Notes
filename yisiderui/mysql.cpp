====================================================Study on Mysql====================================================
install:
sudo apt-get install mysql-server
2.modify configfile:
sudo vi /etc/mysql/my.cnf //修改邦定bind-address 0.0.0.0
记得留意防火墙
mysql 远程连接数据库的二种方法
一、连接远程数据库：
1、显示密码
如：MySQL 连接远程数据库（192.168.5.116），端口“3306”，用户名为“root”，密码“123456”

C:/>mysql -h 192.168.5.116 -P 3306 -u root -p123456
2、隐藏密码
如：MySQL 连接本地数据库，用户名为“root”，

C:/>mysql -h localhost -u root -p 
Enter password:
二、配置mysql允许远程链接
    默认情况下，mysql帐号不允许从远程登陆，只能在localhost登录。本文提供了二种方法设置mysql可以通过远程主机进行连接。
一、改表法
    在localhost登入mysql后，更改 "mysql" 数据库里的 "user" 表里的 "host" 项，将"localhost"改称"%"
注意防火墙（阿里云还有一道防火墙）
例如：
　　#mysql -u root -p
   Enter password:
    ……
   mysql>
　　mysql>update user set host = '%' where user = 'root';

　　mysql>select host, user from user;

二、授权法
    例如： 你想myuser使用mypassword（密码）从任何主机连接到mysql服务器的话。

　　mysql>GRANT ALL PRIVILEGES ON *.* TO 'myuser'@'%'IDENTIFIED BY 'mypassword' WITH GRANT OPTION;

　　如果你想允许用户myuser从ip为192.168.1.6的主机连接到mysql服务器，并使用mypassword作为密码

　　mysql>GRANT ALL PRIVILEGES ON *.* TO 'myuser'@'192.168.1.3'IDENTIFIED BY

　　'mypassword' WITH GRANT OPTION;

   mysql>FLUSH PRIVILEGES

　　使修改生效，就可以了

常见问题： 
1、在采用法二授权法之后，无法在本地登录mysql（如：#mysql -u root -p -h 192.168.5.116
Enter password: 
ERROR 1045 (28000): Access denied for user 'root'@'loadb116' (using password: YES)
上例中loadb116是主机名.
解决方法： 
1、这时可以使用：mysql  -u root -p 登录，进入到mysql后。
mysql> grant all privileges on *.* to 'root'@'loadb116' 
       identified by '123456' with grant option; 
Query OK, 0 rows affected (0.00 sec)
mysql> flush privileges; 
Query OK, 0 rows affected (0.00 sec)
2、在本地使用ip地址登录
# mysql -u root -p -h 192.168.5.116 
Enter password: 
Welcome to the MySQL monitor.  Commands end with ; or /g.
Your MySQL connection id is 60
Server version: 5.1.45 MySQL Community Server (GPL)

Type 'help;' or '/h' for help. Type '/c' to clear the buffer.
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

Mysql的C开发(多的就不用讲了，直接看代码, 查询数据)
#include <stdio.h>  
#include <mysql.h>  
#include <string.h>  
int main(int argc, const char *argv[])  
{  
    MYSQL           mysql;  
    MYSQL_RES       *res = NULL;//总的查询结果会在这里面
    MYSQL_ROW       row;  //可以存取移行数据
    char            *query_str = NULL;  //SQl查询语句
    int             rc, i, fields;   //fields 字段数
    int             rows;  //结果总行数
    if (NULL == mysql_init(&mysql)) {  
        printf("mysql_init(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
    if (NULL == mysql_real_connect(&mysql,  
                "localhost",
                "root",  
                "shallnet",  
                "db_users",  
                0,  
                NULL,  
                0)) {  
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
    printf("1. Connected MySQL successful! \n");  
    query_str = "select * from tb_users";  
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));  
    if (0 != rc) {  
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
    res = mysql_store_result(&mysql);  
    if (NULL == res) {  
         printf("mysql_restore_result(): %s\n", mysql_error(&mysql));  
         return -1;  
    }  
    rows = mysql_num_rows(res);  
    printf("The total rows is: %d\n", rows);  
    fields = mysql_num_fields(res);  
    printf("The total fields is: %d\n", fields);  
    while ((row = mysql_fetch_row(res))) {  
        for (i = 0; i < fields; i++) {  
            printf("%s\t", row[0]);  
        }  
        printf("\n");  
    }  
    mysql_close(&mysql);  
    return 0;  
}  

插入和删除
#include <stdio.h>  
#include <mysql.h>  
#include <string.h>  
int main(int argc, const char *argv[])  
{  
    MYSQL           mysql;  
    MYSQL_RES       *res = NULL;  
    MYSQL_ROW       row;  
    char            *query_str = NULL;  
    int             rc, i, fields;  
    int             rows;  
    if (NULL == mysql_init(&mysql)) {  
        printf("mysql_init(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
    if (NULL == mysql_real_connect(&mysql,  
                "localhost",  
                "root",  
                "shallnet",  
                "db_users",  
                0,  
                NULL,  
                0)) {  
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
    printf("1. Connected MySQL successful! \n");  
//执行插入请求  
    query_str = "insert into tb_users values (12345, 'justtest', '2015-5-5')";  
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));  
    if (0 != rc) {  
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
//执行删除请求  
    query_str = "delete from tb_users where userid=10006";  
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));  
    if (0 != rc) {  
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
//然后查询插入删除之后的数据  
    query_str = "select * from tb_users";  
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));  
    if (0 != rc) {  
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
    res = mysql_store_result(&mysql);  
    if (NULL == res) {  
         printf("mysql_restore_result(): %s\n", mysql_error(&mysql));  
         return -1;  
    }  
    rows = mysql_num_rows(res);  
    printf("The total rows is: %d\n", rows);  
    fields = mysql_num_fields(res);  
    printf("The total fields is: %d\n", fields);  
    while ((row = mysql_fetch_row(res))) {  
        for (i = 0; i < fields; i++) {  
            printf("%s\t", row[i]);  
        }  
        printf("\n");  
    }  
    mysql_free_result(res);  
    mysql_close(&mysql);  
    return 0;  
}  

调用API注意事项
1 开启事务之前需要rollback 连接句柄。（清理垃圾）
2 mysql_ping 失败，程序需要处理重连逻辑；
3 mysql_query()执行的SQL语句是一个以‘/0’结尾的字符串，而mysql_real_query()执行的字符串长度是参数指定的，因此，前者不能不能包含二进制数据（二进制数据中可能会包含‘/0’，导致被认为到达字符串末尾）
实际使用中，推荐使用mysql_real_query
4 mysql C API   中SQL不需要 ';' 结尾；
5 mysql 转义；（老问题了）
6 所有update 语句，建议后边调用函数判断受影响的行数，是否是自己预期值；
7 mysql_real_connect 需要设置连接超时时间，特别是处理重连逻辑的时候，以免程序堵死；
8 程序rollback时候， 需要习惯性的校验应用的错误码，避免错误码没有赋值，调用者以为调用成功，造成漏洞；
9 多线程环境下使用libmysqlclient_r 库，非libmysqlclient 库
10 mysql_real_connect/mysql_init 多线程环境下调用需要加锁；
11 使用mysql_real_escape_string， 需要注意目标缓冲区是 2*n+1 大小；
12 mysql_store_result 这个函数是分配的内存的。 使用完需要释放，避免内存泄露；

13 mysql的事务尽量小，使用完，立即commit或rollback.不要起一个过大的事务。
14 mysql的隔离级别注意使用 Read Commited。不然会产生锁间隙的问题。
15 避免尝试去锁一个不存在的记录，for update语句where条件请使用主键(锁定一个非主键，会默认同时锁定一个主键，这是造成很多死锁的原因)。避免过多的for update。
16 select语句必须使用索引，where条件避免使用 or 或者在条件中运用运算表达式，会造成索引失效。
17 联合索引可以替代单独的索引。如果已有联合索引，不需要重复建立单独的索引。索引过多会导致插入变慢。注意是联合索引的第一个可以省略。 避过（f1,f2),可以省略f1的单独索引，但是不能省略f2的单独索引。
18 where条件，结果集不要太大，如果超过30%，索引会时效，会导致mysql扫描全表。不确定时，请用explain做检测。
19 mysql单表记录保持在1000W以下，以获得较好的性能。
20 mysql数据库链接数不能过多，请保持在200以下。
21 修改mysql 锁等待时间，默认为50s,避免for update等待时间超长，造成系统阻塞 innodb_lock_wait_timeout(修改这个属性需要重启数据库)
22 如果启用事务，可以不必显示的设置set autocommit=0，即使当时autocommit模式为1(直接提交模式)，可以通过begin/commit来隐式的调用。
   如果不使用事务，则必须显示的调用 set autocommit=1.因为不能确定，是否某长链接中，有人设置了set autocommit=0.
   

   查找重复数据
   select * from `transactions` WHERE(`TransactionHash`) in (select `TransactionHash` from `transactions` group by `TransactionHash` HAVING COUNT(*) > 1) ORDER BY `TransactionHash`

