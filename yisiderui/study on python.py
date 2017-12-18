#=========================================python2.x=================================================================
#usr/bin/python
#coding=utf-8#支持中文编码,python默认只支持ASCII码
python与其它语言不同的就是他不用{}来控制类，函数以及一些逻辑判断
python使用缩进符来表示语句段，但是同一语句快的缩进长度必须要个相同
if True:
	print "true"
else:
	print "flase"
如果缩进长度不一致或者使用的缩进符不一样，都可能报错IndentationError//缩进错误
所以尽量使用相同的缩进符，空格或者tab
if else语句后加:
与大部分语言相同python可使用\作为接写下一行
如果语句中包含() {} []就不用换行符也行days = ['Monday', 'Tuesday', 'Wednesday',
        'Thursday', 'Friday'];
python中字符串可用引号('')双引号("")三引号(''' '''or """ """)
三引号可包含多行，也可用作多行注释
string = """This is a segment
frist line
secend line"""

"""
This is a Multi-line comment
function:
name:
argment:
"""

\n可转义换行
#Python可以在同一行中使用多条语句，语句之间使用分号(;)分割
import sys//导入类sys 与using namespace std意义相同
 str = "Hello Python"; sys.stdout.write(str + '\n');
 print 默认输出是换行的，如果要实现不换行需要在变量末尾加上逗号
 print string,
 #缩进相同的一组语句构成一个代码块，我们称之代码组。
#像if、while、def和class这样的复合语句，首行以关键字开始，以冒号( : )结束，该行之后的一行或多行代码构成代码组。
#我们将首行及后面的代码组称为一个子句(clause)。
python test.py arg1 arg2 arg3
Python 中也可以所用 sys 的 sys.argv 来获取命令行参数：
sys.argv 是命令行参数列表。
len(sys.argv) 是命令行参数个数。
#输出所有命令行参数,python的命令行参数,可用sys.argv来捕捉
for i in range(len(sys.argv)):
	print sys.argv[i];
#输出所有命令行参数
#说明:内置函数 len() 和 range(),函数 len() 返回列表的长度，即元素的个数。 range返回一个序列的数。
for 后的参数列表只能是[1, 2, 3, 4]的形式与shell不同
python中执行shell命令的三种方法
1.os.system('cat /proc/cpuinfo')#只会返回0and1，即命令执行成功与否
2.output = os.popen('cat /proc/cpuinfo');print output.read()'''popen只返回output的读对象，需要通过read()取出结果
也可直接cmd = os.popen('shell cmd').read();'''
3.(status, output) = commands.getstatusoutput('cat /proc/cpuinfo');print status, output#'''既可以得到返回值，也能得到结果
#也可直接使用commands.output('shell cmd')获取命令，commands命令需要导入import commands
Python有五个标准的数据类型：
1.Numbers（数字）#整形int，浮点型float,长整形long,复数complex，数据类型是不允许改变的,这就意味着如果改变 Number 数据类型的值，将重新分配内存空间。
a = 20; b = 20;#a与b的地址是一样的，这和C区别很大
2.String（字符串）#可以下标取值str = "Hello World",str[1:6] = ello W str*2 = Hello World Hello World str[1] = e
3.List（列表）#即数组，可以是字符串，数字，甚至可以是列表即嵌套list = ['string1', string2, string3];
4.Tuple（元组）#只读数组，用,号分割，可用(),也可不用，与list的区别就是加[]
5.Dictionary（字典）#列表只能通过下标或者偏移存取，而字典可用键存取(key)，就像shell的关联数组用{}定义
列表     							元组   									字典
[]定义,可读写，通过下标和偏移存取	()or','只读，通过下标和偏移存取			{}定义,可读写，通过键存取
和shell一样，数组长度不用提前定义
数据类型的转换，你只需要将数据类型作为函数名即可。int('string')

