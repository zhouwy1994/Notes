===========================================================================================
周武毅 2017年9月21日								Study On C  Language
===========================================================================================

char *gets(char *s);//该函数存在给指定地址读入字符串，存在严重缺陷，没有限制读入字符长度，超过地址所能容纳的地址将造成程序崩溃
int scanf(const char *format, ...);//该函数也存在上述问题，都是不安全的
char *fgets(char *s, int size, FILE *stream);//该函数可以指定输入长度，比较安全

隐藏数据接口:
头文件定义
typedef struct concel_data_type concel_data_type_t;
此结构体类型在c文件定义。
.c
struct concel_data_type{
	int a;
}
再在当前c文件中定义访问结构体成员函数的接口
int concel_data_type_get_a(concel_data_type_t *pConcelDataType){
	return pConcelDataType->a;
}
在h文件中声明函数接口
extern int concel_data_type_get_a(concel_data_type_t *pConcelDataType);

其他.c文件需要访问此结构体时包含当前头文件，需要访问成员是使用函数

命名规则，函数名全小写，变量名首字母小写，并加类型(p, m, is),变量名无下划线，函数名用下划线

Windows C编程
临界区：CRITICAL_SECTION 在任何时段只允许一个线程访问
CRITICAL_SECTION* memery_section; //定义一个临界区指针
memery_section = calloc(1, sizeof(CRITICAL_SECTION)); //分配空间
InitializeCriticalSection(memery_section) //初始化临界区
EnterCriticalSection(memery_section); //进入临界区
write() //访问临界资源
LeaveCriticalSection(memery_section);// 离开临界区

VC++中 __try,____except( EXCEPTION_EXECUTE_HANDLER ) 结构中，except的参数是什么，求详解！
在__excep后面的()中是一个表达式，值可以是:
EXCEPTION_CONTINUE_EXECUTION (–1)  异常被忽略，控制流将在异常出现的点之后，继续恢复运行。
EXCEPTION_CONTINUE_SEARCH (0)  异常不被识别，也即当前的这个__except模块不是这个异常错误所对应的正确的异常处理模块。系统将继续到上一层的try-except域中继续查找一个恰当的__except模块。
EXCEPTION_EXECUTE_HANDLER (1)  异常已经被识别，也即当前的这个异常错误，系统已经找到了并能够确认，这个__except模块就是正确的异常处理模块。控制流将进入到__except模块中。

SOCKET accept(
__in     SOCKET s,
__out    struct sockaddr *addr,
__inout int *addrlen
);
第一个参数就是套接字描述符，第二个参数是，接受客户端基本信息的结构体，第三参数就火了，是准备接受结构体的大小，
上面的程序 int iAddrSize，传进去的时候只是把未知的iAddrSize的地址传进去，要传进去的应该是接收这些信息的基本大小啊，
所以 得加 iAddrSize = sizeof（SOCKADDR）。
这样程序就会阻塞在accept的时候。

::WSAAsyncSelect(srv_sock, this->m_hWnd, WM_SOCKET, FD_ACCEPT | FD_READ);
将套接字设置为非诸塞
将关心的事件设置处理函数

Windows 线程:
创建线程: HANDLE CreateThread();
1.临界区:API
线程间同步互斥:临界区 CRITICAL_SECTION M_SEC;
初始化临界区:InitializeCriticalSection(&M_SEC);
申请临界区:EnterCriticalSection(&M_SEC);
释放临界区:LeaveCriticalSetion(&M_SEC);
最后要删除临界区:DeleteCriticalSection(&M_SEC)

MFC:
CCriticalSection 类
CCriticalSection m_sec;

BOOL Lock()//上锁
BOOL UnLook() //解锁
m_sec.Lock()
m_sec.UnLock

2.Event Object
API:
HANDLE CreateEvent(); //新创建一个事件对象，可以设置为由信号或者无信号
BOOL SetEvent(HANDLE hEvent) //将事件设置为由信号
DWORD WaitForSingObject(); //该函数将在制定事件上等待信号，如果该事件为由信号状态，则返回，如无信号，则诸塞
BOOL ResetEvent() //重置该事件为无信号状态

MFC:
CEvent 类
BOOL SetEvent() //成员函数
BOOL ResetEvent() //成员函数
::WaitForSingObject() //等待信号

