1.内存对其，golang默认是按照c/c++的内存对其方式，为什么要使用内存对其机制
(1)平台(移植性):不是所有的硬件平台都能够访问任意地址上的任意数据。例如：特定的硬件平台只允许在特定地址获取特定类型的数据，否则会导致异常情况
(2)性能(提高效率):若访问未对齐的内存，将会导致 CPU 进行两次内存访问，并且要花费额外的时钟周期来处理对齐及运算。而本身就对齐的内存仅需要一次访
问就可以完成读取动作，这显然高效很多，是标准的空间换时间做法
内存对其原则:
在不同平台上的编译器都有自己默认的 “对齐系数”。一般来讲，我们常用的 x86(32bit) 平台的系数为 4；x86_64(64bit) 平台系数为 8
一个结构体内的对其系数取决于最大的成员字节数，但是超过平台系数后，以平台系数作为最终的的对其系数。
type T struct {
	a byte
	b uint16 // 以最大成员字节作为对其系数unsafe.Sizeof(*new(T)) == 4
}

有一点需要注意，在32bit下访问int64位的结构体成员指针时，次结构一定要按照8字节对其，否在会报panic,eg:
type T1 struct {
	a int32
	b int64 // 32位下unsafe.Sizeof(*new(T)) == 12
}
如果此时调用:v:=T1{};atomic.AddInt64(&v.B, 1) // 会报panic
解决方案,在结构体内加一个占位符，使结构体的占位为8的倍数
type T1 struct {
	a int32
	_ int32
	b int64 // 32位下unsafe.Sizeof(*new(T)) == 12
}

当结构体中包含数组时，只要最终所占字节是当前结构体对其系数的倍数就行

2.unsafe.Alignof(v) 就是专门用来输出对齐系数的函数,一版对其系数为1、2、4、8

3.可用binary.Size()方法求得结构体在以1为对其系数下所占内存数，但是结构体成员只支持基础数据类型，不支持复合数据类型

4.context是一种在处理慢请求时开多个goroutine时，连接断开时退出众多goroutine的一种手段,通过派生的方式生成子context，父context调用cacel函数是，各子context都能收到信号

5.golang的两个常用的包管理工具vendor(第三方 将依赖都放在工程目录下),go 1.12版本的go modules,构建时拉去依赖(方便管理依赖版本)

6.UPX+压缩golang可执行程序,upx压缩golang可执行文件首先加上编译参数-ldflags,go build -ldflags '-w -s' main.go ,upx main

7.正则表达式查找子项使用Find*Submatch类函数，该函数会返回所有已经匹配的结果通过下标取

8.golang爬虫浏览器渲染框架:chromedp,可以渲染js内容，原理是调用本机的chorme浏览器

protobuf学习:
protobuf就是一种跨语言的一种数据虚拟化的工具，编译统一的.proto文件，定义message结构，再由编译器编译成对应语言，
然后再统一序列化反序列化，支持类型 bool, int,double,float,string,bytes,map,repeated
grpc底层就用的protobuf



9.不只是 set GOPROXY=https://goproxy.cn,direct,GOSUMDB也要设置成国内的地址，不然有的包校验会失败
set GOSUMDB=sum.golang.google.cn
也可以把包校验关闭,可以将 GOSUMDB 设置为 off

10.日常使用的优秀github库
(1) GORM https://github.com/jinzhu/gorm GORM是Golang目前比较热门的数据库ORM操作库，对开发者也比较友好，使用非常方便简单
(2) GIN  https://github.com/gin-gonic/gin Gin 是一个用 Golang编写的 高性能的web 框架, 由于http路由的优化，速度提高了近40倍
(3) Protobuf https://github.com/protocolbuffers/protobuf 一种语言无关、平台无关、可扩展的序列化结构数据的方法，它可用于（数据）
	通信协议、数据存储等
