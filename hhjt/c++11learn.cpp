1.C++中的区域(作用域)锁(scoped_locking)和std::unique_lock与std::lock_guard都是RAII的锁形式，具有自动释放锁功能;
scoped_locking可释放多次，灵活
注意智能指针的引用
{
	boost::shared_ptr<int> pInt = boost::make_shared<Int>(45);
}
*pInt = 8;//错误，pInt已经被释放

2.如果一个函数中有频繁的错误判断并返回，每次返回前都需要释放资源时，则可将资源放入智能指针，因为智能指针是异常安全的

3.windows下c++制作动态库步骤:
vs版本(2017)
文件--->新建---->项目---->Visual C++---->Windows桌面(老版本可能是w32程序----->win32控制台程序)---->动态链接库(DLL)---->命名工程(myDLL)
经过以上步骤，vs自动生成几个文件，这几个文件都是必需的，然后将你的工程文件原样拷入,在要导出的类或函数加上__declspec(dllexport)(win专用)
就可以导出了, (class后加__declspec(dllexport)导入时__declspec(import))(右键源文件---->属性---->C++------>预编译头----->不使用预编译头)

4.windows下c++制作静态库步骤:
文件--->新建---->项目---->Visual C++---->Windows桌面(老版本可能是w32程序----->win32控制台程序)---->静态库---->命名工程(myDLL)
静态库就相对简单了，只需添加源文件，在需导出函数或类修饰符加上extern声明即可生成lib文件

5.Linux c++动态库制作
将需导出的函数声明为extern
编译选项
gcc -c -fPIC max.c
注意:-fPIC是编译选项
-shared是链接选项
gcc -shared -o libmax.so max.o
注意命名规则lib+$name
静态库
ar -crv libmylib.a my_print.o my_math.o

ASIO:
async_write发送消息时虽然能够全部将消息全部发送出去，但是会乱序
async_write_some 发送消息会丢包，不能够全部发送
解决办法:
将发送队列持久化(至少在真整个发送期间不被释放)
在async_write_some的回调函数判断消息队列是否为null不为null继续掉发送函数
发送完成的出队列(记住看看发送成功的字节数)https://www.cnblogs.com/qicosmos/p/3487169.html

6.lambda函数的好处:简洁、代码耦合度低
lambda表达式与函数指针之间的转换
auto lambda = [](int a, int b)->int {
	return a + b;
}
typedef int(*funcPtr)(int, int);
funcPtr ptr = lambda;
或直接
funcPtr ptr = [](int a, int b)->int {
	return a + b;
}
lambda表达式很适合用作函数回调参数

7.Visual Studio2017跨平台编译(Linux),提高编译速度(提高编译并发数),项目属性----->C++----->通用------->最大并行编译数(修改此处即可)

8.linux下有一个命令pkg-config可搜索所需要库的信息，包括路径，编译选项，编译必备，比如你在编译过程中需要使用到opencv相关库，可使用下列命令
g++ source.cpp `pkg-config --cflags --libs opencv`

9.Visual Studio跨平台编译可在项目属性------>链接器----->附加依赖项 添加一些gcc\g++所需要的编译选项

<<<<<<< Updated upstream

10.编译boost库，由于boost跨平台，linux和windows编译过程相同
下载boost库
cd boost_1.68.0
执行bootstrap.bat(linux平台为bootstrap.sh)会生成b2和bjam
如果需要安装执行b2 如果只是编译某个库执行bjam
我只需要编译thread system则执行
bjam -toolset=msvc-10.0 --with-thread --with-system  stage

11.kinux的调试器c/c++调试器为gdb windows的调试器属于cdb(需要安装windbg)

12.QT学习
如果不开线程,那么QT就只有一个线程,总会以为信号槽机制是多线程,其实是信号模式,如果一个信号槽阻塞,当前信号槽所处的线程就会阻塞,
//可能就是信号有优先级别,就算正在执行一个信号槽操作,突然来了一个优先级更高的也跳转,哪怕在执行死循环
开发QT多参考QT的官方Example(D:\Qt\Qt5.11.1\Examples\Qt-5.11.1)和官方文档QTAssistant(QT助手)