python的运算符和C语言类似 + - * / % **(幂)a**b(a的b次方) //返回商的整数部分
比较运算符多了一个<>不等于
赋值运算符与C语言相同
移位运算符与C语言相同
逻辑运算符用and or not表示
python特有运算符：
成员运算符in not in#查找成员是否在列表中
list = [1, 2, 3, 4, 5];a = 4; if (a in list)#查找4是否存在列表
身份运算符：is not is 判断是否引用同一对象
is 与 == 区别：
is 用于判断两个变量引用对象是否为同一个， == 用于判断引用变量的值是否相等。id(var)打印变量id类似于内存值
运算符优先级也和C相同
305995
python中条件语句:if a == b: handel;
if (a == b): handel;
但是python中没有switch，只能用elif代替，break退出
逻辑运算也是采用短路运算
列表出栈list.pop();列表进栈list.append(var);
python的循环语句
while for 
while (true):handel;
特殊：可与else结合使用
while (False):
	handel;
else:
	handel 2;
break continue和C一样
pass空语句，类似C中的;空语句
python的时间处理也是类似于C语言
获取时间time.time();返回浮点型，距离1970-01-01秒数
python中有一个专门用于转换时间的结构体(元组)
struct_time元组
struct_time = (tm_year,tm_mon,tm_mday,tm_hour,tm_min,tm_sec,tm_wday,tm_yday,tm_isdst);
获取时间函数用时查


python提供了2中主要的正则表达式操作：re.match 和 re.search。
match ：只从字符串的开始与正则表达式匹配，匹配成功返回matchobject，否则返回none；
search ：将字符串的所有字串尝试与正则表达式匹配，如果所有的字串都没有匹配成功，返回none，否则返回matchobject；（re.search相当于perl中的默认行为）
match:精确匹配  re.match(Hello,Hello) = matchobject re.match(Hello,He) = none
search:模糊匹配 re.match(Hello,Hello) = matchobject re.match(Hello,He) = matchobject

# -*- coding: utf-8 -*-
代码格式默认为ASCII，以上语句将编码格式改成uft-8,支持中文
 
 import 与 from...import
在 python 用 import 或者 from...import 来导入相应的模块。
将整个模块(somemodule)导入，格式为： import somemodule
从某个模块中导入某个函数,格式为： from somemodule import somefunction
从某个模块中导入多个函数,格式为： from somemodule import firstfunc, secondfunc, thirdfunc
将某个模块中的全部函数导入，格式为： from somemodule import *
 
 #=========================================python3.x=================================================================
 python 基本数据类型:
 1.数值
	1.1:int
	1.2：float
	1.3:complex
#type(var):返回数据类型 isinstance(var, int):判断数据的类型，返回True or False
2.字符串(string)
	str = 'Hello'
3.列表(list)
	list = ["ds", "ds", "dsa"]
4.元组(tuple)
元组（tuple）与列表类似，不同之处在于元组的元素不能修改。元组写在小括号(())里，元素之间用逗号隔开
	tup = ("ds", "ds", "dsd")
5.集合(set)
集合（set）是一个无序不重复元素的序列。
基本功能是进行成员关系测试和删除重复元素
可以使用大括号 { } 或者 set() 函数创建集合，注意：创建一个空集合必须用 set() 而不是 { }，因为 { } 是用来创建一个空字典。
a = {"adds", "ada"}
b = set('asdfd')
if ('s' in b):#判断"s"是否在集群b中

6.Dictionary（字典）
字典是一种映射类型，字典用"{ }"标识，它是一个无序的键(key) : 值(value)对集合。
键(key)必须使用不可变类型。
	dic = {'one':'frist',"two":"secend"}
	
2.Python逻辑运算符
and	x and y	布尔"与" - 如果 x 为 False，x and y 返回 False，否则它返回 y 的计算值。	(a and b) 返回 20。
or	x or y	布尔"或" - 如果 x 是 True，它返回 x 的值，否则它返回 y 的计算值。	(a or b) 返回 10。
not	not x	布尔"非" - 如果 x 为 True，返回 False 。如果 x 为 False，它返回 True。	not(a and b) 返回 False