(4) GRPC https://google.golang.org/grpc 一个高性能、跨平台、开源和通用的 RPC 框架，面向移动和 HTTP/2 设计
(5) GO-Redis https://github.com/go-redis/redis 一款优秀的golang操作redis的工具库
(6) Beego https://github.com/astaxie/beego beego 是一个快速开发 Go 应用的 HTTP 框架，可以用来快速开发 API、Web 及后端服务等各种应用
	,是一个 RESTful 的框架,beego是一个完整的MVC框架包括路由&控制器、model 数据库ORM封装、view模板处理。
(7) echo echo web框架是go语言开发的一种高性能，可扩展，轻量级的web框架。 echo框架真的非常简单，几行代码就可以启动一个高性能的http服务端。

(8) go-chi 一款轻量、简洁、高效的http路由库，chi 是一个轻量级可组合的 router，用于构建 Go HTTP 服务
(9) httprouter https://github.com/julienschmidt/httprouter 一款轻量、简洁、高效的http路由库,gin的路由就是使用它实现的
(10) alice https://github.com/justinas/alice  Go的中间件链,只需要将中间件处理器函数加入到链中，最后调用alice.New(chainArray...).Then(rootHandler))
	即可得到一个中间件处理器，再用router进行路径绑定即可
(11) go-metrics https://github.com/rcrowley/go-metrics Go应用进行代码级的打点监控测量,接口访问统计
(12) gopsutil https://github.com/shirou/gopsutil 一款获取系统性能数据库,可获取CPU、Memory、Host、Disk、NetIo
(13) kingpin https://gopkg.in/alecthomas/kingpin.v2 一款优秀的命令行参数解析工具
(14) Tollbooth  https://github.com/didip/tollbooth 一款Go语言的 HTTP 限速中间件，可以限制某个接口每秒的访问次数
(15) hystrix-go https://github.com/afex/hystrix-go 一款Go语言的 HTTP 限速中间件，可以对某个指定接口做熔断限制
(16) go-Micro https://github.com/micro/micro 是一种go语言微服务开发框架。需要学习微服务架构的可以看一下
(17) go-simplejson https:github.com/bitly/go-simplejson 一款比较好用的json解析库,全部支持链式操作，包括数组
(18) logrus https://github.com/sirupsen/logrus 一款golang中用的比较多的日志库，具有比较高的定制化，通过Hook机制，学习博文:(https://blog.csdn.net/wslyk606/article/details/81670713)
(19) viper https://github.com/spf13/viper 一款强大的配置文件读写库，支持 JSON, TOML, YAML, HCL, INI等格式
(20) com https://github.com/Unknwon/com 一个golang的常用工具函数(Common Functions)一个小而美的工具包
(21) Swagger github.com/swaggo/swag/cmd/swag@v1.6.5 一个好的 API's，必然离不开一个好的API文档，如果要开发纯手写 API 文档，不存在的（很难持续维护），因此我们要自动生成接口文档。
11.golang Web框架选型，小型业务（echo）中型业务（gin）大型业务（beego）

12.go原生http的理解：
http 客户端:Client Request Response Header Cookie 
http 服务器:Server ServerMux Handler/HandleFunc ResponseWriter Header Request Cookie
处理器和处理器函数:
处理器：实现了Handler的ServeHTTP接口的都可以称作为处理器，ServeMux也是一个处理器
处理器函数：type HandlerFunc func(ResponseWriter, *Request)，只要符合这个函数签名的都可以叫处理器函数，
HandlerFunc类型也实现了ServeHTTP接口，所有所处理器函数也可以看作是一个处理器
ServeMux和DefaultServeMux（多路复用器）：
DefaultServeMux是ServerMux的一个实例，它实现了ServeHTTP接口，ServeMux可以看作是一个根ServeHTTP,他的ServeHTTP
主要是对请求的url进行一个解析分发，复制将url分发给不同的处理器，但是他的性能一般，市面上有很多优秀的第三方router实现
比如httprouter，go-chi等

13.http Web服务中可能需要统计访问量，访问限流，接口熔断，用户认证等，这些功能都有可以同中间件实现，中间件实现的原理
就是"处理器串联",比如需要统计接口处理时间，只需在ServeHTTP接口中实现该功能，再调用下一级的ServeHTTP，即可实现，优秀
的中间件第三方库github.com/justinas/alice,一个链式的http中间件实现

