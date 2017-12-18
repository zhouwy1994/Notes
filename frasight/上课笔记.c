
虚拟机的三种上网方式：仅主机：只有主机上网，；虚拟机不能连接1网络，不常用
NAT:虚拟机创建一种上网功能，IP地址被覆盖，外网不能访问虚拟机
桥接：虚拟机和主机都是单独的计算机访问网络；
root = administator
source lnsight：代码编写工具
qt-creator

计算机的三层结构：应用层，操作系统（Kernel），硬件层
应用层与操作系统层之间是系统函数调用，操作系统与硬件之间是驱动

 sudo passwd 用户名 //修改密码，设置密码
 sudo apt-get update,更新软件源
 sudo apt-get dist-upgrade
嵌入式学习主要是学习操作系统层：C/C++,Java,C#
Java,C++主要是一堆函数封装，而C语言是一个面向过程的语言，不事宜写应用程序
书籍：UNIX高级编程，UNIX网络编程卷1
重要：数据结构，算法
学习开源库（压缩库）
文件系统：管理储存器文件的系统，ext4（liunx）ntfs(windows)
windows 分区
liunx 目录树结构
fdisk -l 查看liunx分区 mount查看分区
windows分区下管理目录liunx目录管理分区
普通用户的主目录在/home
root在/root
pwd print work director 打印工作目录
ls list 列表
man 可查看三大类命令
man1 liunx命令
man2 系统函数
MAN3 标准库函数
chown root:root 改变文件所属用户
chmod u g o
chmod u+x
绝对路径 /home/zwy/
相对目录 ../../
pwd 当前目录
~主目录
-上一次目录
./当前目录
../上一层目录
ls -a 显示全部文件
ls -l 显示列表
ls -R 递归显示

cd 什么都不加回到主目录与cd~ 一样
mkdir -p 如果创建递归目录不存在，则创建父目录
rmdir 删除空目录
rm -r 递归删除目录
touch 创建文件，长度为零
rm -f 强制性删除，不报错
mv/cp 剪切/复制 还有改名的功能
shutdown -h/r now 关机
ln -s a.c x.c 创建连接文件 符号链接，软连接l
不加-s为硬连接 为普通文件-,修改连接和源文件效果一样
cat 查看文件内容
saveas uu.c另存为，在保持后面加另存为文件名就可以
vi i,a,o,s
   I,A,O,S
 I 行首插入
 A 行尾插入
 0 上行插入
 0 上行插入
 S 整行删除
 u：恢复
 p：粘贴
 nyy：复制
 ndd:剪切
 yw复制单词
 ctrl+b翻前页
 ctrl+f翻后页
 ynw
 ynb
 dnw
 dnb:剪切n个单词向前
 nG:跳到n行
 
 vi配置文件：主目录里面vimrc //etc/vim/vimrc
 set nu:显示行号
 set tabstop=4:tab键代表四个空格
 set cindent:设置C语言缩进
 set shiftwidth=4 ：设置4空格缩进
 :s/fun/ccc/单行替换
 :%s/fun/ccc/g全部替换
 ：/hhh查找
