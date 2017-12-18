网络体系结构
老师：   张永林   zhangyl@farsight.com.cn
网络体系结构功能：采用分层的思想，每一层向上层提供服务，同时使用下层提供的服务(服务是垂直的，协议是水平的)
网络体系结构概念：每一层以及每一层使用的协议的总称。
两种网络体系结构：osi、TCP/IP
    osi：              TCP/IP：
	应用层
	表示层             应用层
	会话层              
	传输层             传输层
	网络层             网络层
	数据链路层
	物理层             网络接口物理层
	
每一层的协议：
网络接口和物理层：
	mac地址：48bit,每一个网段中唯一。
	arp协议：ip地址--->mac地址
	rarp协议：mac地址--->IP地址
	以太网协议：使用的最广泛的数据链路层协议

网络层：
	ip协议：IP协议是用于将多个包交换网络连接起来的，它在源地址和目的地址之间传
			送据包，它还提供对数据大小的重新组装功能，以适应不同网络对包大小的要求(没有可靠性,流控制)。
	icmp协议：internet控制管理协议，ping命令就是基于这一层开发的应用软件。
	igmp协议：internet组管理协议，广播和组播会采用这层协议。
	ospf协议：自动设置路由

传输层：
	tcp协议：最重要的端口，可靠的,需要建立连接(点对点的通信)，全双工通信。
			tcp：发送的消息是无边界的，所以你必须自己控制长度进行接收。
			tcp数据包头有20个字节。
			tcp：发送0个字节，接收端继续阻塞(具有阻塞控制能力)，没有任何反应。
			tcp服务器流程：
					创建套接字(socket) -> 将套接字和ip地址绑定在一起(bind) -> 监听套接口(listen) 
					-> 取走链接(accept, 就是取走监听套接口中的信息) -> 接受(recv)和发送信息(send)【循环就从取走链接开始】->	最后关闭套接口		
			tcp客户端流程：
					创建套接字(socket)-> 链接套接字(connect) -> 接受(recv)和发送信息(send)-> 最后关闭套接口
				
	udp协议：不用建立连接，不可靠的(可以一对一，一对多，多对一的通信)。
			udp：消息有边界的，对方发送多少次，就必须接收多少次。
			udp数据包头只有8个字节。
			udp:发送0个字节，接收端(recvfrom)不会阻塞(就是不具有阻塞控制)，会返回0(表示发送方，发送0个字节)。	udp服务器流程：创建套接字(socket)->将套接口和ip地址绑定在一起(bind)->接受(recv)和发送信息(send)【循环就从取走链接开始】->关闭套接字	udp客户端流程：创建套接字(socket)->将套接口和ip地址绑定在一起(bind)->接受(recv)和发送信息(send)【循环就从取走链接开始】->关闭套接字
			
	sctp协议：流控制传输协议，多用户、多链路的协议，一般用在军方，保密级别很高的地方
			  所以发送一次，可以多次接收。
			  
应用层协议：
	http： 超文本传输协议(不带加密)  
		   超文本:就是利用超链接的方法把不同区域的文本组织在一起的网状文本。
		   
	https：安全的超文本传输协议(加密)
	snmp： 简单的网络管理协议
	ftp：  文件传输协议

封包和拆包：
       MTU：max transfer unit，在以太网中，最大是1500字节
抓包指令：
		tcpdump
		抓那个接口 -i eth0
		抓ip地址 ：
			tcpdump -i eth0 host 192.168.3.254  and host 192.168.3.107
			tcpdump -i eth0 src host 192.168.3.254
		抓协议：
			tcpdump -i eth0 arp
		抓端口：
			tcpdump -i eth0 port 22
			tcpdump -i eth0 not port 22   (src,dst)
		
socket：是一种编程接口，首先需要返回一个套接口描述字，然后我们通过描述字进行read，write，也就是网络通信。
	套接字类型：套接字就是一个无符号整数。
		流式套接字  ---> tcp
		数据包套接字---> udp
		原始套接字---> 跨过传输层，直接操作网络层
socket函数实际上做了哪些操作：
	    根据套接口类型创建发送和接收缓冲区，对于udp这种数据报套接字类型，只创建了接收缓冲区，没有发送缓冲区。	
