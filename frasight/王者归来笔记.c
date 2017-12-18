任何控制语句都可以用goto语句来实现
switch是一个空间换时间的典型例子，switch要维护一张跳转表，而if-else不用
代码优化：计算机对位操作最快，应为CPU就是专门执行位运行的，所有尽量将乘法，除法转变成加法和位运算
除法指令50个机器周期，位运算加法运算一两个周期
>>右移除二的n次幂
<<左移乘二的n次幂
清零啊a^a;
12*5=12<<2 + 12;
编译器能进行常量折叠
如果计算的表达式有规律，为了节省执行时间，可使用数学公式
eg:从1-n的和可使用高斯定理sum = n*(n+1)/2;
表达式优化：x = x + 1;访问两次内存，x += 1;访问一次内存
if-else if控制程序中，判断得先后问题也是影响程序效率问题，如果有一段程序
要求统计字母数，空格数，数字的个数，因为英文文档中字母占大多数，如果先判断字母数，程序就会少执行点时间
switch:每一条switch语句都要维护一张跳转表，是一个空间换时间的典型例子
如果先判断数字和空格数，那很多字母数就会经过三次if语句才能被判断，明显耗费时间
if - else 可用switch代替，但switch也不是万能的，他不能判断范围
循环优化：如果有的表达式能一次性计算出值，就将他计算出来，如果放在循环中每次都计算，则大大浪费时间
eg:
for (i =0; i < strbuf[buff]; i++)
每次循环都要去遍历整个文件缓冲区，很浪费时间
改进：const int a = strlen(buff);
for(i = 0; i < a; i++);
C语言函数本质是以一段机器指令码，而函数名本质是一个标号，该标号的值是内存中存储该函数代码的内存空间首地址（函数名是一个函数指针常量，类似于数组名）
函数在调用时会使进程空间中的栈不断增长， 从当前进程空间中的栈顶的位置到函数保存返
回地址的位置， 这块内存称为函数的栈帧。 所有函数中定义的局部变量都存储在函数的栈帧上。 当函
数结束调用时该块栈帧就消失了
复合语句内定义的变量只限于复合语句内使用
局部变量存储在函数的栈帧上，全局变量存储在固定的存储区
全局变量如果定义时没有初始化，则编译器会初始化，数值型初始化0,指针初始化null
而局部变量编译器不会初始化值，他将占用原有内存空间的值作为初始值
函数的调用与优化：函数的优点：函数使代码模块性更强，利于代码的修改和阅读，并且可以有效地减小代码
的体积。
缺点：函数的调用通常很费时，时间换空间
函数调用时的过程：
 函数调用需要将参数压入堆栈。
 函数调用需要保存寄存器的值。
 函数调用需要保存返回地址。
 函数调用会造成跳转。

前 3 个步骤都需要访问内存，而最后 1 步造成一次跳转。访问内存
在计算机的操作中很消耗时间
函数的优化1、减少函数调用的次数 3个fun(1)可用3*fun(1)代替
在某个变量使用频率较高的情况下，应该将它设置成局部变量，如果把它设置成全局变量或静态变量，
每次表达式访问此变量时都要访问内存，很耗时间，再说定义在函数里面的局部变量，使用频率较高是编译器会自动将它存储在寄存器中
C预言中的变量存储类别：
auto:只要前面没用加存储类别的变量，编译器会自动辨别他的存储类型，定义在函数内的位局部变量，定义在函数外的位全局变量
register:寄存器类别，编译器会自动把一些使用频率较高的变量(局部变量)存储在寄存器中，比如循环因子
extern:外部变量(全局变量)，说明该变量是从另外一个文件里面(全局变量)引用过来的
static:静态变量，用于限制作用域，全局变量加static将限制此变量只能在当前文件中引用，不能在其他文件中使用，哪怕加了extern也不能使用他
局部变量加static限制此变量只能在函数或复合语句内使用，对于静态局部变量而言，static能改变其生命周期
静态局部变量在现实程序中很常见也很实用
static的另外一个作用就是实现一个模块封装：static定义的全局变量只能在当前文件中使用，不能在其他文件模块中使用，所有想要访问
静态全局变量，就得将文件封装对外提供接口
eg:
#include<stdio.h>
#include<stdlib.h>

struct node{
	int val;//保存值
	struct node* next;//下一个节点的指针
};

typedef struct node* Node;
static Node head;

int insert(int dat)
{
	Node p, q;
	
	p = head;
	if (p != NULL)
	while (p->next != NULL)
		p = p->next;
	q = (Node)malloc(sizeof(struct node));
	if(q = NULL)
		return -1;
	q->next = NULL;
	q->val = dat;
	
	if (p == NULL)
		p = q;
	return 1;
	
	p->next = q;
	return 1;
}

