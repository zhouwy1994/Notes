1.SVN 如果出现 Unable to connect to a repository at URL连接不上服务器时,可能有两种情况
(1)svn客户端与svn服务器网络连接不通(查看是否ping通或是否在同一网段)
(2)查看是否是第一次连接指定的svn服务器，由于svn客户端是缓存机制，当换了一个svn服务器，就要将之前的缓存清空
2.Linux下新建用户,要注意几个问题,如果是使用useradd命令新建的用户，别忘记指定默认sh，在/etc/passwd下加上默认bash
新建文件夹都是白色，是因为没有配置文件，,bashrc,.profile等，可以从其它用户那拷贝过来
3.sftp(Secure File TransferProtocol安全文件传送协议)是openssh-server中一个附带的文件传输协议，
只要是运行了sshd服务的计算机都可以用sftp传输文件
4.VirtualBox后台启动虚拟机
VBoxManage startvm $VMName --type headless
5.高版本gcc编译低版本Gcc时应该要注意以下问题
(1)安装必要依赖包
(2)gcc/config/linux-uuwid.h中的siginfo应该是siginfo_t
(3)gcc4.1.2要用gcc4.8.5版本以下才编译得过(所以先把当前环境换成gcc-4.8.5之后才编译gcc4.1.2)
(4)gcc/config/linux-uuwid.h 的struct sigcontext *sc; 把sc = (struct sigcontext*)(void*)uc->..这句注释掉，后面编译过
了再改回来make
(5)如果出现No Such Director crti.o之类的先找到(find)crti.o的位置，
然后建立一个软连接到/usr/lib中去sudo ln -s /usr/lib/x86_64-linux-gnu /usr/lib64
(6)使用gcc时查看gcc编译是否完整，是否安装gcc-multilib等

6.Reahat下搜索软件包yum search $packagename
Ubuntu下apt-cache search $packagename 而不是用apt-get search

7.ubuntu16.04安装Mysql-5.7-server在图形界面安装和弹出设置root密码对话框。可用xshell等shell界面安装时则不弹出，这时需要设置root密码，步骤如下:
(1)修改/etc/mysql/mysql.conf.d/mysqld.conf(各平台下可能不一致)在[mysqld]字段下添加skip-grant-tables字段
(2)重启服务systemctl restart mysql.service(各平台可能不一致)
(3)mysql -u root -p(直接回车)
(4)use mysql;(选择mysql表)
(5)update user set authentication_string=password('123456') where user='root';(更新root密码)
(6)flush privileges;(执行操作)
(7)删除(1)步骤增加的字段并重启mysqld服务
(8)mysql -u root -p(如果此时还是无法登陆而加了sudo后却登陆成功，则继续执行下列步骤)
(9)use mysql;
(10)UPDATE user SET plugin='mysql_native_password' WHERE User='root';
(11)flush privileges;(执行操作)

8.mysqld如果要开启远程访问，要将user表的Host字段设置成为%(表示可以从任何计算机登录)，还要将mysqld.cnf中的bind-address 127.0.0.1改成0.0.0.0
(监听所有地址)

9.如果误删了/usr/bin/gcc类似的命令，不要慌，其实大部分只是一个软连接，只要找到其真正的实体，就可以，比如gcc连接至x86_64-linux-gnu-gcc-7

10.通常在linux下安装软件步骤都很明确，基本上就两种,autoconf和cmake
通常autoconf都会生成或包含configure，安装步骤基本上就是./configure --prefix=$dir ,make, make install
cmake通常也是这个不走，只不过第一步为cmake $option
为什么在make install大部分需要sudo权限，因为我们使用了默配置，默认配置都将安装目录放在/usr/local/下，因为make install都需要创建文件，所以就需要sudo
如果不想将安装目录默认，可通过--prefix配置

11.编译安装boost步骤，两种方法
(1)源码安装
wget https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.bz2
tar zxvf boost_1_67_0.tar.gz
sudo ./bootstrap.sh --prefix=/usr/local/include/boost --with-$libname //此处目录可将其安装在gcc默认的目录下
sudo ./b2 install
默认最小安装，可通过选项--with-$libname(atomic,chrono,thread)等选择安装
(2)平台安装(ubuntu16)
sudo apt-get install libboost-dev
上面安装后可得到boost所有头文件(hpp)
但是没有lib文件
sudo apt-get install libboost-thread-dev可安装制定的lib文件(将thread换成其他)

