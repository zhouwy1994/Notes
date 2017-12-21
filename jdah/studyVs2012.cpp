===========================================================================================
周武毅 2017年9月21日								Study On Visual Studio 2012
===========================================================================================
VS2012(Microsoft Visual Studio 2012)是微软公司的一款集成开发工具，包含了Visual C++ Visual C#，Visual Basic WEB....,类似于Microsoft
Office包含World，Excel..

VS2012的通用选项在 工具---->选项 ，里面包含VS的所有通用设置

F12跟踪代码，Ctrl + '-' 回退
Alt + G (可替代F12)进入头文件
工程属性，项目--->工程属性，可设置头文件(include)目录，库文件(lib)目录(VC++目录),附加依赖项(链接器)
工程属性顶格可设置平台(配置管理器)

格式化选中代码:Ctrl + K + F
注释选中代码:Ctrl + K + C
反注释选中代码:Ctrl + K + U

查找字符串:Ctrl + F (可选当前文档， 当前项目， 打开的项目， 整个解决方案内查找)
替换字符串:Ctrl + H (可选当前文档， 当前项目， 打开的项目， 整个解决方案内替换)

符号链接未找到，除了考虑缺少相应的库外，还应该考虑是不是平台问题，大部分库是需要64位开发平台，而VS2012默认开发平台为32位

切换断点 F9(新建，关闭断点)
删除所有断点 Ctrl + Shift + F9
逐语句调试(F11) ---- 单步进入(进入函数)
逐过程调试(F10) ---- 单步调试 (不进入函数)

调试状态运行 F5
非调试运行   Ctrl + F5
监视窗口专门监视指定变量
VAssistX是VS的好助手，熟练掌握它的快捷方式能大大提高编程效率。
一些最常用的快捷方式（也就是它最主要的一些功能）
Alt + O： 在对应的cpp和h文件切换，除后缀名之外文件名必须一致
Shift + Alt + O: 打开一个窗口，根据输入的字符来匹配源文件名，从而快速打开一个源代码文件。
Alt + M：列出当前文件的所有函数。在文件编辑窗口的上部有一个ListBox，里面包含了当前文件里的所有的函数。用这个快捷方式可以快速下拉这个窗口，
然后可以输入部分函数名称来快速定位到一个函数。
Shift + Alt +S： 快速查找一个标识符，包括全局变量，函数，类，宏等等

vs的单个源文件是不能编译运行的，所有的代码都必须基于一个项目
Solution 解决方案

VC 从 2005 版本开始，微软引入了一系列的安全加强的函数来增强 CRT（C
运行时），这里对应的是 strcpy_s。_s 意为 safe 的意思。strcpy_s 有两个版本，一个可以帮助我们自动推断缓冲区的大小，而另外一个
不能帮助我们推断，因此在编译器不能推断缓冲区大小的时候，我们需要自己指定缓冲区的大小

#pragma onec
这是一个比较常用的指令,只要在头文件的最开始加入这条指令就能够保证头文件被编译一次，避免文件被重复包含。
#pragma comment
#pragma comment( comment-type [,"commentstring"] )
该指令将一个注释记录放入一个对象文件或可执行文件中。
comment-type(注释类型):可以指定为五种预定义的标识符的其中一种。
1、compiler
2、exestr
3、lib:
这是一个非常常用的关键字,用来将一个库文件链接到目标文件中。常用的lib关键字，可以帮我们连入一个库文件。 
例如: #pragma comment(lib, "user32.lib") 该指令用来将user32.lib库文件加入到本工程中。
4、linker
5、user:
参考:http://blog.csdn.net/njuitjf/article/details/43235859

Asynx:异步
Sync:同步

VS2012 全屏显示当前窗口 Alt + Shift + Enter或者视图---->全屏显示

C++中 __try,____except( EXCEPTION_EXECUTE_HANDLER ) 结构中，except的参数是什么，求详解！
在__excep后面的()中是一个表达式，值可以是:
EXCEPTION_CONTINUE_EXECUTION (–1)  异常被忽略，控制流将在异常出现的点之后，继续恢复运行。
EXCEPTION_CONTINUE_SEARCH (0)  异常不被识别，也即当前的这个__except模块不是这个异常错误所对应的正确的异常处理模块。系统将继续到上一层的try-except域中继续查找一个恰当的__except模块。
EXCEPTION_EXECUTE_HANDLER (1)  异常已经被识别，也即当前的这个异常错误，系统已经找到了并能够确认，这个__except模块就是正确的异常处理模块。控制流将进入到__except模块中。

