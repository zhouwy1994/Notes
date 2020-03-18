一、时间相关
1.timer(简单计时器) <boost/timer.hpp>
timer是一个简单的计时器，从timer对象构建开始计时,通过elapsed方法输出已消逝的时间(单位s),timer的方法如下:
(1)double elapsed() // 输出timer被构造(或调用restart方法)到调用此函数所用的时间
(2)void restart() // 重新开始计时
(3)double elapsed_min() // 最小计时时长 1 / CLOCKS_PER_SEC秒，***CLOCKS_PER_SEC是每秒运行的时钟周期数,CLOCKS_PER_SEC越大，精度越高***
(4)double elapsed_max() // 最大计时时长 std::numeric_limits<std::clock_t>::max / CLOCKS_PER_SEC秒

2.progress_timer(进度计时器,作用域计时器)  <boost/progress.hpp>
继承于timer，唯一的不同是progress_timer在对象西沟时自动输出计时时长, progress_timerd的构造函数:explicit progress_timer( std::ostream & os = std::cout )
可以将输出定义到其他ostream但是这么做没多大意义。输出格式12.89 s

3.progress_display(进度显示器) <boost/progress.hpp>
一个简单的进度显示类，通过构造时传入expected_count_，通过重载 operator++()和operator+=来控制进度显示，restart(new_expected_count)来重置计数
也可通过构造函数传入其他ostreams对象来重定向输出

4.boost的date_time库包含了所有与日期时间相关的处理组件,date_time将时间处理分为两大类:
(1)日期处理组件 <boost/date_time/gregorian/gregorian.hpp>
gregorian(格里高利历,就是我们生活中所说的公历),date_time的所有日期相关的计算都是基于它
(2)时间处理组件 <boost/date_time/posix_time/posix_time.hpp>
格里高利历的时间细化，提供微妙级(必要时可以提供到纳秒级别)的时间处理
基本概念(可以把时间看成是一根两边无限延伸的实数轴):
时间点(time point):就是数轴上的一个点(2019-04-30 17:58:45)
时间区间(time period):两个时间点之间的一个区间(1994年11月2日12:00:00到2019年04月30日18:00:00)
时间段(time duration 时长):一个有符号的标量5天 5个小时 5年 5秒,有正负之分

基本时间点两个类:
(1)boost::gregorain::date // 可以认为是一个精确到天的时间点,构造函数date(2019,05, 03) 表示2019年5月3日
1.可以从字符串构造,boost::gregorian::from_string("2019-05-03"); boost::gregorain::from_undelimited_string("20190503")
2.也可以从时钟工厂函数构建day_clock的两个静态函数构建local_day和universal_day()构建, date dt = boost::gregorain::day_clock::local_day()
3.格式化输出boost::gregorain::to_simple_string, to_iso_string, to_iso_extended_string
4.与struct tm的转换,boost::gregorain::to_tm(date), date dt = boost::gregorain::date_from_tm(tm);
5.基本计算:
date dt = boost::gregorian::from_string("2019-05-03");
date dt1 = dt + boost::gregorian::days(1); // dt == "2019-05-04" days是时长单位,可以是years,months,weeks(1weeks==7days)
6.可以使用成员函数判断是否是一个有效日期is_not_a_date()
7.两个date之间相减类型是日期时长date_duration
dt1("2019-05-04"); dt2("2019-05-03")
dt1 - dt2 == days(1)


(2)boost::posix_time::ptime // 精确到秒<毫秒>的时间点，构造函数ptime(const date_type&, const time_duration&, dst_flag = not_flag)
1.可以从字符串构造,boost::poxix_time::from_string("2019-05-04 21:27:34"), boost::posix_time::from_iso_string("20190504T212832")
2.也可以从时钟工厂函数second_clock(),microsec_clock()的local_time()和universal_time()获取当前时间和UTC时间
3.格式化输出boost::posix_time::to_simple_string(), boost::posix_time::to_iso_string(), boost::pos_formatix_time::to_iso_extended_string();
4.与struct tm转换，boost::posix_time::to_tm(pt); 但是没有像date那样的date_from_tm，只有一个boost::posix_time::from_time_t();
5.基本计算,由于ptime是由date与time_duration的组合,所以它的计算可以拥有date与time_duration的能力
ptime pt = boost::posix_time::time_from_string("2019-05-04 21:27:34");
ptime pt1 = pt + days(1); // 加一天
ptime pt2 = pt + hours(1); // 加一小时
6.可以使用成员函数判断是否是一个有效时间点is_not_a_date_time()
7.两个ptime之间相减类型是时间时长time_duration
dt1("2019-05-04 12:00:00"); dt2("2019-05-04 08:00:00")
dt1 - dt2 == hours(4)