12.1 QT ui设计时擅用布局，在布局里面的部件可以设置显示比例(layout--->layoutStretch),每个布局又可以组合成其他布局，
如果想固定某个部件的大小，可以限定minimumSize和maximumSize，如果想要所有部件随窗口缩放，那所有部件后面都要加进一个布局
13.QT中基本上每个UI控件都会有一个QWidget *parent = nullptr参数
这个参数是指你需要给你的空间设置一个父亲，你是基于你的父亲,如果你的父亲空间被关闭，那你也会被关闭，如果你不设置，这主窗口关闭了你也没有关闭

13.1将QT 的ui文件生成头文件方法，找到uic.exe，打开cmd uic (uic main_windows.ui -o main_wondows.h)

14. io_service::work的作用：io_service::run在任务执行完毕时会立刻返回，这个并不是编写常驻服务的程序所想要的，
boost给的解决方案是定义一个work变量，乍看很神奇，这个跟io_server似乎没有任何关系的变量竟然能控制run的行为
用boost::asio::io_service::work。
boost::asio::io_service io_service_;
boost::asio::io_service::work work(io_service_); 
io_service_.run();

15.类的所有成员函数都可以访问本类的私有成员，但是静态成员函数没有this指针，只要往静态成员函数传递一个this指针成员就行
class t{
private:
    int member;
public:
    static int func(t obj){
    //return member;       不可以
    //return this->member; 不可以
    return obj.member;   //可以
    }
};

15.1类的静态成员函数可以访问所有类的静态成员变量而不需要this指针，就和const的类成员函数只能访问const成员函数是一个道理
16.c/c++中的预处理指令#pragma,适当运用是把利器
#pragma once //防止当前文件被多次包含
#pragma pack(n) //结构体排列以n字节对其，对于协议结构体很有用
#pragma comment( comment-type [, commentstring] ) //将描述记录安排到目标文件或可执行文件中去。comment-type是下面说明的五个预定义标识符中的一个
下面的编译指示导致连接程序在连接时搜索EMAPI.LIB库。连接程序首先在当前工作目录然后在LIB环境变量指定的路径中搜索。
#pragma comment( lib, "emapi" )

#pragma warning( warning-specifier : warning-number-list [,warning-specifier : warning-number-list...] ) //可屏蔽指定代码段警告
//这在引入一些第三方带有warnings的库的时候很有用。
但是msvc 和 gcc的用法不同
https://blog.csdn.net/10km/article/details/51726778
#pragma warning( push[ , n ] )
#pragma warning( pop )
允许有选择地修改编译程序警告信息的行为。
https://blog.csdn.net/piaoxuezhong/article/details/58586014

17.事件和信号
Event and Signal
一个程序总会运行在两种状态
内核态: CPU可以访问内存所有数据, 包括外围设备, 例如硬盘, 网卡. CPU也可以将自己从一个程序切换到另一个程序
用户态: 只能受限的访问内存, 且不允许访问外围设备. 占用CPU的能力被剥夺, CPU资源可以被其他程序获取
https://www.cnblogs.com/zemliu/p/3695503.html
不论是事件或信号，都存在两种状态，就是内核态和用户态
不论是事件或信号，在用户态所谓的异步，都是多线程机制实现，如果所有线程都被阻塞，
信号和事件都回阻塞(比如:Qt的app.exec,asio threadpool(service::run), IO完成端口等, 一般线程数为cpu核心数)
上诉的是用户态，内核态的异步机制是通过中断产生，是进程独有，跳转执行，执行中断将不会执行其他代码

18.c++初始化new数组
char *pArr = new char [n] { 0 };

19.左值引用、右值引用、万能引用(转发引用)
c++中左值定义:有名字能取址，右值:无名字，不能取址
左值引用:int &a = b;
右值引用:int func(int &&rra);
万能引用:template <T> func (T &&a) : 可传入左值引用、右值引用