14.之前计算一段代码都时间都用的end - start,golang中一个函数解决time.Since(t Time),计算从开始到现在的时间等价于time.Now().Sub(t)。

15.做后端也要知道一些前端客户端框架，刚好在书上看见几个前端客户端框架:JQuery Angular React Vue

16.看了几个别人写的golang源码，之前一直是按照google c++标准，遇见}就换行，在golang中}太多，所有不用按照换行，按照功能块换行，
file, err := os.Open("file")
if err != nil {
	return err
}
defer file.Close() // 此处不换行

17.其实golang的单元测试功能已经够用了，它里面还有httptest包可以用作http模块测试，http接口中难免会依赖数据库，这样的单元测试就不独立了，
这时候golang的test提供依赖注入，可以替换接触数据库依赖，可以参考go Web编程的第8章，应用测试，讲得很详细


18.os.Create这个函数，文件存在并不报错，而且会清空文件内容

19.golang创建一个简单的文件服务器只需要2行代码,因为golang提供了一种FileServer类型，改类型实现了ServerHTTP接口，该接口实现了访问文件的细节
http.Handle("/", http.FileServer(http.Dir("./")))
http.ListenAndServe(":8888", nil)

20.golang导入了一个外部的包，在go mod的项目中怎么拉去这个包，鼠标放在导入的import上,Shift + Alt + Enter
21.golang使用了一个不知道的包，导入它的import，Alt + Enter

22.golang面向对象编程:机构内嵌就是继承:
type Server struct {}
type TcpServer struct{ Server } TcpServer继承了Server



23.go调用c库应该是所有语言中最方便的语言。因为golang中可以直接通过C.type调用c头文件中所有
类型和函数，有C.GoString() C.CString() C.GoBytes() C.CBytes等函数
C.GoString() // 将c中的char*转换成Go中的string类型,例：C.char *cStr = "Hello World" goStr := C.GoString(cStr)
C.CString() // 将golang中的string 转换成char*,char *需要释放,例：C.char *cStr = C.CString("hello world") free(cStr)
C.GoBytes() C.CBytes和上面一样

24.golang中导入包的几种形式
(1) import "github.com/zhouwy1994/library" // 正常导入,通过包名library.的方式引用library包中导出的方法
(2) lib import "github.com/zhouwy1994/library" // 通过库别名(alias)的方式导入,通过包名lib.的方式引用library包中导出的方法
(3) . import "github.com/zhouwy1994/library" // 直接可以在当前源文件引用library包中导出的方法而不需要用包前缀(不常用)
(4) _  import "github.com/zhouwy1994/library" // 只是初始化library包(调用library中的init方法),而不使用其中方法

25.今天终于弄清楚了go vendor模式的使用，golang的依赖管理一直依赖都比较多，但会变得越来越规范，vendor模式是一种将工程中所有第三方
依赖文件打包进vendor目录的一种依赖管理办法，这样部署项目比直接通过网络获取第三方依赖方便得多,因为不是所有得生成环境都能访问外网，也
不是所有的外网都能访问到google，所以vendor就至关重要了，vendor使用分为两种模式
(1) go 1.11之前不含go mod版本的工程使用vendor
(2) go1.11后使用go module的工程使用vendor

(1)go 1.11之前不含go mod版本的工程使用vendor必须满足以下条件:
(1.1) 工程目录必须在$GOPATH/src下
(1.2) vendor目录必须在工程目录下($GOPATH/src/$project/vendor)
满足以上两个条件工程编译时才会去链接vendor下面的依赖
vendor目录创建步骤，需要借助go tool:govendor(如果没有需要安装"github.com/kardianos/govendor")
1. cd $GOPATH/src/$project // 进入工程目录
2. govendor init // 传间vendor目录和vedor.json文件
3. govendor add +external // 将工程所依赖的第三方库添加到vendor目录中(第三方库需要提前go get获取,否者不会自动获取)
// govendor的一些其他选项 list:列出所有的依赖包 update:从$GOPATH更新依赖包到vendor目录 
// add PKG_PATH添加指定依赖进vendor(这个选项有用,可以导入非GOPATH下的第三方依赖包)
4.go build时默认链接vendor

