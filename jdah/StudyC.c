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













112.74.167.194 65531
