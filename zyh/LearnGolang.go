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