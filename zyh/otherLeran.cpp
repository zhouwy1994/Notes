1.WMWare虚拟机直接打包，或克隆后(Mac地址一致),会导致其中一台上不了网，是因为路由器是以Mac地址来分辨计算机的，
所以Mac相同的计算机只能获取一次IP地址，所以只能有一台计算机能够正常使用网络，解决方法就是修改其中一台的Mac地址

2.分布式程序之间，只要是设计到时间的业务，基本上都要保证集群的时间是一致的，这时候就需要采用ntp服务其来保证时间的一致性

3.linux(包括windows)的时钟运行原理，不论是什么系统，都会有一个bios时钟，需要一致供电，当linux系统启动后，会从bios去获取时间，
所以我们看见系统开机之后时间还是正确的，linux下可以通过clock(或hwclock)去查看和设置bios时间，当系统关机时也会将当前时间写入bios

4.linux下使用date命令来查看系统时间，还有时区也很重要，一般我们采用的时cst(china standard time +08:00)时区

5.Excel普通的操作其实没什么，它的公式还挺方便,使用公式时要注意两个规则
(1)公式前一定有一个=号
(2)写入公式的单元格格式一定要选择"常规"
一个单元格选择好公式，其他的+号下拉就行

6.Mysql其实也是一样的原理，只要记住一堆函数就行

7.网络排查步骤：
(1)ifconfig/ipconfig查看本机ip，如果没有ip，配置静态ip或dhcp获取ip
(2)获取ip后先ping lo（回环）或本机ip
(3)ping网关（网管是连接其他网络的第一道必经之地）
(4)ping外网(baidu.com)
路由跟踪（查看路由经过的ip地址）
tracert(windows) tracerount(linux)查看网络经过路径
ping得通，查看端口是否通
telnet $ip $port(windows)
nc -v ip port

8.又找到一个好用google chrome的翻墙插件(skyZIP Proxy),不用登陆，直接使用

