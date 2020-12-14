1.Gcc编译c/c++代码时,默认是动态链接库，如果想静态链接，可加选项-Wl,-Bstatic改选项后跟要静态链接的库，但是::最后要恢复动态链接方式
-Wl,-Bdynamic，不然后面全用静态链接方式，*有的静态库本身就依赖有其他动态库,pthread,dl等，如果采用-Wl,-Bstatic方式会有报错,这时需要将静态库所依赖的动态库放在-Wl,-Bdynamic后*
静态链接stdc++，使用选项-static-libstdc++
2.所以linux的64位系统都会有一个lib64目录，任何linux系统都会有lib目录，其实lib64和lib目录里面的东西大部分是一样的（例如lib64和lib中都会有libc.so.6），只是lib64里都是64位库，供64位
程序动态链接，而lib里面的库是32位程序链接的库
linux系统的/lib -> usr/lib（软连接）lib64 -> usr/lib64（软连接）bin -> usr/bin（软连接) sbin -> usr/sbin（软连接）
3.linux下c/c++必备库:libc.so(c) libstdc++.so(c++)
4.查看linux下可执行程序所依赖的库文件（库版本信息）方法:
(1)objdump -p /path/exceable_pargram | grep NEEDED
(2)objdump -p /path/exceable_pargram 后面Version References:有详细的GLIBC版本信息
(3)strings /path/execable_pargram | grep GLIBC 查看GLIBC版本

5.查看库文件是32位还是64位 file /path/execable_pargram

6.gcc4.8 gcc8.2切换命令

7.vistual studio2017支持添加cmake工程(linux、windows)，步骤:
(1)打开vs2017-->文件---->打开----->CMake(或者文件夹<包含CMakeLists.txt的文件夹>)--->选择CMakeLists.txt
(2)在窗体调试(团队)下发有一个下拉框--->选择管理配置--->弹出CMakeSettings.json---->这个文件就是项目配置的关键
(3)编辑CMakeSettings.json中的$remoteMachineName(远程主机的ip)、$remoteCMakeListsRoot(远程CMake工程的root目录，此root目录就是项目工程的主目录)
(4)$cmakeExecutable(远程主机cmake命令所在路径)、$buildRoot(本机的构建目录，使用默认)，$installRoot(本机安装目录)，$remoteBuildRoot(远程构建目录，应该是与buildRoot对应，做了一个拷贝)
(5)$remoteInstallRoot(远程安装目录，存放编译之后的可执行文件,应该是与installRoot对应，做了一个拷贝)
(6)其他值使用默认
(7)如果cmake中有多个生成对象（选择启动项）即可编译调试

(8)右击CMakeLists.txt,"调试和启动设置"，选择需要的启动项，就会弹出对应程序的launch.vs.json，里面可以甚至调试选项,args,程序启动参数

8.分布式之间的时间同步需采用ntpserver方式

9.c++17也出了很多新特性，可以学习一下，我目前遇见的最实用的库filesystem，编译时需要链接-lstdc++fs（其实这些库都是从boost移植而来）

10.std::static_point_cast、dynmic_point_cast、const_point_cast专门用来转换智能指针
class Base {};
class Driver::Base{};
std::shared_ptr<Base> basePtr {std::make_shared<Base>()}
std::shared_ptr<Driver> driverPtr {std::make_shared<Driver>()}
上行转换:
auto ptr {static_point_cast<Base>(driverPtr)}
static_point_cast只适合用来做上行转换，下行转换没有类型安全检查，static_cast也可用来转换裸指针时原理相同
下行转换
auto ptr1 {dynamic_point_cast<Driver>(ptr)}
dynamic_point_cast用来做上行转换时和static_point_cast效果相同，用来做下行转换时有类型安全检查，如果类型检查不通过结果为nullptr,dynamic_cast转换裸指针时效果相同
但是dynamic_point_cast和dynamic_cast做上行或下行转换时基类必须包含虚函数

const_point_cast用来转换const特性

11.std::weak_ptr,一直以为弱指针没有什么用处，当你函数返回一个指针值，你又不想返回裸指针，但是返回shared_ptr会增加引用计数（你不想把指针的生命周期控制权转移出去）
这是就可以将shared_ptr转为weak_ptr作为函数返回值，这样不会增加引用计数，而且在必要情况下可以通过lock方法来获取shared_ptr值

