/*C++面向对象编程：

类：
我们使用类定义自己的数据类型，通过定义新的类来来反映待解决的问题中的各种概念和解决问题的方法
类的基本思想是数据抽象和封装。
数据抽象：数据抽象是一种依赖接口和实现分离的编程技术，类的接口包括用户能执行的操作，类的实现则包括类的数据成员
负责接口实现的函数以及定义类所需的各种私有函数
封装：封装实现了类的接口和实现和实现的分立,封装后的类隐藏了它实现的细节，也就是说，类
的用户只能使用接口而无法访问实现部分
类要实现数据抽象和封装，需要定义一个一个抽象数据类型，
在抽象数据类型中，由类的设计者负责考虑类的实现过程，而调用此类的程序员只需考虑类能做什么，怎么用，而无需考虑类的实现细节；
访问数据成员：Box.box1;
box1.length;
访问类成员函数box1.Get_Volume();
public、private、protected
成员和类的默认访问修饰符是 private。
class SmallBox:Box // SmallBox 是派生类
{
   public:
      void setSmallWidth( double wid );
      double getSmallWidth( void );
};

skipws忽略空格符将空白符后的内容也读入
noskipws 遇见空格停止读入
assert(int expr) expr为假立即退出程序;不执行下面代码；
创建枚举，需要使用关键字 enum。枚举类型的一般形式为：
enum enum-name { list of names } var-list; 
在这里，enum-name 是枚举类型的名称。名称列表 { list of names } 是用逗号分隔的。
例如，下面的代码定义了一个颜色枚举，变量 c 的类型为 color。最后，c 被赋值为 "blue"。
enum color { red, green, blue } c;
c = blue;
默认情况下，第一个名称的值为 0，第二个名称的值为 1，第三个名称的值为 2，以此类推。但是，您也可以给名称赋予一个特殊的值，只需要添加一个初始值即可。例如，在下面的枚举中，green 的值为 5。
enum color { red, green=5, blue };
在这里，blue 的值为 6，因为默认情况下，每个名称都会比它前面一个名称大 1。
整数常量也可以带一个后缀，后缀是 U 和 L 的组合，U 表示无符号整数（unsigned），L 表示长整数（long）。后缀可以是大写，也可以是小写，U 和 L 的顺序任意。
请注意，把常量定义为大写字母形式，是一个很好的编程实践。const int MAXLEN = 1024;
下面是我从C语言核心技术一书上摘的：
void *memcpy( void * restrict dest ,const void * restrict src,sizi_t n) 这是一个很有用的内存复制函数，由于两个参数都加了restrict限定，
所以两块区域不能重叠，即 dest指针所指的区域，不能让别的指针来修改，即src的指针不能修改. 相对应的别一个函数 memmove(void *dest,const void * src,size_t)
则可以重叠。
最后注意一点，restrict是C99中定义的关键字，C++目前并未引入；在GCC可通过使用参数" -std=c99"
来开启对C99的支持
C++中的类static变量一定要由类初始化，int Box::sta = 89;
i = j = 0;
i > j ? i++ : j++;
i = 0, j = 1;
短路运算
C++ 随机数
在许多情况下，需要生成随机数。关于随机数生成器，有两个相关的函数。一个是 rand()，该函数只返回一个伪随机数。生成随机数之前必须先调用 srand() 函数。
下面是一个关于生成随机数的简单实例。实例中使用了 time() 函数来获取系统时间的秒数，通过调用 rand() 函数来生成随机数：
int arr[10][10];
arr[0][2]:int
arr[0]:int *
&arr[0]:int(*)[10]
arr:int(*)[10]
&arr:int(*)[10][10]
C++ 引用 vs 指针
引用很容易与指针混淆，它们之间有三个主要的不同：
不存在空引用。引用必须连接到一块合法的内存。
一旦引用被初始化为一个对象，就不能被指向到另一个对象。指针可以在任何时候指向到另一个对象。
引用必须在创建时被初始化。指针可以在任何时间被初始化。
试想变量名称是变量附属在内存位置中的标签，您可以把引用当成是变量附属在内存位置中的第二个标签。
因此，您可以通过原始变量名称或引用来访问变量的内容。例如：
范围解析运算符 :: 来定义
私有成员变量或函数在类的外部是不可访问的，甚至是不可查看的。只有类和友元函数可以访问私有成员。类成员函数可访问
class Test1
{
public:
    Test1(int n)
    {
        num=n;
    }//普通构造函数
private:
    int num;
};
class Test2
{
public:
    explicit Test2(int n)
    {
        num=n;
    }//explicit(显式)构造函数
private:
    int num;
};
int main()
{
    Test1 t1=12;//隐式调用其构造函数,成功
    Test2 t2=12;//编译错误,不能隐式调用其构造函数
    Test2 t2(12);//显式调用成功
    return 0;
}
C++中的explicit
Test1的构造函数带一个int型的参数，代码23行会隐式转换成调用Test1的这个构造函数。而Test2的构造函数被声明为explicit
（显式），这表示不能通过隐式转换来调用这个构造函数，因此代码24行会出现编译错误。
普通构造函数能够被隐式调用。而explicit构造函数只能被显式调用。
使用初始化列表来初始化字段：适用于初始化const类型变量
Line::Line( double len): length(len)
如果在类中没有定义拷贝构造函数，编译器会自行定义一个。如果类带有指针变量，并有动态内存分配，则它必须有一个拷贝构造函数。
友元函数可以访问类中所有成员，包括私有和保护变量
类的静态函数不可调用成员函数，和成员变量，只能访问静态变量和static函数
static类属性，非static，成员属性
const函数不能修改任何成员属性，放在函数后，const函数只能调用const函数
把一个类定义为另一个类的友元类，会暴露实现细节，从而降低了封装性。理想的做法是尽可能地对外隐藏每个类的实现细节。
void func(void) const{
	....
}
friend友元函数可以访类的私有变量，类可以访问友元类中所以私有变量
malloc/free 与 new/delete 的区别
malloc分配的空间需要强转
new不需要强转malloc给对象开辟空间时不会构造对象，单独开辟一片空间
而new可以在分配是可以构造Array *ptr = new Array(int);
new/delete是运算符//天生支持
malloc/free是库函数
定义对象数组只能调用默认构造函数
Array *ptr = new Array[10];
delete [] ptr;
命名空间就解决重名问题
<<重载时一定要定义友元函数因为应用引用到ostream类，不能直接在类里使用

C++运行出错处理
运行错误抛出一个异常（异常是一个对象）throw class  IndexError;创建对象
处理对象try catch处理异常
class Box{
	public:
	Box()
	{
		
	}
}
class Box1 : public Box{
	public:
	Box1() : Box()  //在构造自己的同时构建父类
	{
		
	}
}
继承目的：代码重用
抽象类：不允许定义对象，装一堆纯虚函数
C++的四种强制类型转换，所以C++不是类型安全的。分别为：static_cast(j基本数据类型转换) 
, dynamic_cast , const_cast , reinterpret_cast(指针数据类型转换)
reset重新分配新指针
clid.Parent::id
child.Praent1.id
虚继承virtual

*/

