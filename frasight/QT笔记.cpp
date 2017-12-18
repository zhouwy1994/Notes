QT就是一堆封装的类，调用不同的类创建不同的对象
QT主函数main()
int main(int argc, char** argv)
{
    QApplication a(argc, argv);
	.
	.
	.
    return a.exec();
}

QApplication 是一个类
a 是QApplication的创建的一个对象而且调用构造函数构造a对象
argc,argv是构造函数的参数
...是中间需要执行的动作
a.exec a对象调用QApplication类的exec成员函数exec的功能是阻塞程序，直到关闭窗口返回0
exec:时间循环
信号 嘈(QT的信号和UNIX的信号不是同一概念，QT信号)
按钮发送信号，曹函数处理
Designer界面设计
可以设置各自软件界面
定义按钮，单击右键转到槽，在个字编辑每个按键动作函数

QLabel a = QLabel("hello");
a.show();显示标签
a.setGeometry();默认设置标签大小
a.resize(sizeHint())系统推荐尺寸
QObject::connect(scrollBar, SIGNAL(valueChanged(int)),
 label,  SLOT(setNum(int)));
QT窗口的三种继承
QObject类是所有QT对象的基类
QMainwindows
QDialog
QWidege
在QT命令行编译qt程序步骤：
1、建立一个文件夹，在当前文件夹下面建立.cpp文件
2、使用命令qmake -project 建立工程文件.pro
并在.pro文件中加上QT += widgets(QT5)
3、使用命令qmake project.pro
5、来源QT使用mingw32-make.exe Microsoft VS 的使用命令nmake;
6、在release 或则debug文件夹下运行.exe 文件
注意：以上所有前提在系统环境变量已经存在这些命令
QT里面的每个小构件都不一个类，而这个类，这个类可以实例化对象
而每一个对象第一可以执行相应的成员方法，每一个类都有一个基类
前置声明，可以在要用文件中class 类名 来声明一个类的存在，为不用
加头文件
对于所有定义了信号和曹的类，在类的定义开始处的Q_OBJECT宏是必须的。
signal是一个QT宏，C++处理器会把他代替成相应的代码
QObject::connect(scrollBar, SIGNAL(valueChanged(int)),
 label,  SLOT(setNum(int)));
 发送信号时的参数必须一致，就像以上这个，都是int型 有一个例外，参数个数不一样
 但是前面几个类型相同1，匹配完成多出来的会被忽略
 QT中庸emit宏发送信号
 并在类里面使用signals:来声明发送信号的函数






