创建函数:int socket (int domain, int type, int protocol);
		第一个参数：地址族
		第二个参数：套接字类型
		第三个参数：协议类型，udp和tcp，protocol可以直接写0，如果采用原始套接字，protocol需要自己写
		返回值：套接字描述字，如果-1，表示错误。
		//INADDR_ANY:表示所有这样你的程序就会自动获取本机的ip地址不用自己设置。
struct sockaddr_in  struct sockaddr_un{           
       u_short sin_family;      // 地址族, AF_INET，2 bytes
       u_short sin_port;      // 端口，2 bytes
       struct in_addr sin_addr;  // IPV4地址，4 bytes 	
       char sin_zero[8];        // 8 bytes unused，作为填充
}; 

struct in_addr{
     in_addr_t  s_addr;            // u32 network address 
};

注意：进程运行在ip地址和端口上，并不是程序本身，而是程序创建的套接口绑定到了ip地址和端口上.

IP地址：
	IPv4：4个字节
	IPv6:16个字节
	点分十进制，实际上是一个字符串，计算机本身不认识：192.168.0.1
		int inet_aton(const char *cp, struct in_addr *inp);
		功能：把点分十进制IP地址转换为网络字节序IP地址
		第一个参数：点分十进制IP地址
		第二个参数：转换后的IP地址存放位置
		返回值：返回0表示成功，返回-1表示失败
	inet_addr()

	inet_ntoa()
			功能：把计算机识别的IP地址转换为人能识别的点分十进制IP地址。

	端口号：/etc/services   linux下存放服务和端口的对应关系我们自己开发使用的是5000也上的端口号，
							最大的是65535这是由于最大的无符号整数。

	 2个字节：lsof -i:端口 查看该端口上运行的服务.

	字节序：
		小端字节序：低地址存放低字节，小端机
		大端字节序：低地址存放高字节，大端机
		如何判断大小端：
					1): int i = 1; char *a = (char *)&i; 输出a的值看是0是1， 1就是大端0就是小端
					2): 利用共用体进行操作,存放一个int 和一个 char 给int存值用char输出(强制转化)。 
		主机字节序：一般的为小端字节序
		网络字节序：大端字节序
	地址转换：
			htonl() :将主机字节序转换为网络字节序，ntohl相反
			htons() :将主机字节序转换为网络字节序，ntohs相反


		struct sockaddr_in IPv4套接口地址
		struct sockaddr_un （unix域套接字地址）

		任何一个套接字都是绑定到IP地址和端口上，一般来说服务器要将套接和具体的IP地址和端口绑定，客户端可以忽略。


		int bind(int sockfd, struct sockaddr?*my_addr, int addrlen) ; 
		功能：将套接口描述字绑定到端口和IP地址上
		listen函数：会维护两个队列，accept函数会从已完成队列中将连接取走。在listen函数执行完成后，套接口就会变成监听套接口。
		listen函数的第二个参数：没有被accept函数取走的连接最大个数。
		监听套接口：不会同客户端进行通信，只是维护队列。
		
		int accept(int sockfd, struct sockaddr?*addr, socklen_t *addrlen) ;
			功能：从已完成队列中取走连接。
			返回：连接套接口，服务端通过这个链接套接口同客户端通信。
			第三个参数：值结果参数。事先要有值，并且返回值有可能被修改。
			参数addr：表示客户端的地址，是跟我链接套接口对应的客户端的地址。
			参数addrlen：地址长度，值结果参数。
			返回值：链接套接口
			返回的链接套接口同我们客户端的套接口一一对应。
			
		ssize_t recvfrom(int socket, void *buffer, size_t length, int flags,
						struct sockaddr *address, socklen_t *address_len);
		参数：address，表示对端的地址，是由recvfrom函数自动给我们填充。
		参数：address_len，是一个值结果参数。
		返回值是0：表示的是对端发送0个字节。
		如果你不关心谁发送的消息给我，address和address_len都可以设置为NULL。

