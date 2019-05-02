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