9.一款轻巧的web服务器程序:boa(http://www.boa.org/)，使用比较方便

10.c++写http服务器时,回复客户端请求时需要包含以下字段，浏览器才能正确解析
HTTP/1.1 200 OK
Content-Type: text/plain
Connection: keep-alive
Content-Length:12
Access-Control-Allow-Origin:*  // 此处在跨域访问时需存在

11.git clone命令拉取代码时如果代码提交历史过大，拉取下来的代码将很大，速度也比较慢，这是可以指定clone指定分支并可以限定提交历史深度
git clone git_仓库_url 获取全部branch内容，整体下载时间较长 & 所占磁盘空间较大
git clone -b git_分支名称 git_仓库_url 和上述 1. 结果一致
git clone -b git_分支名称 --single--branch git_仓库_url 获取指定分支的代码
git clone --depth 10 git_仓库_url 只会获取最近 xx（10条提交记录的）代码，默认是master分支， 如果想要指定分支，可以结合 -b --single--branch 使用



12.base64加解密是一种简单通用的数据加密方式（用A-Za-z+/共64个可打印符号来表示所以数据,所以叫base64编码）,编码方式
第一步，将待转换的字符串每三个字节分为一组，每个字节占8bit，那么共有24个二进制位。
第二步，将上面的24个二进制位每6个一组，共分为4组。（所以三个字节的数据加密后为4个字节数据，加密后的文件会增加三分之一）
第三步，在每组前面添加两个0，每组由6个变为8个二进制位，总共32个二进制位，即四个字节。
那为什么有的base编码后面会有=或==,出现这种情况是应为原文字节不能整除3,后面就会剩余一个或两个字节，此时的加密方式
剩余两个字节：两个字节共16个二进制位，依旧按照规则进行分组。此时总共16个二进制位，每6个一组，则第三组缺少2位，用0补齐，得到三个Base64编码，第四组完全没有数据则用“=”补上。因此，上图中“BC”转换之后为“QKM=”；
剩余一个字节：一个字节共8个二进制位，依旧按照规则进行分组。此时共8个二进制位，每6个一组，则第二组缺少4位，用0补齐，得到两个Base64编码，而后面两组没有对应数据，都用“=”补上。因此，上图中“A”转换之后为“QQ==”；

13.密钥、加密、签名、证书、CA(证书认证机构)
密钥对，公钥是公开的，谁都可以拥有，私钥自己保存
公钥加密----->私钥解密
加密过程,A->B通信，A将公钥给B，B将公钥给A，通信时互相用对方公钥加密，对方收到后用他自己的私钥解密
私钥签名----->公钥验证
验签过程，A->B通信，A将公钥给B，B将公钥给A，通信时用自身私钥签名，对方收到后用发送方的公钥验签
其实不是有加密方式有对称和非对称加密，签名也有对称和非对称只分，普通的签名都是对称的sm2等，md5,sha256等散列函数就可以看成是一种对称签名的方式
怎么保证公钥是张三的，通过第三方机构CA验证，拥有私钥者(张三)向CA申请数字证书(CA一般是权威的第三方机构，收费(就像是公安局))，其实数字证书就是
CA利用自身的根证书(密钥对)中的私钥对张三的公钥签名形成的，所以张三向外公布的公钥就是他从CA获取的数字证书,客户端想要证明数字证书是张三的，就用
CA本身的公钥验签张三的数字证书，只要CA是权威的，那么主流浏览器（客户端）都会有CA的公钥，为什么12306会要求浏览器安装根证书，其实就是12306自身有一个
CA，只是他不是专门负责认证的第三方CA，所以浏览器没有他的公钥，所以需要安装，安装后就没有其他网站能够冒充12306了
CA可以自己搭建，其实就是一个密钥对(根证书)，只是自己搭建的CA不会得到主流浏览器的认可(目前全球拥有的权威CA只有50几家，大部分要收费)，但在分布式节点验证时可能有用

14.TLV(Tag Length Value)协议传输格式
|Tag|Length|Value
|0x80|12|Hello World
优点,可以自由的添加消息字段易于扩展，用得最多的协议标准就是facebook的thrift和google protocol buffer
google protocol buffer学习:
(1)环境搭建,google protocol buffer本身是一个工具(编译器),需要编写IDL(Interface description language的缩写，指接口描述语言)文件，
在利用编译器protoc生成指定平台的代码(.cc .h)
(2)编写对象描述文件(.proto)
(3)protoc *.proto --cpp_out OUTDIR

15.update-alternatives 在ubuntu系统中，update-alternatives是专门维护系统命令链接符的工具，其可以对某个工具的多个软件版本进行管理，
通过它可以很方便的设置系统默认使用哪个命令的哪个软件版本.比如我们系统里面有多个版本的gcc,要学习一下

16.给vmware虚拟机添加两张网卡,一张桥接(接外网)，一张NAT(内网)用于本机ssh登陆,添加网络适配器,修改网络配置文件(添加HWADDR,注释UUID)
 
17. zabbix:一款服务器性能指标监控工具

18.Mycat,阿里开发的一款mysql的中间件,数据库读写分离,分表分库

19.安裝vs番茄助手，步驟，在網上下載一個破解版的程序,安裝前（1）關閉vs2017,（2）點擊va安裝程序安裝,（3）運行破解工具,（4）替換VA_X.dll
在C:\Users\Administrator\AppData\Local\Microsoft\VisualStudio\15.0_88834d53\Extensions\ozp2y0jl.5i4下（Administrator為用戶名,ozp2y0jl.5i4隨機名）

20.七牛云存，对象存储，App图片存储

21.一行全选技巧,鼠标点击三次

22.http服务器压力测试工具:siege，可以顺序或随机发送urls.txt 内的url，使用方法简单https://www.cnblogs.com/lrxing/p/3782530.html

23.
a.windows安装Gmssl(也是折腾好久，断断续续几个月)
1.clone Gmssl master代码(我编译的是GmSSL-gmbrowser-v0.1)
2.安装nasm(https://www.nasm.us/),这步关键，一定要现在对，64位的就只能下载win64版本,32位的只能下载win32版本，win32也能安装在64位的机器上,然后编译会有莫名奇妙的错误
3.将NASM的nasm.exe所在目录添加至环境变量
4.启动vs命令行(注意X86和x64)，运行命令perl Configure VC-WIN32 no-asm(32位平台), perl Configure VC-WIN64A no-asm(64位)
5.注意上面步骤是编译动态库的，如果只想要静态库，加上no-shared选项,no-asm也要加上，防止出现因为汇编的一些错误
6.nmake,编译过程中会出现错误，我遇到的是中文注释,把对应包含中文注释的地方删除,就ok了
7.如果需要安装nmake install
b.mingw64下安装gmssl(整整搞了两天,尝试了各种办法,msys2,lib连接等，泪奔,其实就是一个小问题，总是不愿意去尝试找原因，而是直接认为是环境的原因)
1.clone Gmssl master代码(我编译的是GmSSL-gmbrowser-v0.1)
2.perl Configure mingw64 no-asm no-shared no-dso
3.由于cmd不支持很长的参数输入，修改Makefile，DEPS+=****后面的***删除只留下DEPS+=,不要DEPS+=""会有问题
4.mingw32-make -j8 (以为一键完成，可是卡了两天，就是报的一种错误)
In file included from C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32/include/windef.h:8,
                 from C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32/include/windows.h:69,
                 from C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32/include/winsock2.h:23,
                 from crypto/sof/../../e_os.h:190,
                 from crypto/sof/sof_lib.c:57:
C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32/include/minwindef.h:24:29: error: conflicting types for 'ULONG'
   typedef unsigned __LONG32 ULONG;
                             ^~~~~
In file included from include/openssl/gmsaf.h:57,
                 from crypto/sof/sof_lib.c:54:
include/openssl/sgd.h:361:18: note: previous declaration of 'ULONG' was here
 typedef UINT32   ULONG;
一眼就能看出来是类型冲突了，但是刚开始又不想去深究，以为是环境导致的(本来也是环境导致的),就尝试换了各种环境，其中发现msys2其实挺好用的(ps:msys-bat启动 --full-path)，是一个
windows下的arch架构的Linux环境，支持pcaman包管理工具，一键安装gcc make等，而且也在msys编译成功了，但是go支持mingw gcc,所以也白搞，后面一咬牙，还是用mingw编译，去找原因。
发现原因其实就是:crypto下面有很多.c文件包含了../../e_os.h,e_os_.h包含了windef.h,而windef.h里面用宏定义了ULONG等一堆基础数据类型，但是gmssl里面也自己定义了自己的一套基础
数据类型(比如像gmsaf.h等),但是gmsaf.h里面使用了ifndef _WINDEF_H限定的，按照这样子说，应该是没什么问题的，问题就出在gmsaf.h出现在了e_os.h前面，所以ifndef _WINDEF_H失效了。
只要把所有产生错误的c文件里gmsaf.h等放在e_os.h下面，ifndef _WINDEF_H就生效了，问题就解决了
总结:有时候遇到问题，不要认为解决这个问题很难，心理上觉得自己解决不了，其实并不是所有问题都很难，只是自己没有胆量去尝试
由于mingw在编译时链接到了-lws2_32 -lgdi32 -lcrypt32(别以为这是windows的库，其实还是mingw的.a，mingw还是很强的，实现了一遍windows的基础库),
所有在编译go程序的时候LD_FLAGS还是要加上上述参数


c.Alpine上编译Gmssl(弄了一晚加一天),之前已经在centos上编译出了对应的.so文件，但是生产环境上是用docker+alpine环境运行，由于现在通用的linux发行版的c库都是glibc，
而alpine得c库是musl-libc,在glibc上编译得程序是不能直接在alpine上运行的，然后就在alpine上直接编译，因为想要在特定系统上能运行的最好办法就是在要运行的机器上源码
编译。但是并不是一帆风顺的：
/usr/lib/gcc/x86_64-alpine-linux-musl/8.2.0/../../../../x86_64-alpine-linux-musl/bin/ld: ./libcrypto.so: undefined reference to `getcontext'
/usr/lib/gcc/x86_64-alpine-linux-musl/8.2.0/../../../../x86_64-alpine-linux-musl/bin/ld: ./libcrypto.so: undefined reference to `setcontext'
/usr/lib/gcc/x86_64-alpine-linux-musl/8.2.0/../../../../x86_64-alpine-linux-musl/bin/ld: ./libcrypto.so: undefined reference to `makecontext''

因为getcontext这些函数是已经过时了的函数，musl-libc已经不支持这几个函数了，然后就各种换库，都失败告终
最后在openssl的issues中(**这也是解决问题的一种办法**)搜索关键词(alpine)就找到了原因
 crypto/async/arch/async_posix.h 修改if _POSIX_VERSION >= 200112L 为 # if _POSIX_VERSION >= 200112L \
     && (_POSIX_VERSION < 200809L || defined(__GLIBC__))


24.Windows shell工具总是被吐槽的，cmd,powershell,后续有gitshell依靠git自身携带的bin，带入一些linux下常用的命令,但是今天发现一款比gitshell还要好用的shell
cmder(https://cmder.net/)

25.elk一个日志规范化的日志系统，方便日志查找和跟踪，结合ElasticSearch、kibana一起使用,kafka作为日志通道

26.一款linux下进程监控工具supervisor，supervisor是一个Linux上用来管理程序后台运行的工具，支持程序的自启动，挂掉重启，日志等功能。可配置程序随系统启动，
并支持挂掉重启，增强程序稳定性。

27.网络图，思维导图绘制软件(亿图)，可以下载破解版，一个好的框架描述抵不过一张清晰的描述图

28.chocolatey Windows下类似与ubuntu下的apt-get的包管理工具

29.修改cmd powershell中文乱码,chcp 65001
65001   UTF-8代码页
950 繁体中文
936 简体中文默认的GBK
437 MS-DOS 美国英语


30.windows和linux文件mode的不同，会导致git diff出现(old mode 100755 new mode 100644)这种，我们只关心文件内容，所以就屏蔽filemode,使用下面命令
git config --add core.filemode false

31.一款查看dll导出函数的可视化工具，"DLL函数查看器"

32.1、通过本次的学习了解，当前技术可以给目前工作带来什么实质性的帮助？结合你的实际工作，谈谈你的想法。

a)由于之前没有接触过大数据方面的技术，所以第一次听说ClickHouse、ES等工具，通过这次学习，对ClickHouse有了一定的了解，ClickHouse是一个用于联机分析的列式数据库管理系统，
和行式数据库(Mysql等)不同，他的数据是按列存储的，这样对于后期大量数据的检索有较好的性能优势，更方便项目后期的各类报表统计和大数据分析，但就目前我的工作而言，还暂时
用不了此类工具，但不排除项目后期会使用到，所以现在的学习可以为以后的使用做一个铺垫。

2、你觉得它的核心价值在哪里，未来可能用于哪些方面？
a)ClickHouse可以作为大型数据仓库来使用，方便后期对大量数据进行分类、统计、分析和计算，可以在报表统计、大数据分析方面得到应用。



33.查看exe是32bit还是64bit，用notepad++打开，以16进制显示，在开头几行能找到PE..
如果是PE..L证明exe是32bit程序，如果是PE..d则是64bit程序


34.gcc8.2安装笔记(其他版本也适用)
1.下载安装包:镜像地址(http://www.gnu.org/prep/ftp.html),该地址是gun官方镜像地址，里面有各个国家的具体镜像地址，选择China镜像源(https://mirrors.sjtug.sjtu.edu.cn/gnu/gcc/gcc-8.2.0/gcc-8.2.0.tar.gz)
2.tar -xvf gcc-8.2.0.tar.gz
3.cd gcc-8.2.0
4. ./contrib/download_prerequisites(下载依赖包),由于下载依赖包时是国外地址，下起来特别慢，可以打开download_prerequisites,看需要哪些依赖包，在去国内的镜像源下载(https://mirrors.sjtug.sjtu.edu.cn/gnu)
5.如果上面是手动下载依赖包，就还要执行一遍上一步骤命令
6.mkdir build && cd build
7.如果希望编译出的gcc编译器能使用-m32参数编译出32位环境的可执行程序，就需要安装32位开发库:yum install glibc-devel.i686 libstdc++-devel.i686 (RedHat系列) apt-get install gcc-multilib g++-multilib (debian系列)
8. ../configure --prefix=/usr/local/gcc --enable-bootstrap --enable-checking=release --enable-languages=c,c++（参数说明:1.prefix:make install安装目录2.enable-languages:希望gcc能编译的语言，可以
加上go、java之类的 --disable-multilib:这个参数比较重要，如果你不希望编译其他平台的代码，就加上次参数，如果你再64位希望编译出32位的程序就不能用次参数，在32位上想编译64位也是如此，
最好要指定一个prefix,如果不指定，默认安装到/usr/local/bin下，会和原有的gcc冲突，导致一些不必要的麻烦）
9.make && make install

35.vscode搭建golang开发环境，起始我比较喜欢vscode这款IDE,界面简洁，看起来代码清爽
1.安装GO插件(这个并不是编译器,go的编译器就是go命令，只不过该插件去调用go命令而已),只是一个IDE插件,就像是QTCreator不提供编译器一样，插件的名字就叫"Go"Microsoft出品
2.安装一堆go工具(这些工具都是方便在开发go代码中的一些辅助工具，但是特别好用,有格式化检查的，有自动补全的，有代码跳转的),但是有一些要翻墙才能下，但他在github上可以下载，所有就可以手动安装
go get -u -v github.com/mdempsky/gocode
go get -u -v github.com/uudashr/gopkgs/cmd/gopkgs
go get -u -v github.com/ramya-rao-a/go-outline
go get -u -v github.com/acroca/go-symbols
go get -u -v golang.org/x/tools/cmd/guru
go get -u -v golang.org/x/tools/cmd/gorename
go get -u -v github.com/go-delve/delve/cmd/dlv
go get -u -v github.com/stamblerre/gocode
go get -u -v github.com/rogpeppe/godef
go get -u -v github.com/sqs/goreturns
go get -u -v golang.org/x/lint/golint

3.golang.org/x/一般会被墙，可以去github上先clone下来,一般对应在这个地址 https://github.com/golang
4.将3步骤中的代码拷贝到$GOPATH/src/golang.org/x/下（如果sourcegraph被墙步骤也是一样）
5.再次执行go get(只针对安装失败的)
6.go get 会获取代码并安装，如果没有安装可以cd到代码目录去go install .

36.golang的第三方库很丰富，很多，但是质量也参差不齐，怎样去识别一个三方库的可靠性，https://godoc.org/ 官方专门有一个库搜索器,可以看第三方github的STARS数量，排在前面的应该还不错

37.iostat,linux io监控工具，还比较好用,用时查询 iostat -kx 1
avg-cpu:  %user   %nice %system %iowait  %steal   %idle
           0.47    0.00    0.30    0.03    0.00   99.20

Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
sda               0.00     0.06    0.25    5.48    12.07   419.53   150.66     0.01    0.95    1.54    0.92   0.52   0.30
%user：CPU处在用户模式下的时间百分比。
%nice：CPU处在带NICE值的用户模式下的时间百分比。
%system：CPU处在系统模式下的时间百分比。
%iowait：CPU等待输入输出完成时间的百分比。
%steal：管理程序维护另一个虚拟处理器时，虚拟CPU的无意识等待时间百分比。
%idle：CPU空闲时间百分比。

如果%iowait的值过高，表示硬盘存在I/O瓶颈
如果%idle值高，表示CPU较空闲
如果%idle值高但系统响应慢时，可能是CPU等待分配内存，应加大内存容量。
如果%idle值持续低于10，表明CPU处理能力相对较低，系统中最需要解决的资源是CPU。

%util：这个值比较重要,一秒中有百分之多少的时间用于 I/O 如果%util接近100%，说明产生的I/O请求太多，I/O系统已经满负荷

38.iotop，查看具体进程占用io的情况,上面的iostat命令是查看系统级别的io使用情况，iotop查看具体进程使用io情况， iotop -o

39.windows下安装boost，以前一直都是参考网上的参数编译，后来发现编译出来的库有时候vs不能用，应为库还分release，debug，多线程,静态库，动态库之分，想要编译出指定模式的库，还得仔细看参数
参考(https://blog.csdn.net/qq_27395289/article/details/87429402)
1.首先指向.\bootstrap.bat生成编译工具bjam和b2(此步没有参数)
2.编译指定库
bjam --toolset=msvc-14.1 address-model=64 --with-system --with-date_time --with-chrono --with-regex --with-thread link=static runtime-link=static  threading=multi --build-dir=./build variant=release
--build-dir=<builddir> 编译的临时文件会放在builddir里(这样比较好管理，编译完就可以把它删除了)
--stagedir=<stagedir>存放编译后库文件的路径，默认是stage
--build-type=complete 编译所有版本，不然只会编译一小部分版本（确切地说是相当于:variant=release, threading=multi;link=shared|static;runtime-link=shared）
variant=debug|release 决定编译什么版本（对应文件中的d 调试版本 不出现表示 release 版）
link=static|shared 决定使用静态库还是动态库。（对应文件中的BOOST_LIB_PREFIX ）
threading=single|multi 决定使用单线程还是多线程库。（对应文件中的BOOST_LIB_THREAD_OPT） 
runtime-link=static|shared 决定是静态还是动态链接C/C++标准库。（对应文件中的BOOST_LIB_THREAD_OPT）
--with-<library> 只编译指定的库，如输入--with-regex就只编译regex库了。
--show-libraries 显示需要编译的库名称

不断变换variant、link、runtime-link就可以编译出不同版本的库文件了

40.vcpkg,一款windows下好用的c++第三方库管理工具，比如我要安装libcurl,zlib，cpp-json等第三方库时好用
参考文章:https://blog.csdn.net/cjmqas/article/details/79282847#1-%E4%B8%BA%E4%BB%80%E4%B9%88%E8%A6%81%E7%94%A8vcpkg


41.在windows下使用cgo，不像linux上那么方便，go官方推荐的是mingw，网上很多c/c++第三方库都是用,configure编译，windows下不能直接运行configure,
但是mingw套件中的msys可以，我安装了msys1.0.11，可以直接运行configure，还要make等工具非常好用的




42.编写linux开机启动项
要使自己的脚本或程序再/etc/init.d下面开机自动运行，操作步骤
在/etc/init.d下编写脚本（vim /etc/init.d/selfd），脚本内容如下，以下内容必须要，否则会报chkconfig不支持

#!/bin/bash
#
# Startup script for itpupdaterd
#
# chkconfig: 345 85 15
# description: Gionoco process self-starting script
# processname: itpupdaterd
su - root -c /Afc/gioneco/itpupdater &>/dev/null &

保存上面脚本
执行sudo chkconfig --add selfd
https://cloud.tencent.com/developer/article/1416251

systemctl、service的服务就是通过这种方式启动
43.linux下保存git密码，不用每次都要手动输入
打开~/.gitconfig  有的git版本可能是~/.git/config
增加以下内容即可:
[credential]
        helper = store



44.原来代理原来就是如此，xshell隧道 secureCRT端口映射,你可以借助跳板机访问任何跳板机能够访问到的网页,什么内网穿透，都是一个原理，借助跳板机

45.又找到一款翻墙工具pandaVPN

46.设置ssh公钥登陆，并不是设置好authorized_keys就行的文件的权限位是有要求的,.ssh目录权限位700,authorized_keys权限位600,有可能不是一定的，用命令生成ssh参考

47.有的很优秀的工具需要学习下:
Docker、K8s、Jenkins、Rancher、Zabbix、Grafana、Es(ElasticSearch),Clickhouse,ELK

48.在本地创建了使用的git库后，想把这个库与远程库相关联,比如在github.com上创建了一个库:https://github.com/yourname/learngit.git
本地库:git@112.124.109.39:~/dev/zyh/HaerBinBomSdk.git
步骤1：进入本地库目录，执行git remote rm origin
步骤2：git remote add origin https://github.com/yourname/learngit.git
步骤3：git pull origin master --allow-unrelated-histories
步骤4: git push -u origin master

49.哈尔滨中软闸机Linux系统文件系统只读，不能写入文件，查了下原因发现是系统启动时就把磁盘挂载成只读系统
将文件系统重新挂载成可写系统:mount -o remount,rw /
在写入成功后再恢复mount -o remount,ro /

50.之前一直看网页源代码都是F12，也看不出哪部分对应什么代码，网页代码调试快捷键 Ctrl+Shift+C,指哪就出来代码，主要是还能自动替换变量，v8引擎

51.xmind思维导图工具

52.windows查看所有进程命令tasklist,kill进程taskkill /F /IM chrome.exe,/IM：根据程序名kill，/PID：根据PID kill

53.linux安装java环境，很简单，
1.去java官网下载jdk1.8的64位的jdk-8u251-linux-x64.tar.gz压缩包
2.mkdir -p /usr/local/java && tar -xvf jdk-8u251-linux-x64.tar.gz -C /usr/local/java
3.在/etc/profile下增加环境变量
export JAVA_HOME=/usr/local/java/jdk1.8.0_251
export JRE_HOME=${JAVA_HOME}/jre
export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib
export PATH=${JAVA_HOME}/bin:$PATH
4.生效环境变量文件 source /etc/profile

54.es安装https://blog.csdn.net/happyzxs/article/details/89156068，先安装java环境上一步，然后下载最新版es解压，
遇到得问题在链接中都有

55.在日常操作中难免会应为操作不当导致linux不能启动，比如删除系统so等，这时候就需要用安装盘启动方式（虚拟机也可以，选择启动时连接），进入
troubleshooting模式，可以把原来系统挂载到光盘内操作

56.编写http api文档，网上一个第三方api工具比较好用，APIDOC https://apidocjs.com/

57.前端开发框架recat、Vue、Bootstrap、Angular，完全的js语言开发，可通过第三方软件打包成android于ios应用


58.一款常用的测试工具jmeter，可以用于http接口的压力测试

59.阿里云主机登陆不上+控制台远程连接不上时，还有一个功能《发生远程命令》可以救急



60.Linux的声卡驱动不会像Windows那么多，但是Alsa是Linux上应用比较广泛，linux-kernel-3以上内核默认带了alsa驱动，所以就不用
再安装，查看系统是否已经安装alsa驱动:cat /proc/asound/devices 查看是否有设备
alsa官网(https://www.alsa-project.org/)
驱动层:alsa-driver(kernel-3以上可以不用装) ftp://ftp.alsa-project.org/pub/driver/alsa-driver-1.0.9.tar.bz2
开发层(头文件，动态库):alsa-lib	ftp://ftp.alsa-project.org/pub/lib/alsa-lib-1.2.3.2.tar.bz2
应用层(aplay:播放 arecord:录音):alsa-utils ftp://ftp.alsa-project.org/pub/utils/alsa-utils-1.2.3.tar.bz2
以上安装通用步骤，以上层层依赖:./configure && make && make install
录音和播放都要先找到设备: 
aplay -l 或 arecord -l
会得到：card 0: AudioPCI [Ensoniq AudioPCI], device 0: ES1371/1 [ES1371 DAC2/ADC]
自需要记住card 和device -Hwd:$card,$device
播放：aplay -Dhw:0,1 test.wave
录音：arecord -Dhw:0,0 -d 10 -f cd -r 44100 -c 2 -t wav test.wav




61.使用adb通过网络连接android设备,打开开发者模式，USB调试,首先获取android设备ip，然后通过adb connect $androidIP,正常是连不上的
需要使用数据线连接连接安卓设备,然后运行命令
adb tcpip 5555 // 设置目标设备以监听端口5555上的TCP/IP进行连接.
拔掉数据线,运行命令
adb connect $androidIP:5555 // 连接安卓设备,注意安卓设备会弹出认证框点击确认
adb shell

62.adb常用命令
adb shell // 进入安卓设备终端环境
adb push /cpp/pic.jpg /sdcard/Video/ // 上传文件到安卓设备
adb pull /sdcard/Video/pic.jpg /cpp/ // 下载安卓设备的文件
adb reboot [bootloader|recovery]    // 重启设备,可选参数进入bootloader(刷机模式)或recovery(恢复模式)
adb install test.apk -r     adb uninstall -k <package_name>    // 安装与卸载
adb shell service list  // 后台服务列表
adb shell input text "$cotent" // 向安卓设备发送文本信息，手机按键或触摸屏坏了，特别有用
adb shell input keyevent 85 // 向安卓设备发送按键信息，手机按键或触摸屏坏了，特别有用，详细按键编号百度
adb shell am start -a android.media.action.STILL_IMAGE_CAMERA // 打开相机，按理说可以打开任何应用，具体打开方式百度
adb shell am start -a android.intent.action.CALL -d tel:10086 // 打电话
adb exec-out screencap -p > sc.png // 截屏

63.android studio中没有像QT中的转到槽的功能，只能将Button添加，然后打开xml，android:"$EventName"="EventHandle"
然后Alt+Entry，可以创建EventHandle

64.android studio需要使用第三方库时，怎么导入？首先找到build.gradle中添加库导入命令     
implementation 'com.squareup.okhttp3:okhttp:3.0.1'
刷新gradle就可以了

65.vscode，比较喜欢它的代码风格,使用它阅读c++代码，需要安装c++插件"c/c++"，安装完成后打开c++项目,ctrl+shift+p/3782530
打开命令模式输入:C/C++:Edit Configure,生成c_cpp_propreties.json，编辑includePath和defines可以方便的设置头文件目录以及一些宏定义

66.二层交换机与三层交换机的概念和区别（http://m.elecfans.com/article/594508.html）讲的很好，二层交换机根据MAC地址转发，工作在网络架构
的第二层（数据链路层），三层交换机具有路由功能，转发方式通过（ip地址路由+二层MAC转发），同一网络上的计算机如果超过一定数量（通常在200台左右，视通信协议而定），就很可能会因为网络上大量的广播而导致网络传输效率低下。为了避免在大型交换机上进行广播所引起的广播风暴，可将其进一步划分为多个虚拟网（VLAN）。但是这样做将导致一个问题：VLAN之间的通信必须通过路由器来实现。但是传统路由器也难以胜任VLAN之间的通信任务，因为相对于局域网的网络流量来说，传统的普通路由器的路由能力太弱。
而且千兆级路由器的价格也是非常难以接受的。如果使用三层交换机上的千兆端口或百兆端口连接不同的子网或VLAN，就在保持性能的前提下，经济地解决了子网划分之后子网之间必须依赖路由器进行通信的问题，因此三层交换机是连接子网的理想设备。


67.linux创建普通用户，没有root权限，之前一直都是修改sudoer文件，比较麻烦，现在有如下命令，可快速赋予普通用户root权限
1.添加指定用户到root组:sudo gpasswd -a zhouwy root
2.更新root用户组:newgrp root

68.docker启动容器指定ip，docker指定的ip必须是用户自定义网络段,
1.创建自定义网络:docker network create --subnet=172.18.0.0/16 k8net
2.docker network ls 查看docker所有网段
3.docker run -itd --network k8net --ip 172.18.0.2 centos /bin/bash

68.docker主机文件映射,将宿主机内的文件或目录映射到容器内 -v
docker run -itd -v /var/build:/vat/build centos /bin/bash // 将宿主机内/var/build目录映射到容器内的/var/build

68.在学习k8s的过程中，需要至少三台机器才能搭建起一个k8s集群,但是没有这么多机器或虚拟机，所以就想到用docker容器来代替虚拟机
因为每台节点都必须按照docker所以，需要在docker容器内运行docker，听起来有点...(其实业界早就有成熟的解决方案docker-in-docker)，但还是尝试了，遇见的第一个问题就是docker容器默认
存储系统类型为Overlay2，该文件系统不再支持运行docker，所以得修改docker的默认文件系统，我准备修改成vfs，vi /etc/sysconfig/docker-storage
将Overlay2修改为vfs，启动docker，第一个问题解决，第二个问题怎么都解决不了（可能是容器启动时没有加privileged参数），换了种思路
docker的运行机制是客户端-服务器机制，客户端与服务器通过unix sock通信，就在/var/run/docker.sock
只需要在docker容器内安装docker-cliet yum install docker-client
让后通过把宿主机上的docker.sock映射到容器内，就可以了
docker run -itd -v /var/run/docker.sock:/var/run/docker.sock centos:7 /sbin/init
但是上面的命令执行后在容器里面就找不到/var/run/docker.sock，以为是没映射成功，其实不然，是我们执行了/sbin/init命令，
该命令会清空/var/run下面的除系统自带的所以文件，也就是映射进来的docker.sock被清理了，解决办法就是把docker.sock映射到其他目录
我这映射成了根目录，然后进入容器执行ln -s /docker.sock /var/run/docker.sock就行了
其实在容器内运行的镜像都是运行在docker daemon的机器上的
注意要将docker 容器当作虚拟机来用就必须要运行/sbin/init

69.Dockerfile修改账户密码
RUN echo "root:admin" | chpasswd
也可在容器运行时指定密码

70.大约在0.6版，privileged被引入docker。使用该参数，container内的root拥有真正的root权限。否则，container内的root只是外部的一个普通用户权限。
如果需要将容器内的root用户赋予root权限，run --privileged=true

71.docker默认的仓库在国外，所以pull image的速度比较慢，设置国内代理方法,vim /etc/docker/daemon.json （没有改文件则创建）
添加以下内容:
{
  "registry-mirrors": ["http://ovfftd6p.mirror.aliyuncs.com"]
}

72.docker ps -a -q获取所有运行容器id,可以利用此命令来停止所有容器 docker stop $(docker ps -a -q)
docker run -itd --privileged=true -v /run/docker.sock:/docker.sock -p 3580:80 -p 3443:443 --network k8net --ip 172.18.0.160 --hostname rancher --name rancher centos:docker /sbin/init