3.互斥对象
API:
HANDLE CreateMutex() //创建互斥锁，创建即有锁
::WaitForSingObject() //等待互斥锁
::ResetMutex() //释放锁

MFC:
CMutex 类
CMutex m_mux
Lock() //上锁，成员函数
UnLock() //解锁，成员函数

Windows进程间通信
1.邮槽 Mailslot
1.创建邮槽
HANDLE m_mail;
m_mail = CreateMailslot("\\\\.\\mailslot\\muslot", 0, MAILSLOT_WAIT_FOREVER, NULL);
2.WriteFile() 对句柄m_mail进行写操作
WriteFile(mail, msgBuf, 256, &writeText, NULL)
3.ReadFile() 对句柄m_mail进行读操作
ReadFile(mail, msgBuf, 256, &writeText, NULL)
总结:与匿名管道相似，半双工通信

2.命名管道
命名管道不止能在同一计算机上通信，还能在不同计算机的进程间通信，与邮槽不同的是，命名管道是面向连接的可靠通信方式
，所以命名管道只能一对一进行传输
HANDLE CreateNamePipe() //创建命名管道
BOOL ConnectNamePipe() //连接命名管道（服务器端）
BOOL WaitNamePipe() //等待命名管道连接(客户端) 面向连接可靠传输

WriteFile() //对命名管道进行写
ReadFile() //对命名管道进行读

创建新进程函数CreateProcess();

3.匿名管道
只可以在父子进程之间通信
CreatePipe();


异步IO模式
WSAAsyncSelect();

// 启动线程
AfxBeginThread(ThreadProc10, NULL);

在.c中定义一个全局变量并初始化，在对应的.h中声明extern 然后就可以在其他.c文件使用这个全局变量了

calloc = malloc + memset
并不是绝对的
char *p = malloc(1, 0);
strlen(p) ！= 0; // 初步猜想应该是一个野指针，如果认为calloc分配的内存都是0就引起bug //只限于vistual C++2015devenv
以上指针不能操作，否则会引起内存错误，最好的办法是将p置空

左右两边能复制的条件是 = 号左边变量的限定符应该包含左边变量的所有限定符，例如 1式成立，2式不成立
1.const char *ptr = char *
2.char *ptr = const char *ptr

const char** = char** 为什么会报警告
应为const char** 是指向const char* 的指针， char **是指向char*的指针，指向内容不一致的指针也不能相互赋值

常量为右值，不可取址&，但如果是指针类型的可以*

typedef struct test {
	char* m_data;
}test_t;

char* test_get_data(test_t* pTest) {
	return m_data;
}

&test_get_data(pTest); //错误，不可对右值取值
*test_get_data = 'c'; //对


创建软连接时要使用绝对路径,不然会出现Too many levels of symbolic links ”的错误
软连接:快捷方式
硬连接:多个文件镜像，修改某一个全局变化(所有文件指向同一个nodenum)，防止删除一个文件丢失的情况

npm是NODE.js的包管理器，一般命令
npm -v //查看版本号
npm install -g truffle //安装软件包
使用npm默认软件库在国内较慢，国内用的比较多的就是淘宝库，设置库路径
npm config set registry https://registry.npm.taobao.org

windows 下的find命令，功能是查找文本中的指定字符串
如果要在windows查找文件，使用如下命令
for /r director %i in (匹配模式(test.*, abc.*)) do;@echo %i

url 下载本地文件file:///F:/cpp-ethereum/build/leveldb-1.2.tar.gz 加前缀file:// 

memmove 是一个内存搬移函数
memmove用于从src拷贝count个字节到dest，如果目标区域和源区域有重叠的话，memmove能够保证源串在被覆盖之前将重叠区域的字节拷贝到目标区域中。
但复制后src内容会被更改。但是当目标区域与源区域没有重叠则和memcpy函数功能相同。
原型：void *memmove( void* dest, const void* src, size_t count );
头文件：<string.h>
功能：由src所指内存区域复制count个字节到dest所指内存区域。
相关函数：memset、memcpy