VS 默认开启SDL(安全开发生命周期)检测，这时一个保证程序正确使用库函数的检测，由于很多版本较旧的API使用不太安全，编译器会提示使用安全的API
如果程序出现SDL的提示，可以有两种办法解决
1.关闭SDL检测 工程--->属性---->C/C++--->常规----->SDL检查
2.工程--->属性---->C/C++--->预处理器---->预处理器定义 加上编译提示的宏定义

vs2015编辑快捷键：
1.回到上一个光标位置/前进到下一个光标位置
1)回到上一个光标位置：使用组合键“Ctrl + -”;
2)前进到下一个光标位置：“Ctrl + Shift + - ”。
2.复制/剪切/删除整行代码
1)如果你想复制一整行代码，只需将光标移至该行，再使用组合键“Ctrl+C”来完成复制操作，而无需选择整行。
2)如果你想剪切一整行代码，只需将光标移至该行，再使用组合键“Ctrl+X”来完成剪切操作，而无需选择整行。
3)如果你想删除一整行代码，只需将光标移至该行，再使用组合键“Ctrl+L”来完成剪切操作，而无需选择整行。
3.撤销/反撤销
1)撤销：使用组合键“Ctrl+Z”进行撤销操作;
2)反撤销：使用组合键“Ctrl+Y”进行反撤销操作。
4.向前/向后搜索
1)使用组合键“Ctrl+I”;
2)键入待搜索文本(将光标移至搜索词输入框位置即可开始输入);
3)键入搜索文本后，可以使用组合键“Ctrl+I”及“Ctrl+Shift+I”前后定位搜索结果，搜索结果会被高亮显示。
4)要结束搜索，可以按“ESC”键或者点击查找框右侧的关闭按钮。
[补充]选择一个单词后，按组合键“Ctrl+F”也可调出查找框口，且搜索结果也会被高亮显示。
5.框式选择
使用组合键“Shift+Alt+方向键(或鼠标)”即可完成框式选择。框式选择允许你同时对代码行和列进行选择。这对批量删除某些代码很方便的哦。
6.在光标所在行的上面或下面插入一行
1)组合键“Ctrl+Enter”：在当前行的上面插入一个空行;
2)组合键“Ctrl+Shift+Enter”：在当前行的下面插入一个空行。
7.定位到行首与行尾
1)home键：定位到当前行的行首;
2)end键：定位到当前行的行尾。
8.选中从光标起到行首(尾)间的代码
1)选中从光标起到行首间的代码：使用组合键“Shift + Home”;
2)选中从光标起到行尾间的代码：使用组合键“Shift + End”。
9.调用智能提示
1)方法1：使用组合键“Ctrl+J”;
2)方法2：使用组合键“Alt+→”。
10.调用参数信息提示
对于某些函数体较大的函数来说，想轻松地确认参数在函数内部的使用情况是件比较麻烦的事情。这时可以将光标置于参数名上，再按组合键“Ctrl+Shif+空格”，参数被使用  的地方会被高亮显示。
11.快速切换窗口
使用组合键“Ctrl+Tab”(此时可以打开IDE的导航，获得鸟瞰视图)。
12.快速隐藏或显示当前代码段
使用组合键“Ctrl+M,M”(记住：要按两次M哦)。
13.生成解决方案
使用组合键“Ctrl+Shift+B”。
14.跳转到指定的某一行
1)方法1：组合键“Ctrl+G”;
2)方法2：单击状态栏中的行号。
15.注释/取消注释
1)注释：组合键“Ctrl+K+C”;
2)取消注释：组合键“Ctrl+K+U”。
16.全屏显示/退出全屏显示
使用组合键“ SHIFT + ALT + ENTER ”。
17.定义与引用
1)转跳到定义：F12;
2)查找所有引用：使用组合键“Shift+F12”。
18.查找和替换
1)查找：使用组合键“Ctrl+F”;
2)替换：使用组合键“Ctrl+H”。
19.大小写转换
1)转小写：使用组合键“Ctrl+ U”;
2)转大写：使用组合键“CTRL + SHIFT + U”。
20.调试相关
1)调试(启动)：F5;
2)调试(重新启动)：使用组合键“Ctrl+Shift+F5”;
3)调试(开始执行不调试)：使用组合键“Ctrl+F5”;
4)调试(逐语句)：F11;
5)调试(逐过程)：F10;
6)设置断点：F9。

