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
私钥签名----->公钥验证
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

23.windows安装Gmssl(也是折腾好久)
1.clone Gmssl master代码(我编译的是GmSSL-gmbrowser-v0.1)
2.安装nasm(https://www.nasm.us/),这步关键，一定要现在对，64位的就只能下载win64版本,32位的只能下载win32版本，win32也能安装在64位的机器上,然后编译会有莫名奇妙的错误
3.将NASM的nasm.exe所在目录添加至环境变量
4.启动vs命令行(注意X86和x64)，运行命令perl Configure VC-WIN32 no-asm(32位平台), perl Configure VC-WIN64A no-asm(64位)
5.注意上面步骤是编译动态库的，如果只想要静态库，加上no-shared选项,no-asm也要加上，防止出现因为汇编的一些错误
6.nmake,编译过程中会出现错误，我遇到的是中文注释,把对应包含中文注释的地方删除,就ok了
7.如果需要安装nmake install

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