memmove_s 是memmove的升级版(安全版)
memmove_s( void* dest, size_t destcount, const void* src, size_t srccount );
destcount:destcount 保证不超过destcount
注:
char* m_buffer; //装载元素的容器，装载的是元素的指针形式
是怎么达到装载指针的目的
正常逻辑:
char *m_buffer = malloc(100);
m_buffer[1] = 'a'; //这时m_buffer是一个char*所以他的元素是char
((int*)m_buffer)[1] = 12345; //这时m_buffer是一个int*所以他的元素是int
int a;((int**)m_buffer)[1] = &a; //这时m_buffer是一个int**所以他的元素是int*
vector_array_t 中就是利用这一特性来达到char*buffer装载任意类型的数据
type* Data; ((type**)m_buffer)[1] = Data; //这时m_buffer是一个yupe**所以他的元素是type*

头文件包含规则:
只需遵守一个规则,那个文件需要用到头文件，就在该文件内包含，不要将头文件包含在其他头文件中，在通过引用此头文件来达到目的
除非是common中的公用头文件


char buffer[1024];
1.int a; ((int**)buffer)[1] = &a;
2.int *ptr = *(int**)(buffer + 1 * sizeof(void*))
*ptr == a;
第一种情况是以[]访问buffer可以存放int*,第二种是以buffer偏移，这时的buffer就是存放指针的地址了

内存中申请的heap(堆),也是不能操作越界，可能越界的时候运行不报错误，但是free时就会出现内存错误
char *heap = calloc(1, 10);
memcpy(heap, src, 11); //此时可能不会报错
free(heap) //就会发生中断

网络通信中，一个套接字只可以绑定一个端口，但是多个套接字可以绑定同一个端口(端口复用)
默认的情况下(没有设置端口复用)，如果一个网络应用程序的一个套接字 绑定了一个端口( 占用了 8000 )，这时候，
别的套接字就无法使用这个端口( 8000 )，这是就会出现Address Already is use错误
当将套接字设置成端口复用时，就可以将此端口绑定多个套接字，而不报错
int opt = 1;  
// sockfd为需要端口复用的套接字  
setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));  
SO_REUSEADDR可以用在以下四种情况下。 (摘自《Unix网络编程》卷一，即UNPv1)
1、当有一个有相同本地地址和端口的socket1处于TIME_WAIT状态时，而你启动的程序的socket2要占用该地址和端口，你的程序就要用到该选项。
2、SO_REUSEADDR允许同一port上启动同一服务器的多个实例(多个进程)。但每个实例绑定的IP地址是不能相同的。在有多块网卡或用IP Alias技术的机器可以测试这种情况。
3、SO_REUSEADDR允许单个进程绑定相同的端口到多个socket上，但每个socket绑定的ip地址不同。这和2很相似，区别请看UNPv1。
4、SO_REUSEADDR允许完全相同的地址和端口的重复绑定。但这只用于UDP的多播，不用于TCP。

需要注意的是，设置端口复用函数要在绑定之前调用，而且只要绑定到同一个端口的所有套接字都得设置复用：
就是说在每一个bind之前都要设置端口复用
*****************
端口复用允许在一个应用程序可以把 n 个套接字绑在一个端口上而不出错。同时，这 n 个套接字发送信息都正常，没有问题。但是，
这些套接字并不是所有都能读取信息，只有最后一个套接字会正常接收数据。
******************
端口复用最常用的用途应该是防止服务器重启时之前绑定的端口还未释放或者程序突然退出而系统没有释放端口。
******************

intptr_t类型

　我接触最早的处理器是32位，目前64位处理器发展迅速。数据类型特别是int相关的类型在不同位数机器的平台下长
度不同。C99标准并不规定具体数据类型的长度大小。
cpu位数	char		short			int				long			指针
 16	 1个字节8位	  2个字节16位	 2个字节16位	 4个字节32位	2个字节16位
 32	 1个字节8位	  2个字节16位	 4个字节32位	 4个字节32位	4个字节32位
 64	 1个字节8位	  2个字节16位	 4个字节32位	 8个字节64位	8个字节64位
为了保证平台的通用性，程序中尽量不要使用long类型。可以使用固定大小的数据类型宏定义，
这些宏定义需要引用stdint.h头文件。
# if __WORDSIZE == 64
  typedef long int       　　　int64_t;
  # else
 __extension__
 typedef long long int        int64_t;

