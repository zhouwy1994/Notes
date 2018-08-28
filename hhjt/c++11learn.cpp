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
经过以上步骤，vs自动生成几个文件，这几个文件都是必需的，其中一个文件名为($ProjectName).cpp的程序是定义要导出函数的源文件,可将要导出的
函数定义到此源文件中,在要到处的函数头加修饰符__declspec(dllexport)(win专用)
也可以自己新建一个($ProjectName).h将需要导出的函数进行声明，导出类特别说明(需要在class后加__declspec(dllexport)导入时__declspec(import))
记得每个源文件要添加#include "stdafx.h"声明

4.windows下c++制作静态库步骤:
文件--->新建---->项目---->Visual C++---->Windows桌面(老版本可能是w32程序----->win32控制台程序)---->静态库---->命名工程(myDLL)
静态库就相对简单了，只需添加源文件，在需导出函数或类修饰符加上extern声明即可生成lib文件

5.Linux c++动态库制作
将需导出的函数声明为extern
编译选项
gcc -c -fPIC max.c
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

