20.c++中如果函数参数列表有，但又不使用它，为了防止编译器产生Unsed警告，可使用
c:#define UNUSED(v) ((void)(v))
c++:不写形参的参数名,c++支持 int func(int, int b);

21.vistual studio编译linux动态笔记
(1)属性---->常规------->目标文件名:修改为lib$(ProjectName)
(2)属性---->常规------->目标扩展名:修改为.so(静态库为.a)
(3)属性---->C/C++----->所有选项------>附加选项:添加-fPIC(fPIC为编译选项)
(4)属性---->链接器----->所有选项------>附加选项:添加-shared(shared为链接选项)
(5)ok

22.STL并不是现程安全的,在写入时,其他线程有动作都要加锁
如果不存在写行为,那可以多个线程同时读取,但所有前提都是不存在修改操作

23.如果需要调试windows下的dll代码，需要将生成DLL工程的pdb、lib、与dll文件拷贝至当前工程的debug目录下，即可调试
24.QT下制作动态库静态库也比较简单，如果已经建立好了app模式只需要将pro文件中的TEMPLATE=app 修改成lib，参考https://blog.csdn.net/u010168781/article/details/78549862
不管哪个平台需要导出的函数或类要加上导出修饰符，vc为__declspec(dllexport) QT为 Q_DECL_EXPORT，因为只有加上才会生成lib文件
25.QT中如果要添加一个UI文件并且自动生成对应的头文件和源文件，请选择QT设计师界面类

26.windows下的动态库(dll)为什么都跟着一个lib(静态库),其实这时的lib不能叫静态库而是一个符号表，它里面记录了每个导出函数的地址，如果没有这个lib，我们就只有
通过LoadLibrary来打开dll，再通过GetProcAddress获取每个函数的地址，再说正常生成dll都会生成一个lib，如果没有证明没有函数导出成功

27.boost 当使用两个外来库,两个库都使用到boost,但是boost的版本不一致，运行时会导致意想不到的错误，最好使用同一版本的boost，就算不一样也要保持在同一等级(1.56 1.57)
而不要是(1.58 1.64)

28.gcc中动态库与静态库同时存在时选择连接静态库参考https://www.cnblogs.com/lidabo/p/6206504.html

29.c++内存泄露测试(只针对VistualC++)
win提供内存泄露测试工具crtdbg.h,只需要在代码(main.c)中加入#include <crtdbg.h>,就可以使用内存泄露测试工具了，使用比较简单
在程序退出点前一步添加 _CrtDumpMemoryLeaks()函数即可，如果程序有多个退出点则在main函数第一行添加_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
程序运行完成时输出内存泄露信息，如下格式
Dumping objects ->
{96} normal block at 0x006B9090, 20 bytes long.
 Data: <                > 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
Object dump complete.
从上可看出产生一处20字节的内存泄露，编号96，这个编号要记住，用于定位产生内存泄露的代码点
定位产生内存泄露的代码点
在main函数第一行加入_CrtSetBreakAlloc(96)函数，运行时自动断点在产生内存泄露的地方
如果想输出产生内存泄露的.cpp文件行数，需要在之前加入#define _CRTDBG_MAP_ALLOC

http://bbs.2cto.com/read.php?tid=263708&page=1

30.广义内存泄露
广义的说，内存泄漏不仅仅包含堆内存的泄漏，还包含系统资源的泄漏(resource leak)，比如核心态HANDLE，GDI Object，SOCKET， Interface等，
从根本上说这些由操作系统分配的对象也消耗内存，如果这些对象发生泄漏最终也会导致内存的泄漏。而且，某些对象消耗的是核心态内存，
这些对象严重泄漏时会导致整个操作系统不稳定。所以相比之下，系统资源的泄漏比堆内存的泄漏更为严重。

31.第三方内存检测工具NuMega
NuMega是一个动态測试工具，主要应用于白盒測试。该工具的特点是学习简单、使用方便、功能有效。NuMega共同拥有三个独立的子功能——BoundsChecker、
TrueCoverage、TrueTime。BoundsChecker为代码检错工具，TrueCoverage为測试覆盖率统计工具，TrueTime为程序执行性能測试工具。
详细参考博客http://www.cnitblog.com/qiuyangzh/archive/2005/07/14/975.html