vs2015重置窗口。窗口---->重置窗口
如果需要设计窗口，则可通过鼠标拖动相应窗口，此时会有绿色图标提示

windows菜单选项后括号大写字母代表使用Alt + 相应字母打开选项卡（文件(F)） Alt + F
如果该选项还有子选项也存在以上情况，则再加按一次对应的字母即可打开

复制一行，不用选中，只需要讲光标移动到该行，Ctrl + C Ctrl + V Ctrl + X就可以操作一整行
复制一个单词，鼠标点击两下即可选中。CTRL + C复制

选择 调试--->窗口即可调出调试窗口

svn比较某一个文件的diff，右键单击，diff比较

替换时一般选择全字替换


SVN使用:
每次commit之前记得要先update，不然提交会覆盖别人的修改
update下来的内容可能和本地有冲突，这时存在四个文件(以language.c为例)
language.c //此文件有一个'!'号，证明这时远程的版本与本地的版本存在冲突，并且存在同一文件上
language.c.mine //这是你正准备提交的文件，已经修改，但与远端存在冲突 mine(自己)
language.c.r809 //r809代表版本号，是本地与远程的共同版本
language.c.r810 //r810代表版本号,是别人在你之前提交的版本

提交存在冲突的两种方法
1、更新文件之前直接查看对比不同之处，手动调整资源库中的文件内容和本地的文件内容进行合并；
2、直接更新，更新之后打开该文件会有这样的标识符<<<<<<< .mine，=======，>>>>>>>.r810，这代表什么意思呢？
<<<<<<< .mine
这里的内容呢，就是你本地的内容，显而易见mine就是自己的意思嘛！
<<<<<<<<<r.809
这里的内容呢，就是你修改之前的内容！
=======
而这里的内容就是资源库中的最新内容，这是svn更新之时自动合并产生的结果；
>>>>>>>.r810
（这里的.r810代表是版本号）远程库的最新版本

只要将<<<<<<< .mine ==========之间的内容删除，保留>>>>>>>>r.810(最新版)就可以解决冲突

****每次解决冲突之后，都要update之后才能commit

get一项技能，正则表达式替换:
如果有以下代码需要替换
pUpdateRowReq->m_msg->m_p_stream->m_buf 需要替换成stream_get_p_buf(pUpdateRowReq->m_msg->m_p_stream)
需要将pUpdateRowReq->m_msg->m_p_stream找到，方法如下
查找:([a-zA-Z]+->m_msg->m_p_stream)->m_buf
替换:stream_get_p_buf($1)
说明:()括号用于匹配子串，从左到右依次用$1 $2...作为替换标志，Linux下用\1 \2表示
^除了，[^r]排出r
stream_set_memeroy\(([^,]+), ([^,]+), ([^,]+), ([^,]+), [^\)]+\)

stream_add_int\(([^,]+), ([^,]+), ([^\)]+)\)
RE_MALLOC_SIZE(pStream->m_buf, pStream->m_buf_size);
注意\n的影响
return link_list_get_length(cluster_get_p_p2p_client(union_stream_manager_get_p_cluster(pUnionStreamManager))->m_p_server->m_bussiness_server->m_c_tel_sockets);
  F:\Work\source\database\server\oo_database_server.c(394):			sy_client_get_p_native_adress(pRaftClient)->m_other_ident,
sy_client_get_p_remote_adress(pClient)
数据结构隐藏:续6，struct net_point_address标记
net_msg_get_attribute\(([^,^\n]+),[ ]?([^,^\n^\)]+)\)->m_p_value
(net_msg_attribute_get_p_msg\([^,^\n^\)]+\))->m_p_stream
([a-zA-Z0-9]+->m_msg)->m_recv_cmd

