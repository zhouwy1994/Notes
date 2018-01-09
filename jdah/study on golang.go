==============================study On Golang=====================================
			Date:2017.12.11
			Author:Zhouwy
===================================================================================
1.go语言简介
Go语言是谷歌推出的一种全新的编程语言，可以在不损失应用程序性能的情况下降低代码的复杂性。
Go语言专门针对多处理器系统应用程序的编程进行了优化，使用Go编译的程序可以媲美C或C++代码的速度，而且更加安全、支持并行进程。
2.Go语言用途
Go 语言被设计成一门应用于搭载 Web 服务器，存储集群或类似用途的巨型中央服务器的系统编程语言。
对于高性能分布式系统领域而言，Go 语言无疑比大多数其它语言有着更高的开发效率。它提供了海量并行的支持，这对于游戏服务端的开发而言是再好不过了。
3.Go语言结构(基本组成)
3.1 包声明 //package main
3.2 引入包 //import "fmt"
3.3 函数 //func main()
3.4 变量 //
3.5 语句&表达式 //fmt.Println("Hello Golang");
3.6 注释 //注释
以下为例:
package main

import "fmt"

func main() {
	/*This is a Simple Process of golang*/
	fmt.Println("Hello Golang")
}

3.7.1第一行代码 package main 定义了包名。你必须在源文件中非注释的第一行指明这个文件属于哪个包，如：package main。package main
表示一个可独立执行的程序，每个 Go 应用程序都包含一个名为 main 的包。
3.7.2下一行 import "fmt" 告诉 Go 编译器这个程序需要使用 fmt 包（的函数，或其他元素），fmt 包实现了格式化 IO（输入/输出）的函数。
3.7.3下一行 func main() 是程序开始执行的函数。main 函数是每一个可执行程序所必须包含的，一般来说都是在启动后第一个执行的函数
（如果有 init() 函数则会先执行该函数）。
3.7.4下一行 /*...*/ 是注释，在程序执行时将被忽略。单行注释是最常见的注释形式，你可以在任何地方使用以 
// 开头的单行注释。多行注释也叫块注释，均已以 /* 开头，并以 */ 结尾，且不可以嵌套使用，多行注释一般用于包的
//文档描述或注释成块的代码片段。
3.7.5下一行 fmt.Println(...) 可以将字符串输出到控制台，并在最后自动增加换行字符 \n。 
3.7.6使用 fmt.Print("hello, world\n") 可以得到相同的结果。 
Print 和 Println 这两个函数也支持使用变量，如：fmt.Println(arr)。如果没有特别指定，它们会以默认的打印格式将变量 arr 输出到控制台。
当标识符（包括常量、变量、类型、函数名、结构字段等等）以一个大写字母开头，
3.7.7如：Group1，那么使用这种形式的标识符的对象就可以被外部包
的代码所使用（客户端程序需要先导入这个包），这被称为导出（像面向对象语言中的 public）；标识符如果以小写字母开头，则对包外是不可见的，
但是他们在整个包的内部是可见并且可用的（像面向对象语言中的 protected ）。

编译golang源码
go build hello.go
直接运行
go run helo.go

4.行分隔符
golang 默认一行为一条语句，分号不是必须的，可有编译器完成，也可以在一行使用多条语句，人为使用分号分隔(不推荐)
5.标识符
与普通语言一样，数字字母下划线
6.关键字
下面列举了 Go 代码中会使用到的 25 个关键字或保留字：
break	default	func	interface	select
case	defer	go	map	struct
chan	else	goto	package	switch
const	fallthrough	if	range	type
continue	for	import	return	var
除了以上介绍的这些关键字，Go 语言还有 36 个预定义标识符：
append	bool	byte	cap	close	complex	complex64	complex128	uint16
copy	false	float32	float64	imag	int	int8	int16	uint32
int32	int64	iota	len	make	new	nil	panic	uint64
print	println	real	recover	string	true	uint	uint8	uintptr
程序一般由关键字、常量、变量、运算符、类型和函数组成。
程序中可能会使用到这些分隔符：括号 ()，中括号 [] 和大括号 {}。
程序中可能会使用到这些标点符号：.、,、;、: 和 …。