基本时长的两个类:
(1)boost::gregorian::date_duration // 日期相关，构造格式date_duration dd(5)表示5天
1.date_duration的另一个名是days，是以天为单位,有几个子类years,months,weeks
(2)boost::posix_time::time_duration // 时间相关，构造格式time_duration td(12, 05, 09)表示12个小又05分又秒
1.time_duration的构造函数和date_duration有点差别,虽然time_duration的基本单位是秒,但不能直接以time_duration(secs)构造,必须以HH-MM-SS几个小时又几分钟又几秒
它有几个子类hours, minutes, seconds, millisecons
2.time_duration还有一种从字符串构造的方法，boost::posix_time::duration_from_string("1:10:20:001"),还有反向转换to_simple_string()和to_iso_string()
3.可以通过to_tm转换成struct tm，但没有反响的转换方法
boost::this_thread::sleep_for(const chrono::duration<Rep, Period>& d) //可以看书时长和时间点的关系
sleep_until(const chrono::time_point<Clock, Duration>& t)

基本时间区间的两个类:
(1)date_period,日期区间，时间轴上一个左闭右开的两个date端点，从构造函数可以很直观的看出他的结构date_period(date, date),date_period(date, days)
1.成员函数begin()和last()返回日期的两个端点，end()返回last()的后一天，是一个逾期的位置,length()函数返回区间的天数
2.基本计算
shift(const days &n) // 将日期区间平移n天,时间区间时长不变
expand(const days &n) // 将日期向两端延伸n天,时间区间长度加2n天
is_before(const date &dt), is_after(const date & dt) // 判断日期点dt是否在日期区间前后
is_contains(const date& dt), is_contains(const date_period &dp) // 判断日期点或日期区间是否包含在日期区间内
intersects(const date_period &dp) // 两个日期区间是否存在交集
intersection(const date_period &dp) // 返回两个日期区间的交集
is_adjacent(const date_period &dp) // 判断两个时间区间是否相邻
merge(const date_period &dp); //返回两个时间区间的并集
span(const date_period &dp); // 合并两个日期区间**及两者的间隔**,相当与广义merge;

(2)time_period,时间区间，和date_period相似,只不过是date_period的精确版,从构造函数就可以看出,time_period(ptime, ptime), time_period(ptime, time_duration);
其他参考date_period

其他:
(1)日期迭代器:
day_iterator d_iter(const date, int n = 1); // 日期(天)迭代器,默认增长步长为1
d_iter(date(2019-05-04), 2);
++d_iter == date(2019-05-06)
日期迭代器还有week_iteroaor, month_iterator,year_iterator。。。
(2)时间迭代器
time_iterator(const ptime, int n = 1); // 和日期迭代器类似用法

本地时间:
上述所有讨论都是基于简单得时间操作，但考虑到时间各地的时间不同时区的问题，时间处理就变得复杂了
本地时间的处理需要包含头文件<boost/date_time/local_time/local_time.hpp>
并在命名空间boost::local_time中
最常用的应该就是local_date_time,它的构造函数格式为boost::local_time::local_date_time(ptime, zone) // 时间点加时区,ptime一般都是UTC时间
date_time库可以使用boost::serializeation库能力实现虚拟化和反虚拟化



二、智能指针
1.boost中提供了一下几种智能指针
scoped_ptr:作用域指针，离开作用域即释放,由于它将拷贝构造和拷贝赋私有化(private)，不能将其拥拥有权转移
scoped_ptr和auto_ptr的区别在于auto_ptr可以将指针所有权转移，转移后原auto_ptr悬空
和unique_ptr的区别在于unique_ptr有move构造函数，可以将所有权转移，而且unique_ptr有专门针对数组的特化模板，对数组类的内存
管理有着独特优势
还有一个特点是scoped_ptr不支持自定义删除器，特别需要说明的是scoped_ptr并不是使用简单的delete释放对象内存,而是使用boost::checked_delete( px )

2.scoped_array,scoped_ptr的数组版本,不同的是scoped_array是使用deletep[]释放对象指针boost::checked_array_delete( px );