go1.11后使用go module的工程使用vendor必须满足以下条件:
(1.1) 工程使用go module作为依赖管理方式
vendor目录创建步骤
1.cd $GOPATH/src/$project // 进入工程目录
2.go mod vendor // 创建vendor目录并添加第三方依赖库
3.go build -mod=vendor // 编译时指定-mod=vendor(如果不指定改选项不会则不会链接vendor)

26.go doc命令可以输出当前包所以导出的程序实体 go doc 后可跟包名如:go doc fmt,在当前目录可直接执行go doc

27.bufio包的func (b *Reader) ReadLine() (line []byte, isPrefix bool, err error) 之前一直都不理解返回值isPrefix是什么含义
因为Reader的默认缓冲是4096，就是说ReadLine读取到4096就会返回，如果读取的一行内容大于4096，那么这时读取第一次后，函数返回isPrefix
的值为false，表示没有读完，还需要调用ReadLine直到isPrefix为false，go官方并不推荐使用此方法,推荐使用ReadBytes('\n')来代替

28.go中不止有管道channel可以进行通信共享内存,golang中提供了很多好用的pipe,而且pipe的一个优点就是没有数据类型限制，chan一般都是有类型的
chan int, chan string等，pipe可以写入[]byte,比较常用的两个pipe，os.Pipe()和io.Pipe(),os.Pipe()不是原子性的，多个goroutine操作时随机
写入数据，io.Pipe()是原子性的，多个goroutine操作时数据保持原子性

29.chan技巧
(1) 避免在读端关闭chan
(2) 不能给已关闭的chan中再写入数据，否则会引起panic
(3) 判断chan受否被关闭，读取时 v,ok := <- chan，判断ok
(4) 关闭chan后缓存中的数据还可以读出，直到读取到最好一个元素时ok被置为false
(4) 单向通道:var orchan <-chan int(只读通道) var owchan chan<- int(只写通道),单独定义单向通道没有意义，单向通道一般都作为入参或出参,用双向通道赋值而来
(5) go中不允许关闭只读通道，语法错误,只可以关闭只写通道
(6) 还有一种很简洁的chan读取方式,使用for + range,当chan被关闭后,for循环会退出,之前不知道这条规则，还在for中加入 if v,ok + break跳出，真是太low了
(6) 不止是能通过if v,ok来判断管道是否关闭,select { case v,ok := <- ch }也可以判断


30.select中的break只可以跳出select{},如果select与for语句一起使用时,break跳不出for怎么办,在for语句上方加一标签Loop: select中break Loop就行

31.golang中的lable比c++中更强大，go中的goto、break、continue语句都可以使用lable，goto后的lable标签是必须的,你可以任务break和continue本来后面就是
要跟lable，只是默认情况下被省略了,lable在多层循环、for+select、for+switch中特别有用
(1) lable只能包含在函数内，不能在函数外
(2) 闭包内不允许使用闭包外的lable,也可以说闭包外的lable对闭包内的作用域不可见

goto语句，只要lable符合以上规定，调到哪都可以,但是goto 后面不能有变量定义
break语句,常常与for+select for+switch 这时的break不单单是跳出select或switch，而是跳出lable下方的for，这种lable有一个条件
lable必须紧挨for语句或lable与for语句直间不能有其他语句
Loop:
	for {
		select {
		case <- ch:
			fmt.Println("====")
			break Loop 
		 }
	} 
你以为这个语句会一直输入"==="，错,当执行break Loop是就已经结束for循环了,这样lable在结束多层循环有很重要的作用
continue语句，作用与break相似,只不过continue是跳转到loabe下方的for语句继续执行,多层循环中也很有用

32.golang中的并发同步工具:channel、Mutex、RWMutex、Condvariable、Atomic、Once
其中atomic不止可以对int32，uint32,int64,uint64操作外，它其实可以对任何类型进行Store和Load操作,
atomic.Value 有两个方法Store Load可以实现原子性操作