Golang数据类型
在 Go 编程语言中，数据类型用于声明函数和变量。
数据类型的出现是为了把数据分成所需内存大小不同的数据，编程的时候需要用大数据的时候才需要申请大内存，就可以充分利用内存。
Go 语言按类别有以下几种数据类型：
序号	类型和描述
1	布尔型
布尔型的值只可以是常量 true 或者 false。一个简单的例子：var b bool = true。
2	数字类型
整型 int 和浮点型 float，Go 语言支持整型和浮点型数字，并且原生支持复数，其中位的运算采用补码。
3	字符串类型:
字符串就是一串固定长度的字符连接起来的字符序列。Go的字符串是由单个字节连接起来的。Go语言的字符串的字节使用UTF-8编码标识Unicode文本。
4	派生类型:
包括：
(a) 指针类型（Pointer）
(b) 数组类型
(c) 结构化类型(struct)
(d) Channel 类型
(e) 函数类型
(f) 切片类型
(g) 接口类型（interface）
(h) Map 类型

1.数字类型
Go 也有基于架构的类型，例如：int、uint 和 uintptr。(占用内存根据架构16,32,64)
1	uint8
无符号 8 位整型 (0 到 255)
2	uint16
无符号 16 位整型 (0 到 65535)
3	uint32
无符号 32 位整型 (0 到 4294967295)
4	uint64
无符号 64 位整型 (0 到 18446744073709551615)
5	int8
有符号 8 位整型 (-128 到 127)
6	int16
有符号 16 位整型 (-32768 到 32767)
7	int32
有符号 32 位整型 (-2147483648 到 2147483647)
8	int64
有符号 64 位整型 (-9223372036854775808 到 9223372036854775807)
浮点型：
序号	类型和描述
1	float32
IEEE-754 32位浮点型数
2	float64
IEEE-754 64位浮点型数
3	complex64
32 位实数和虚数
4	complex128
64 位实数和虚数

以下列出了其他更多的数字类型：
序号	类型和描述
1	byte
类似 uint8
2	rune
类似 int32
3	uint
32 或 64 位
4	int
与 uint 一样大小
5	uintptr
无符号整型，用于存放一个指针

go 语言变量
golang声明变量的一般形式
var identifier type //identifier(标识符)

变量声明
第一种，指定变量类型，声明后若不赋值，使用默认值。
var v_name v_type
v_name = value
第二种，根据值自行判定变量类型。
var v_name = value
第三种，省略var, 注意 :=左侧的变量不应该是已经声明过的，否则会导致编译错误。
v_name := value

// 例如
var a int = 10
var b = 10
c : = 10 

如值 5 在：_, b = 5, 7 中被抛弃。
_ 实际上是一个只写变量，你不能得到它的值。这样做是因为 Go 语言中你必须使用所有被声明的变量，
但有时你并不需要使用从一个函数得到的所有返回值。

Go语言常量
常量是一个简单值的标识符，在程序运行时，不会被修改的量。
常量中的数据类型只可以是布尔型、数字型（整数型、浮点型和复数）和字符串型。
常量的定义格式：
const identifier [type] = value
由于 variant := 32 这种定义是属于变量定义，所以 const variant = 34 是非法的；
常量还可用作枚举数据类型:
const (
	Unknown = 0
    Female = 1
    Male = 2
)
iota，特殊常量，可以认为是一个可以被编译器修改的常量。
在每一个const关键字出现时，被重置为0，然后再下一个const出现之前，每出现一次iota，其所代表的数字会自动增加1。

gokang 运算符
基本和C相同
区别:没有前置++后后置++区别
关系运算符和的结果是bool型
Golang也存在指针类型，所以也存在取址运算符和解址运算符 & and *
var1 := 32;
fmt.Println(&var1); //output 0xc04204c078

golang条件语句
select是Go中的一个控制结构，类似于用于通信的switch语句。每个case必须是一个通信操作，要么是发送要么是接收。
select随机执行一个可运行的case。如果没有case可运行，它将阻塞，直到有case可运行。一个默认的子句应该总是可运行的。
每个case都必须是一个通信
所有channel表达式都会被求值
所有被发送的表达式都会被求值
如果任意某个通信可以进行，它就执行；其他被忽略。
如果有多个case都可以运行，Select会随机公平地选出一个执行。其他不会执行。 
否则：
如果有default子句，则执行该语句。
如果没有default字句，select将阻塞，直到某个通信可以运行；Go不会重新对channel或值进行求值。