：12:15s/fuu/ggg/g从12到15行替换
ctags:查找c程序函数
先安装ctags sudo apt-get install ctags
然后ctags -R ./file建立tags
打开vi光标移动到想要查找的函数名
ctrl + ]:查找
ctrl + T：返回
使用putty控制虚拟机liunx条件：
1、虚拟机网络桥接模式
2、liunx安装了ssh，apt-get install ssh
3、获取liunxip地址
4、配置putty
find /查找的目录 文件名
liunx上的分区都是以文件的形式存在
mount /dev/sda /mnt/xx 挂载sta到mount/xx下 xx称为挂载点
/tmp目录启动自动清空，重要资料不要放在tmp中
chmod//改权限 u,g,o
chown//改文件所属者
chgrp//改文件所属组
目录：755
文件：644
ubuntu的程序菜单栏在屏幕左上角
cpu：alu:运算器cu:控制器
如果程序需要调试需要加-g选项
gcc -g -o hello hello.c
gdb hello.exe
disassemble反汇编选项
si执行下一条汇编指令
程序代码存放在存储器中，但一定要放在内存上
ASCLL UTF-8 GB2312
ASCLL 前32个控制字符不可显示，用于通讯，后面95个可显示
C语言的注释编译器以一个空格代替
gcc -E -o acc.i acc.c 预处理文件
gcc -S -o acc.s acc.i 汇编文件
gcc -c -o acc.o acc.c 二进制文件
define ADD(a,b) a + b 
mkdir -p dir/dir1
rmdir -p dir/dir1/dir3 在删除dir3时递归删除dir2,dir3空目录jj
cp -i 复制前提示是否覆盖
cp -R 复制文件夹
cp -f 强制复制
cp -l 建立硬连接
cp -v 显示详细过程
currently not installed 当前没有安装
vi中的命令L,H光标移动到末尾和开头
cat -n 显示行号
cat -b 空白行不变行
stat：显示文件的时间属性
通配符：touch file_{1,2,3,4,5}
创建file1,file2,file3...
unlink 删除普通文件
umask可用来设定[权限掩码]。[权限掩码]是由3个八进制的数字所组成，将现有的存取权限减掉权限掩码后，即可产生建立文件时预设的权限。
which cp 查看命令所在路径
locate/slocate hello 查找文件名中包含hello的文件的绝对路径
补码等于原码取反加一
ubuntu 里安装deb软件，可直接双击，如果出现问题，在终端里输入sudo dpkg -i 软件名
进行安装
如果依赖关系不完整，可用apt-get install -f 解决依赖关系
如果还是不行,安装gdebi工具进行安装，apt-get install gdebi
运行sudo gdebi 软件包进行安装
using 与typedef 功能相同 typedef double ware
using ware = double;
typedef double *p:p为doublt*类型
短路法则
交换算法
a = a^b;
b = a^b;
a = a^b;
c++中支持输出+号连接符
cout << str + "is" << endl;
一个无符号类型与负数相比，负数永远大
左移几位，右边补0；
右移几位，左边补符号为；
位运算：#define setbit(a,N) (a | (0x01 << N)) :将a的第N位置一
#define setbit(a, N) ))(a & (!(0x01 << N))
条件表达式，可代替简单的if-else语句
sizeof也叫运算符返回无符号整数
数制在计算机中都是以补码的形式存在，正数的补码、原码相同，反码取反，负数符号位为一，取反后符号位不变
如-1 原码10000001 反码：11111110补码=反码加一=11111111=255
c++中引用c语言中的头文件在前面加c就不用加.h了，加了c就是c++中的std空间的
decltype(对象) a = xx;获取对象的类型以便定义a
auto自动获取等号右边的类型以便定义，auto a = 4.22,a的类型就为浮点型
全局变量放在头文件里面，方便引用
编译时编译器使用的标准太低，C89，如果我们需要使用更高版本的标准，需在编译选项里加-std=版本号eg:-std=c++0x
在格式控制符后加#可以打印进制的前缀%x# 十六进制
scanf不常用,用gets(),用atoi()函数字符串转整数
find 在指定目录查找文件 find ./ *.cpp 当前文件夹查找所有以.cpp的文件
grep 在指定文件中查找含有指定字符的行并输出
grep network jjj.c 在jjj.c中查找含有network的行
cmp比较两个文件的大小，相等不返回
diff比较两个文件的不同之处
sort 排序命令
迭代器：容器，运算begin()取容器中的第一个元素，end()取尾后的一个元素，注意是尾后元素
面对对象：类定义的变量叫对象，对象引用类里面的方法也叫成员
auto语句只能在函数或复合语句中定义和使用
迭代器里面装的是地址，需要解引用后才能使用
如果在到迭代器类型的情况下，不想使用auto的情况下，可使用iterator或const iterator 来获取迭代器的类型
eg：vector<int>::iterator it; //it可读写vector<int>的元素
而const_iterator成员只能读元素而不能写元素
begin()和end()返回的类型根据实际而定，而有时候我们需要只读而不可写那c++11标准定义了两个函数
cbegin()和cend()不论迭代器类型是什么，返回的类型都是const_iterator类型
数组：数组是一种类似于标准库类型vector的数据结构，但是性能和灵活性的权衡上又与vector有所不同与vecyor相同的是数组也是存相同类型对象的容器，只不过
数组的大小确定不变，不能随意向数组中添加元素，因此对某些特殊应用来说程序的运行时性能较好，但是也会损失一点点灵活性
注：如果不清楚元素的确切个数，使用vector
引用不是对象，而数组是存放对象的，所有不能有存放引用的数组
32位计算机系统，4G虚拟内存，不管真实内存有多大，操作系统都活映射出4G的虚拟内存
内存单元的地址叫指针，专门用来存放变量的地址
地址可以用%p或%#x打印
const在C语言中只有函数参数中常用
volatile int a;//容易变化的变量；硬件开发中常使用
指针相加减，移动的位置与指针的类型相同，
vi中命令.重复命令很实用
求素数也可用求公约数算法来求，辗转相除法，如果1——本身之间有一个约数就不是
vim 命令：w向下移动一个单词b向下移动一个单词
$移动到行尾0移动到行首
dw删除光标后的单词，可先使用b将光标移到单词首再使用dw命令
也可直接使用db命令删除光标前的内容
小端：高地址存放高位，底地址存放低位，Inter小端机
数组作为实参传递的时候，函数形参的形式：
int a[4];
add (a);
fun(int *a);
fun(int a[4])
fun(int a[])
二维数组：
int a[4][3]
fun(int (*)[3])
fun(int a[][3])
fun(int a[4][3])
C语言中数组作为函数实参时，编译器总是将其解析为指向数组首元素地址的指针(地址调用)
每一个程序都有4GB的空间，代码段(.text)，只读代码段（only read data）代码段(.data)，堆栈
4GB的空间是虚拟内存，是操作系统映射出来的
堆区：malloc
栈区：函数里面定义的变量
data：全局变量
rodata：常量，字符串
text:代码