C++ primer 第五版笔记
UNIX下查看程序返回码：echo $?
Windows下查看程序返回码：echo %ERRORLEVEL%
低版本GCC编译器编译C++11标准是加上-std=c++0x编译选项
c++中的标准输入输出
iostream库包含两个基本类，istream,ostream
三个标准流：
1、标准输出流 cout(行缓冲)
2、便准输入流 cin(行缓冲)
3、标准错误流 cerr(不缓冲)clog(带缓冲)
cout 和 cin 是行缓冲，只有当缓冲区满或则遇到换行符，或程序结束才会刷新缓冲区
所以编写程序时因注意这个问题
命名空间：namespace 作用是防止函数与变量重名
所有的标准库里面的定义名字都放在std中，所有引用是格式:std::cout
::作用域运算符
注释应防止嵌套
语句块里面定义的变量只能语句块内可使用，也就是作用域就在语句块内
{
	int a = 23;
}
cout << a << endl; //错误，a未定义
文件重定向 > <
hello.exe > outfile  //将hello.exe输出重定向到outfile中
hello.exe < infile   //将infile的文件内容输入到hello.exe
类的概念：
成员函数(成员方法)
成员变量(成员属性)
C++ 中的数据类型：
1、基本数据类型：算术基本类型、空类型(void)
bool char wchar_t char16_t(unicode) char32_t(nuicode) short
int long float double (long long) (long double)
bool :false true
除了 bool 和 char16_t char32_t 外，其余的都是可带符号的数据类型
C++里的基本数据类型能发生自动类型转换
也可根据自身要求强制类型转换
***有符号数和无符号数发送运算，和自动转成无符号数参与运算*** 
***无符号数的值不会小于零，所以使用做循环因子时应注意******
浮点型可用指数形式E或e e表示10 
字面值修饰：前缀：u： char16_t U: char32_t  L: wchar_t 
后缀：U or u unsigned
L or l long
ll or LL long long
F or f float
变量的初始化和赋值
int i = 10; //定义一个变量并初始化（初始化即是分配空间）
i = 32; //赋值，擦出i原有的值并给他赋一个新值
所以说初始化和赋值不是同一个概念
C++ 中的列表初始化
int a = 0;
int a = {0};
int a{0};
int a(0);

变量的声明和定义
可以有多个声明但只能有一处定义，声明用 extern 

引用必须被初始化,也就是说声明时就要初始化
初始化的过程被称作绑定
应用就是变量的别名
指针一定要赋初值NULL
******************指针：*************************
*************指针就是地址的偏移 
所有的指针都是四个字节(32位机)，所有**********
sizeof(*p) = 4;(32位机)
不同类型的指针都是一个存放地址的变量********
唯一不同的就是当指针计算时所偏移的长度不同*************************************
int *p = 1;
p + 1 = 4;
char *p = 1;
p + 1 = 2;
double *p = 1;
p + 1 = 9;
sizeof(struct std) = 24;
********************
struct std *p = 1;
p + 1 = 25;
*******************************
void* 为什么不转换成确定类型就不能参与运算？
就是因为编译器不知道他是什么类型，装的是什么类型
所以void* 使用时必须转换成确定的数据类型
但是唯一的好处就是可以可以装任何类型的地址
指针的引用：
int a;
int *ptr = NULL;
int *&r = ptr;
r = &a =====  ptr = &a;
C++中的多继承容易造成二义性
所以大部分语言都抛弃了多继承机制
const int *ptr = NULL;  //底层指针，常量指针，指向的值不能改变
int *const ptr = NULL;  //顶层指针， 指针常量， 指针本身不会变
常量表达式constexpr 如果你认定变量是一个常量表达式
可以把他定义成constexpr
constexpr int mf = 0; //20是常量表达式
constexpr int limist = mf + 1;
constexpr int size = size();  //size()函数也必须是constexpr修饰

auto编译器自动分析变量的类型；
vector 容器，用来装同一类型的数的集合，是一个模板，定义时vector<type> value_array;
vector 是一种模板而非容器
迭代器，除了vector外，标准库定义了其他几种容器，所有标准库容器都支持迭代器，但只有
少数支持下标运算，严格来说，string不属于容器类型，但string支持与容器相似的操作，
vector支持下标运算符，这点和string一样：string支持迭代器，这也和vector是一样的。

迭代器判空条件：vector vec;   vec != vec.end();
迭代器返回类指针类型，要先取址才可使用，迭代器元素移动++vec;
迭代器返回类型：iterator， const_iterator
如果迭代器类型是常量只能使用const_iterator
如果不是常量，两个都可使用。
begin()和end()返回iterator和const_iterator；类型
begin()和end()返回itertor类型，类指针类型，可以用来访问迭代器元素
1）const成员函数可以访问非const对象的非const数据成员、const数据成员，也可以访问const对象内的所有数据成员；
2）非const成员函数可以访问非const对象的非const数据成员、const数据成员，但不可以访问const对象的任意数据成员；
3）作为一种良好的编程风格，在声明一个成员函数时，若该成员函数并不对数据成员进行修改操作，应尽可能将该成员函数声明为const成员



gdb笔记:
GDB是一个由GNU开源组织发布的、UNIX/Linux操作系统下的、基于命令行的、功能强大的程序调试工具。
GDB固然强大，但日常调试几个常用命令足矣：
GDB调试可分为几类:
1. 单步执行和跟踪函数调用
2. 断点
3. 观察点
4. 段错误

通用命令:help查看GDB帮助help command查看某一条命令的子命令帮助
file 加载需要调试的目标程序
1. 单步执行和跟踪函数调用
1.1 list
l(list):列出源代码
list line1,line2(列出指定行范围)
list funcname(列出指定函数)
list *(adderrs)(列出指定地址的代码)eg:list *(0x400757)
list 依赖于源文件，如果没有源文件，list是不起作用的
1.2 quit
q(quit) 退出调试