12.c++中的读写锁实现，读写锁:允许多个线程同时获取读锁所以权，只有一个线程能够获取写锁的所以权，当读锁被持有时，写锁不能被持有，写锁被持有时，读锁不能持有
实现:
typedef std::shread_lock<shared_mutex> read_lock;
typedef std::unique_lock<shared_mutex> write_lock;
std::shared_mutex smutex; // shared_mutex也可使用shared_timed_mutex替代,timed_mutex带有定时功能try_lock_for,try_lock_until
读取锁定
read_lock rlk(smutex);
写入锁定
write_lock wlk(smutex);

13.数据库访问工具ODB（https://www.codesynthesis.com/）是c++访问数据库的ORM（对象关系映射），可以访问数据库不用写SQL语句，将数据库访问
映射成面向对象操作(ODB 支持所有主流数据库 sqlite_orm)

14.消息队列：RabbitMQ(访问客户端rabbit-c(c),SimpleAmqpClient(c++对rabbit-c的封装)),消息队列要学习

15.MinGW-w64(Minimalist(极简) GNU for Windows)安装，MinGW是windows版的GUN工具套件，包含gcc，g++,gdb还有比较多的可用工具
安装步骤:
(1)下载http://mingw-w64.org/doku.php/download选择MingW-W64-builds
(2)下载的mingw-w64-install.exe直接打开
(3)Version选择最新版、Architecture(i686<32bit>,x86_64<64bit>)、Threads<posix(unix/linux),win32>(使用那个风格的线程库)、
Exception(异常类型<seh<新版，只支持64bit程序><sjlj 老版支持32bit>>)、Build revision
(4)将MinGW的bin目录加入环境变量目录
(5)ok

16.void func(const std::string &param);
func("Hello Word") //可以正确调用
void func(std::string param);
func("Hello World") //可以正确调用
void func(std::string &param);
func("Hello World") //不可以调用，因为"Hello World"不是一个有效的std::string引用

17.ODB学习笔记
如果要使用一下方式
#pragma db object(person)
#pragma db member(person::id_) id
那使用成员必须要有公共访问接口，而且命名有规则,例如有一个数据成员(表字段) std::string name_;
(1)cosnt std::string& name(void) const;
void name(const std:string& name);
(2)cosnt std::string& getName(void) const;
void setName(const std::string& name); // 注意首字母小写
odb在使用boost第三方支持时，在odb编译步骤需要加--profile boost,链接时除了加-lboost_**，还要加上-lodb-boost
odb null要使用odb::nullable<T> mem;

g++编译时加上-DDATABASE_MYSQL条件