volatile:c语言关键字
作用：确保本条指令不会因编译器的优化而省略，且要求每次直接读值.
eg:
XBYTE[2]=0x55;
XBYTE[2]=0x56;
XBYTE[2]=0x57;
XBYTE[2]=0x58;
以上是单片机的一段程序，我们本希望能每一条都执行，但编译器只会认为最后
一条才是最终结果，前面三条将不执行，这种会造成很严重的后果，所以我们需要
在XBYTE前加volatile,说明该变量每次都要访问和取值
一个参数既可以是 const 还可以是 volatile 吗？解释为什么。 
一个定义为volatile的变量是说这变量可能会被意想不到地改变，这样，编译器就不会去假
设这个变量的值了。精确地说就是，优化器在用到这个变量时必须每次都小心地重新读取这
个变量的值，而不是使用保存在寄存器里的备份
const修饰的变量在程序里面是不能改变的，但是可以被程序外的东西修改，就象上面说的外
部端口的值，如果仅仅使用const，有可能complier会优化掉这些变量，加上volatile就万无一失了。
char str[] = "Hello"
sizeof(str) = 6;
strlen(str) = 5;
sizeof加'\0'
char *str = "Hello"
sizeof(str) = 5;
strlen(str) = 5;
char *Get_Str(void)
{
        char *p = "Hello World";
        
        return p;
}

int main()
{
        char  *str = NULL;
        
        p = Get_Str();
        puts(str);
        
       return 0;
}
以上代码能输出Hello World
而下面这段代码不行呢？
#include<stdio.h>