32.对c++资源释放的理解
Effective c++中讲过,不要在析构中抛出异常，构造函数也尽量不要，因为析构函数抛出异常不处理析构函数就不会被调用
所以尽量将支援的分配放到Initialize，析构函数放到Destroy中


33.thread_local变量是C++ 11新引入的一种存储类型。它会影响变量的存储周期(Storage duration)，C++中有4种存储周期：automatic(栈)、static(静态存储区)、dynamic(堆)、thread(线程)
有且只有thread_local关键字修饰的变量具有线程周期(thread duration)，这些变量(或者说对象）在线程开始的时候被生成(allocated)，
在线程结束的时候被销毁(deallocated)。并且每 一个线程都拥有一个独立的变量实例(Each thread has its own instance of the object)。
thread_local 可以和static 与 extern关键字联合使用，这将影响变量的链接属性(to adjust linkage)。


34.经过一段时间的面向对象方式开发,才明白软件之前所从书上所说,软件开发应遵循高内聚、低耦合的原则，开始不懂，自己开发一段时间后，
发现自己写的代码越庞大，越难维护，更新一个功能会影响整个代码结构，这就违背了模块间的低耦合原则，封装的不科学，接口设计不完善
以后要注意设计。
内聚性又称块内联系。指模块的功能强度的度量，即一个模块内部各个元素彼此结合的紧密程度的度量。若一个模块内各元素（语名之间、程序段之间）
联系的越紧密，则它的内聚性就越高。

35.ffpeg要学习

36.实践总结:关于c++的资源释放(内存释放,线程释放,套接字、窗口句柄)，释放的原则一般遵循出栈入规则,被依赖的资源先初始化(SDKInit),依次初始化其他资源（入栈）
释放时要先释放有依赖于其他模块的模块，依次（出栈），否则依赖的资源先被释放，则本模块无法运行

37.如果在A.cpp定义了namespace NS而没有导出任何头文件声明,B.cpp想使用A中的命名空间的内容则要先声明,怎么声明:在B.cpp中
namespace NS {
	extern int var;
	extern void func2(int, int);
}

38. shared_ptr 的reset方法，一直以为是重置原始指针并释放，但是它只是减少引用计数，但引用计数为1时释放

39.计算机常识:在计算机的世界中,1Byte = 8bit, 1KB = 1024Byte,1MB = 1024KB...所以不管是容量还是网速都是按照此方式计算,一个容易误导我们的是硬盘厂商
计算容量的方式比较独特(计算基数是1000)1KB = 1000Byte,1MB = 1000KB


40.抽象基类的构造函数和析构函数尽量放在protected下，不可在外构造

41.c++11中STL新增了一个emplace成员函数，此函数的目的在于减少对象复制过程中调用构造函数的次数，参数直接传递T对象的构造参数

42.priority_queue(优先队列)，自动排序的队列，新增元素自动排序，前提是对象要支持<操作符，也可以自己重载<操作符

43.typename 还有一个功能，在模板编程中引用T内部的类型,using ValueType = typename T::value_type;

44.分布式消息队列:分布式节点间保证消息的可靠性(不丢失)、有序性(FIFO)、持久化(宕机后可用)、多对多(n*m)
应该学习的两种消息队列:kafka(Broker)、zmq(Brokerless)
消息队列的分类:Broker(消息队列就是一个第三方服务)、Brokerless(API方式调用)
1.Broker类的分布式消息队列，是指有独立部署进行的分布式服务，即发送者把消息发布到Broker进程，再由Broker进程推（或者是拉）给订阅者。
2.Brokerless类的消息队列，主要采用api的方式，编译到应用程序中，在应用程序间进行点对点的通信。
https://blog.csdn.net/mysunshinexia01/article/details/80871696（zmq学习指南）
45.协程:协程所产生的并发为伪并发，所有的协程执行过程都在一个线程之内(通常是主线程)，所有协程之间的切换都处在用户
空间内（线程间的切换发生在内核空间），协程的底层切换可以理解成c中的setjemp和longjemp，用户空间切换代价小、由于都是
在一个线程内，所有资源不用加锁

46.c++中有wchar_t常常被我们忽略，wchar_t类型的常量通常用L前缀来标识
wchar_t ch = L'e';
wchar_t *pData = L"Hello Wworld";
c++原生字符串(不用任何转义)(const char *pData = R"(dsadsadsadsadsa)");

47.对异步事件服务器模型的理解
asio 一定要有有一个上下文(context),其实这就是一个事件循环，由多个线程共同运行 boost::thread(boost::asio::io_context::run)
然后之后所有的套接字都基于这个上下文建立，向这个套接字注册回调函数，只要这个套接字上发生事件，就会回调函数，达到异步
同信的效果，但是套接字的数据处理环节不能耗时太久，否者会减少活跃的线程数量，如果套接字的数据处理会耗时太久,则需要每个
套接字分配一个线程，或者专门分配几个线程处理数据

47.同一项目想的不同子模块应该放在一个解决方案下，共用一份源代码,省得源代码修改后全部子模块更新,这样也使得项目更容易管理

48.rpc(远程过程调用),其实就是一种进程间的通信方式,就是A进程调用B进程的函数,想过就像是调用本进程其他函数一样,rpc就是要屏蔽
底层的进程间通信协议，使用户不关心通信，只关心函数调用结果

49.rpc只是一种名词定义，并不是一个协议,具体的实现有很多第三方库，rpc尤其在分布式架构中频繁使用，可以好好学习一下

50.lockfree(无锁)操作，是一种不需要锁即可实现线程安全的数据操作，它的实现是就CAS(compare and set or compare and swap),现在很多处理器
架构都有相应的汇编指令实现,代码层c++又有相应的库automic系列,但是CAS又要防止ABA问题
gcc的CAS操作函数
bool__sync_bool_compare_and_swap (type *ptr, type oldval type newval, ...)
type __sync_val_compare_and_swap (type *ptr, type oldval type newval, ...)
Windows:
InterlockedCompareExchange ( __inoutLONGvolatile*Target,
                                __inLONGExchange,
                                __inLONGComperand);
c++11:
template<classT >
bool atomic_compare_exchange_weak( std::atomic* obj,
                                   T* expected, T desired );
template<classT >
bool atomic_compare_exchange_weak(volatilestd::atomic* obj,
T* expected, T desired );


51.bind函数绑定的参数默认是值传递，如果需要应用传递请在参数前加上std::ref修饰符
int func(int a, int b&, int c);
std::bind(func, a, std::ref(b), c);
std::ref 何 std::move相似

52.c/c++中的整形溢出问题
溢出类型一:
char varc = 123 + 12345;
溢出类型二:
uint32_t vara = 12340;
uint64_t varb = 1024 * 1024 * vara;
varb正常的运行结果应该是12939427840,但是程序运行的结果为54525952可以看书已经发生了整形溢出，本来
我以为uint64_t是能够容纳12939427840，就不会溢出，但是理解错了，在运算时的结果字面值已经发生了溢出
如果改成uint64_t varb = (uint64_t)(1024 * 1024 * vara); 结果还是54525952
如果改成uint64_t varb = 1024 * 1024 * (uint64_t)vara; 结果就对了
为什么、就是在字面值运算时已经溢出，我想应该时运算时最终结果转换为参与运算元素中最长元素的类型

53.字符串数字互转,以后尽量使用string中的stoi to_string函数来替换string.h中的atoi itoa等

54.c++中当库里面的函数与当前工程源文件里面重名(命名空间也相同)，如果链接的库是动态库,那同名的库函数中的同名函数会优先连接工程目录下的源文件
如果是静态库，则链接失败,编译器不知道要链接哪个函数

55.遇见一个有趣的问题，在写daemon或服务器程序时，一般在main函数之前注册信号(signal),然后再服务初始化完成后getchar()让main函数所在线程睡眠,
把cou让出来,后续清理资源,但是退出程序的方法就是输入一个字符,但是daemon时无法接受输入的,这时用signal来注册信号就不太妥当,应该使用linux系统库函数sigactive函数
来注册信号,此函数注册的信号处理函在接受到信号时可让线程从睡眠状态转变为可运行状态,跳过getchar()，来清理函数

56.使用c++11的变量初始化方式赋值，bool isSuccess{initNetworkSDK()},这样{}在函数参数较多时可以起到格式化作用,所以以后编程尽量用{}赋值


57.c++中的namespace有一个特殊的作用，提供单独的作用域，它类似于静态全局声明的使用，可以使用未命名的namespace定义来实现
namespace {
    int count; // 等价与static int count;
}

func (int i) {count = i}

58.多线程编程中,为了使多核cpu发挥最大效率,通常会将线程均匀分布在cpu的每个core上,而且各种平台都提供了这类接口
#ifdef _WINDOWS
	const Int32 tempThreadAffinityMask{ 0x01 << mask };
	status = static_cast<Int32>(SetThreadAffinityMask(tid, tempThreadAffinityMask));
#else
	cpu_set_t tempCpuSet;
	CPU_ZERO(&tempCpuSet);
	CPU_SET(mask, &tempCpuSet);
	status = pthread_setaffinity_np(tid, sizeof(cpu_set_t), &tempCpuSet);
#endif//_WINDOWS

59.内存屏障(memory barrier),编译器在编译代码时会存在代码优化，指令重排(-O2 -O3),优化的目的在于提升程序运行时的性能，
但有时这种优化会导致内存乱序访问, 内存乱序访问主要发生在两个阶段并:
1.编译时，编译器优化导致内存乱序访问（指令重排）
2.运行时，多core CPU间交互引起内存乱序访问
什么是内存访问乱序? int x, y, r; void f(){x = r;y = 1;} 加上-O2优化后的汇编代码movl r(%rip), %eax movl $1, y(%rip) movl %eax, x(%rip
明显发生了乱序,这时候就需要使用到memory barrier来限制(或者使用volatile关键字来优化,但是volatile只能解决编译时内存乱序访问,而不能解决
运行时内存访问乱序),memory barrier的主要作用为:
code1;
#define barrier() __asm__ __volatile__("" ::: "memory")
code2
***内存屏障保证在执行code2时,code1已经执行完毕***
Memory Barrier 常用场合包括：
1.实现同步原语（synchronization primitives）
2.实现无锁数据结构（lock-free data structures）
3.驱动程序


60.当进行数学运算时,如果能用位运算代替，尽量使用位运算,如果参与计算的一方为2^n，那一定会有办法进行位运算

61.bloom过滤器,由于快速查找某个键值(key)是否存在与filter(过滤器)中，布朗过滤器就是一个bitset，通过把key(hash)加上步长规则
映射到过滤器上，查找时再通过相同的规则映射，如果结果不匹配,那一定不在过滤器上,如果结果匹配不一定在过滤器上，因为映射可能
会出现碰撞,可以通过增加bit_pre_key，每个(key)所包含的bit数，或者复杂的步长计算规则减少碰撞记录，但是同时也要考虑空间利用率
具体例子参考leveldb util/bloom_filter.cc

62.Policy(策略)设计模式

63. boost的enable_shared_for_this这个工具很有用,应用场景:需要将this作为回调函数的userdata(context),但是一般要用boost::bind绑定
可以防止在this被释放(其实不是释放，在其他地方使用this一定要使用shared_ptr，不然释放this后还是会内存错误)后继续使用

64.forward_list，前向列表(单向列表),每个node只有一个next指针，所以它的迭代器都是forward_iterator,只能支持++操作，不能--，他又before_begin可以获取head的前面位置

65.以后再项目代码中遇见错误，在各种codereview都没有找到bug(或编译错误)所在,那就用终极办法，屏蔽(注释)所以可能出现错误的位置，尽可能的让代码运行起来，然后再一个个慢慢解注释，
定位出错位置

64。编译遇见一个错误，硬是搞了一天.boost::function<int(int, int)> func;我直接给在初始化列表中赋值nullptr，然后报错硬是看不懂，赋值0又编译通过了
我想func压根就是一个函数对象，不是一个指针,所以不能够直接nullptr，为什么0又行呢，我想时因为std::function 与整数存在implicit convert(隐式转换)

65.造成64的编译错误还有一种可能会导致，就是实参与形参函数返回值、函数参数个数类型对不上，也会赋值不成功，编译时错误

66.一直不知道thread detach的作用,只知道是线程分离的意思,当启动一个线程后,当线程退出时并没有join在等待,那程序就会抛出terminate called without an active exception
所以当线程执行完成后一定要调用join等待,最好调用joinable判断,不然对一个thread对象两次join也会抛出异常,join就是在回收线程资源,有没有办法不用调用join去释放线程,那就是
detach,当调用detach后，等于把资源管理权限交给了线程，由它自生自灭,线程执行完成时操作系统会自动回收资源，但不管是join还是detach，当main线程退出时,全部线程将被回收

67.shared_ptr存在相互引用而最终不能释放导致内存泄漏的问题,请看例子
class TestA {                                   class TestB {
    public:                                      public:
    func1(shared_ptr<TestB> ptrB) {              func1(shared_ptr<TestA> ptrA) {
        m_ptrB = ptrB;                              m_ptrA = ptrA;
    }                                             }
   private:                                      private:
   shared_ptr<TestB> m_ptrB;                        shared_ptr<TestA> m_ptrA;
}                                                 }
    
std::shared_ptr<TestA> ptr_a = std::make_shared<TestA>();
std::shared_ptr<TestB> ptr_b = std::make_shared<TestB>();
ptr_a->func1(ptr_b);
ptr_b->func1(ptr_a);
最终导致的结果是TestA和TestB都不能被释放,
ptr_a对ptr_b说，哎，我说ptr_b，我现在的条件是，你先释放我，我才能释放你，这是天生的，造物者决定的，改不了。
ptr_b也对ptr_a说，我的条件也是一样，你先释放我，我才能释放你，怎么办？
是吧，大家都没错，相互引用导致的问题就是释放条件的冲突，最终也可能导致内存泄漏。
解决这个问题的方法就是使用weak_ptr作为成员变量,因为对eark_ptr的赋值不会引起引用计数增加

 
 68.std::move和std::forward,有一点值得注意,经过两者操作过的变量,并没有产生1Byte的代码,他们就是一个type_cast,move将左值cast成右值
 右值引用类型是独立于值的，一个右值引用参数作为函数的形参，在函数内部再转发该参数的时候它已经变成一个左值，并不是他原来的类型。
 如果我们需要一种方法能够按照参数原来的类型转发到另一个函数，这种转发类型称为完美转发。
 template<typename T>
void print(T& t){
    cout << "lvalue" << endl;
}
template<typename T>
void print(T&& t){
    cout << "rvalue" << endl;
}
 
template<typename T>
void TestForward(T && v){
    print(v);
    print(std::forward<T>(v));
    print(std::move(v));
}
 
69.在现代软件开发中，常常使用url方式访问资源,其实url访问就是遵照http协议的TCP连接,只不过是java、php对url的访问方式支持较好,
不像c++这总底层语言,在收到url是还需要去解析url的后缀,其实之前我一直把url访问看的很复杂,其实url经过dns解析之后就是一个ip地址，
通过url访问等价于TCP连接，在收到url之后只要解析url后缀即可知道url需要访问的内容:https://baike.baidu.com/item/fd84/453974?fr=aladdin
https://baike.baidu.com就是url前缀经过DNS解析后就是一个ip地址,item/fd84/453974 就是一个资源后缀，网站后台通过url后缀去判断你要访问
的资源,fr=aladdin是get参数，就是你向资源传送的参数