#if __WORDSIZE == 64
  # ifndef __intptr_t_defined
  typedef long int               intptr_t;
  #  define __intptr_t_defined
  # endif
  typedef unsigned long int    uintptr_t;
  #else
  # ifndef __intptr_t_defined
 typedef int                    intptr_t;
 #  define __intptr_t_defined
 # endif
 typedef unsigned int        uintptr_t;
 #endif

 从定义可以看出，intptr_t在不同的平台是不一样的，**始终与地址位数相同，因此用来存放地址**，即地址
 
 eg:
 stndent *stu = calloc(1, soizof(stndent));
 intptr_t handle = (intptr_t)stu;
 handle_student(handle);

 function declaration
 static int handle_student(intptr_t handle) {
	 student *stu = (stndent*)(handle);
 }
 
 //第一次见到成员函数后面跟=default or =delete，解释如下
 #define ATOMIC_FLAG_INIT	{0}
typedef struct atomic_flag
	{	// structure for managing flag with test-and-set semantics
	bool test_and_set(memory_order _Order = memory_order_seq_cst)
		volatile _NOEXCEPT;
	bool test_and_set(memory_order _Order = memory_order_seq_cst) _NOEXCEPT;
	void clear(memory_order _Order = memory_order_seq_cst)
		volatile _NOEXCEPT;
	void clear(memory_order _Order = memory_order_seq_cst) _NOEXCEPT;

	_Atomic_flag_t _My_flag;

	atomic_flag() _NOEXCEPT = default;
	atomic_flag(const atomic_flag&) = delete;
	atomic_flag& operator=(const atomic_flag&) = delete;
	atomic_flag& operator=(const atomic_flag&) volatile = delete;
	} atomic_flag;
	
 std::atomic_flag 构造函数如下：
atomic_flag() noexcept = default;
atomic_flag (const atomic_flag&T) = delete;
std::atomic_flag 只有默认构造函数，拷贝构造函数已被禁用，因此不能从其他的 std::atomic_flag 对象构造一个新的 std::atomic_flag 对象。
//std::atomic_flag对象可以当作一个简单的自旋锁(spin lock)使用。

c++11新特性之atomic
原子类型对象的主要特点就是从不同线程并发访问是良性(well-defined)行为，不会导致竞争危害。
与之相反，不做适当控制就并发访问非原子对象则会导致未定义(undifined)行为。

std::atomic<int> foo(0); atomic_flag ===== atomic<bool> atomic_flag(true);

//atomic的主要方法为load(读取) store(赋值)
其实就是一个线程安全的变量(并发访问良性)
类似与
EnterCriticalSection(&lock);
foo = 4;
LeaveCriticalSection(&lock)
一般与atomic_flag结合使用

c++关键字explicit(释义:明确的，显式的)
要解释关键字explicit就必须要先解释c++中的显示转换和隐式转换
class Test1 {
	public:
	Test1(int dat) {
		num = dat;
	}
}

class Test2 {
	public:
	explicit Test2(int dat) {
		num = dat;
	}
}

Test1 t1=12;//隐式调用其构造函数,成功
Test2 t2=12;//编译错误,不能隐式调用其构造函数
Test2 t2(12);//显式调用成功


内存屏障 (Memory barrier)
程序在运行时内存实际的访问顺序和程序代码编写的访问顺序不一定一致，
这就是内存乱序访问。内存乱序访问行为出现的理由是为了提升程序运行时的性能。
内存乱序访问主要发生在两个阶段：

编译时，编译器优化导致内存乱序访问（指令重排）
运行时，多 CPU 间交互引起内存乱序访问
// thread 1
while (!ok);
do(x);
 
// thread 2
x = 42;
ok = 1;
此段代码中，ok 初始化为 0，线程 1 等待 ok 被设置为 1 后执行 do 函数。假如说，线程 2 对内存的写操作乱序执行，
也就是 x 赋值后于 ok 赋值完成，那么 do 函数接受的实参就很可能出乎程序员的意料，不为 42。
使用volatile可以避免内存优化
判断是否是2的次方时，可用 a & (a - 1) == 0来判断,最快速高效