void print()
{
	Node p;
	
	p = head;
	
	while (p != NULL)
	{
		printf("%d\n", p->val);
		p = p->next;
	}
}

void destroy()
{
	Node p;
	
	p = head;
	
	while (p != NULL)
	{
		Node q;
		q = p;
		p = p->next;
		free(q);
		
	}
	
	head = NULL;
}

对外提供函数接口:extern int insert(int);
				 extern void print();
				 extern void destroy();
				 
主函数：int main()
{
	int i;
	for (i =0; i < 6; i++)
	{
		if (insert(i) == -1)
			exit(1);
		print();
		destroy();
		
		return 0;
	}
}

这就是接口的概念，以后在开发程序的过程中，我们都在使用别人写的接口函数
链接符号解析规则：两个概念：声明和定义，声明是I告诉编译器有一个符号存在，定义是给符号分配空间
符号：变量和函数
变量比较特殊，声明时如果没有定义，编译器会自动将第一个声明认为是变量的定义
符号解析的三个规则：
1、不允许有多个定义存在：eg:a.c里面有int a = 4,b.c 里面也有int a = 6;
2、如果有一个符号的定义和一个符号的声明时，编译器会选择被定义的符号作为定义。a.c中的int a;b.c里面的int a = 6;  
3、如果有两个符号的声明，则先扫描到的作为符号的定义
可变参数函数，在函数调用时才确定参数的个数
以printf(const char* faomat,...)为例第一个参数(const char*)的类型已经确定，...代表后面的参数可变
要编写可变参数函数，必须要用到stdarg.h头文件，要使用时可再参考
指针：首先申明，代码优化第一准则，能少访问内存的就少访问内存，访问内存的时间和乘法除法比起来，要长得很多，所以能少用访问内存的就少用
*p = &a;
*q = &b;
p 是q的别名指针，在程序中要少用别名指针，容易造成调试混乱
数组指针和指针数组：int (*p)[5]，p是一个数组指针，类型为int(*)[5](重点),p+1移动五个元素的位置，也就是20个字节，[]的数值是什么就移几位
数组指针用来装数组名的地址，p = &a;
指针数组：int *p[4];定义一个含四个元素数组，数组里面装的是整形指针类型
const 关键字，限定修饰符，const将变量放在只读数据段，对这段只读数据段的写都是非法的；
定义变量const int a = 8;//a的值不能被修改
定义指针，在指针之前，指针指向的内容不能改变，指针的值可以改变const int *p = &a;//不能改变a的值，p = &c是合法的
int const *p和 const int *p等价，可用改变指针，但不可以改变指针指向的值
int *const p = &a;//指针本身不能改变，指向的值可以改变
int const * const p = &a//指针和指向的值都不能改变
char *p = "Hello World";
可以通过p + 1;p[3]访问字符串中的元素，但是不能通过*(p + 1) = 's,p[3] = 'd'来修改
所以说char *p = "Hello World",等价于const char *p = "Hello World";
C语言中的高级技术：
内存对齐，对于32位体系结构的计算机系统而言，默认采用4字节对齐，64位的采用8字节对齐
struct val{
	char ch;
	short s;
	int i;
}

sizeof(struct val) = 8;
不满四字节的自动补齐；
struct val{
	char ch;
	int a;
	short s;
}

sizeof(struct val) = 12;
所有对齐方式的系统是以空间换时间的例子，这样便于CPU访问数据，提高代码执行速度
但是在某些空间紧张的情况下，例如嵌入式Liunx中，对齐方式往往会被禁用，以保证系统存储空间的使用
位运算：位运算出现的原因在于节省存储空间，因此将最小的存储形象单元由字节变成位。在系统编程中位运算及其重要，因为在系统编程方面要求对空间占用少
掩码：用来提取系统标志位的，其基本思想是将变量中所需的位保持，其余的清零；为例节省空间，通常会用一个字节来保存很多标志位
将一个整数的最后一位清零，0xfffe & a;但是这种代码在不同体系的计算机上会得到不同的结果，16位32位64位，16位的掩码位0xfffe如果移植到32位机上，就变成了0x0000fffe
了，所以掩码要这样表示int b = ~1;在所有计算机上通用
异或运算：使用最多的位运算，相同为0不同为1
1、与1相异或取反码
2、与0相异或保持不变
3、交换两个值，不需要中间变量 a = b ^ a;b = a ^ b;a = b ^ a;
移位操作：移位次数不能超过被移位的数的长度，如int a;移位不能超过31,超过31就是未定义，很危险
int a = 31;
int x = 0xffffffff;
x >> 31 = 1//右移左边补0
x >> a = -1;//因为a是有符号数，所有编译器会吧x的最高位当成符号位，左边补1
循环右移，将低位溢出的不在高位上，
b = a << (32 - n);
c = a >> n;
c = c & ~(~0 << n)
c = c | b;