3.ckeck_delete(px),说明:
class A;
int main(int argc, char *argv[]) {
    A *pa = nullptr;
    delete pa;
    return 0;    
}
首先说明class A只是一个声明，没有定义，但是这样编译器是不会错的，这样的delete也是未定义行为，使用ckeck_delete后这段代码就会报错，因为check_delete里面使用了
sizeof(T),没有定义则会报错

3.unique，这是c++11定义的智能指针，不属于boost，但c++11在定义unique_ptr时没有定义工厂函数（c++14补上了），boost实现了一个make_unique<T>(Args ...),和标准无异

4.shared_ptr,shared_array，也就没什么好说的了，但是他有一个成员函数release，不管有多少个引用,都会释放指针资源,工厂函数make_shared

5.weak_ptr的主要作用是监控shared_ptr的引用状态,在必要的时候通过lock获取shared_ptr，enable_shared_from_this就是基于weak_ptr，在回调函数需要绑定this
时，通过shared_from_this来获取this的shared_ptr，从而保证在this释放后回调函数还能继续使用(王科威代码参考) (注:weak_ptr没有重载* ->运算符,不可以用来操作
业务,只能通过lock()来得到shared_ptr操作业务)
weak_ptr主要解决两个问题,
1.空悬指针问题
int *p1 = new int(3);
p2 = p1; // 这时p2和p1指向同一块内存,如果这时delete p1(就算再把p1置为nullptr),去操作p2也是会产生未定义行为，这时的p2称作空悬指针
要解决上述问题, shared_ptr<int> p1; weak_ptr p2 = p1;就算p1被释放,操作p2时通过lock()获取的shard_ptr已经是一个空值

2.循环引用问题 struct node {
	shared_ptr<node> next;
}
shared_ptr<node> p1, shared_ptr<node> p2;
p1->next = p2; p2->next = p1;
当p1,p2被释放时引用计数减一，但是上述p1、p2的引用计数都是2,所以会造成内存泄漏
可以将shared_ptr<node> next替换成weak_ptr<node> next

6.intrusive_ptr<T>(入侵指针)，其实就是自定义智能指针辅助类，需要实现两个回调函数intrusive_ptr_add_ref(T*)，增加引用
计数，intrusive_ptr_release(T*) //减小引用计数，用户可以在此回调函数中做相应操作，比如当引用计数减为0时，做相应操作，intrusive_ptr构造和析构时会
回调这两个回调函数

7.enable_shared_from_this,enable_shared_from_raw，区别是enable_shared_from_this在调用shared_from_this时本身应该是一个shared_ptr对象,不能是裸指针
而enable_shared_from_raw在调用shared_from_raw时可以时裸指针

8.boost内存池pool，boost中有四种内存池对象
1.pool最原始的内存池对象,分配制定大小的内存，但每次只能分配固定大小或几倍固定大小的内存空间(我想这是boost为了使内存对齐所做的限制)
2.object_pool，分配sizeof(T)大小的内存,但是可以通过调用construct成员函数来构造对象，调用destroy成员函数来析构对象
3.singleton_pool是增对每种类型特化的单例内存池对象,每种类型T全局只存在一个内存池对象,最后调用release释放所有内存
4.pool_alloc是一种内存分配器,可以作为STL的内存分配器std::vector<int, boost::pool_allocator<int> > v;