文件服务器系统：		
	客户端调用的函数：
		int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
		该函数会发起三次握手
		recv和read如果返回0，表示对端把链接套接口关闭close(cfd)。
		如果接收缓冲区中没有数据，read，recv，recvfrom都会阻塞。
		send，write发送时，如果写了发送长度如1024，buf缓冲区中没有1024个字节，也会发送1024。

		需求：文件服务器
			客户端输入ls ，服务器获取当前目录中的文件返回给客户端，opendir readdir closedir
				strcut filemsg{0,,}
				服务器没找到一个文件，就发送到客户端
				while（readdir（））{
					send（fd，struct filemsg，）；
				}
				strcut filemsg{0,filename,}
				客户端接收：
				while(read(fd, struct filemsg, sizeof(struct filemsg))){
					printf("%s  "，filemsg.filename);
				}

			客户端输入get file ，获取服务器中的文件
				客户端：struct filemsg{1，filename，}
				服务端：判断cmd ==1表示客户端向我要文件
					读取文件的内容buf
					buf内容放到cotext中去。
				客户端：在本地创建这个文件，然后将文件内容写到文件中

			客户端输入put file ，上传文件file到服务器。
				客户端：struct filemsg{2，filename，文件内容}
				服务器端：
					创建文件filename
					将文件内容写到filename中去

			struct filemsg{
				int command;       //0：ls,1:get; 2:put
				char filename[20]; //文件名
				char cotext[1024]; //存放文件的内容

			}
			