golang循环语句
Go语言的For循环有3中形式，只有其中的一种使用分号。
和 C 语言的 for 一样：
for init; condition; post { }
//eg: for a := 0; a < 10; a++ {
      fmt.Printf("a 的值为: %d\n", a)
   }
   
和 C 的 while 一样：
//eg:for a < b {
      a++
      fmt.Printf("a 的值为: %d\n", a)
      }
for condition { }
和 C 的 for(;;) 一样：
for { }
//eg:for i,x:= range numbers {
      fmt.Printf("第 %d 位 x 的值 = %d\n", i,x)
   }   
}

golang函数
函数是基本的代码块，用于执行一个任务。
Go 语言最少有个 main() 函数。
你可以通过函数来划分不同功能，逻辑上每个函数执行的是指定的任务。
函数声明告诉了编译器函数的名称，返回类型，和参数。
Go 语言标准库提供了多种可动用的内置的函数。例如，len() 函数可以接受不同类型参数并返回该类型的长度。如果我们传入的是字符串则返回字符串的长度，如果传入的是数组，则返回数组中包含的元素个数。

函数定义
Go 语言函数定义格式如下：
func function_name( [parameter list] ) [return_types] {
   函数体
}
func：函数由 func 开始声明
function_name：函数名称，函数名和参数列表一起构成了函数签名。
parameter list：参数列表，参数就像一个占位符，当函数被调用时，你可以将值传递给参数，这个值被称为实际参数。参数列表指定的是参数类型、顺序、及参数个数。参数是可选的，也就是说函数也可以不包含参数。
return_types：返回类型，函数返回一列值。return_types 是该列值的数据类型。有些功能不需要返回值，这种情况下 return_types 不是必须的。
函数体：函数定义的代码集合。

//eg:
func cmp(dat1 int, dat2 int) int {
	if (dat1 > dat2) {
		return dat1;
	} else {
		return dat2;
	}
}

golang可以返回多个值，定义如下
func function_name( [parameter list] ) ([return_types list]) {
   函数体
}

func cmp(dat1 int, dat2 int) (int, int) {
	if (dat1 > dat2) {
		return dat1, 34;
	} else {
		return dat2, 34;
	}
}

函数参数传递也分为值传递和引用传递
Go 语言变量作用域
作用域为已声明标识符所表示的常量、类型、变量、函数或包在源代码中的作用范围。
Go 语言中变量可以在三个地方声明：
函数内定义的变量称为局部变量
函数外定义的变量称为全局变量
函数定义中的变量称为形式参数
接下来让我们具体了解局部变量、全局变量和形式参数。
基本上和C相同

golang 数组和C不太相同，如果声明时指定大小就是类似于C的数组，不指定大小就是另一种go类型，切片类型
声明方式有差别:
var a  = [10]int{1, 2, 3...};
var arr = [10]int;

如果不想指定数组大小又不想使用切片类型，可使用如下方式定义
var arrStatic = [...]int{1, 3, 5} //tepeOF [3]int
数组作为函数参数传递
func function(arr [10]int) //指定数组大小
func function(arr []int) //不指定数组大小
与C不同的是golang不允许将数组名当作指针传递，以下非法
func function(arr *int) //非法

golang指针
什么是指针
一个指针变量可以指向任何一个值的内存地址它指向那个值的内存地址。
类似于变量和常量，在使用指针前你需要声明指针。指针声明格式如下：
var var_name *var-type
var-type 为指针类型，var_name 为指针变量名，* 号用于指定变量是作为一个指针。以下是有效的指针声明：
var ip *int        /* 指向整型*/
var fp *float32    /* 指向浮点型 */
var pptr **int; /*双重指针*/

基本和C相同
空指针 == nil