1.3 start
start(开始运行代码)
1.4 next
n(next)执行一行源程序代码，此行代码中的函数调用也一并执行。
n 相当于其它调试器中的“Step Over (单步跟踪)”。
1.5 setp
s(step)执行一行源程序代码，如果此行代码中有函数调用，则进入该函数；
s 相当于其它调试器中的“Step Into (单步跟踪进入)”；
以上两个命令必须在有源代码调试信息的情况下才可以使用（GCC编译时使用“-g”参数）。

1.5 run
r(run)运行被调试的程序。
如果此前没有下过断点，则执行完整个程序；如果有断点，则程序暂停在第一个可用断点处。
1.6 backtrace
bt(backtrace)回溯,查看函数调用的栈帧：查看各级函数调用及参数

1.7 info
i(info):可以查看很多信息，具体可参考help info
info locals:查看函数局部变量的值
1.8 frame 帧
f(frame):如果想查看 main 函数当前局部变量的值也可以做到，先用 frame 命令（简写为
f）选择 1 号栈帧然后再查看局部变量：

1.9 print
p(print):打印制定变量的值
1.10 finish
finish：让程序一直运行到从当前函数返回为止(不是run，是从当前函数执行返回，应该不作用于main函数)
1.11 set
set var var="" 在程序调适中设定某个变量的值。(print var="")也可达到效果

2.断点 breakpoint
2.1 display(变量跟踪)
display var:重点观察某个变量的值，每次运行到变量时都打印出此变量的值
2.2 undisplay
undisplay n :取消跟踪显示 n为变量标号
2.3 break
b(breakt):设置断点（一般与c(continue)命令联合使用）
b line：根据行号来设置断点
b funcname ：根据函数名设置断点
b *(address):根据指定地址设置断点

2.4 continue
c (continue):连续运行而非单步运行，程序到达断点会自动停下来
2.5 info breakpoint
查看设置端点的信息
每个断点都有一个编号，可以用编号指定删除某个断点：

2.6 delete breakpoints 

delete breakpoints 2：可以用编号指定删除某个断点
2.7 disable breakpoints 3：禁用指定断点，并不是删除
2.8. enable breakpoints 3:重新使能断点
2.9
break ... if ... eg:break 23 if var!=0 当var为true时在23行设置断点
设置条件断点

3.观察点(watch)
x/nb var:x 命令打印指定存储单元的内容。nb 是打印格式，b 表示每个字节一组，n 表示
打印n组

watch
可以用观察点（Watchpoint）来跟
踪。我们知道断点是当程序执行到某一代码行时中断，而观察点是当程序访问某
个存储单元时中断，如果我们不知道某个存储单元是在哪里被改动的，这时候观
察点尤其有用。下面删除原来设的断点，从头执行程序，重复上次的输入，用
watch 命令设置观察点，跟踪 input[4]后面那个字节（可以用 input[5]表示，
虽然这是访问越界）：
watch input[5]
info watchpoint 查看观察点信息
观察点一般设置在循环当中

4. 段错误
4.1如果程序运行时出现段错误，用 gdb 可以很容易定位到究竟是哪一行引发的段错
run 运行程序
bt 查看指定函数栈


C++ STL 
Standard Template Library的简称，中文名标准模板库
STL可分为容器(containers)、迭代器(iterators)、算法(algorithms)、空间配置器(allocator)、配接器(adapters)、仿函数(functors)六个部分。

重要的前三种
容器部分主要由头文件
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <stack>
#include <queue>
组成。对于常用的一些容器和容器适配器（可以看作由其它容器实现的容器），
可以通过下表总结一下它们和相应头文件的对应关系。

一、
容器（container）：容器是数据在内存中组织的方法，例如，数组、堆栈、队
列、链表或二叉树（不过这些都不是 STL 标准容器）。STL 中的容器是一种存
储 T（Template）类型值的有限集合的数据结构,容器的内部实现一般是类。这
些值可以是对象本身，如果数据类型 T 代表的是 Class 的话

二、
迭代器(iterator)：一旦选定一种容器类型和数据行为(算法)，那么剩下唯一
要他做的就是用迭代器使其相互作用。可以把达代器看作一个指向容器中元素
的普通指针。可以如递增一个指针那样递增迭代器，使其依次指向容器中每一
个后继的元素。迭代器是 STL 的一个关键部分，因为它将算法和容器连在一
起。

三、
算法（algorithm）：算法是应用在容器上以各种方法处理其内容的行为或功
能。例如，有对容器内容排序、复制、检索和合并的算法。在 STL 中，算法是
由模板函数表现的。这些函数不是容器类的成员函数。相反，它们是独立的函
数。令人吃惊的特点之一就是其算法如此通用。不仅可以将其用于 STL 容器，
而且可以用于普通的 C＋＋数组或任何其他应用程序指定的容器

1.容器

1.序列式容器（队列容器（顺序容器），队列容器按照线性排列来存储 T 类型值的集合，
队列的每个成员都有自己的特有的位置。顺序容器有向量类型、双端队列类
型、链表类型三种）

1.1向量(vector) 连续存储的元素<vector>
1.2链表(list) 由节点组成的双向链表，每个结点包含着一个元素<list>
1.3双端队列(deque) 连续存储的指向不同元素的指针所组成的数组<deque>

2.适配器容器
2.1栈(stack) 后进先出的值的排列 <stack>
2.2队列(queue) 先进先出的值的排列 <queue>
2.3优先队列(priority_queue) 元素的次序是由作用于所存储的值对上的某种谓词决定的的一种队列 <queue>

3关联式容器
3.1集合(set) 由节点组成的红黑树，每个节点都包含着一个元素，节点之间以某种作用于元素对的谓词排列，没有两个不同的元素能够拥有相同的次序 <set>
3.2多重集合(multiset) 允许存在两个次序相等的元素的集合 <set>
3.3映射(map) 由{键，值}对组成的集合，以某种作用于键对上的谓词排列 <map>
3.4多重映射(multimap) 允许键对有相等的次序的映射 <map>


=========================Vector============================
vector（向量）：vector 是一种动态数组（长度可变），是基本数组的类模板。其内部定义了很多基本操作。既然这是一个类，那么它就会
有自己的构造函数。vector 类中定义了 4 中种构造函数：
vector<int> vec:默认构造函数,构造一个长度为0的空向量
vector<int> vec(n,0):初始化向量长度为n，值为0
vector<int> vec(vec1):复制构造函数，构造一个新的向量，作为已存在的向量的完全复制
vector<int> vec(frist, last):带两个常量参数的构造函数，产生初始值为一个区间的向量
eg:int arr[] = {1, 2, 3, 4, 5};vector<int> vec(arr, arr+5)