3.Python成员运算符
除了以上的一些运算符之外，Python还支持成员运算符，测试实例中包含了一系列的成员，包括字符串，列表或元组。
运算符	描述	实例
in	如果在指定的序列中找到值返回 True，否则返回 False。	x 在 y 序列中 , 如果 x 在 y 序列中返回 True。
not in	如果在指定的序列中没有找到值返回 True，否则返回 False。	x 不在 y 序列中 , 如果 x 不在 y 序列中返回 True。
以下实例演示了Python所有成员运算符的操作：

4.Python身份运算符
身份运算符用于比较两个对象的存储单元
运算符	描述	实例
is	is 是判断两个标识符是不是引用自一个对象	x is y, 类似 id(x) == id(y) , 如果引用的是同一个对象则返回 True，否则返回 False
is not	is not 是判断两个标识符是不是引用自不同对象	x is not y ， 类似 id(a) != id(b)。如果引用的不是同一个对象则返回结果 True，否则返回 False。
id()函数返回变量的地址
python是动态解析变量的，在运行时解析
s 与 == 区别：
is 用于判断两个变量引用对象是否为同一个， == 用于判断引用变量的值是否相等。
 
 构建列表:
 list = [i for i in range(0,14)]
 
 while 可与 else联合使用

shell使用seq python使用range
Python3 迭代器与生成器
迭代是Python最强大的功能之一，是访问集合元素的一种方式。
迭代器是一个可以记住遍历的位置的对象。
迭代器对象从集合的第一个元素开始访问，直到所有的元素被访问完结束。迭代器只能往前不会后退。
迭代器有两个基本的方法：iter() 和 next()。
字符串，列表或元组对象都可用于创建迭代器：
list=[1,2,3,4]
it = iter(list)    # 创建迭代器对象
print (next(it))   # 输出迭代器的下一个元素 
生成器
在 Python 中，使用了 yield 的函数被称为生成器（generator）。
跟普通函数不同的是，生成器是一个返回迭代器的函数，只能用于迭代操作，更简单点理解生成器就是一个迭代器。
在调用生成器运行的过程中，每次遇到 yield 时函数会暂停并保存当前所有的运行信息，返回yield的值。并在下一次执行 next()方法时从当前位置继续运行。
以下实例使用 yield 实现斐波那契数列：

 可更改(mutable)与不可更改(immutable)对象
在 python 中，strings, tuples, 和 numbers 是不可更改的对象，而 list,dict 等则是可以修改的对象。
不可变类型：变量赋值 a=5 后再赋值 a=10，这里实际是新生成一个 int 值对象 10，再让 a 指向它，而 5 被丢弃，不是改变a的值，相当于新生成了a。
可变类型：变量赋值 la=[1,2,3,4] 后再赋值 la[2]=5 则是将 list la 的第三个元素值更改，本身la没有动，只是其内部的一部分值被修改了。
python 函数的参数传递：

不可变类型：类似 c++ 的值传递，如 整数、字符串、元组。如fun（a），传递的只是a的值，没有影响a对象本身。比如在 fun（a）内部修改 a 的值，只是修改另一个复制的对象，不会影响 a 本身。
可变类型：类似 c++ 的引用传递，如 列表，字典。如 fun（la），则是将 la 真正的传过去，修改后fun外部的la也会受影响
python 中一切都是对象，严格意义我们不能说值传递还是引用传递，我们应该说传不可变对象和传可变对象。
 调用函数时，如果没有传递参数，则会使用默认参数。以下实例中如果没有传入 age 参数，则使用默认值：
#!/usr/bin/python3
 
#可写函数说明
def printinfo( name, age = 35 ):
 
 python 可变参数函数格式
 
 def func (argv, *args):
	print (argv)
	for var in args:
		print (var)