char *Get_Str(void)
{
        char p[] = "Hello World";
        
        return p;
}

int main()
{
        char  *str = NULL;
        
        str = Get_Str();
        puts(str);
        
       return 0;
}
因为你第一种写法，返回的是常量字符串的地址（它不会因为Get_Str函数调用结束就释放）
而第二种写法，char p[] = "Hello World";是在栈上开辟的字符数组，Get_Str函数调用结束就释放了
常量储存在程序的只读数据段上，不可修改，但也不消失
****字符串是常量，而字符数组是变量，局部变量分配在栈中，函数调用完毕即消失
****字符串是常量，而字符数组是变量，局部变量分配在栈中，函数调用完毕即消失
****字符串是常量，而字符数组是变量，局部变量分配在栈中，函数调用完毕即消失
还有char p[]="Hello World"
sizeof(p) = 12;
自动加'\0';
char p[]={'H','e','l','l','o'};
sizeof(p) = 5;
上面那个是字符串，后面自动补'\0';后面一个是字符数组，不用填'\0'，
字符串是常量，而字符数组是变量

在函数里面用malloc分配的空间需要程序员自己释放，函数结束也不会结束
由malloc分配的空间释放后并不为空（NULL）保持原值
函数里面访问同名全局变量在使用时加::printf("%d %d",a,::b);
只要有无符号参与运算的表达式，最后统统装换成无符号数，负数转变成很大的正数
*******不能返回局部变量地址。
*******不能返回局部变量地址。
内存溢出，malloc 申请的空间使用结束之后没有释放
kill -9 PID强行结束
不同类型的两个指针运算是没有意义的
double *p;
int *q;
p - q 没有意义
***p + n 向前移动n个数据
指针支持关系运算< > <=...
int q;
int p;
q - p 表示相隔元素个数，不是地址值
int a[10];
int *q = a 等价于q = &a[0];
q[i],a[i]具有相同的作用
但是他们有本质上的区别q是指针变量a是地址常量
vim 撤消上次撤消的内容：ctrl + r或命令行下输入：undo
vim 清空文件，光标移动到首行dG
将DOS/MAC下的文档转换到UNIX下：
因为Windows下的换行是由\r\n组成而UNIX下是由\n组成所以移植时需要用dos2unix filename 命令
gcc 的编译过程：
1、将源文件预处理，将头文件包含，宏定义替换，取出注释，添加行号，处理以#
号开头的预编译GCC -E hello.c -o hello.i
2、编译和优化，编译过程将用户可识别的语言翻译成一组计算机可识别的操作码，通常为汇编语言#GCC -S hello.c -o hello.s
3、汇编：将汇编代码翻译成计算机能识别的二进制机器码，目标文件(汇编器 as)#GCC -c hello.s -o hello.o
4、链接：链接器ld将各个目标文件组装在一起，解决符号依赖，库依赖关系，并生成可执行文件(链接器ld)#GCC hello.o -o hello

建立静态库：静态库名:静态库名lib库名.a 扩展名.a
命令：ar -rcs libname.a hello.o
使用时：gcc -o hello hello.c libname.a
也可用gcc -o hello hello.c -L./ (当前文件夹)-lname

liunx的默认库文件文件夹/usr/lib/gcc/i686-Liunx-gun/4.6.3/下，只要将用户的库文件放到里面，连接直接用-lname选项
LIunx头文件默认文件夹：/usr/local/include ,/usr/include....
建立动态库:
程序加载是才运行的库
1、生成动态库：gcc -shared -Wl, -soname, libname.so -o libname.so.1 hello.c

GDB常用命令：
list print break next step run info display set args continue file
设置断点：break 行号 函数名 
查看断点信息：info break
删除断点：delete breakpoint 断点编号
禁止断点：disable b 断点编号
允许断点：enable b 断点编号
清除某行全部断点：clear 行号
 查看变量类型：whatis 变量名