18.libcurl学习(http://blog.csdn.net/JGood)
curl_global_init(); // 初始化全局资源(每个程序只调用一次)
CURL *easy_handle = curl_easy_init(); // 初始化一个easy对象,easy_handle好似一个连接session，一个easy对象需要设置option,才能工作
curl_easy_setopt(easy_handle, CURLOPT_URL, "sftp://192.168.101.134/root/upload.html"); // 设置easy属性
curl_easy_perform(easy_handle); // 开始执行(同步)

multi_handle = curl_multi_init(); // multi是异步执行方式，可以通过向其添加easy_handle
curl_multi_add_handle(multi_handle, easy_handle1); // 添加任务
curl_multi_perform(multi_handle, &running_handle_count); //开始执行异步任务

curl_global_cleanup(); // 释放全局资源(每个程序只调用一次)

19.c99新特性,__VA_ARGS__,可变参数宏
#define PRINT(...) printf(__VA_ARGS__)
PRINT("%s:%d", argv[0], argc);


20.std::string convert to c++ base type function std::stoi std::stoll...

21.c++11允许用户自定义字面值,方法如下
std::chrono::seconds operator"" _S(unsigned long long n) {
	return std::chrono::seconds(n);
}
然后就可以使用
std::this_thread::sleep_for(1_S); // c++标准规定,用户自定义字面值必须带下划线_,不带下划线的只允许c++标准使用，而c++14已经有了s，ms等字面值

22.gdb 调试程序时制定程序参数 gdb --args a.out arg1 arg2 ...

23.boost里面有一个智能指针,intrusive_ptr<T>(入侵指针)，其实就是自定义智能指针辅助类，需要实现两个回调函数intrusive_ptr_add_ref(T*)，增加引用
计数，intrusive_ptr_release(T*) //减小引用计数，用户可以在此回调函数中做相应操作，比如当引用计数减为0时，做相应操作，intrusive_ptr构造和析构时会
回调这两个回调函数

23.c++中2进制转16进制，简单实现版
std::string bin_to_hexstr(uint8_t *bin, std::size length) {
	std::stringstream ss;
	std::for_each(bin, bin + length, [&ss](uint8_t ch) {
		ss.fill('0'); // 不足部分用0填充
		ss.width(2); // 设置宽度为2
		ss << static_cast<uint32_t>(ch);
	});
	
	return ss.str();
}


24.c++中大部分容器的成员函数都会返回迭代器(iterator)类型(继承与标准的iterator)，iterator并不是一个针对不同容器的特点类型，而是一个标准的迭代器类型，
iterator存在于头文件<iterator>,这就是为什么只要是迭代器类型都适合于algorithm中的所有算法，for(auto)方法

25.可以自定义迭代器，继承标准的iterator，地带其类型又分为输入输出迭代器，前置后置迭代器等，每一种迭代器有不同的访问方式

26.STL中resize和reserve的区别,resize和容器的size相关，reserve与容器的capacity相关
resize(n):不管n是大于size()还是小于size()，最终size() == n，多出的会被销毁，不够的按初始化值补全，或者可以通过resize(n, value)以value填充
reserve(n):如果n > size()那会再增加n-size()个capacity,但不会初始化，如果n < size()不做任何处理

27.STL中的容器分为三大类:顺序性容器、关联式容器，容器适配器
顺序性容器:是一种各元素之间有顺序关系的线性表，是一种线性结构的可序群集。(vector,list,deque)
关联式容器:和顺序性容器不一样，关联式容器是非线性的树结构，更准确的说是二叉树结构。(set，map，multiset,multimap)
容器适配器:适配器是使一事物的行为类似于另一事物的行为的一种机制。容器适配器是让一种**已存在的容器**类型**采用另一种不同的抽象类型**的工作方式来实现的一种机制。
其实仅是发生了接口转换。就是用已知的容器来实现另一种容器(stack,queue,priority_queue,slist)

28.golang中函数可以返回多个值，外部调用时可按返回顺序接收返回值，不想接收的返回值可用_占位符过滤.c++中可以用tuple代替,std::tie，std::igonre
// golang
func vals()(int,int,int)  {
	return 3,7,9
}

a,b,_ : vals();

// c++
std::tuple<int,int,int> vals() {
	return {3,7,9};
}

int a,b;
std::tie(a,b,std::igonre) = vals;

c++17中的一个新特性--结构化绑定更简洁
auto [a,b,c] = vals();

29.如果程序中使用了getchar()作为程序阻塞的方法，那这个程序就不能以后台的形式运行(a.out &),unix是这样解释的，当后台任务遇到getchar()时会产生
SIGINT信号，导致程序异常退出


30.boost::enable_shared_from_this是一个好用的智能指针工具，可以在boost::bind回调中使用this而不需要担心函数回调后this被释放，但是存在一种场景
基类继承了enable_shared_from_this,派生类中直接使用Base::shared_from_this时会报错，那是因为Base::shared_from_this返回的时shared_ptr<Base>,而在
c++中是不允许基类直接转换为派生类,需要使用dynamic_point_cast<Driver>进行转换

31.a.一直以来使用vs总是有中文不能正常输出<常量中有换行符>，编译报一大堆警告和错误，这是可以在--->属性---->c/c++--->所有选项--->附加选项加上 /utf-8选项即可解决,并建议
在后面的工程中也加上此选项
b.如果是QT使用MSVC编译器也会遇到上述问题，解决方案，工具--->选项--->文本编辑器--->行为--->文件编码--->默认编码选择UTF8--->UTF-8 BOM选择:如果编码是UTF8则添加
在包含中文符号的文件添加宏定义:#pragma execution_character_set("UTF-8")就解决了(防止MingGW不能识别该宏，可使用_MSVC宏定义限制)

32.终于知道boost不用连接库直接编译源码的方法了，先要声明宏BOOST_ALL_NO_LIB，然后将boost_1_69_0/libs/下面对应的库目录下的src下的文件加入
项目源码中一起编译，就可以了，也可以针对每一个库这样做，例如date_time(BOOST_DATE_TIME_NO_LIB)

33.其实vs提供命令行编译方式，很多第三方开源软件也默认支持cmake或nmake构建工程，但直接从cmd或powershell下是无法使用cmake或nmake或cl的，要使用
Vistual Studio专用的命令行工具《适用于VS2017的本机工具命令提示(注意32bit还是64bit)》,在这个工具下才可以使用全部的vs下的工具

34.libcurl库编译时如果指定了ENABLE_WINSSL选项，就包含了ssl库，如果这时候项目中包含了其他也要使用导ssl库，可能就会默认连接curl库中的ssl，
就会导致连接不正常，所有如果使用libcurl的话就要注意连接ssl库的问题

35.vs编写windows程序时默认动态链接运行库，倒是这样对于没有安装windows运行库的计算机是不能正常运行的，要不就是连动态库一起拷贝，要不就静态链接
运行库，静态链接运行库方法：
项目 -> 配置属性->常规->MFC的使用 :在静态库中使用MFC（此项必须设置）。
项目 -> 配置属性->C/C++->代码生成->运行库 :选择/MT。（此项可选，设置之后部分机器可能会编译出错）


36.c++访问redis第三方库，CRedisClient(https://github.com/shawn246/redis_client),是一个不错的redis访问数据库工具，
但是也相应的存在bug,需要自己外加代码选择db,和auth（认证）,在CRedisConnection::ConnectToRedis中添加，注意他的redisCmd.SetArgs
里面的m_bShareMem，默认是开启的，CRedisCommand redisCmd("cluster", false);需要额外的添加false；

37.今天学习go语言多维切片,[][]int,是这样理解的，这是一个切片类型，他的元素类型是[]int(整形切片),这样我联想到学习多年的c中的多维数组,
int[4][3];之前一直是这样理解的:这是一4*3的二位数组，这样理解没错，但是我认为这样理解更为恰当:这是一个包含3个元素的一维数组，他的元素类型是
一个int[4]的一维数组


38.Mingw Mingw-w64 TDM-GCC之间的区别，怎样选型
共同的:
一、 他们都是用于编译生成Windows应用程序的工具链。
二、 他们都是基于gcc的。

1. MinGW应该是最先诞生的。只支持生成32bit程序，不建议使用
2. MinGW-w64项目最初是做为MinGW的一个分支而诞生，但现在已经独立发展。可支持生成32bit和64bit的程序（推荐使用）
3. TDM-GCC是对MingGW-w64的工具打包

39.****由于Mingw-w64的稳定,且不容易出错，golang底层也要用到，所以就选用Mingw-w64做为之后的Windows平台的gun开发工具****
下载：http://www.mingw-w64.org/doku.php/download (mingw-w64-install.exe)
打开mingw-w64-install.exe
选择平台****这步最重要i686,是32位平台
x86_64是64位平台,平台很重要，将决定你以后能够通过gcc编译出来的程序位数，也是golang的cgo平台能不能运行在32bit或64bit的前提
目前尝试用mingw-w64 加-m32参数编译32位程序失败，因为mingw-64只包含64位的库，可以安装mingw-w64 i686来获取32位库


40.算是解决了一个大问题了，golang交叉编译32位程序时，只要用到了cgo就编译不过，总是提示库冲突，是因为本地的mingw-64是64位的，并没有32位的库，
解决办法:
安装Mingw-w64的32位版(i386)
将i686-w64-mingw32-gcc.exe所在的目录添加进环境变量
set GOARCH=386
set CGO_ENABLED=1
set CC=i686-w64-mingw32-gcc
set CXX=i686-w64-mingw32-g++
就可以了，为什么不将CC设置成gcc?
因为系统上同时安装了mingw-w64的64位版和32位版，而且都同时加入了环境变量，谁的环境变量排在前面gcc就是谁的，所以为了区分
64为的gcc g++:x86_64-w64-mingw32-gcc x86_64-w64-mingw32-g++
32位的gcc g++:i686-w64-mingw32-gcc i686-w64-mingw32-gc++
耗时几天


41.上面的是针对windows的，如果平台是linux,要在linux64编译出32位程序，就不用像windows这么复杂，只需要安装32位的运行库即可，
其实windows也可以这样做，但是gcc -m32 它不会去链接32位库（应该还要通过-L链接选项去限定，但没有成功），ubuntu安装32位运行库:
sudo apt-get install libc6-dev-i386
centos:
yum install libgcc-dev.i686


42.今天算是弄好了Linux下golang的Gmssl调用,我编译好了GMSSL得到了libssl.a libcrypto.a,我想以静态库的方式链接，但是一直链接不上，是两个问题导致的
1.Gmssl本来是在build.go里面写好了编译参数
#cgo darwin CFLAGS: -I/usr/local/include
#cgo darwin LDFLAGS: -L/usr/local/lib -lcrypto -lssl
1.darwin参数限定了平台,我们在linux上编译，应该改成linux
2.虽然它指定了链接库路径与要链接的库名称，但是与我们编译出的.a所在目录不一致，导致不能链接，所有需要指定正确的目录
3.-lssl -lcrypto默认链接动态库，由于之前系统遗留的openssl库，导致它去链接openssl的库，没能链接正确的Gmssl库
4.链接静态库需要指定库的路径 /usr/lib/libssl.a /usr/lib/libcrypto.a才能正确链接
5.libssl.a 和 libcrypto.a的顺序不能乱，乱了也链接不上

43.linux下的go env设置和windows不同,win下直接set GOARCH=386但是linux这样设置不生效，必须在编译之前指定:GOARCG=386 go build main.go
所有就像42描述的问题，可以通过CGO_LDFLAGS="/usr/lib/libssl.a /usr/lib/libcrypto.a" go build main.go来编译

44.这个问题困扰了几天时间，在给后台写一个工具时，需要用到国密Gmssl库，本身这个库是给nodejs使用的，node是依赖openssl库的，就是因为这个原因
导致的问题，Gmssl是openssl的一个分支，只不过Gmssl实现了一系列国密算法，所以他们包含的公共部分是一样的(函数名和全局变量名)，node去调用我所导出的so时，so里面
所用到的函数默认链接到openssl的动态库上了，由于openssl里面没有国密的椭圆曲线，所以就生成不了椭圆曲线。导致调用失败。
怎么样才能让so里面的函数链接到Gmssl的库上。就差一个编译参数-Wl,-Bsymbolic
应用程序进行链接的时候，动态库中全局变量定义，将会被应用程序中同名的全局变量所覆盖。这样也就造成了，在动态库中修改A变量时，应用程序中的A也发生了变化。
Bsymbolic表示强制采用本地的全局变量（或函数）定义，这样就不会出现动态链接库的全局变量定义被应用程序/动态链接库中的同名定义给覆盖了！

45.在项目中，可能会用到不同的gcc版本，就会在同一系统下存在两个不同版本的gcc编译器，尽量不要将两个版本的gcc的bin目录都防止PATH下，这样可能会导致一些不必要的麻烦
不常用版本的gcc可以不必放在PATH下，正常编译是只要指定绝对路径即可，但如果是cmake，或者是configure编译项目怎么办，小问题
ccmake:两种方式
1.cmake使用的编译器默认是cc和c++,然而这两个命其实只是一个软连接，在编译项目时只需要将cc和c++的链接指向指定的gcc和g++即可编译调试
2.在主CMakeLists.txt中指定编译器绝对路径:
set(CMAKE_C_COMPILER "/usr/local/gcc8/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/local/gcc8/bin/g++")
configure:一般configure在指向时都可在命令行指定编译器,不同configure可能不太一样，但都会提供，使用configure --help查看

编译boost时指定编译器:运行bootstrap.sh后生成project-config.jam 打开修改using gcc为using gcc : 8.2.0 : /usr/local/gcc8/bin/g++

46.库路径也可以同个上述方式指定

47.用mingw编译libmgp123时遇见错误invalid instruction suffix for push，错误原因是，在64位系统和32位系统对于某些汇编指令的处理
支持不一样造成的。在文件出现错误的.s中，在代码头部添加.code32即可。

48.还是中文编码的问题,vsc++，要保持utf8,就要设置/utf-8参数，我只设置了/source-charset:utf-8,只用源代码是utf-8，但执行文件不是utf-8格式的
若只需要修改源代码的编码，也可以只输入：
/source-charset:utf-8
类似的，还有可执行文件编码：/execution-charset:utf-8
/utf-8相当于同时设置源代码和可执行文件。

49.c++kafka消费消息，为防止消息丢失，需要设置手动提交，还需要把offset设置为earliest模式
// https://blog.csdn.net/csCrazybing/article/details/76593855
m_global_conf->set("enable.auto.commit", "false", errstr);
m_topic_conf->set("auto.offset.reset", "earliest", errstr);

50.打包QT开发的exe文件依赖库,C:\Qt\Qt5.9.8\5.9.8\msvc2017_64\bin\windeployqt.exe message.exe


51.开发sdk时，希望最后提供出来的就一个dll或so，第三方依赖尽量链接相应静态库，gcc中-static-libgcc -static-libstdc++ -Wl,-Bsymbolic编译参数
就可以将gcc c++依赖的基础库封装，但是有的系统上需要提前安装yum install libstdc++-static

Linux下编译so导出源文件里面的指定函数：
1、在文件里面最前面加上：#define DLL_PUBLIC  __attribute__ ((visibility("default")))
2、在文件里面需要导出的函数前加上：extern "C" DLL_PUBLIC 
3、Linux下动态库（so）编译时默认不导出，在Makefile中需要添加：-fvisibility=hidden


52.使用libcurl库，官网下载库，只包含dll和一个def文件，由于vs使用dll需要一个导入的lib文件，可以通过lib命令将def转换成lib文件
命令:lib /def:libcurl.def

53.VS默认使用编码格式为GB2312，这给代码移植带来很大的不便，代码需要使用utf8,先安装插件ForceUTF8(NO BOM),然后再所有工程的
C/C++附加选项填/utf-8

54.QT只是一个开发库一套框架，既然是库就有32位与64位之分，所以安装QT的时候就会选择,如果想开发使用与32位于64位的QT程序，在安装选项中
就要选择，可以同时选择两个，其中选项有mingw-32bit,msvc2015bit、msvc2015-64bit,msvc201764bit，这些是什么意思呢
就是说QT的库使用上述编译器编译出来的，如果选择了对应版本，那么计算机上就必须要有相应的编译器，ming版的QT的安装包中顺带有
mingw编译套件，但是msvs就得本地安装相应得mscv编译器了

56.我计算机上安装的版本MSVC2015-32bit MSVC2015-64bit,我还以为只可以使用MSVC2015版本的IDE，其实还可以在构建套件中配置vs2017或更高版本的vs,
只要选择好编译器版本与调试器版本就行,vs2017对应vs编译器为15，调试器版本为cdb

56.如果QT编译时提示“无法运行rc.exe”，请用everything搜索rc.exe,复制相应平台(x86与x64)下的rc.exe与rc.dll到Qt\msvc2015\5.9.8\bin下


57.c++编译出来的动态库是很通用的，大部分语言都可以使用c++的dll或so，但是c++调用其他语言就比较麻烦，还好微软对c++与c#的支持都比较好
所以c++调用c#也比较方便，首先得在vs中将(公共语言运行时支持(/clr))开启，使用using "../Debug/C#.dll"导入即可,但得包括一些头文件才可
使用

58.c++编写动态库dll导出函数时一版为了能够事得导出函数可用，都会使用 extern "C" __declspec(dllexport) int ExportFunc(int)
这样导出的函数没有问题，但是我就遇见一种情况，客户要求导出函数遵循__stdcall的调用方式，这样的话函数声明就会变成
extern "C" __declspec(dllexport) __stdcall int ExportFunc(int),奇怪的是加了__stdcall之后，导出的函数名就会变成_ExportFunc@4这种c++
导出函数方式，解决办法之一就是#pragma comment(linker, "/export:ExportFun=_ExportFunc@4")通过将导出函数alias(别名的方式导出)


59.本条记录熬夜到凌晨3点，waveInOpen一个WIN的底层api，功能为打开麦克风，之前在编译的64位，没问题，但是换乘32位后，代码都没有
改动，莫名其妙报了一个内存错误，排查一晚都没早到问题，最后一刻万能的度娘解救了我，waveInOpen里面有一个参数，回调函数，这个函数的
原型为void CALLBACK waveInProc(
   HWAVEIN   hwi,
   UINT      uMsg,
   DWORD_PTR dwInstance,
   DWORD_PTR dwParam1,
   DWORD_PTR dwParam2
);
忽略了一个参数CALLBACK，我自己定义的回调函数就是没有这个参数，导致堆栈调用错误,血的教训，以后要重视__stdcall和__cdel了


60.最近使用portaudio取代winmm接口，portaudio还是比较好用的，他将底层的接口封装成一个易用的接口，注意里面的framesPerBuffer是每帧
不代表字节数，每帧的大小：bit / 8 * channel,播放时一定要每帧填满数据，也不能填0,否则会有噪音或者吱吱声

c++给Android开发动态库专题,使用Android Studio 3.5，4.0版本的SDKManager打不开,不知道怎么被玩坏了
(1)下载Android Studio3.5:https://redirector.gvt1.com/edgedl/android/studio/install/3.5.1.0/android-studio-ide-191.5900203-windows.exe
(2)安装完成后首次打开会提示安装Android SDK，Gradle，如果Gradle下载失败，就手动下载，然后放到相应目录下
(3)打开SDKManger,安装NDK、Cmake、LLVM
(4)安装一个Vad虚拟Android设备，用于调试，当然在真实的手机上更好
(5)开发Android动态库,有两种构建工具,ndk和cmake，ndk使用Android.mk,cmake使用CMakeLists.txt,c++开发人员建议使用CMake
(6)As3.5有专门用于创建Android动态库的工程，File-->New->New Project->Native C++ 设置好相应的工程参数，Language最好选Java
(7)其实也不一定要通过Native C++来创建工程，只是通过Native C++创建的工程会在Android视图下app module的build.gradle中配置好cmake的相关参数,创建
app文件夹和几个示例文件其实也可以手动创建和添加，也没几个参数，主要有:
android {
    defaultConfig {
        externalNativeBuild {
            cmake {
                cppFlags "" // c++参数，如指定c++11、c++14等，异常模式、等参数
            }
        }

        ndk {
            // Specifies the ABI configurations of your native
            // libraries Gradle should build and package with your APK.
            abiFilters 'x86', 'x86_64', 'armeabi-v7a', // 需要生成的平台库,之前以为Android都是ARM架构，没想到也有x86架构，微软就出过x86的Android手机，Vad里面的虚拟机就是x86架构、汗
                    'arm64-v8a'
        }
    }
   
    externalNativeBuild {
        cmake {
            path "src/main/cpp/CMakeLists.txt" // 指定CMakeLists.txt路径，关键代码
            version "3.10.2" // cmake版本
        }
    }
}

(8)在cpp文件下包含了CMakeLists.txt和源码，所有的c/c++源文件都放在下面
(9)可以参考生成的native-lib.cpp里面的调用，下面列出一些重点
1.Java语言调用c++开发的库都需要通过Jni作为桥梁
2.Jni文件就是一个c/c++文件，只是里面的类型都是经过映射的,需要包含#include <jni.h>，其实jin.h里面就是一堆类型typedef
3.还有就是Jni的导出函数明是需要遵守规则的，不能随便取，不然Java里面识别不了，规则如下
Java_前缀+全限定的类名下划线（_）分隔符 + Native函数名
增加第一参数JNIEnv* env,增加第二个参数jobject,其他参数按类型映射,返回值按类型映射
4.调用Native库需要创建一个Java类,比如类名叫MainActivity，包名(package)为com.example.myapplication，如下
package com.example.myapplication;

public class MainActivity extends AppCompatActivity {
	// Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib"); // 加载Native库必须语句
    }

	public String externFunc() {
		stringFromJNI(); // 调用c++库函数
	}
	/**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI(); // 需要调用的Native c++库函数
}

那对应上面的Jni里面的函数定义如下:
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str()); // 在这里面就可以任意的c++代码了，好爽
}

Java：前缀
com_example_myapplication：包名
MainActivity：类名
stringFromJNI：Native函数名
这样类MainActivity才可以调用函数stringFromJNI(),
5.需要增加接口就在MainActivity类里增加一个成员函数，然后在native-lib里面增加相应的Jni接口
6.就是要注意对应的类型映射，不然编译没错，运行时app会崩溃
7.点击Build-->Make Project就可以生成so了，so在Project视图的app\build\intermediates\stripped_native_libs\debug\out\lib\arm64-v8a\libnative-lib.so,arm64-v8a属于架构
8.点击Run app就可以看见效果了
(10)ndk中提供了编译工具链,一般是LLVM的clang编译器


61.使用jsoncpp遇到一个坑，"abcd" 默认的Reader连这种字符串都能解析成功，不符合正常思维，需要将json_reader.cpp里面的Features默认构造函数的strictRoot_改为true才能正常解析