匿名函数 lambda
 
 
列表推导式
>>> vec = [2, 4, 6]
>>> [3*x for x in vec]
[6, 12, 18]

>>> [[x, x**2] for x in vec]
[[2, 4], [4, 16], [6, 36]]
 
 Python3 错误和异常
 1语法错误
 SyntaxError: invalid syntax
 
 2异常
 NameError: 
 TypeError:
 除 SyntaxError:的大部分就是异常
 
 
 异常处理
以下例子中，让用户输入一个合法的整数，但是允许用户中断这个程序（使用 Control-C 或者操作系统提供的方法）。用户中断的信息会引发一个 KeyboardInterrupt 异常。
>>> while True:
        try:
            x = int(input("Please enter a number: "))
            break
        except ValueError:
            print("Oops!  That was no valid number.  Try again   ")
   
try语句按照如下方式工作；
首先，执行try子句（在关键字try和关键字except之间的语句）
如果没有异常发生，忽略except子句，try子句执行后结束。
如果在执行try子句的过程中发生了异常，那么try子句余下的部分将被忽略。如果异常的类型和 except 之后的名称相符，那么对应的except子句将被执行。最后执行 try 语句之后的代码。
如果一个异常没有与任何的except匹配，那么这个异常将会传递给上层的try中。
一个 try 语句可能包含多个except子句，分别来处理不同的特定的异常。最多只有一个分支会被执行。
处理程序将只针对对应的try子句中的异常进行处理，而不是其他的 try 的处理程序中的异常。
一个except子句可以同时处理多个异常，这些异常将被放在一个括号里成为一个元组，例如:
    except (RuntimeError, TypeError, NameError):
        pass

self代表类的实例，而非类
类的方法与普通的函数只有一个特别的区别——它们必须有一个额外的第一个参数名称, 按照惯例它的名称是 self。
与C++的this指针差不多

python 的变量随处定义随处使用
从执行结果可以很明显的看出，self 代表的是类的实例，代表当前对象的地址，而 self.class 则指向类。
 self 不是 python 关键字，我们把他换成 runoob 也是可以正常执行的:只要是第一个参数就行
 
 #定义私有属性,私有属性在类外部无法直接进行访问
    __weight = 0
私有属性只能在类的方法访问
继承
Python 同样支持类的继承，如果一种语言不支持继承，类就没有什么意义。派生类的定义如下所示:
class DerivedClassName(BaseClassName1):
    <statement-1>
    .
    .
    .
    <statement-N>
需要注意圆括号中基类的顺序，若是基类中有相同的方法名，而在子类使用时未指定，python从左至右搜索 即方法在子类中未找到时，从左到右查找基类中是否包含方法。
BaseClassName（示例中的基类名）必须与派生类定义在一个作用域内。除了类，还可以用表达式，基类定义在另一个模块中时这一点非常有用:
class DerivedClassName(modname.BaseClassName):

类属性与方法
类的私有属性
__private_attrs：两个下划线开头，声明该属性为私有，不能在类地外部被使用或直接访问。在类内部的方法中使用时 self.__private_attrs。
类的方法
在类地内部，使用 def 关键字来定义一个方法，与一般函数定义不同，类方法必须包含参数 self，且为第一个参数，self 代表的是类的实例。
self 的名字并不是规定死的，也可以使用 this，但是最好还是按照约定是用 self。
类的私有方法
__private_method：两个下划线开头，声明该方法为私有方法，只能在类的内部调用 ，不能在类地外部调用。self.__private_methods。
实例

类的专有方法：
__init__ : 构造函数，在生成对象时调用
__del__ : 析构函数，释放对象时使用
__repr__ : 打印，转换
__setitem__ : 按照索引赋值
__getitem__: 按照索引获取值
__len__: 获得长度
__cmp__: 比较运算
__call__: 函数调用
__add__: 加运算
__sub__: 减运算
__mul__: 乘运算
__div__: 除运算
__mod__: 求余运算
__pow__: 乘方


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 