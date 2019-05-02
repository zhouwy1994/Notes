1.Gcc编译c/c++代码时,默认是动态链接库，如果想静态链接，可加选项-Wl,-Bstatic改选项后跟要静态链接的库，但是::最后要恢复动态链接方式
-Wl,-Bdynamic，不然后面全用静态链接方式，而有的库是没有静态库的，所以将链接失败
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