以下为vector的简单实例子:

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
	int arr[] = {1, 2, 3, 4, 5};
	const char *str = "Hello STL";
	vector<int> vec_i(arr, arr+5);
	vector<char> vec_c(str, str + strlen(str));
	
	for (vector<int>::iterator itr_i = vec_i.begin(); itr_i != vec_i.end(); itr_i++)
	{
		cout << *itr_i;
	}
	cout << endl;
	
	for (vector<char>::iterator itr_c = vec_c.begin(); itr_c != vec_c.end(); itr_c++)
	{
		cout << *itr_c
	}
	cout << endl;
	
	/*
	for (int i = 0; i < vec_i.size(); i++)
	{
		cout << cec_i[i];
	}
	*/
	
	return 0;
}

result:
12345
Hello STL

vector成员方法:
#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
	vector<int> vec;
	
	////测试添加和插入成员函数，vector 不支持从前插入
	vec.push_back(1); //从后面添加一个成员
	vec.insert(vec1.begin()+1,5);//在 vec1 第一个的位置上插入成员 5
	//从 vec1 第一的位置开始插入 vec3 的所有成员
	vec1.insert(vec1.begin()+1,vec3.begin(),vec3.end());
	vec2.assign(8,1); // 重新给 vec2 赋值，8 个成员的初始值都为 1
	//测试引用类函数
	cout<<"vec1.front()="<<vec1.front()<<endl;//vec1 第零个成员
	cout<<"vec1.back()="<<vec1.back()<<endl;//vec1 的最后一个成员
	cout<<"vec1.at(4)="<<vec1.at(4)<<endl;//vec1 的第五个成员
	//测试移出和删除
	vec1.pop_back();//将最后一个成员移出 vec1
	vec1.erase(vec1.begin()+1,vec1.end()-2);//删除成员
	//显示序列的状态信息
	cout<<"vec1.size(): "<<vec1.size()<<endl;//打印成员个数
	cout<<"vec1.empty(): "<<vec1.empty()<<endl;//清空
	
}

2.u 双端队列（qeque 容器类）：
deque（读音：deck，意即：double queue，#include<qeque>）容器类与
vector 类似，支持随机访问和快速插入删除，它在容器中某一位置上的操作所
花费的是线性时间。与 vector 不同的是，deque 还支持从开始端插入数据：
push_front()。此外 deque 也不支持与 vector 的 capacity()、reserve()类似
的操作。
支持前插:
#include <iostream>
#include <deque>
#include <cassert>

using namespace std;

void put_deque(deque<int> que, const char *name)
{
	assert(name);
	
	deque<int>::iterator itr_q;
	
	cout << "=========" << name << endl; 
	for (itr_q = que.begin(); itr_q != que.end(); itr_q++)
	{
		cout << *itr_q << " ";
	}
	cout << endl;
}

int main(int argc, char *argv[])
{
	deque<int> que(5, 0);
	
	put_deque(que, "initQue");
	//test push_back
	que.push_back(12);
	que.push_back(13);
	put_deque(que, "test push_back");
	//test push_front
	que.push_front(1);
	que.push_front(2);
	put_deque(que, "test push_front");
	//test pop_back
	que.pop_back();
	que.pop_back();
	put_deque(que, "test pop_back");
	//test pop_front
	que.pop_front();
	que.pop_front();
	put_deque(que, "test pop_front");
	
}
result:
=========initQue
0 0 0 0 0 
=========test push_back
0 0 0 0 0 12 13 
=========test push_front
2 1 0 0 0 0 0 12 13 
=========test pop_back
2 1 0 0 0 0 0 
=========test pop_front
0 0 0 0 0 
3.List（#include<list>）又叫链表，是一种双线性列表，只能顺序访问（从
前向后或者从后向前），图 2 是 list 的数据组织形式。与前面两种容器类有一
个明显的区别就是：它不支持随机访问。要访问表中某个下标处的项需要从表
头或表尾处（接近该下标的一端）开始循环。而且缺少下标预算符：
operator[]。
同时，list 仍然包涵了
erase(),begin(),end(),insert(),push_back(),push_front()这些基本函数，
下面我们来演示一下 list 的其他函数功能。merge()：合并两个排序列表；
splice()：拼接两个列表；sort()：列表的排序。
#include <iostream>
#include <string>
#include <list>
using namespace std;

void PrintIt( list<int> n )
{
	for ( list<int>::iterator iter = n.begin(); iter != n.end(); ++iter )
		cout << *iter << " ";   /* 用迭代器进行输出循环 */
}


int main()
{
	list<int> listn1, listn2;       /* 给 listn1,listn2 初始化 */
	listn1.push_back( 123 );
	listn1.push_back( 0 );
	listn1.push_back( 34 );
	listn1.push_back( 1123 );       /* now listn1:123,0,34,1123 */
	listn2.push_back( 100 );
	listn2.push_back( 12 );         /* now listn2:12,100 */
	listn1.sort();
	listn2.sort();                  /* 给 listn1 和 listn2 排序 */
	/* now listn1:0,34,123,1123 listn2:12,100 */
	PrintIt( listn1 );
	cout << endl;
	PrintIt( listn2 );
	listn1.merge( listn2 );         /* 合并两个排序列表后,listn1:0，12，34，100，123， */

	cout << endl;
	PrintIt( listn1 );
}



 result:
 0 34 123 1123 
12 100 
0 12 34 100 123 1123

C多线程编程:
条件变量需和互斥锁结合才可达到效果
共同使用同个互斥锁的线程都有相同jilve强到锁

静态数据成员
我们可以使用 static 关键字来把类成员定义为静态的。当我们声明类的成员为静态时，这意味着无论创建多少个类的对象，静态成员都只有一个副本
静态成员在类的所有对象中是共享的。如果不存在其他的初始化语句，在创建第一个对象时，所有的静态数据都会被初始化为零。我们不能把静态成员
的初始化放置在类的定义中，但是可以在类的外部通过使用范围解析运算符 :: 来重新声明静态变量从而对它进行初始化