Go 语言结构体
Go 语言中数组可以存储同一类型的数据，但在结构体中我们可以为不同项定义不同的数据类型。
结构体是由一系列具有相同类型或不同类型的数据构成的数据集合。
结构体表示一项记录，比如保存图书馆的书籍记录，每本书有以下属性：
定义结构体
结构体定义需要使用 type 和 struct 语句。struct 语句定义一个新的数据类型，结构体有中一个或多个成员。type 语句设定了结构体的名称。
结构体的格式如下：
type struct_variable_type struct {
   member definition;
   member definition;
   ...
   member definition;
}
一旦定义了结构体类型，它就能用于变量的声明，语法格式如下：
variable_name := structure_variable_type {value1, value2...valuen}

访问结构体成员
如果要访问结构体成员，需要使用点号 (.) 操作符，格式为："结构体.成员名"。
结构体类型变量使用struct关键字定义，实例如下：
与C不同的是指针类型的结构图访问成员变量也是使用 ".",而不是->

Go 语言切片(Slice)
Go 语言切片是对数组的抽象。
Go 数组的长度不可改变，在特定场景中这样的集合就不太适用，Go中提供了一种灵活，功能强悍的内置类型切片("动态数组"),与数组相比切片的长度是
不固定的，可以追加元素，在追加时可能使切片的容量增大。
定义切片
你可以声明一个未指定大小的数组来定义切片：
var identifier []type
定义切片类型不需要指定数组大小，否则会变成静态数组
或使用make()函数来创建切片:
var slice1 []type = make([]type, len)

也可以简写为
slice1 := make([]type, len)
也可以指定容量，其中capacity为可选参数。
make([]T, length, capacity)
这里 len 是数组的长度并且也是切片的初始长度。
容量表示该切片最多可容纳的元素个数
切片初始化
s :=[] int {1,2,3 } 
直接初始化切片，[]表示是切片类型，{1,2,3}初始化值依次是1,2,3.其cap=len=3
s := arr[:] 
初始化切片s,是数组arr的引用
s := arr[startIndex:endIndex] 
将arr中从下标startIndex到endIndex-1 下的元素创建为一个新的切片
s := arr[startIndex:] 
缺省endIndex时将表示一直到arr的最后一个元素
s := arr[:endIndex] 
缺省startIndex时将表示从arr的第一个元素开始
s1 := s[startIndex:endIndex] 
通过切片s初始化切片s1
s :=make([]int,len,cap) 
通过内置函数make()初始化切片s,[]int 标识为其元素类型为int的切片

len() 和 cap() 函数
切片是可索引的，并且可以由 len() 方法获取长度。
切片提供了计算容量的方法 cap() 可以测量切片最长可以达到多少。

空(nil)切片
一个切片在未初始化之前默认为 nil，长度为 0，实例如下：

切片截取
可以通过设置下限及上限来设置截取切片 [lower-bound:upper-bound]，实例如下：
 numbers := []int{0,1,2,3,4,5,6,7,8}  
  numbers[0 : 2] == [0, 1, 2]
  
append() 和 copy() 函数
如果想增加切片的容量，我们必须创建一个新的更大的切片并把原分片的内容都拷贝过来。
下面的代码描述了从拷贝切片的 copy 方法和向切片追加新元素的 append 方法。
func main() {
   var numbers []int
   printSlice(numbers)

   /* 允许追加空切片 */
   numbers = append(numbers, 0)
   printSlice(numbers)

   /* 向切片添加一个元素 */
   numbers = append(numbers, 1)
   printSlice(numbers)

   /* 同时添加多个元素 */
   numbers = append(numbers, 2,3,4)
   printSlice(numbers)

   /* 创建切片 numbers1 是之前切片的两倍容量*/
   numbers1 := make([]int, len(numbers), (cap(numbers))*2)

   /* 拷贝 numbers 的内容到 numbers1 */
   copy(numbers1,numbers)
   printSlice(numbers1)   
}
Go 语言范围(Range)
Go 语言中 range 关键字用于for循环中迭代数组(array)、切片(slice)、通道(channel)或集合(map)的元素。在数组和切片中它返回元素的索引值，在集合中返回 key-value 对的 key 值。
实例
package main
import "fmt"
func main() {
    //这是我们使用range去求一个slice的和。使用数组跟这个很类似
    nums := []int{2, 3, 4}
    sum := 0
    for _, num := range nums {
        sum += num
    }
    fmt.Println("sum:", sum)
    //在数组上使用range将传入index和值两个变量。上面那个例子我们不需要使用该元素的序号，所以我们使用空白符"_"省略了。有时侯我们确实需要知道它的索引。
    for i, num := range nums {
        if num == 3 {
            fmt.Println("index:", i)
        }
    }
    //range也可以用在map的键值对上。
    kvs := map[string]string{"a": "apple", "b": "banana"}
    for k, v := range kvs {
        fmt.Printf("%s -> %s\n", k, v)
    }
    //range也可以用来枚举Unicode字符串。第一个参数是字符的索引，第二个是字符（Unicode的值）本身。
    for i, c := range "go" {
        fmt.Println(i, c)
    }
}
以上实例运行输出结果为：
sum: 9
index: 1
a -> apple
b -> banana
0 103
1 111