网络编程中的I/O编程模型：总共5种
	1.阻塞式IO：recv read recvfrom accept write send这些函数都会发生阻塞。
        2.非阻塞式IO：
		方法1：int fcntl(int fd, int cmd, long arg);
			参数2：表示对这个fd做什么操作。
			参数3：如果是要设置，就是设置的值
			fcntl(sockfd, F_SETFL, O_NONBLOCK);

		方法2：recv的第四个参数设置为MSG_DONTWAIT。
			
		read：返回-1，并且将errno设置为11，EAGAIN或者EWOULDBLOCK，这两个值是相等的，表示接收缓冲区中的数据已经读完

	3.信号驱动式IO：(边缘触发模式)
		信号驱动式io 对于tcp套接字几乎无用，很多情况都能导致tcp套接字产生SIGIO信号都是正常的；可以对套接字使用SIGIO，因为对于监听套接字来说产生SIGIO的唯一条件是某个新连接完成，或异步错误(因为tcp是可靠传输)。
		对于udp来说，发生SIGIO时调用recvfrom可以读入数据报，或者发生异步错误。	但是如果要精确的获得消息报到达时间，可以使用UDP的SIGIO，当产生该信号时就记录时间，并把消息报存入应用层队列供上层使用。

	4.异步IO：线程发送一个IO请求到内核，然后继续处理其他的事情，内核完成IO请求后，将会通知线程IO操作完成了。
	
	5.多路复用IO：
		注意：多路复用IO不适合服务器处理用户的请求非常耗时的场合。
		selelct系统调用会在内核不断扫描套接字，看那个套接字准备好。
		FD_SETSIZE：说明了这个整数有多少bit。
		实现方式1：(最多支持1021个服务器连接，水平触发方式)
		int select(int n, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds, struct timeval *timeout);
		fd_set是一个很大的数字，一般来说1024bit的整数。
		参数一：n表示的是最大描述字加1，因为计算机计套接字数是从0开始计数不能实际表示扫描的个数。
				告诉内核扫描多少个套接字。	
		参数二：read_fds,是一个值结果参数，表示关注那些读套接字，程序返回时表示的是那些套接字准备好。
				所以在下次调用select函数要重新设置。
		参数三：write_fds，是一个值结果参数，表示关注那些写套接字，程序返回时表示的是那些套接字准备好。
		参数四：except_fds，是一个值结果参数，表示关注那些异常套接字，程序返回时表示的是那些套接字准备好
				一般不用这个参数，所以调用的时候一般设置为NULL。
		参数五：timeout，值结果参数，超时时间设置，比如3秒，在3秒内没有一个套接字准备好，select函数还是返回。
				一般是将该参数设置为NULL，表示永远等待。
		返回值：大于0，表示有多少个套接字准备好。
				等于0，表示超时返回。
				小于0，出错
				
		void FD_ZERO(fd_set *fdset) 全设置为0
		void FD_SET(int fd,fd_set *fdset) 把fd位bit设置为1
		void FD_CLR(int fd,fd_set *fdset) 把fd位bit设置为0
		int FD_ISSET(int fd,fd_set *fdset) 判断fd位bit是不是1，是1返回真，不是返回0。
		
		实现的第二种方式：poll函数(水平触发方式)
			 int poll(struct pollfd *fds, nfds_t nfds, int timeout);
			 struct pollfd {
               			int   fd;         /* file descriptor */
              			short events;     /* requested events */表示关注那些事件
               			short revents;    /* returned events */表示可以进行的事件
						};
			第一个参数：fds表示的是一个结构体数组(每个数组表示一个套接字)。
			第二个参数：告诉系统，你关注几个数组元素，从0开始。
			第三个参数：timeout 超时时间，以毫秒为单位。
			返回值： >0 表示有多少个套接字(数组)准备好
					=0 超时返回
					<0 出错

			事件：POLLIN：表示读事件
			      POLLOUT：写事件
				
		    第一步：建立一个大的结构体数组；
		    第二步：将结构体中的描述字设置为-1，表示该元素没有使用。
			第三步：加入关注的套接字到结构体数组中。
					
		实现的第三种方式：(边沿触发方式)
			epoll:（总共有三个函数）
				int epoll_create(int size);
				size：在2.6.8内核过后没有使用，但这个值必须大于0.
				返回值：epoll的实例，用整数来表示这个实例。

				int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
				//直接往内核注册事件
				参数1：epfd表示的是那个实例。
				参数2：向我们的epoll实例做什么操作
					1）添加关注事件  EPOLL_CTL_ADD
					2）删除关注事件  EPOLL_CTL_DEL
					3）修改关注的事件 EPOLL_CTL_MOD
					4）触发方式：EPOLLET边沿触发(这个选项是epoll高效的关键因素之一)，
						告诉应用程序套接口可读的方式
					(select和poll采用的水平触发)
					注意：采用边沿触发的时候，读数据时一定要把数据读完。
				参数3：表示哪一个套接口
				参数4：是一个结构体epoll_event，如下：
					   typedef union epoll_data {
               void        *ptr;
               int          fd; //哪一个套接字
               uint32_t     u32;
               uint64_t     u64;
           } epoll_data_t;

           struct epoll_event {
               uint32_t     events;      /* Epoll events */ 表示关注的事件：EPOLLIN(可读)，EPOLLOUT(可写)，EPOLLET
               epoll_data_t data;        /* User data variable */
           };
				返回值：0：表示成功
					-1：出错

				int epoll_wait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout);
				参数1：epfd表示epoll实例
				参数2：events 表示的是准备好的套接字(结构体数组的名字)
				参数3：最大返回多少个套接字(数组大小)
				参数4：timeout表示毫秒数 如果是-1表示永远等待
				返回值：

			采用边沿触发的时候，一定要使用非阻塞方式。(接收数据时必须要把数据接收完,可靠传输)

			
	select：1）每次调用select，都要拷贝一次(很大的整数，拷贝到内核）。
		2）不断的扫描大整数，扫描最大描述字加一
		3）每次通过直结果参数进行返回，所以需要两个fdset大整数。
		4）扫描返回的结果，看哪一个套接字准备好
	poll：1）每次调用，都要拷贝一次(将结构体数组拷贝到内核)。
		2）内核不断扫描结构体数据中的前n个。
		3）直接就返回，不需要两个结构体数组。
		4）返回后，扫描，看哪一个套接字准备好。
	epoll：1）不用每次都拷贝到内核，只设置一次就可以。epoll_ctl直接将描述字及关注事件直接注册到内核。
		2）返回后，前面都是有用的。
		3）采用边沿触发的方式（高效的原因之一）
		4）采用非阻塞方式。
		
	Level_triggered(水平触发) ：当被监控的文件描述符上有可读写事件发生时，epoll_wait()会通知处理程序去读写。如果这次没有把数据一次性全部读写完(如读写缓冲区太小)，那么下次调用epoll_wait()时，它还会通知你在上没读写完的文件描述符上继续读写，当然如果你一直不去读写，它会一直通知你！如果系统中有大量你不需要读写的就绪文件描述符，而它们每次都会返回，这样会大大降低处理程序检索自己关心的就绪文件描述符的效率！
	
	Edge_triggered(边缘触发) 		当被监控的文件描述符上有可读写事件发生时，epoll_wait()会通知处理程序去读写。如果这次没有把数据全部读写完(如读写缓冲区太小)，那么下次调用epoll_wait()时，它不会通知你，也就是它只会通知你一次，直到该文件描述符上出现第二次可读写事件才会通知你！这种模式比水平触发效率高，系统不会充斥大量你不关心的就绪文件描述符！

服务器的模型：
	循环服务器：简单的tcp，udp服务器都是
	
并发编程：
	服务器每接收一个用户请求，就产生一个子进程来处理。	
	服务器主进程要主动回收子进程的尸体，不然会有僵尸进程。
	服务器在回收子进程尸体时，不能采用wait函数(因为wait函数会阻塞)来做，一定要使用waitpit。
			waitpid(-1,NULL,WNOHANG)
	
	服务器主进程关闭连接套接字
	子进程关闭监听套接字

协议头：
	以太网协议头：14个字节
	IP头一般来说：20个字节
	TCP头：20个字节
	UDP头：8个字节
	MTU: 表示可传输的最大字节数，1500字节

	设置套接口属性：
	int setsockopt(int sockfd, int level, int optname,const void *optval, socklen_t optlen)
	
	参数1：哪一个套接口
	参数2：级别：SOL_SOCKET(设置套接字属性)，IPPROTO_IP，IPPRO_TCP
	参数3：设置哪一个选项，
		SO_RCVBUF 内核接收缓冲区大小
		SO_RCVTIMEO 接收超时时间设置
		SO_REUSEADDR：允许本地地址和port可重用。
		SO_BROADCAST：允许广播
	参数4：设置值的地址
	参数5：第四个参数的大小
	返回值：成功返回0，出错返回-1.
	
	网络超时检测：
	1：设置套接口属性
		struct timeval  tv;
                      tv.tv_sec = 3;
                      tv.tv_usec = 0;
		setsockopt(cfd,SOL_SOCKET,SO_RCVTIME    O,&tv,sizeof(tv));
	2：通过select、poll、epoll_wait自带的参数来设置

	3：定时器：
		int sigaction(int signum, const struct sigaction *act,
                     struct sigaction *oldact);
		参数1：表示哪一个信号
		参数2：设置信号处理
		参数3：获得以前对这个信号处理的方法
		struct sigaction {
               void     (*sa_handler)(int);//信号处理函数
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };
		注册信号处理函数
		void sigfun(int sig)
  		{
      			printf("time come....\n");
     			alarm(5);
 		}

		struct sigaction act;
	    act.sa_handler = sigfun;
		sigaction(SIGALRM,&act,NULL);
		alarm(5);产生信号SIGALRM
		如果说程序阻塞在select、read、recv等等，一旦捕获这个信号，马上会进行信号处理程序，
		这些函数会返回-1，并且errno的值为EINTR。
	
	单播：一对一
		
	广播和组播：都是采用UDP
		广播：一对网段中的所有人
		同单播区别：
			发送的目的IP地址不同
			包会默认发送给自己一份：我们也不管
			目的MAC地址为全1:(由系统决定的，系统看到目的IP是广播地址，会将目的mac设置为全1)	我们也不管	
			
	代码： 服务器端：
			目的的IP地址为广播地址
			将套接字的广播选项打开
			循环这个目的广播地址发送消息
		    客户端：
			绑定套接字到指定的端口上
			循环接收

		组播：一对多
			
组播：
	IP地址：
		A类：(100)1-127
		B类：(101)128-191
		C类: (110)192-223
		D类：(111)224-240  组播地址
		E类：240-255 保留
	网络层：目的地址是组播地址
	
	目的mac地址：01:00:5E+组播地址的最后三个字节
			    224.20.20.20  目的mac：01:00:5E:14:14:14
	服务端：
		1.创建套接口
		2.封装一个目的的组播地址结构
		3.循环往这个地址结构发送

	客户端：
		1.创建套接字UDP
		2.绑定套接字到套接字地址结构上(端口)
		3.加入到组播组
			struct  ip_mreq  mreq;
			bzero(&mreq, sizeof(mreq));
			mreq.imr_multiaddr.s_addr = inet_addr(“224.10.10.1”);
			mreq.imr_interface.s_addr = htonl(INADDR_ANY);(这样设置的ip地址使用性更强)
			setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));加入到组播组
		4.循环接收消息