预处理：预处理的三个工作，过滤注释，包含文件(include),和展开宏
C语言里面应该将含有类似功能或者是操作同一个对象的函数放在一个文件里面，c语言中一个文件代表一个模块，如链表的插入，查找，删除等可以放在同一个.c文件中，对外
提供接口，方便管理
如果·模块中的函数有一个是函数接口，需要被其他模块引用，则应当定义成外部函数，如果此函数是只在本模块中使用，为了防止重名，应定义成static形式，变量也是如此；
调试开关：条件编译
#define DEBUG 1
#ifdef DEBUG
...
#else
	...
#enfif

C99新标准关键字详解
inline
inline 是C语言1999年的标准新关键字
作用是将函数展开，把函数代码复制到调用位置，这样调用就可以直接执行代码而不发生跳转，压栈等一些行为，时间会节省不少，也因此会提高程序执行的速度
注意：但是不是所有以inline定义的函数都会被展开，展不展开将由编译器决定
只有代码较短的情况下才会展开，过多的使用inline关键字，编译器将不会展开，以防止代码过多而膨胀
inline 在某种程度上讲很想带参数得而宏
inline int add(int a,int b) == #define add(a,b,c) {c = a + b;}
inline 不一定会被展开，但define 一定会被展开 宏就是进行简单的替换，使用宏也要注意代码膨胀
restrict 关键字用于使编译器放心的进行优化。
void sum(int *out, int *arr1, int *arr2, int num)
{
	int i;
	for (i =0; i < num; i++)
	{
		out[i] = arr1[i] + arr2[i];
	}
}

对于以上代码，编译器不确定arr1、arr2和out是否同时指向同一块区域，所以程序不能被优化，只能串行执行,就是先取arr1地址里面的值，再取arr2的值，想加后
在存储在out里面，很耗时
优化：void sum(restrict int *out, restrict int *arr1, restrict int *arr2, int num)
{
	int i;
	for (i =0; i < num; i++)
	{
		out[i] = arr1[i] + arr2[i];
	}
}

由于使用到了restrict关键字，编译器只读者三个指针指向不同区域，因此可以进行优化,对arr1和arr2的取值和对out的赋值就可以并行完成了
C语言中的跳转goto短跳转、longjump长跳转
goto对应汇编中的B跳转

C 可变参数函数的编写
所需头文件:stdarg.h
所需要宏:
va_list va
va_start
va_arg
va_end
没有研究其原理，只研究其使用
print(const char *fmt, ...){
	va_list va;//定义一个接受参数的数据结构
	const char *ptr = NULL;
	va_start(va, fmt);//初始化va
	va_arg(va, const char *);//移动参数
	puts(ptr);
	va.end(ap);//清除va_list
}

空指针:NULL
在C中NULL的定义为 #define NULL ((void *)0), C++ 中的NULL为#define NULL 0;尝试去操作一个NULL指针会发生段错误，但是free一个NULL指针则非常安全
野指针:产生野指针的两种途径
1.指针变量没有被初始化。任何指针变量刚被创建时不会自动成为NULL指针，它的缺省值是随机的，它会乱指一气。所以，\
指针变量在创建的同时应当被初始化，要么将指针设置为NULL，要么让它指向合法的内存
2.free//delete后的指针只是释放了堆内存，但斌没有将指针置NULL，这时再去操作这个指针就会使程序出现意想不到的结果，所以好的习惯就是，free后\
的指针要置NULL


函数指针赋值：
int add(int a, int b) {
	return a + b;
}

int main(int argc, char *argv[]) {
	int (*fPtr)(int a, int b);
	fPtr = add;
	
	printf("%d", (*fPtr)(2, 5));
	return 0;
}
//result:7
解析:fPtr是一个函数指针，add是一个函数指针常量，类似于数组int a[3]; int *p = a;
如果&add表示指向函数指针的指针,函数名为函数代码的首地址，调用时可用*fPtr(),也可用fPtr()

内存拷贝函数:一定要考录地址重叠的问题，地址重叠从后向前拷贝；
void* mymemcpy( void *dest, const void *src, size_t count )   
{   
	char* pdest = static_cast<char*>( dest );   
	const char* psrc = static_cast<const char*>( src );   
	if( pdest>psrc && pdest<psrc+cout ) 能考虑到这种情况就行了 ，地址重叠 
	{   
	for( size_t i=count-1; i!=-1; --i )   
	pdest[i] = psrc[i];   
	}   
	else  
	{   
	for( size_t i=0; i<count; ++i )   
	pdest[i] = psrc[i];   
	}   
	return dest;   
	}   
	int main( void )   
	{   
	char str[] = "0123456789";   
	mymemcpy( str+1, str+0, 9 );   
	cout << str << endl;   
	  
	system( "Pause" );   
	return 0;   
}