静态函数成员
如果把函数成员声明为静态的，就可以把函数与类的任何特定对象独立开来。静态成员函数即使在类对象不存在的情况下也能被调用，静态函数只要使用类名加范围解析运算符 :: 就可以访问。
静态成员函数只能访问静态数据成员，不能访问其他非静态成员函数和类外部的其他函数。
静态成员函数有一个类范围，他们不能访问类的 this 指针。您可以使用静态成员函数来判断类的某些对象是否已被创建。
下面的实例有助于更好地理解静态函数成员的概念：

c++虚函数，virtual void *entry() = 0;一般在父类中定义，在子类中实现，子类实现时void *entry() override; override:覆盖父类方法

extern "C" int function();告诉C++编译器该函数以C的方式编译（为了避免函数重载产生的问题）
1.C++引用C
/***** C头文件c.h *****/  
#ifndef  _C_H_  
#define _C_H_   
#ifdef __cplusplus    /*C++编译器包含的宏，例如用g++编译时，该宏就存在，则下面的语句extern "C"才会被执行*/  
extern "C" {          /*C++编译器才能支持，C编译器不支持*/  
#endif   
void C_fun();   
#ifdef __cplusplus  
}  
#endif  
#endif  

/***** C源文件c.c *****/  
＃include "c.h"  
void C_fun()  
{  
    /*dosomething*/  
}  

功能：在文件cpp.cpp中调用文件c.c中的函数C_fun()  
/****** C++源文件cpp.cpp ******/  
＃include "c.h"  
int main()  
{  
     C_fun()  
}  

2.C引用C++
/**** C++头文件 cpp.h *****/  
#ifndef  CPP_H  
#define CPP_H  
  
extern "C" int add( int x, int y );  
  
#endif  

/**** C++源文件 cpp.cpp *****/  
＃include "cpp.h"  
int add( int x, int y )  
{  
    return x + y;  
}  

功能：C文件中调用C++的接口  
/**** C源文件c.c *****/  
extern int add( int x, int y );  
int main( int argc, char* argv[])  
{  
      
}  

类的static数据成员与静态成员函数
class CBook{
	public:
	static int m_static;//静态数据成员
	int m_data;//非静态数据成员
	static int function(int a, int b);//静态成员函数
	int function1(int a, int b);
}

1.静态数据成员可以通过类名直接访问，也可通过对象名访问，但静态数据成员只保留一个副本
2.静态数据成员可以使当前类类型，也可以是当前类指针，而普通非静态成员不可以定义成当前类类型
class CBook{
	public:
		static CBook cb; //允许
		CBook cb1;//不允许
		CBook *ptr;//允许
		static CBook *ptr1;//允许
}

3.静态类的成员函数能作为其他成员函数的初始化参数，而普通成员函数不能
4.静态成员函数可以访问类的构造函数****
class CBook{
	public:
		static int a;
		int b;
		int fuc1(int c = a);//允许
		int func2(int c = b);//不允许
}

4.类的静态成员函数只能访问类的静态函数成员，而不能访问类的非静态成员，包括非静态成员函数，且静态成员函数在外部定义
时就不能加static关键字了
5.静态成员函数后不能再加const关键字

C++中的const
当const在函数名前面的时候修饰的是函数返回值，在函数名后面表示是常成员函数，该函数不能修改对象内的任何成员，只能发生读操作，不能发生写操作。
const永远是readonly,
1.const 修饰变量时说明该变量是只读变量
2.const 修饰函数时自能放在函数后面,而且只有类的成员函数才能使用const关键字修饰，exmaple:
class CBook{
	public:
		int print()const{
			std::cout << "This a const functon"
		}
};
const成员函数里面的所有非静态成员变量都不能修改，可以修改static型数据成员
const定义的对象(注意是对象)自能访问const类型的成员函数，不能访问非const型的成员函数
非const对象可以访问const定义的成员函数

const常量的初始化必须在构造函数初始化列表中初始化，而不可以在构造函数函数体内初始化
const int func()const{
	
}//一个返回常量的常量成员函数

类可以嵌套：
class Class1{
	
	public:
		class Class2{
			public:
				friend class Class1;
				int m_data;
			private:
				int m_private;
		}
		int m_data;
		Class2 c2;
		void func();
}

上述的Class2在外围类中不可见，自可以通过class1去引用，由于class1为class2的友元类，所以class2可以访问class1中的所有private成员
局部类：
定义在函数中的类，只能在该函数内使用，外部不可见

友元函数：友元函数能访问类的private,protected数据成员
class CBook{
	public:
		friend int function();
}
友元类：友元类能访问类的private,protected数据成员
class CBook{
	public:
		friend class CCook;
}
友元成员方法，友元成员函数能访问类的private,protected数据成员
class CBook{
	public:
		friend int CCook::func();
}//只有CCook的func成员函数才能访问CBook的所有数据

命名空间 namespace
namespace MyName{
	int var1;
	int var2;
}
可在头文件中声明命名空间的函数，在源文件中定义
/*****Detail.h****/
namespace MyName{
	int func();
}

/**Detail.cc**/
int MyName::func(){
	...
}
命名空间的定义可在多个文件中进行，是一个叠加的过程，但是不能出现同名的定义
当使用 using namespace myname;
引用命名空间时，因注意避免与其他命名空间的名字相冲突
与当前的文件重名不会引起冲突，但是命名空间的成员会被当前函数的变量覆盖
命名空间可以嵌套，引用遵从从外到里的规则，using namespace Myname::Myname1;//只可以使用Myname1中的数据成员
面向对象的三个特征:封装、继承、多态
公有继承（public）：当一个类派生自公有基类时，基类的公有成员也是派生类的公有成员，基类的保护成员也是派生类的保护成员，基类的私有成员不能直接被派生类访问，但是可以通过调用基类的公有和保护成员来访问。
保护继承（protected）： 当一个类派生自保护基类时，基类的公有和保护成员将成为派生类的保护成员。，private永远不可见
私有继承（private）：当一个类派生自私有基类时，基类的公有和保护成员将成为派生类的私有成员。private永远不可见

继承方式		public		protected		private
public			public		protected		不可见
protected		protected	protected		不可见
private			private		private			不可见
当子类和父类存在同名成员函数，子类的函数会覆盖父类的成员函数，以及父类的所有函数重载
C/C++编译器是一个静态绑定的过程，静态绑定即是在编译时就根据数据类型给变量分配空间，但是C++的virtual能让
程序运行时动态绑定


CMakefile.txt:
通常C++的编译选项都为CXXFLAGS C的编译选项为CFLAGE