本地UNIX域套接字：
	作用：用在本地多个进程间通信(一个server，多个client)
	server：
		1.创建套接口  PF_UNIX/AF_UNIX,PF_LOCAL/AF_LOCAL
			socket（AF_LOCAL,套接口类型，0）//可以是UDP，也可以是TCP
		2.绑定
			封装地址结构
			struct sockaddr_un        //  <sys/un.h>
        		{
             			sa_family_t  sun_family;
             			char  sun_path[108];         // 套接字文件的路径
         		};
		    注意：SO_REUSEADDR 这个选项不能再使用
			      如果文件存在，bind会失败，所以在绑定之前要删除这个文件调用unlink()函数删除文件
				  
		3.监听
		
		4.循环
			取得用户链接，然后接收客户端请求，然后处理，处理完成关闭链接套接字
		5.关闭监听套接字

	 client：
		1.创建套接口 PF_UNIX/AF_UNIX,PF_LOCAL/AF_LOCAL
			socket（AF_LOCAL,套接口类型，0）//可以是UDP，也可以是TCP

		2.链接服务器connect
			先封装一个服务器地址结构
	
		3.发送消息到服务器
		
		4.接收服务器对我请求消息处理结果的回应
		
		5.关闭套接字			   

数据库sqlite3：
		1.	数据库分类
		大型数据库：oracle、DB2
		中型数据库：sqlserver 
		小型数据库：mysql
		Sqlite属于微小型数据库，主要应用于嵌入式领域。

		2.	Sqlite3数据库特点，主要用在嵌入式领域
		a)	SQLite的源代码是C，其源代码完全开放。
		b)	零配置一无需安装和管理配置；
		c)	储存在单一磁盘文件中的一个完整的数据库；
		d)	数据库文件可以在不同字节顺序的机器间自由共享；
		e)	支持数据库大小至2TB；
		f)	足够小，全部源码大致3万行c代码，250KB；
		g)	比目前流行的大多数数据库对数据的操作要快；


	安装：