三、boost使用工具
1.noncopyable,它定义了一个不可拷贝类的实现方法,继承一个不可拷贝类(拷贝构造函数私有化
2.ignore_unused,它可消除一些未使用变量导致的编译器警告
3.optional,提供了一个"无效值"的概念,不是所有函数的返回路径所返回的值都是可用的(有意义的)
4.assign,使用boost::assign命名空间,就可显示的使用容器的+=、()、,等操作符,std::vector<int> v; v += 1,2,3
5.swap,高效的对象交换,使用std::move实现，应该在开发工程中多多使用
6.singleton,单件模式,boost::serialization::signleton<class>::get_mutable_instance get_const_instance
7.tribool,第三态bool值,它除了有true,flase还有第三种状态indeterminate介于true与flase之间,和optional<bool>作用相似，有细微却别
8.operators,一个强大的操作符重载库，没细看
9.boost::exception,是对标准异常std::exception的补充和完善,尽量使用虚继承来使用它·
10.uuid,一个可以生成uuid的辅助工具，基于boost sha1实现
11.一些常用宏:
BOOST_STRINGIZE:实现编译器字符串转换
BOOST_STATIC_CONSTANT:定义类的静态整形常量
BOOST_BINARY:可以使用字面量二进制
BOOST_CURRENT_FUNCTION:输出当前函数名，与__func__区别，前者可以输出函数参数,后者只可以输出函数名


四、字符串处理
1.lexical_cast,可以作为atoi的替代工具，只要满足三个条件，就可相互完成cast
int number = boost::lexical_cast<int>(std::string("12345"));
转换起点:std::string("12345")
转换终点:number
(1)转换起点对象是可流输出的，即定义operator<<
(2)转换终点对象是可流输入的，即定义operator>>
(3)转换终点对象必须是可缺省构造和拷贝构造的
此处不得不提c++11中的stoi, stoll等函数

2.format,之前以为boost中没有像fmt(开源的c++格式化字符转库)这样好用的库，可是强大的boost竟然有，而且用法还比较丰富
fmt库中使用{n}来标识需要输出的参数位置','来连接参数,boost::format使用%n%,使用%来连接参数,还要说明的是boost::format
还支持所有printf的格式控制符
boost::format fmt( "format-string %1% %2%") % arg1 % arg2 % ... % argN ;
fmt.str()

3.string_ref,是一个轻量级的字符串实现，功能与std::string可以说是一模一样,包含std::string的所有成员函数,只不过string_ref持有的是
内存地址，而string持有内存拷贝，所以string_ref多持有的字符串内存不能被释放

4.string_algo,<boost/algorithm/string.hpp>,boost::algorithm命名空间下，提供了大量的字符转操作函数，可以与其他语言的字符串处理函数相媲美
但是大量的算法需要经常使用去熟悉

5.tokenizer，专注处理字符串分词功能,与boost::string_algo下的splite相似,

6.xpressive,是一个灵活且功能强大的正则表达式解析库，可以构建小型语法，同时提供静态和动态两种用法，功能十分强大，
但由于其功能强大，相应的性能就不如string_algo和tokenizer，不到万不得已不建议使用

五、单元测试
1.assign库中提供一个断言宏BOOST_ASSIGN,它的默认行为与assign相同，如果声明宏BOOST_ENABLE_ASSIGN_HANDLE，那就可以给断言安装一个handler;
2.static_assign编译期断言，再模板编程中有很重要的作用
3.lightweight_test是一个轻量级的单元测试框架，不需要编译就可直接使用，但不适合大多数软件开发项目
4.boost中重要的单元测试框架test库,它提供了单元测试框架UTF(Unit Test Frame),UTF提供了完整的单元测试框架，测试套件，测试夹具等概念，可以参考
宏和集团HHFS里面的单元测试

六、容器和数据结构
(1) array:对标准c++数组的一个封装，为数组增加一些迭代器操作和一些有用的函数，使数组的行为更像一个标准容器，但永远不是容器，但性能上没有
任何损失，强烈建议使用。
(2) dynamic_bitset:类似与std::bitset,可以容纳任意数量的二进制数，方便用于位运算，接口和bitset的接口完全相同，配合BOOST_BINARY配合使用可以
获得个更高的运行效率.
(3) unordered类型容器，他的内部数据结构使用散列(hash)而不是二叉树，可以获得更高的性能
(4) bimap是一个双向map,可以实现key-value value-key的双向映射关系
(6) circular_buffer是一个循环队列，他的内部存储是循环利用的。工作方式类似dequeue
(7) tuple是对std::pair的泛化，常用做函数返回值，返回值可用std::tie来接收，性能比struct高效,tuple是模板元编程的基本构建
(8) any,可以容纳任何类型的元素，any a = "string" std::cout << any_cast<std::string>(a);
(9) variant,可以容纳用户指定的任何类型元素（只能容纳一个元素）
(10) multi_array：多维数组，比vector<vector>更高效,可以动态改变数组维度
(11) property_tree库能够解析xml、json、ini、info四种配置文件,用得最多

七、算法
(1) foreach:c++11新的for语法，但c++98不支持，boost提供两个迭代器算法(宏)
BOOST_AUTO(auto i, vec) // 注意是逗号，而不是:
BOOST_REVERSE_FORCH // 反向迭代
(2) minmax:找出最大值和最小值，适合容器
(3) hex、unhex这个算法有用
(4) clamp,

八、数字与数学
常用的几个库:
ratio:分数
random：随机数
crc算法

九、操作系统相关
常用库:
system_error、error_code:系统错误码
chrono:高精度时钟相关
cpu_timer:高精度计时器
filesystem:文件系统相关,几乎涵盖了所有文件系统api
program_options:命令行相关,用过

十、函数与回调