总结：   
reinterpret_cast 将一个类型指针转换为另一个类型指针(通常用于基本类型间指针类型转换)，
也常将指针类型转换成intptr_t,不能转换非指针类型，也就是不能基本类型转基本类型
const_cast    用于去除指针变量的常属性，将它转换为一个对应指针类型的普通变量，
反过来也可以将一个非常量指针转换为一个常量指针变量,但是不能将类型转换成非指针类型(const_cast<ptr-type>(type-id))
static_cast    用于转换基本类型和具有继承关系的类新之间转换,不太用于指针类型的之间的转换 (通常用于通用类型转换)
dynamic_cast    只能在继承类对象的指针之间或引用之间进行类型转换  
  
以上只有dynamic_cast这种转换并非在编译时，而是在运行时，动态的。其它均在编译时

初始化数据成员与对数据成员赋值的含义是什么？有什么区别？
首先把数据成员按类型分类并分情况说明:
1.内置数据类型，复合类型（指针，引用）
    在成员初始化列表和构造函数体内进行，在性能和结果上都是一样的
2.用户定义类型（类类型）
    结果上相同，但是性能上存在很大的差别。因为类类型的数据成员对象在进入函数体前已经构造完成，
	也就是说在成员初始化列表处进行构造对象的工作，调用构造函数，在进入函数体之后，进行的是对已
	经构造好的类对象的赋值，又调用个拷贝赋值操作符才能完成（如果并未提供，则使用编译器提供的默认
	按成员赋值行为）eg:
class A {
	private:
	class B;
	int a;
}
A:A() : B(123),a(4) {
	
}
上述初始化列表中B的构造是显式的(B(123))，并非隐式(B = 123)


目前大型的C++工程都是通过cmake来管理,cmake 一键可生成指定平台的工程，cmake的所有核心都
在于CMakeLists.txt这个配置文件，只要编写好这个文件，就可一键生成MakeFile等文件，其实cake不是
传说中那么难，如果项目中需要用到，可以好好学习一下，生成cmake项目只需两步:
编写CMakeLists.txt
执行cmake .

还有一款也是比较流行的自动生成makefile的工具automake makefile的工具automake,(第一个公司使用过),
但是配置的过程比较繁琐(需要9步)

这么多年的一个C误区,由于产生随机树需要随机数种子srand()如果不止定，默认使用1
for (int i = 0; i < 10; i++) {
	cout << rand();
}
ret:
1804289383
846930886
1681692777
1714636915
1957747793
都是产生随机数，但srand中种子不一样，每次都会选择在不同线上生成，选择随机数种子就像是选择椭圆曲线的参数
多线程也能公用一个种子而不一样，所有一个线程有一个srand(time(NULL))就可以了

多态:
用C语言实现多态
struct parent {
	int dat1;
	int dat2;
}

struct child {
	struct parent par;
	int dat3;
	int dat4;
}

child 继承与parent
多态:
struct child *ch = calloc(1, sizeof(struct child));
struct parent * par = ch;
par.dat1 == ch.parent.dat1
用父类指针可调用子类函数

善于利用回调函数,如果是异步发送网络消息,你需要的到对方发过来的函数,这是你在函数中,不可能得到,
这时可以将回调函数传入接收函数内,并在回调函数内传入一个接收句柄
fun1(void **);
func2(prama, func1) {
	func1(prama);
}

C中操作内存时要小心,应为访问非法内存时并不会立即出错,可能在执行一段后提示这时最为难找,这时你就应该确定
出错的地方存在不存在内存访问不当,如果不是则向上文查找,只要是涉及到内存操所的都应该仔细排查

在面向对象的语言中,有一种捕捉异常的方法叫try catch,一般而言，在程序预见运行错误时会直接退出，但是有的情况
可以避免，只要该错误能够抛出异常，那就能够通过try catah捕获，避免遇见错误就直接退出

C中函数中途return是一种不好的习惯，这样可能会忘记释放一些资源
但是如果像下面:

ret = func();
if (ret == 0) {
	ret = func2();
	if (ret == 0) {
		...
	}
}
显得太过于累赘，可以使用do while(0)形式
do {
	ret = func1();
	if (ret != 0)
		break;
	ret = func2();
	if (ret != 0)
		break;
}
这样看起来就很清楚了