a)	dpkg -i sqlite3_3.7.2-1ubuntu0.1_i386.deb
b)	dpkg -i libsqlite3-0_3.7.2-1ubuntu0.1_i386.deb
c)	dpkg -i libsqlite3-dev_3.7.2-1ubuntu0.1_i386.deb

	SQLite将数据值的存储划分为以下几种存储类型：
    NULL: 表示该值为NULL值。
    INTEGER: 无符号整型值。(比较频繁)
    REAL: 浮点值。
    TEXT: 文本字符串，存储使用的编码方式为UTF-8、UTF-16BE、UTF-16LE。(比较频繁)
    BLOB: 存储Blob数据，该类型数据和输入数据完全相同。
	

	函数API
	int   sqlite3_open(char  *path,   sqlite3 **db)；
        功能： 打开sqlite数据库
        path： 数据库文件路径
        db：   指向sqlite句柄的指针   sqlite3 *db；
    	返回值:成功返回0，失败返回错误码(非零值)
	
	    int   sqlite3_close(sqlite3 *db);
	    功能：关闭sqlite数据库

	const  char  *sqlite3_errmg(sqlite3 *db);
         
    	 返回值：返回错误信息  //在调用api接口时产生错，可以通过这个函数了解到是什么错误

	typedef  int (*sqlite3_callback)(void *para, int f_num, char **f_value, char **f_name);
	功能：每找到一条记录自动执行一次回调函数

	      para：传递给回调函数的参数
	      f_num：记录中包含的字段数目
	      f_value：包含每个字段值的指针数组
	      f_name：包含每个字段名称的指针数组

	      返回值：成功返回0，失败返回-1

	int sqlite3_exec(sqlite3 *db, const  char  *sql,  sqlite3_callback callback, void *,  char **errmsg);
	    功能：执行SQL操作
        db：数据库句柄
        sql：SQL语句
        callback：回调函数
		void* ：给这个回调函数传递的参数
        errmsg：错误信息指针的地址
        返回值：成功返回0，失败返回错误码
		注意：没查询到一条记录都会调用callback一次。


	int   sqlite3_get_table(sqlite3 *db, const  char  *sql,  char ***resultp,  
							int*nrow,  int *ncolumn, char **errmsg);
	功能：	执行SQL操作
    db：	数据库句柄
    sql：	SQL语句
    resultp：用来指向sql执行结果的指针
    nrow：	满足条件的记录的数目
    ncolumn：每条记录包含的字段数目
    errmsg：错误信息指针的地址
    返回值：成功返回0，失败返回错误码