12.编译遇见找不到cdef.h情况，请安装libc6-dev-i386，这里面包含32位的所有gcc库，只要是找不到gcc的公共库，都可能是缺失这个库
13.编译链接时找不到
/usr/bin/ld: cannot find crt1.o: No such file or directory
/usr/bin/ld: cannot find crti.o: No such file or directory
是因为crti.o不在默认路径，只需创建一个软连接到/usr/lib64 或/usr/lib32里即可
ln -s /usr/lib/x86_64-linux-gnu/crt1.o /usr/lib64/crt1.o

14.在使用vs创建项目时，会设置附加包含目录，附加库目录等，不能设置成绝对路径，因为要提交到代码管理器上，别人down下来要直接编译
vs中每个工程都有自己的环境变量，例如:ProjectDir就是当前工程路径，一切附加目录都应该使用此变量来设置

15.netcat 这个工具小巧实用,确实是不可多得的工具
https://blog.csdn.net/wangqingchuan92/article/details/79666885
netcat -l $ip:$port 监听端口
netcat $ip $port 连接
netcat  -v $ip $port 检测某个端口是否开放
netcat -l port < file 发送文件	netcat -n server_ip port > file 接受文件(很有用)
cat video.avi | netcat -l port 视频传输		netcat server_ip port | mplayer -vo x11 -cache 3000 -  视频读取

16.tcpdump抓包工具是linux下的抓包工具，比较实用，如果要监听哪个端口是否有数据出来或除去，查看抓取内容等
监听本地回环(本机到本机)
tcpdump -i lo
监听指定主机
tcpdump host $ip
监听指定端口(-X)查看包内容
sudo tcpdump -X tcp port 12345
https://www.cnblogs.com/maifengqiang/p/3863168.html

17.wireshark是一款非常好用的可视化抓包工具,打开wireshark选择capture---->start即可开始抓包，可以根据过滤规则进行过滤
https://blog.csdn.net/wojiaopanpan/article/details/69944970

17.登陆linux后清除登陆记录(last lastb(失败记录))
echo /dev/null > /var/log/wtmp
echo /dev/null > /var/log/btmp
清除历史命令 history -c or echo /dev/null > ./.bash_history
admin hk123456 248


18.linux下查看c++库(so,a)等是多少位的 用file *.so

19.git clone http方式出现认证失败但又没有弹出输入任何提示输入用户名密码的情况下,就是说之前你的电脑保存有凭据,但可能凭据已经过期,这时需
要清除之前保存的凭据win:控制面板----->用户帐户-------->凭据管理器-------->普通凭据---->找到你之前的git地址，删除----->ok

20.windows创建服务命令:sc
(1)创建服务 sc create $ServiceName	binPath= (此处有空格)"exe路径" start= "启动方式"
(2)启动服务 sc start $ServiceName
(3)停止服务 sc stop $ServiceName
(4)删除服务 sc delete $ServiceName


21.nmap 一款不错的局域网(广域网也行)的ip+port稍描工具，用于局域网类的设备查找很方便,有linux和windows版
nbtscan也不错命令行工具(但是好像不能稍描端口 nc -v port可以但是不可以设定范围)


22.svn创建分支教程,不错(https://www.cnblogs.com/firstdream/p/5632296.html),一般在创建一个svn工程时，都要建立三个文件夹
branches 用于新建分支
tags	 用于建立标签(只读)一般用于阶段性版本发布
trunk	 主干，主分支
版本号:主版本号 . 子版本号 [. 修正版本号 [. 编译版本号 ](https://baike.baidu.com/item/%E8%BD%AF%E4%BB%B6%E7%89%88%E6%9C%AC%E5%8F%B7/188753?fr=aladdin)


23。linux下查看.so或.a导出函数时用命令nm,windows下用vs工具dumpbin查看dll或lib的导出函数

24.VS下建立Linux跨平台项目，在项目属性--->配置属性----->常规----->项目默认值------>配置类型，可以选择你要生成文件的类型，害我之前为
了生成Linux动态库而去修改编译选项(汗),什么都还是应该去看官方文档而不应该盲目去百度

25.Linux项目设置共享库搜索路径，可以将搜索路径设置到当前目录，那只需要将动态库与.out在同一目录就可执行




