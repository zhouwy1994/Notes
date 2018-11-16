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
funcPtr ptr = ](int a, int b)->int {
	return a + b;
}
lambda表达式很适合用作函数回调参数

7.Visual Studio2017跨平台编译(Linux),提高编译速度(提高编译并发数),项目属性----->C++----->通用------->最大并行编译数(修改此处即可)

8.linux下有一个命令pkg-config可搜索所需要库的信息，包括路径，编译选项，编译必备，比如你在编译过程中需要使用到opencv相关库，可使用下列命令
g++ source.cpp `pkg-config --cflags --libs opencv`

9.Visual Studio跨平台编译可在项目属性------>链接器----->附加依赖项 添加一些gcc\g++所需要的编译选项


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