stdio.h里面有一堆格式化字符函数如
sprintf
fprintf
有一种格式化字符函数可包含可变参数列表
_vsnprintf...可接受可变参数va_list
对可变参数的传递很有用处
int mon_log(char* format, ...)
{
char str_tmp[50];
int i=0;
va_list vArgList; //定义一个va_list型的变量,这个变量是指向参数的指针.
va_start (vArgList, format); //用va_start宏初始化变量,这个宏的第二个参数是第一个可变参数的前一个参数,是一个固定的参数
i=_vsnprintf(str_tmp, 50, format, vArgList); //注意,不要漏掉前面的_
va_end(vArgList); //用va_end宏结束可变参数的获取
return i; //返回参数的字符个数中间有逗号间隔
}
//调用上面的函数
void main()　
{
int i=mon_log("%s,%d,%d,%d","asd",2,3,4);
printf("%d\n",i);
}

今天算是弄懂了传统一致性算法和转为区块公链产生的公司算法(POW,POS,DPOS等弄明白)

传统一致性算法是强一致性算法，每一次提议必须得到每一个节点确认，(收到并是有序的)，就算某的节点有网络延迟也不会影响，
当它网络恢复或者重新启动后会向主节点（领导者去）请求最新数据，当主节点冗机后整个集群会重新选举，从而避免了中心化模型带来的影响。
传统一致性算法的主要流程
	             提议						  转发
1、Client ----> Point(集群中的一台群众节点) ------->(Leader)主节点将提议加上序号(领导人)
	    转发提议						                判断并回复
2、Leader ----->Points(集群中所有群众节点，将提议值缓存) --------->(Leader)主节点(领导人)
		统计结果
3、Leader------>Points(集群中所有群众节点)------>(如果本次达成共识，记录数据，否则丢弃提议值)


POW算法
POW是一种最终一致性的算法，当网络中有某一台计算机挖矿成功(获得记帐权)，则将挖到的块广播到集群中，
当其它节点收到这个新块，则立即去验证，如果验证通过则记录，验证不通过，则丢弃

所以POW等区块链共识算法和传统一致性共识算法最主要的区别就是，POW等算法没有Leader主节点，每一次提议不能保证
整个集群的每个节点的数据都保持相同，由于挖到新块需要复杂的计算，所以产生新块的难度将增大，并且每一次交易的确认
必须要在挖到六个块以后才能被确认(比特币),所以产生双花的几率极低，除非掌控集群51%的节点
所有的共识算法都不能逃避51%攻击

所遇C奇怪语法:
1.const char *str = "My" "Name" "is Zhouwy"; //这语句竟然能够通过编译,输出后str为"My Name is Zhouwy"

2.结构体赋值
struct structTest {
	int a;
	int b;
	int c;
};

struct structTest var = {
	.a = 10,
	.b = 24,
	.c = 56
}
3.unix风格的数组赋值
int arr[10] = {[4] = 67, [5] = 34}; // 可根据数组下标赋值

4.可变长数组
struct mutableArray {
	int len;
	char data[0];
}
sizeof (struct mutableArray) == 4(32bit);
struct mutableArray *pDta = malloc(sizeof(struct mutableArray) + 1024); //这是data结构体成员指向了1024字节的内存空间
memcpy(pDta->data, "Hello Mutable Array...", 1024);

“通常情况下，你会在.h文件中声明函数和类，而将它们的定义放置在一个单独的.cpp文件中。但是在使用模板时，
这种习惯性做法将变得不再有用，因为当实例化一个模板时，编译器必须看到模板确切的定义，而不仅仅是它的声明。因此，
最好的办法就是将模板的声明和定义都放置在同一个.h文件中。这就是为什么所有的STL头文件都包含模板定义的原因。

应为不管是模版类还是模版函数，都是在电用到使用部分代码时才实例化对象，所有如果模版函数与模版嘞的定义和声明不在
同一文件时，就算是在引用到模版函数或模版类再声明也没用。连接会出错


memmove用于从src拷贝count个字节到dest，如果目标区域和源区域有重叠的话，
memmove能够保证源串在被覆盖之前将重叠区域的字节拷贝到目标区域中。
但复制后src内容会被更改。但是当目标区域与源区域没有重叠则和memcpy函数功能相同.