Go 语言Map(集合)哈希表
Map 是一种无序的键值对的集合。Map 最重要的一点是通过 key 来快速检索数据，key 类似于索引，指向数据的值。
Map 是一种集合，所以我们可以像迭代数组和切片那样迭代它。不过，Map 是无序的，我们无法决定它的返回顺序，这是因为 Map 是使用 hash 表来实现的。
定义 Map
可以使用内建函数 make 也可以使用 map 关键字来定义 Map:
/* 声明变量，默认 map 是 nil */
var map_variable map[key_data_type]value_data_type

/* 使用 make 函数 */
map_variable := make(map[key_data_type]value_data_type)
  
delete() 函数
delete() 函数用于删除集合的元素, 参数为 map 和其对应的 key。实例如下：
delete(MapName,key);

Go 语言递归函数
递归，就是在运行的过程中调用自己。
语法格式如下：
func recursion() {
   recursion() /* 函数调用自身 */
}

func main() {
   recursion()
}
Go 语言支持递归。但我们在使用递归时，开发者需要设置退出条件，否则递归将陷入无限循环中。
递归函数对于解决数学上的问题是非常有用的，就像计算阶乘，生成斐波那契数列等。

Go 语言类型转换
类型转换用于将一种数据类型的变量转换为另外一种类型的变量。Go 语言类型转换基本格式如下：
type_name(expression)
type_name 为类型，expression 为表达式。
var a = int(12.34) //a = 12


在go install -v go-ethereum/cmd/...时出现需要golang的net/context文件
以太坊建议命令go get -u -v golang.org/x/net/context安装但是国内不能翻墙，所以此命令不实用
可以直接区golang的github下载
git clone https://github.com/golang/net.git下载，由于限制，应该将其放到goWork/src/下
后面又出现
cc1.exe: sorry, unimplemented: 64-bit mode not compiled in
这时由于go 编译依赖于gcc,windows下gcc是来自于mingw(Minimalist GNU For Windows)
mingw有32位与64位区别，由于我之前的mingw时32位所以会出现这个错误
重新安装mingw64
http://sourceforge.net/projects/mingw-w64/files/latest/download?source=files
目前主要有三种不同的线程库的定义，分别是Win32，OS/2，以及POSIX，前两种定义只适合于他们各自的平台，
而POSIX 定义的线程库是适用于所有的计算平台的。我这里选的是threads-posix。
http://zh.wikipedia.org/wiki/POSIX%E7%BA%BF%E7%A8%8B 
C++ Exceptions有DWARF、SJLJ、SEH三种处理方式。对应的我们这里选择的是seh方式。

***************
golang 的defer关键字常用
golang的defer关键字，它可以在函数返回前执行一些操作，最常用的就是打开一个资源（例如一个文件、数据库连接等）时就用defer延迟关闭改资源，以免引起内存泄漏。例如：

func do() (ok bool) {
  file,_ := os.Open("c:\a.txt")
  defer file.Close()
  // doSomething
  return ok
}
我们可以在官方的文档中看到defer的执行顺序是逆序的，也就是先进后出的顺序：

for i := 0; i < 5; i++ {
  defer fmt.Printf("%d ", i)
}
打印结果是：4,3,2,1,0
那么再看这个例子：

func deferRet(x,y int) (z int){
  defer z += 100
  z = x + y
  return z + 50 // 执行顺序 z = z+50 -> (call defer)z = z+100 -> ret  
}

func main() {
  i := deferRet(1,1)
  println(i)  // print 152
}
我想这个例子已经能够让你明白defer的执行顺序了。




















