ptype 变量名 同上
单步调试：
next:下一步
step 进入函数
finish跳出函数
run 断点编号 在指定断点处停止
continue 运行到下一个断点停止如无断点运行到末尾
display 变量名查看变量名的值，但只能查看当前作用域的值
display所显示的变量名一直存在于调试过程而print直显示一次
info break 查看断点信息
info thread 查看进程信息
help 命令 查看帮助信息
如果在调试时找不到源文件,可用director命令来设置源文件目录

gdb与多线程

在多线程编程时，当我们需要调试时，有时需要控制某些线程停在断点，有些线程继续执行。有时需要控制线程的运行顺序。有时需要中断某个线程，切换到其他线程。这些都可以通过gdb实现。
先来看一下gdb调试多线程常用命令：

info threads：显示可以调试的所有线程。gdb会为每个线程分配一个ID（和tid不同），编号一般从1开始。后面的ID是指这个ID。

thread ID:切换当前调试的线程为指定ID的线程。

break FileName.cpp:LinuNum thread all:所有线程都在文件FileName.cpp的第LineNum行有断点。

thread apply ID1 ID2 IDN command:多个线程执行gdb命令command。

thread apply all command：所有线程都执行command命令。

set scheduler-locking off|on|step：在调式某一个线程时，其他线程是否执行。off，不锁定任何线程，默认值。on，锁定其他线程，只有当前线程执行。step，在step（单步）时，只有被调试线程运行。

set non-stop on/off:当调式一个线程时，其他线程是否运行。

set pagination on/off:在使用backtrace时，在分页时是否停止。

set target-async on/ff:同步和异步。同步，gdb在输出提示符之前等待程序报告一些线程已经终止的信息。而异步的则是直接返回

如果只是想调试当前线程，让其他线程停止，scheduler-locking
/**************************************/
建立链表时请注意如果要删除尾节点
建立栈时rear-next 应指向rear的前一个元素，而不是head->next指向后一个元素
要不然不能正常删除
无名管道(pipe) 命名管道(fifo) 信号(signal) 共享内存(share_memory) 消息队列(message)
信号量(semaphore) 
有符号到无符号的转变 负数取反加一，符号位不变
计算机中负数是以补码的形式存储
例如，-1，在计算机中以11111111储存
unsigned char a = 256; a = 0, 只取低8位切强制隐式转换成左边的类型 
char a = 255, a = -1;

二叉树编程的基本思想:递归
层次遍历的特点，利用队列实现，将根节点入队，左孩子，右孩子依次入队，再出队
队列深度也可采用递归的思想来实现
桶排序思想:
②将20个范围为0-999的整数进行排序
如果按照①中的思路，则需要创建999个桶，然后进行一趟桶排序即可。
但是还有另外一种方式，只创建10个桶，但是要进行3趟桶排序。
10个桶对应0-9 一共10个不同的数字，说白了就是一个长度为10的整型数组。3趟桶排序是因为：0-999范围内的数由3个位组成：个位、十位、百位
第一趟对个位数进行桶排序，根据个位数的值，将该数放入对应的桶中，比如425，个位数为5，则将425放到a[5]中---（这是将元素本身放到桶中，不是计数，这种方式待排序的元素个数不能超过桶的个数！！！）
第二趟对十位数进行桶排序，根据十位数.....
第三趟对百位数进行桶排序，根据百位数.....
具体的实现可以这样：
在第一趟桶排序时，将待排的20个数依次放到桶中。然后，再把这20个数拷贝回原数组，然后再根据 十位 数排序:根据十位数的大小 将这20个数 按顺序放到桶中，然后再把十位数有序的桶中的数据复制回原数组......百位数....
最终，原数组中的数据就是 已经排好序的数据了。
（注意：可能一个桶里面存储了多个 数，比如: 425, 685 在第一趟桶排序时会被放入到同一个桶中）(所以一维数组不可能完成)