虚继承virtual
class CAnimal{};
class CBrid : public CAnimal{};
class CFish : public CAnimal{};
class CWaterBrid : public CBrid, public CFish{};
以上class CWaterBrid wb;就会调用两次CAnimal的构造，存在两份CAnimal的复制
虚继承解决这个问题。class CBrid : virtual public CAnimal{};
class CFish : virtual public CAnimal{};
这样定义CWaterBrid时就只会存在一份CAnimal的备份
虚继承对子类没什么影响，但对于之类的子类有影响，虚继承保证了子类的子类只存在一份祖类的副本

抽象类:
含有纯虚函数的类称为抽象类，抽象类只能作为基类派生子类，派生类必须要存在纯虚函数的定义，而不能实例化对象
，但可以使用抽象类指针
纯虚函数:format
virtual int function(int args) = 0;
纯虚函数不能被继承，当基类是抽象类时，在派生类中必须给出定义，或在该类中继续将该函数定义成为纯虚函数

Template（模板）：
C++语言的高级特性，模板能使程序员快速的建立类型安全的类库集合和函数库集合；
C++模板分为类模板和函数模板：

1.函数模板：
函数模板并不是一个实在的函数，编译器并不能把它编译成可执行代码，函数模板只是对函数进行一个框架性的描述，当它具体执行时，将
根据实际参数决定其功能format:
template <class T>
void func(T args);
关键字:class typename
正确的模板函数调用方式
func<int> (T);
另一种模板函数定方式
template func<class T, int a>
T:模板参数，a:非模板参数
example:
template <class T, int len>
type Max(T array[len]){
	.....
}
虽然函数模板使用比较方便，但也会存在一个问题example：
template <class T>
T Max(T a, T b){
	return a > b ? a : b;
}
不是所有的类型都可以用'>'来比较，例如char *
这时候可以对模板函数进行重载来实现有的特殊情况

char *Max(char *a, char *b){
	if (strcmp(a, b)) {
		return a;
	}
	else {
		return b;
	}
}

2.类模板，与函数模板类似 format:
template <typename T>
class Class1{
	public:
		T var;
		T func(T args);
}
类模板不是一个真实的类，不可实例化对象，需要重新生成类 example：
Class1 <int> a;实例化对象
类模板和普通模板一样，也要对其成员函数进行定义，定义format：
template <typename T>
int Class1<T>::function() {
	...
}

类模板参数可以在定义时指定，也可以在声明时指定
template <class T1, class T2 = int>
template <class T1, class T2, int len = 10>
防止数组越界，C/C++并没有数组下标检测机制，越界访问往往会造成程序崩溃，利用函数模板与运算符重载来做到
数据下标检测
template <class T, int len>
class Array {
	T& operator[](int sub) {
		assert(sub >= 0 && sub < sub);
	}
}

定制类模板：
与模板函数重载相同，有时我们对特殊类型的实现不能通过通用方法
这时可以使用定制类模板来实现特殊类型的实现
template <typename T>
class Class1{
	public:
		T var;
		T func(T args);
}
定制类模板
class <char *> Class1 {
	public:
		char* var;
		char * func(T args);
}

定制类模板成员函数:
template <class T>
int Class1<T>func() {
	...
}

类模板中的静态数据成员:
在类模板中可以定义静态数据成员，类模板中同一类型的实例都有自己的静态数据成员，而不是所有的类模板共享一份静态成员，
这和正常类大有区别
template <class T>
int Class1<T>func() {
	static int m_Static;
}

Class1 <int> c1; //共享一份m_Static
Class1 <char> c2; //共享一份m_Static
c1 与 c2 的m_Static的副本是独立的

****************STL********************************
1.序列容器:只提供插入功能，元素都是有序的，但未经过排序，序列容器包括vector(向量)，deque（双端队列），list（链表）
vector.begin();//首元素,迭代器类型，可用*(vec.begin())取值
vector.end();//容器末尾，不包含元素，迭代器类型，可作为结束判断标志
vector 成员方法:
assign()
vec.assign(7, 100); //vec:100, 100, 100, 100, 100, 100, 100
vec.assign(vec1.frist(), vec.end());//vec将初始化为vec2的内容
向量存在[]下标运算

deque；双向队列
比vector多了push_front,pop_fornt,可在前端操作
支持[]运算

list：链表
比vector多了push_front,pop_fornt,可在前端操作
不支持[]运算
list 不允许随机访问，他必须从头开始遍历元素，所以插入与删除元素的时间复杂度相同

2.结合容器：STL容器的一种，其中元素都是经过排序的，主要通过关键字的方式来提高查询效率，主要包括set,multiset, map, multimap和hash_table
结合容器一般存在find()算法，因为结合容器的关键值是唯一的
1.set
set<int, less<int> > multset1;
set<int, less<int> >::iterator setit;
集合类模板，一个集合响链表一样顺序的存储一组值，在一个集合中，集合元素既是数据又是关键字，集合最大的特点就是元素唯一
2.multset 多重集合
多重集合与一般集合的区别在于多重集和是可以有相同的数据存在,但是元素还是有序排列,结合类容器与序列容器最大区别就是，
multset<int, less<int> > multset1;
multset<int, less<int> >::iterator setit;
3.map 映射
map 与 set、multset最大的区别是set、multset的元素即是关键字也是数据，而map有唯一的关键字，关键字和数据分开的
map支持[]运算
map<char,int,less<char> > map1;
map<char,int,less<char> >::iterator mapIter;
映射取key和value:(*iterator).first(key) (*iterator).second(value),

map[key];//下标使用
4.multmap:不支持[]运算，可存取重复的值;一个key可以对应多个值

explicit //显式的
在C++中，类默认可以隐式声明对象。example:
class CExample {
	public:
		CExample(void);
		CExample(int data1, int data2 = 4){
			...
		}
		~CExample(void);
		int dat;
		int dat1;
};

CExample Eobj(12);//合法,第二个参数有默认值
CExample CEobj = 12;//合法的隐式声明对象，等价于CExample temp(12);CEobj = CExample(temp);
上面的隐式声明调用了编译器提供的默认复制构造函数
在日常编程中，我们并不需要这种隐式声明的发生，但是在大型代码中总是会默默发生隐式转换，为了防止这种情况发生，我们可用explicit(显式)的声明函数
经过explicit关键字修饰的构造函数不能隐式调用
class CExample {
	public:
		explicit CExample(void);
		CExample(int data1, int data2 = 4){
			...
		}
		~CExample(void);
		int dat;
		int dat1;
};
CExample CEobj = 12;//不合法