33.实际开发中会需要用到很多第三方库，依赖golang.org或google等，这时候不翻墙是不能拉去到的，而且golad会通过go list -m -json拉取
失败，这时候就需要设置go env GOPROXY为国内代理,goland具体设置方法,File->Setting->Go->Go Modules->Goproxy设置成https://goproxy.io或通过设置
环境变量GOPROXY=https://goproxy.io

34.下划线的作用，不止可以用来导入不使用的包,还可以作为变量占位符,还可以用作接口断言,用于判定某个struct是否实现了某个interface,没实现则会
编译不通过
1. import _"github/zhouwy1994/library"
2. file,_ := os.Open("file)
3. _ Interface = &Struct{}

35.内置函数len求chan长度时表示chan内有多少个已写入但未消费的对象，而不是chan的容量，cap函数才能求chan的容量

36.一个比较完整的http服务器处理过程图
																	辅助包工具(第三方工具)
																	Session管理
main文件监听端口接收请求--->路由功能--->参数过滤--->controller<-->  Model------------------>数据库
						<---视图输出<---输出过滤<--					日志管理
																	缓存管理
http请求从左侧main入口函数开始进入框架
UrL路由解析然后确定执行那个控制器(controller)
执行请求前的过滤器 （过滤器一般用来拦截请求，例如做api签名校验，session处理，安全验证等等）使用中间件实现
执行控制器 （控制器根据需要调用model，session, 日志等模块）,所有我们认为的MVC中的MOdel不只是数据库
执行请求后的过滤器
视图输出返回给用户

37.golang第三方日志记录器logrus,他的JSONFormatter里面有一个CallerPrettyfier(*runtime.Frame)，Frame里面明确有日志产生的文件名，函数
使用非常方便，首先得打开logger.ReportCaller = true,而且可以通过TimestampFormat自动自定义时间格式，可以通过FieldMap字段改变默认字段名
比如msg可以重命名为message，还可以自定义Formatter接口来实现自己的日志格式，可以实现Hook接口实现自己的钩子，比如第三方日志文件分割就是
实现了Hook接口,也可以自己实现，这就是golang接口的好处

38.logrus常用的日志回滚器github.com/lestrrat-go/file-rotatelogs，只需要设置几个选项就可以使用,
	r1, err := rotatelogs.New("test-%Y%m%d%H%M%S.log", 
		rotatelogs.WithRotationCount(7), 
		rotatelogs.WithRotationTime(3*time.Hour))
WithMaxAge：需要保留日志文件的日期，比如只需要保留3天内的文件，WithMaxAge(3*time.Hour*24)
WithRotationCount：需要保留日志文件的个数,比如只需要保留7个文件，WithRotationCount(7)
注意：WithMaxAge 和 WithRotationCount不能同时使用
WithRotationTime():多久分割一次日志，比如三小时分割一次，WithRotationTime(3*time.Hour)
为什么file-rotatelogs没有实现按照日志大小分割日志，因为这样的话每调用一次Write操作都会去判断一次文件大小，性能
损耗大，按照时间分割是不错的选择。
WithLinkName：当前日志文件的软链接，总是指向最新日志文件，只要Linux实现，Windows没实现
ForceNewFile：如果日志文件名固定（没有设置%Y等后缀），那就算触发日志分割，也不会有新文件产生，只有设置次标志，系统才会
分割出新日志文件，新日志文件名后缀为.1 .2

39.golang调用so、或dll步骤
dllHandle, err = syscall.LoadLibrary("WaveApi.dll")
syscall.FreeLibrary(dllHandle)
waveInInit, err = syscall.GetProcAddress(dllHandle, "waveInInit")
syscall.Syscall6(waveInInit, 5, uintptr(channels), uintptr(samplesPerSec),
		uintptr(bitPerSec), syscall.NewCallback(func(data *C.char, len C.int, user unsafe.Pointer) int {
			waveData := C.GoBytes(unsafe.Pointer(data), C.int(len))
			dataCb(waveData)
			return 0
}), uintptr(0), 0)
如果dll中函数需要传入回调函数，则需要使用syscall.NewCallback或syscall.NewCallbackCDel转换，且golang的回调函数
一定要有一个返回值（即使dll中的函数所需要回调函数没有返回值）

40.c#常用第三方包 https://www.nuget.org/下载地址 https://www.cnblogs.com/harrychinese/p/CSharp_3rd_lib.html
安装步骤，以RestSharp为例
打开vs-->工具--->NuGet包管理器--->程序包管理控制台--->打开命令行-->输入官网的命令
Install-Package RestSharp -Version 106.11.5-alpha.0.18

41.一个不错的golang项目学习https://eddycjy.com/posts/go/gin/2018-02-11-api-01/

42.一款不错的第三方excel处理库，处理excel不只是python得专利:https://github.com/360EntSecGroup-Skylar/excelize

43.vscode作为Golang开发IDE配置，解决代码提示慢问题
Go 扩展默认是使用大量的 Go 工具来提供各种功能的, 每个工具提供某个方面的能力, 比如代码提示是依靠 gocode 的.
不过微软在开发 VS Code 过程中, 定义一种协议, 语言服务器协议, Language Server Protocol.
这可是个好东西, 如果你需要开发编辑器或 IDE, 就不需要再为每种语言实现诸如自动完成, 代码提示等功能了, 直接利用 语言服务器协议 就行了.
gopls 就是官方的语言服务器, 当前处于 alpha 状态.
安装步骤:
(1) go get golang.org/x/tools/gopls@latest (不要用-u选项,记得要设置goproxy)
(2) 打开vscode Ctrl + Shift + P 输入"settings" 找到Open Settings(JSON),复制下面一段
"go.useLanguageServer": true,
"[go]": {
    "editor.snippetSuggestions": "none",
    "editor.formatOnSave": true,
    "editor.codeActionsOnSave": {
        "source.organizeImports": true
    }
},
"gopls": {
    "usePlaceholders": true, // add parameter placeholders when completing a function
    "completionDocumentation": true // for documentation in completion items
},
"files.eol": "\n", // formatting only supports LF line endings
保存，然后就可用了
44.设置gopls后，就会存在gomod项目的代码跳转问题，这时就需要将vscode的workspace设置到go.mod目录

45.传统Web应用MVC架构，其中的C层可划分成两层，协议层（Protocol Layout）和控制层（Controllor Layout）,
协议层可支持http,rpc（thrift、grpc）,tcp等，协议解析完成后交由Controllor Layout层处理,这样的Web层就会
支持多种协议访问

46.http、rpc、restful、redis、mongdb、kafka、rabbit、etcd、docker、etcd、k8s、racher、elk

47.如果只是像在for中进行range而不需要取值时，可以用以下语法
slice := make([]struct{}, 100) for range slice {}

47.type SelfStruct struct{
	Member int
}

func(m SlefStruct)Func() {
	m.Member = 10 // 并不能改变调用者的Member值,哪怕是以指针形式调用
}

func(m *SlefStruct) Func1() {
	m.Member = 10 // 不管以值或指针形式调用,都可改变调用者的Member值
}

48.上述47例子，只要给自定义类型定义一个方法，不管是定义的是值类型还是指针类型，都可通过值或指针的值来调用
但是如果是接口(interface就不一样了)，如下例子
type SelfInterface interface {
	Func()
}

type SelfStruct struct{
	Member int
}

type SelfStruct1 struct{
	Member int
}

func(m *SlefStruct)Func() {
	m.Member = 10 // 并不能改变调用者的Member值,哪怕是以指针形式调用
}

func(m SlefStruct1)Func() {
	m.Member = 10 // 并不能改变调用者的Member值,哪怕是以指针形式调用
}


var s SelfStruct
var s1 SelfStruct
var i SelfInterface
i = s // 这样赋值报错，因为s不能转换成&s
i = &s1 // 这样就不会报错，因为&s1可以转换成s1
i.Func()

49.Go的json有一个omitempty标签，意思是如果字段为空值，定义为false、0、零指针、nil接口值以及任何空数组、切片、映射或字符串,则该字段在json序列化时省略。

50.包的未公开表示符不能被其他包引用，这会误导以为所有的未公开表示符都不能被访问，其实可以通过以下方法引用
package pack
type duration int64
var value duration
func New() duration {
	return value
}

package pack1
v := pack.New() // 这样以用是可以的
解释：(1)标识符才用公开或未公开属性，而值没有
(2)不能定义一个未公开类型的变量，但可以通过函数返回值的形式获取它的值
50.golang内置函数func copy(dst, src []Type) int
不仅可以复制两个slice，也可以将string复制给slice，很方便,当然不是想象中用来复制[]byte，任何类型的[]int []struct都可以用此函数

51.理解goroutine的调度GMP机制
前言:目前已处于多核CPU运行时代，这就是go语言具有优势的地方,按理说每个CPU核心运行一个操作系统线程，目前的cpu都有一个最重要指标，cpu核心数
cpu核心数越多，可执行的并行任务就越多，注意这里区分并发和并行
G：Goroutine go 协程 可理解为用户态线程
M：thread 操作系统线程（内核态线程），在CPU上运行，最终的goruntine就是跑在M上,最大10000个，通过debug.SetMaxThreads设置
P:Process（逻辑处理器）最大256可通过runtime.GOMAXPROCS设置（可以理解P是一个调度器）
1.每个go进程都有两类goroutine运行队列,全局队列和每个P维护的本地队列
2.每个goroutine被创建的时候都会加入一个本地队列或全局队列,一般会加入一个P的本地队列
3.每个P必须和一个M绑定，P作为本地队列的调度器，M作为goroutine的执行器
4.P负责将本地队列的G放到M中去运行，每个G有一个执行时间片，时间到了P又将G拿出来放在队列的尾部，换上队列头部的G，有点像一个防止插队的保安，哈哈
5.每个go程序运行后P的数量就固定了，当然可以通过GOMAXPROCS设置，但最好是在程序开始的时候执行，运行过程中不建议更改
6.M的数量就不固定了，它就只有一个最大数量限制，当goroutine多的时候，他就会多，那就有疑问了，P不是和M绑定的吗，不应该是P的数量等于M的数量吗？
7.当M在执行G的过程中，如果G中遇到阻塞任务时，P发现之后就会把当前和自己绑定的M分离，重新创建一个M来执行队列中的G，我不可能一直等你啊，后面还有
这么多人排队呢，这就是为什么P的数量不等于M的数量的原因
8.当G从阻塞任务中恢复过来时，P又会把它拿回来放在本地运行队列中
9.每当有一个被创建时，操作系统底层都会有一个线程被创建，Windows是CreateThread Linux是clone
10.G任务的执行顺序是，P先从本地队列找，本地没有则从全局队列找（一次性转移(全局G个数/P个数）个，再去其它P中找（一次性转移一半）,看来P还是任劳任怨的,不会让自己太闲
11.为什么叫逻辑处理器呢，这就得知道什么叫物理处理器了，每台计算机都有一个或多个物理处理器，每个物理处理器(核)同时只能运行一个操作系统线程，别看操作系统可以创建
很多线程，其实每个处理器(核)同时只能运行一个线程，那这就得依赖操作系统底层的调度器了，调度器让每个线程都有相应的时间片，这是不是和Golang的GMP机制很像啊，这就是为什么
GMP中的P叫逻辑处理器了，他就是模拟物理处理器的调度机制
12.标准库中有一个函数，Gosched(),这个函数的功能是让出时间片给其他goroutine，它怎么实现的呢，当执行这个函数后，P就会把当前Goruntine重新放回队列尾部，执行队列头的G


52.经常会有一个场景，有一个多重循环，我们需要从最里面的循环跳到最外层循环或者，跳到指定的循环，用break只能跳出当前循环，这时候就需要用LABEL了
LABEL:
	for {
		for {
			break LABEL // or countine LABEL
		}
	}
53.之前一直使用time.Format("2006-01-02 15:04:05")来打印时间格式化字符串，但是这也只能打印到秒，"2006-01-02 15:04:05.999"可以打印到毫秒微秒，多加几个9

54.学习别人优秀的经验
## git代码合并
- `master`作为最终发布到生产环境的分支,开发主分支在`dev`,个人开发分支在`feature-xxx`
- 在`feature`分支合并到`dev`之前先运行 `golint ./...`处理警告, 然后rebase一下dev的代码。然后再合并到dev。(参考博文:https://www.jianshu.com/p/4079284dd970)
- 尽量不要在`dev`上面出现*merge*节点，出现*merge*不便于代码回退和codereview
- 出现需要紧急修复的提交，需要从`master`切一个`hotfix`分支进行代码修复。修复完成后分别合并到master和dev分支

## 代码
- service 中如果和用户相关的函数, 第一个参数都放 currentUser
- 路由的路径对于模型有关的，切记用复数，其他使用名词的地方也都用复数

## 业务目录
- `src/model`下面主要放数据库结构相关的struct，**切记不做数据库连接**,其中和包名相同的文件里面定义struct，其他struct相关的实例方法定义在method文件里面。参考 `src/model/catalog`
- `src/routes/helper` 定义了接口通用的一些帮助函数
- `src/service/helper` 文件夹下面放和版本迭代关联不大的常用方法。可以将简单的数据库*增删改查*写到这个地方

## 测试
- 除了`src/routes`下面的测试直接放到了`test/src/routes`下面，其他的测试均放到各自的包里面进行测试
- 由于后面测试要生成的数据需要比较多，所以`test/fakedata`下面写专门用来生成测试需要的数据的函数


55.golang实现热更，有realize、endless，都可采用发送信号kill -1 $pid的方式来实现热更

56.go 单元测试，一般执行go test之后只会执行当前目录下的test文件，想要执行当前目录下的所有目录中的test文件，需要运行
go test ./...
如果测试用例中有终端输出，则需使用-v参数

57.在vscode编写go代码时,只有在main函数执行F5才能开始调试，不能在其他文件开始调试，需要在launch.json修改"program": "${workspaceFolder}",

58.GORM中定义模型时，GORM帮我们定义了一个gorm.Model，增加id created_at updated_at deleted_at几个字段并且会自动更新,所有我们不用再
重复定义这几个字段了，但是会有一个问题
db.Create(model) // 这种写法是不会更新gorm.Model的几个字段
db.Create(&model) // 正确
如果不喜欢created_at字段名，可以自己定义，但是不会自动更新，需要Model实现BeforeCreate、BeforeUpdate、BeforeDelete几个接口
如果需要将两个字段共同设置为唯一键，那么只要给他们的TAG定义时去一个相同的名字就行 unique_index:common_index

59.gin中有很好用的binding，可以将请求参数与结构体绑定，支持url参数，请求Body，（Json,Xml,Yaml等）
具体的tag:(参考https://blog.csdn.net/weixin_44540711/article/details/105211991)
required 验证该值不是数据类型的默认零值。数字不为０，字符串不为 " ", slices, maps, pointers, interfaces, channels and functions 不为 nil
isdefault 验证该值为数据类型默认值
len=10 对于数字，长度将确保该值等于给定的参数。对于字符串，它会检查字符串长度是否与字符数完全相同。对于切片，数组和map，验证元素个数。
max=10 对于数字，max将确保该值小于或等于给定的参数。对于字符串，它会检查字符串长度是否最多为该字符数。对于切片，数组和map，验证元素个数。
eq=10 对于字符串和数字，eq将确保该值等于给定的参数。对于切片，数组和map，验证元素个数。
ne=10 和eq相反
oneof=red green (oneof=5 7 9) 对于字符串，整数和uint，oneof将确保该值是参数中的值之一。参数应该是由空格分隔的值列表。值可以是字符串或数字。
gt=10 对于数字，这将确保该值大于给定的参数。对于字符串，它会检查字符串长度是否大于该字符数。对于切片，数组和map，它会验证元素个数。
gt 对于time.Time确保时间值大于time.Now.UTC（）



