******正则表达式是以文本为单位,就算是换行符也会记入其中,所以要多加谨慎,以下为栗子:

extern void stream_add_int(stream_t* pStream, int nums);
stream_add_int(pStream, *pBlockFileOffset, 0);
extern void stream_add_int(stream_t* pStream,int nums);
如果用以下正则表达式你就知道stream_add_int\(([^,]+),[ ]?([^,]+),[ ]?([^\)]+)\)
正确的用法:stream_add_int\(([^,^\n^ ]+),[ ]?([^,^\n^ ]+),[ ]?([^\^ )]+)\)

没有用正则表达式匹配不到的字符，自是看你的功力有多深厚

SVN 服务器搭建
1.Subversio和TortoiseSVN 简介
Subversio简介：SVN服务器
Tortoisesvn简介: SVN客户端
SVN是一款集中式版本控制系统，Tortoisesvn可以在本地建立一个本地库，但是不能通过网络共享Subversio的功能就是将本地库共享与网络，
设置用户权限等

搭建步骤:
1.下载Subversio和TortoiseSVN尽量保持版本一致，否则会报"期望文件系统格式在“1”到“4”之间；发现格式“6”"等错误
下载地址(Subversio1.6.x):http://subversion.tigris.org/servlets/ProjectDocumentList?folderID=11151&expandFolder=11151&folderID=91
下载地址(TortoiseSVN1.6.x):http://tortoisesvn.net/downloads.html
2.默认安装
3.  建立仓库/版本库（Repository）
运行Subversion服务器需要建立一个版本库（Repository），用来存放项目代码。
1.可以右击文件夹 TortoiseSVN-->Create Repository here
2.命令行创建 svnadmin create D:\repository (推荐:防止出现版本不匹配的错误)

4.修改库的配置文件，打开新建库，D:\repository\confg文件夹，找到svnserver.conf
 # anon-access = read
 # auth-access = write
 # password-db = passwd
将上三行去处注视并置于行首(不留空格， 否则会出错)
5。修改D:\repository\confg， 找到passwd文件
在[user]下增加用户 格式 : username = password

5.启动SVN服务 命令行下
svnserver -d -r "D:\repository" //此种方式打开启服务窗口不会关闭，可以设置随系统启动的服务，方法如下
系统启动,
此命令有一个特殊的地方,-d 与 -r的顺序不能调换，且路径要加双引号(windows server 2008)
sc create subversion_service binpath= "C:/Program Files/Subversion/bin/svnserve.exe --service -r D:\repository" displayname= "Subversion Repository" depend= Tcpip start= auto
此命令'='后都应存在一个空格等号前不可有空格
解释：subversion_service为服务的名称。所有的系统服务可以在dos下通过命令手动启动和停止。启动：net start subversion_service 停止：net stop subversion_service
binpath为安装subversion的路径，可执行文件的路径。
D:\repository"为版本库的路径。
displayname= "Subversion Repository"为注册成的系统服务显示名称，注册成功后，可以在系统服务中找到这个名称。
depend= Tcpip为依赖Tcpip协议。
start= auto为注册成的系统服务启动类型为自动。
启动成功后 在计算机--->管理---->服务中可看见Subversion Repository服务，可以自由设置

6.导入工程
右击你要导入的工程目录， TortoiseSVN--->Import,输入你的地址，一般为svn://ipaddr/repositroy
提示输入用户名和密码，就是passwd文件所创立的配置文件，如果之前TortoiseSVN有设置帐号，需要 右击TortoiseSVN->Setting-->SaveData-->clearall

7.checkout
应注意问题:svn://127.0.0.1/ 就是你的库根文件夹，不要再加其他后缀，checkout根据你之前Import的目录格式，如果你导入时用 svn://127.0.0.1/repository/Work
导出是也要用svn://127.0.0.1/repository/Work

vs2015多列多行操作
5.框式选择

使用组合键“Shift+Alt+方向键（或鼠标）”即可完成框式选择。框式选择允许你同时对代码行和列进行选择。这对批量删除某些代码很方便的哦。



