set 与 map的key都只能存在一个，insert会失败，
gcc开启编译选项-D g++ source.cpp -D COMPLE_OPTION

算法:
算法(algorithm)是STL的中枢，为STL提供算法库，算法库都是模板函数。算法一般都是操作迭代器来实现
标准算法分为4个类别:非修正式序列算法,修正式序列算法、排序算法和数值算法
1.非修正序列算法不修改所作用的容器，例如：计算元素个数，查找等
2.修正序列算法，有的操作会改变容器的内容，复制，填充等
3.排序算法
4.数值算法
用时查
迭代器：
迭代器相当于指向容器元素的指针，他在容器内可以向前移动，向后移动。分类:
输入迭代器、输出迭代器、随机访问迭代器

==================================================
RTTI(run-time type indentfication)运行时类型识别 是在只有一个指向基类的指针或引用时所确定的一个对象类型；
在工程中，往往只提供一个对象的指针，但在使用时要明确这个指针的类型，利用RTTI可以获取某个对象指针的确切类型

C++的四种强制类型转换：
1.static_cast:可以实现 C++中内置基本数据类型之间的相互转换。如果涉及到类的话，static_cast 只能在有 相互联系的类型中进行相互转换,不一定包含虚
函数。
static_cast<int>(7.987);//可以看出static_cast属于一个模板函数
class B{};
class A:public B{};
class C{};
B *B1 = new A();
A *A1 = static_cast<A*>(B1);//合法，因为class A与class B是继承关系
C *C1 = new A();
A *A1 = static_cast<A*>(C1);//不合法，因为class A与class C不存在任何关系

2.const_cast: const_cast 操作不能在不同的种类间转换。相反，它仅仅把一个它作用的表
达式转换成常量。它可以使一个本来不是 const 类型的数据转换成 const 类型的，或者把 c
onst 属性去掉。
3.reinterpret_cast: 有着和 C 风格的强制转换同样的能力。它可以转化任何内置的数据类型
为其他任何的数据类型，也可以转化任何指针类型为其他的类型。它甚至可以转化内置的数
据类型为指针，无须考虑类型安全或者常量的情形。不到万不得已绝对不用。

4.dynamic_cast:
（1）其他三种都是编译时完成的，dynamic_cast 是运行时处理的，运行时要进行类型检查。
（2）不能用于内置的基本数据类型的强制转换。
（3）dynamic_cast 转换如果成功的话返回的是指向类的指针或引用，转换失败的话则会返
回 NULL。
（4）使用 dynamic_cast 进行转换的，基类中一定要有虚函数，否则编译不通过。
B 中需要检测有虚函数的原因：类中存在虚函数，就说明它有想要让基类指针或引用指向派
生类对象的情况，此时转换才有意义。
这是由于运行时类型检查需要运行时类型信息，而这个信息存储在类的虚函数表（关于虚函
数表的概念，详细可见<Inside c++ object model>）中，
只有定义了虚函数的类才有虚函数表。
（5）在类的转换时，在类层次间进行上行转换时，dynamic_cast 和 static_cast 的效果是
一样的。在进行下行转换时，dynamic_cast 具有类型检查的功能，比 static_cast 更安全。
向上转换即为指向子类对象的向下转换，即将父类指针转化子类指针。向下转换的成功与否
还与将要转换的类型有关，即要转换的指针指向的对象的实际类型与转换以后的对象类型一
定要相同，否则转换失败。
名词解释:向上转型(子类类型转为基类类型)
向下转型(基类类型转为子类类型)

C++异常处理:
异常处理是程序开发过程中除调试之外的一种错误处理的方法，但大部分人在编写时都忽略了异常处理
C++中，异常的抛出使用throw关键字来实现，关键字后面可以跟任何类型的数据，捕获异常catch;
异常的抛出和处理主要使用了以下三个关键字： try、 throw 、 catch 。
如果在try语句块的程序段中（包括在其中调用的函数）发现了异常，且抛弃了该异常，则这个异常就可以被try语
句块后的某个catch语句所捕获并处 理，捕获和处理的条件是被抛弃的异常的类型与catch语句的异常类型相匹配。
由于C++使用数据类型来区分不同的异常，因此在判断异常时，throw语 句中的表达式的值就没有实际意义，而表达式的类型就特别重要。

try {
	throw "This is a error"
}
catch(type errorname) {
	.......
}

异常抛出可以逐层传递，知道异常被捕获
catch(...)接受所有异常

c++静态库与动态库
静态库,占用内存,链接时调用 lib库名.a(linux) 库名.lib(windows)
准备:在链接阶段生成目标文件.o(linux) .obj(windows)
生成:ar -crs lib库名.a *.o (linux)
lib.exe 生成
使用:gcc -L../libdir/ -l库名 (L库目录 l静态库名)
实质:静态库就是一堆.o相互依赖文件的打包，如果静态库有变化，程序需要重新编译一次

空间浪费是静态库的一大问题
一个程序就包含一个静态库的拷贝在内存中，如果运行多个程序，占用内存叠加
动态库（共享库）:.so(linux) .dll(windows)
运行时打开，多个程序共享一份动态库拷贝，节省内存空间

动态库生成
g++ -fPIC -c source.cpp //生成.o文件；fPIC 创建与地址无关的编译程序（pic，position independent code），是为了能够在多个应用程序间共享。
g++ -shared -o lib库名.so source.o //-shared指定生成动态链接库。
其实上面两个步骤可以合并为一个命令：
g++ -fPIC -shared -o libdynmath.so DynamicMath.cpp

1)        当系统加载可执行代码时候，能够知道其所依赖的库的名字，但是还需要知道绝对路径。此时就需要系统动态载入器(dynamic linker/loader)。
2)        对于elf格式的可执行程序，是由ld-linux.so*来完成的，它先后搜索elf文件的DT_RPATH段—环境变量LD_LIBRARY_PATH—/etc/ld.so.cache文件列表—/lib/,/usr/lib 目录找到库文件后将其载入内存。
如何让系统能够找到它：
l  如果安装在/lib或者/usr/lib下，那么ld默认能够找到，无需其他操作。
l  如果安装在其他目录，需要将其添加到/etc/ld.so.cache文件中，步骤如下：
n  编辑/etc/ld.so.conf文件，加入库文件所在目录的路径
n  运行ldconfig ，该命令会重建/etc/ld.so.cache文件
我们将创建的动态库复制到/usr/lib下面，然后运行测试程序。

C++单例//get from shuizi
一个类在一个工程中只能被构造一次，实现
class CDanli {
	public:
		static CDanli* getptrnull();
	private:
		CDanli();
		~CDanli();
		static CDanli* ptrnull;
};

char *CDanli::ptrnull = NULL;
CDanli* CDanli::getptrnull() {
	if (ptrnull == NULL) {
		 ptrnull = new CDanli();
	}
	return ptrnull;
}

C++与Mysql:
安装mysql开发库,sudo apt-get install libmysqlclient-dev;//安装动态库，liblibmysqlclient.so
头文件:mysql/mysql.h
编译时 gcc source.c -L/lib/ -lmysqlclient 动态库编译
mysql 句柄:
MYSQL //句柄
MYSQL_RES //结果集
MYSQL_ROW //一行结果，字符串数组

mysql_init(hdl);//初始化句柄
mysql_real_connect();//连接远端数据库
mysql_query();//执行SQL语句
res = mysql_store_result;//取得结果
mysql_num_fields();//取得列数
while (row = mysql_fetch_row(res))//循环取得结果
输出字段row[i];

智能指针:
share_ptr //可实现多个指针指向同一对象
unique_ptr //只可以指向一个对象
auto_ptr//构造函数有 explicit 必须显式调用
局部变量与全局变量同名,用::符号引用全局变量

C++中为什么用模板类:
1.它与类型无关，代码具有高可用性
2.他是类型安全的，在代码编译阶段可以检查类型而不是在代码运行阶段
3.他是与平台无关的，具有良好的移植性

14.使用线程是如何防止出现大的波峰。
答：意思是如何防止同时产生大量的线程，方法是使用线程池，线程池具有可以同时提
高调度效率和限制资源使用的好处，线程池中的线程达到最大数时，其他线程就会排队
等候。
15函数模板与类模板有什么区别？
答：函数模板的实例化是由编译程序在处理函数调用时自动完成的，而类模板的实例化
必须由程序员在程序中显式地指定。
22.TCP/IP 建立连接的过程?(3-way shake)
答：在TCP/IP协议中，TCP协议提供可靠的连接服务，采用三次握手建立一个连接。
　　第一次握手：建立连接时，客户端发送syn包(syn=j)到服务器，并进入SYN_SEND状
态，等待服务器确认；
第二次握手：服务器收到syn包，必须确认客户的SYN（ack=j+1），同时自己也发送一个
SYN包（syn=k），即SYN+ACK包，此时服务器进入SYN_RECV状态；
　　第三次握手：客户端收到服务器的SYN＋ACK包，向服务器发送确认包ACK(ack=k+1)
，此包发送完毕，客户端和服务器进入ESTABLISHED状态，完成三次握手。

25.winsock建立连接的主要实现步骤?
答：服务器端：socker()建立套接字，绑定（bind）并监听（listen），用accept（）
等待客户端连接。
客户端：socker()建立套接字，连接（connect）服务器，连接上后使用send()和recv（
），在套接字上写读数据，直至数据交换完毕，closesocket()关闭套接字。
服务器端：accept（）发现有客户端连接，建立一个新的套接字，自身重新开始等待连
接。该新产生的套接字使用send()和recv（）写读数据，直至数据交换完毕，closesock
et()关闭套接字。

28. New delete 与malloc free 的联系与区别?
答案：都是在堆(heap)上进行动态的内存操作。用malloc函数需要指定内存分配的字节数并且不能初始化对象，new 会自动调用对象的构造函数。delete 会调用对象的destructor，而free 不会调用对象的destructor.

C/C++中函数参数的传递方式，三种：值传递，地址传递，引用传递，因该注意的事项
如果是指针传递，当作为输入时（不修改其值），因该在形参加上const
如果是对象值传递，而不希望修改对象的成员变量，可以使用const &修饰形参，因为引用不用开辟新空间，并不会产生对象的构造和析构，从而提高效率

虚函数只能借助指针或引用来达到效果

C++编译器一旦发现一个类型中有虚拟函数，就会为该类型生成虚函数表，并在该类型的每一个实例中添加一个指向虚函数表的指针。在32位的机器上，
一个指针占4字节的空间，因此求sizeof得到4；如果是64位的机器上，一个指针占8字节的空间，因此求sizeof则得到8。

由于是传值参数，我们把形参复制到实参会调用复制构造函数。因此如果允许复制构造函数传值，就会在复制构造函数内调用复制构造函数

拷贝构造函数也是一种类的构造函数,他和'='操作符重载就是两个不挨边的机制，拷贝构造函数不返回值
class A {
	public:
	int m_data;
	A();//构造函数
	~A()//析构函数
	A(const A &other);//拷贝构造函数
}

而且拷贝构造函数的形参类型必须为const Class &;//不然调用拷贝构造函数时会发生无限递归；编译器不允许
通过调用拷贝构造函数构建的对象会正常析构

C++有六个默认函数：分别是

1、default构造函数;
A(void);
2、默认拷贝构造函数;
A(const A &other);
3、默认析构函数;
~A();
4、赋值运算符;
A &operator = (const A &other);
5、取址运算符;
A *operator & (void);
6、取址运算符const;
const *operator & (void) const;

返回引用类型的函数是为了返回一个有效的左值，才可以被赋值，赋值运算符重载函数就是利用这一点来实现连续赋值
class A a;
class A b;
class A c;

a = b = c;//连续多重赋值，所以赋值运算符重载函数返回类型必须是引用型

c/c++零长数组char a[0];GUN允许，作用，可作为可变长结构体
struct Test {
	int len;
	char a[0];
}

char *ptr = malloc(sizeof(Test) + 1024);
Test *tPtr = (Test *)ptr;
ptr->len = 1024;
memcpy(ptr->a, "content", 1024);
通过强转来达到可变长结构体

const 修饰的对象只能访问const成员
C++关键字：mutable(易变的)，与const相反
Class::func (int a) const {
	return i++;//i++是类的一个成员变量
}
按照原理被const修饰的成员函数不可以修改任何成员；但是被mutable的变量可以；
与volatile相似，但完全不同，volatile是意想不到的改变
静态数据成员的值在const成员函数中可以被合法的改变。

树,链表等就用递规的思想来做,反响输出链表节点
int InverPrint(List *node) {
	if (NULL == node) {
		return 0;
	} else {
		InverPrint(node->next);
		std::cout << node.data;
	}
}



























