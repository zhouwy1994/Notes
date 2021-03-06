*********Liunx 网络编程笔记 *******************、
第三章：文件系统简介
3.1liunx下的文件系统
在liunx下文件是一个很广的概念既包括磁盘上的数据文件，还包括一切设备，目录
UNIX下一切皆文件
UNIX下的文件类型
1、普通文件-
2、字符设备文件，比如像串口、控制台c
3、链接文件 软连接-l 硬链接就是普通文件
4、块设备文件 磁盘就是典型的块设备文件b
5、目录文件 目录d
6、管道文件p pipe
7、套接字文件 s  socket
fdisk -l 查看当前磁盘的状态
格式化分区mkfs 分区
挂载分区mount /dev/sta1 /mnt 挂载ada1分区
df -h 查看分区挂载情况
挂载文件系统：mount -t type destdir srcdev -o option
type 需挂载的文件系统类型 
挂载网络文件系统nfs
mount -t nfs 服务器地址:/目录 挂载点
Liunx下有两个主要概念来访问文件
1、inode索引节点,包含文件的一些信息，文件的唯一标识，硬链接的索引值和源文件的索引值相同
2、块(block)存放文件的主要内容
ls -i 最开始的那个为索引节点
ls -i | grep 节点号 //查找指定节点信息
ln 建立硬链接
ln -s 建立软连接
删除硬链接对源文件没有影响
删除源文件对硬链接也没有影响只会影响连接数 -wx-rwx-rwx 后面一位表示连接数
一、普通文件
linux下目录页属于普通文件
二、设备文件
/dev/装的大部分为设备文件 字符设备 块设备文件
c 字符设备文件：打印机，终端，显示器，绘图仪器(实时读取)
b 块设备文件 以固定大小读写，并且带有缓冲 硬盘软盘 
大部分情况下，字符设备都和特点的一个硬件或者硬件设备的某个物理分区相关联
但有的时候又不与设备文件关联，如/dev/null 黑洞，向里面添加文件时会默认吸收
虚拟文件系统：VFS  
Liunnx通过虚拟文件系统将所有不同的文件系统进行抽象
对内核提供统一的系统调用
文件的通用操作：
一、打开和创建文件(open/creat)
int open(const char *pathname, int flag, mode_t mode);
int open(const char *pathname, int flag);
int creat(const char *path, mode_t mode);
注意事项:
如果有O_CREAT 选项时必须要有mode存在
pathname不能超过1024字节否则后面会被截断取前1024字节
O_RDONLY O_WRONLY O_RDWR 互斥
O_APPEND 在文件末尾添加
O_TRUNC 文件存在则清空
O_NONBLOCK 打开文件为非阻塞方式**影响read和write 如果为非阻塞方式read and write将不阻塞
成功0 失败:EOF
擅用出错处理：习惯在出错处理中加__LINE__ __func__等信息
dup和dup2函数
int newfd =  dup(int oldfd);
将oldfd文件描述符复制到fd， 返回的是当前系统最小的文件描述符
成功后oldfd与newfd操作的是同一个文件，定位信息也是同步 成功返回新的文件描述符，失败-1
int copyfd = dup2(int newfd, int oldfd)
将oldfd的值赋值给cpoyfd,此时copyfd和newfd操作同一个文件
常用dup2(fd, 2);
int read(fd, void* buf, maxlen);
注意事项:
返回读到的字节,读到文件尾返回0，可以用作判断文件是否结束
while((ret = read(fd, buf, maxlen) > 0)来判断
条件不能为>=0不然一直死循环

int write(int fd, const void *buf, int maxlen);
write并不是能保证写成功，磁盘已满，异步写入
write也会将数据写入缓冲区，系统在合适的时机写入设备
如果在异步操作的情况下可调用fsync()函数将缓冲区的内容写入设备
int fsync(int fd);
失败 ：-1；
文件定位
lseek(int fd, off_t offset, int whence);
whence :
SEEK_SET 文件开始位置
SEEK_CUR 当前位置
SEEK_END 文件末尾
注意事项：
标准输入流不可以定位
空洞文件:
当定位位置超过了文件大小，不会报错
下次读写都在当前位置读写中间空余位置用'\0'填充
hello world \0 \0 \0  C++ dsd
以十六进制查看文件命令:od -c file***************
获取文件状态:
 int stat(const char *path, struct stat *buf);
 int fstat(int fd, struct stat *buf);
 int lstat(const char *path, struct stat *buf);
 struct stat {

        mode_t     st_mode;       //文件对应的模式，文件，目录等

        ino_t      st_ino;       //inode节点号

        dev_t      st_dev;        //设备号码

        dev_t      st_rdev;       //特殊设备号码

        nlink_t    st_nlink;      //文件的连接数

        uid_t      st_uid;        //文件所有者

        gid_t      st_gid;        //文件所有者对应的组

        off_t      st_size;       //普通文件，对应的文件字节数

        time_t     st_atime;      //文件最后被访问的时间

        time_t     st_mtime;      //文件内容最后被修改的时间

        time_t     st_ctime;      //文件状态改变时间

        blksize_t st_blksize;    //文件内容对应的块大小

        blkcnt_t   st_blocks;     //伟建内容对应的块数量

      };
	  mmap()函数用来将文件和设备文件映射到一段内存空间，通过对映射后的地址空间对文件进行统一的存取
	  就免去将我文件从磁盘读到内存，内存比磁盘要快，映射并不占用空间，只占用一段内存地址；
	  
	 void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);
	将文件描述符fd对应的文件中，自offset开始的一段长length的数据空间映射到指定内存中去
	可以自己指定要映射的地址，也可以置空NULL让系统去自己分配，成功返回映射到的地址，失败(void *)-1;
	参数prot表示操作的方式，可以复合使用
	PROT_EXE表示映射区可执行
	PROT_READ 映射区可读
	OROT_WRITE 映射区可写
	PROT_NONE 映射区禁止读写
	但是这和fd的打开方式有关，如果fd的打开方式为O_RDONLY，这PORT_WRITE就会失效
	flags MAP_SHARED|MAP_PRIVATE 必选其中之一
	MAP_SHARED 多个进程共享这段地址， MAP_PRIVATE 私有的
	
     int munmap(void *addr, size_t length);
	 解除映射addr为mmap的返回地址，length需要解除的长度
	 使用mmap应遵守一定的编程规则
	 1、通过open获得文件描述符
	 2、对fd进行映射
	 3、通过指针对这块内存进行操作
	 4、nunmap释放映射地址
	 
	 fcntl(file control 文件控制)用于获得或设置一个打开的文件的性质
	 int fcntl(int fd, int cmd); 
	 int fcntl(int fd, int cmd, long arg); 
	 int fcntl(int fd, int cmd, struct flock *lock);
	复制一个现存的描述符(cmd=F_DUPFD)
	获得/设置文件描述符标记(cmd=F_GETFD 或 F_SETFD) 
 	获得/设置文件状态标志(cmd=F_GETFL 或 F_SETFL) 
 	获得/设置异步 I/O 有权(cmd=F_GETOWN 或 F_SETOWN) 
 	获得/设置记录锁(cmd=F_GETLK,F_SETLK 或 F_SETLKW)
	struct flock {
             short l_type; /* 锁类型： F_RDLCK, F_WRLCK, F_UNLCK */
             short l_whence; /* l_start字段参照点： SEEK_SET(文件头), SEEK_CUR(文件当前位置), SEEK_END(文件尾) */
             off_t l_start; /* 相对于l_whence字段的偏移量 */
             off_t l_len; /* 需要锁定的长度 */
             pid_t l_pid; /* 当前获得文件锁的进程标识（F_GETLK） */
};

ioctl (input output control 输入输出控制)对设备文件的读写控制
进程和程序得最大区别：
1、进程是动态的，而程序是静态的
2、进程有一定的生命周期，而程序是一堆指令的集合本身就无运动的含义，没有建立
进程的程序不能作为一个独立的单位得到操作系统的认可；
3、一个进程只能对应一个程序，但一个程序可以对应多个进程

线程和进程之间的区别
1、进程是操作系统进行资源分配的基本单位，进程拥有完整的虚拟空间。进行系统资源分配时，除了CPU
资源外，不会给线程分配独立的资源，线程所需要的资源需要共享。
2、线程是进程的一部分，如果没有显式的线程分配，可以认为进程是单线程的，如果进程中建立
了线程，则可以认为系统是多线程的，
3、多线程和多进程是两种不同的概念，虽然两者都是并行完成功能，但是，多个线程之间像内存
、变量等资源在多个线程之间可以通过简单的方法来共享，多个进程则不同。进程间的共享方式有限。
进程和线程都有自己的控制表，进程有进程控制表PCB，系统通过PCB对进程进行调度，线程
有线程控制表TCB，但是TCB所表示的状态比PCB要少的多。
*****进程是计算机中运行的基本单位******
进程号是进程的唯一标识PID
pid_t getpid(void);
pid_t getppid(void)
pid_t 是一个 unsigned int

产生进程的方式：
1、进程复制fork(),fork()会以父进程为蓝本复制一个进程，产生的子进程只有内存和父进程不同
，其他的与父进程共享。
pid_t fork(void);
fork()的特点:执行一次返回两次，子进程和父进程返回的值不同

2、system()方式
system()函数调用bash执行特定的命令，阻塞当前进程知道命令执行完毕
int system(const char* string);
system()执行过程会调用fork(),execve(),waitpid等函数，其中任意一个调用失败
将导致system()函数执行失败
返回值:失败 -1
当sh不能执行 返回127
成功返回进程状态值
3、exec函数系列
使用fork和system或vfork函数时都会产生一个新进程，来执行调用者的操作
而原来的进程还会存在，而exec()族函数与之前的函数不同，exec会用新进程代替原有
的进程，系统会从新的进程开始执行，新的PID与原来PID相同
extern char **environ;
 #include <unistd.h>
extern char **environ;
int execl(const char *path,const char *arg, ...);
int execlp(const char *file,const char *arg, ...);
int execle(const char *path,const char *arg,..., char * const envp[]);
int execv(const char *path,char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execve(const char *file,char *const argv[],char *const envp[]);
只有execve才是真正的系统调用，其它的都是基于execve的封装的库函数
只有出错才会有返回值-1；
所有用户态进程都是由init产生，所有的进程都是父子或则堂兄弟关系的，没有哪个进程完全独立
IPC进程间通信(Inter-Process Communication)就是指多个进程之间相互通信，交换信息的方法。
Linux IPC基本上都是从Unix平台上继承而来的。主要包括最初的Unix IPC，System V IPC以及基
于Socket的IPC。另外，Linux也支持POSIX IPC。

vfork()
pid_t vfork(void);
1、fork()用于创建一个新进程。由fork()创建的子进程是父进程的副本。即子进程获取父进程数据
空间，堆和 栈的副本。父子进程之间不共享这些存储空间的部分。而vfork()创建的进程并不将父进
程的地址空间完全复制到子进程中，因为子进程会立即调用exec (或exit)于是也就不会存放该地址空
间。相反，在子进程调用exec或exit之前，它在父进程的空间进行。
子进程结束后向父进程发送SIGCHLD信号
父进程调用waitpid,wait来接收子进程返回状态
2、vfork()与fork()另一个区别就是：vfork保证子进程先运行，在调用exec或exit之前与父进程
数据是共享的,在它调用exec或exit之后父进程才可能被调度运行。
1. UNIX早期IPC：半双工管道、FIFO、信号；
2. system V IPC：System V消息队列、System V信号灯、System V共享内存区；
3. Posix IPC： Posix消息队列、Posix信号灯、Posix共享内存区；
4. 基于socket的IPC；

1、半双工管道:pipe
在Liunx下用|表示：如：ls-l | grep *c --将数据从管道的左边传到右边
int pipe(fd[2]);
***************
只有当管道写满是write才会阻塞
当管道没有数据时read会阻塞
而且管道(水管)都是按顺序读取
如果不希望是阻塞，则可通过fcntl(fd[1], SETFL, 0)进行设置
************************************
2.命名管道fifo(全双工通信)
fifo是一个在系统存在的特殊文件，不同进程之间可以通过这个特殊文件进行通信
创建管道：
int mkfifo(const char *pathname, mode_t mode);
FIFO总是处于阻塞状态，也就是说，如果打开管道时设置了读权限，则读一直会处于
阻塞状态，一直到其他进程打开管道并向管道写入数据，反过来也是成立的
如果不希望是阻塞，可在open时设置O_NONBLOCK选项，也可通过fcntl(fd, SETFL, 0)设置
打开读写的顺序没有要求(write, read)

3、消息队列message queue
消息队列是内核空间中的内部链表，通过Liunx内核在各个进程之间传递内容
不同的消息队列由不同的IPC标识符来区别，不同的消息队列是独立的，每个消息队列
又构成一个独立的链表
消息缓冲区结构struct msgbuf{
	long mtype;//消息类型
	char mtext[MAXLEN];//消息数据
}
mtype可以指定接收不同类型的人发来的数据
键值构建函数 ftok(const char *pathname, char proj_id);
pathname是一个必须存在的文件目录， 而proj_id 是一个char 的八位数, a, b;
如要成功通信，通信两段都必须有相同的键值，和消息队列id
消息队列创建函数int msgget(key_t key, int msgflg);
key为ftok()产生，也可以为IPC_PRIVATE用于创建当前进程的私有队列
msgflg为IPC_CREAT IPC_EXCL | 0666
IPC_CREAT不存在则创建，IPC_EXCL存在建立失败 0666 权限
成功返回msgid s失败-1

发送消息函数msgsnd()
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
msqid:由msgget获得
msgp：消息缓冲区结构体
msgse:消息数据长度
msgflg:IPC_NOWAIT不阻塞 0阻塞
成功0
失败-1
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,
                      int msgflg);
与上相同，msgtyp 0
注意返回成功是读到的字符数
消息队列控制函数msgctl()
 int msgctl(int msqid, int cmd, struct msqid_ds *buf);
 msqid:msg_id
 cmd:IPC_RMID:删除指定消息队列
4、信号量 Semaphore
信号量是一种计数器，用来控制对多个进程共享资源(临界资源((同时只能允许几个
进程访问的资源))进行的访问。他们常常被用作
一个锁机制，在某个进程正在访问特定资源时，信号量可以防止另一个进程去访问他，
生产者和消费者就是一个典型的例子(PV操作)，
P操作申请一个可用资源(如无可用资源则阻塞等待)(信号量+1)
V操作如有阻塞任务在等待资源，则唤醒阻塞任务，如无则释放一个可用资源)(信号量-1)
 信号量获取函数：semget
 int semget(key_t key, int nsems, int semflg);
 key为ftok()产生，也可以为IPC_PRIVATE用于创建当前进程的私有信号量
semflg为IPC_CREAT IPC_EXCL | 0666
IPC_CREAT不存在则创建，IPC_EXCL存在建立失败 0666 权限
成功返回semid s失败-1
 int semctl(int semid, int semnum, int cmd, union arg);
 semid:由semget获得
 semnum:信号量编号,只有使用到信号量集合时才用到，通常为0,就是取单个信号量
 cmd操作命令，但使用单个信号量时有以下几个命令
 IPC_STAT:获取该信号量的semid_ds结构
 IPC_SETVAL:将信号量的值设为arg的val值
 IPC_GETVAL返回当前信号量的值
 IPC_RMID：从系统中删除信号量
 int semop(int semid, struct sembuf *sops, unsigned nsops);
 union semun {
  int val;
  struct semid_ds *buf;   
  unsigned short  *array; 
  struct seminfo  *__buf; 
 };
 函数返回值根据cmd的值返回值不同
 出错-1
 int semop(int semid, struct sembuf *sops, unsigned nsops);
 semid:由semget获得
 struct sembuf{
  unsigned short sem_num;//信号量编号，使用单个信号量，通常取值为0
  short sem_op;//信号量操作，-1,P操作 +1V操作
  short sem_flg;//通常设置SEM_UNDO
 }
 
 nsops:操作数组sops中的操作个数，元素数目，通常取一，表示只有一个操作
 成功:信号量标识符，在信号量其他函数中都会使用该值
 出错:-1
 5、共享内存shared memory
 共享内存是IPC最快捷的方式，应为没用中间过程而管道，消息队列等需要建立一
 中间机制进行通信。而共享内存只需要对某段内存进行映射，多个进程共享一段
 内存空间；但是这样就要使用信号量进行通信控制
 int shmget(key_t key, size_t size, int shmflg);
 key为ftok()产生，也可以为IPC_PRIVATE用于创建当前进程的私有信号量
 shmflg为IPC_CREAT IPC_EXCL | 0666
 size 共享内存区大小
 IPC_CREAT不存在则创建，IPC_EXCL存在建立失败 0666 权限
 成功返回msgid s失败-1
 void *shmat(int shmid, const void *shmaddr, int shmflg);
 每个进程需要建立一次映射
 shmid:shmget获取的标识符
 shmaddr:将共享内存映射到指定地址，若为0则系统自动分配地址，并把该段地址
 映射到调用进程的地址空间
 shmflg:SHM_RDONLY 共享内存区只读
 0 可读可写
 成功：返回被引射的地址
 失败(void *)-1 
 解除共享内存映射(每一个进程需要解除一次)
 int shmdt(const void *shmaddr);
 被映射的共享内存段地址
 成功0
 失败-1
 共享内存控制函数
 int shmctl(int shmid, int cmd, struct shmid_ds *buf);
 与之上相同
 cmd：IPC__RMID删除共享内存区
 buf NULL
 附加知识:文件权限掩码umask
 默认为022 所建立的文件为(6-0,6-2,6-2)(644) 目录(7-0, 7-2, 7-2)(755)
 用命令umask可查看和修改
 IPC通信消息队列、信号量、共享队列使用和创建方法类似，通信时不同进程都是通过
 相同键值来的到相同的IPC——ID 通过这个id来通信
 共享内存是进程间通信最高效的方法，但是需要信号灯控制
 进程1
 P操作
 进程2
 V操作
6、信号signal()
 typedef void (*sighandler_t)(int);
 sighandler_t signal(int signum, sighandler_t handler);
 信号处理函数
 signal(int sig, void *func(int));
 GIGSTOP 和 SIGKILL
 不可忽略信号
 像单片机的中断，收到信号跳到信号处理函数;
  int kill(pid_t pid, int sig); 向别的进程发送信号
 raise(int sig)
 多线程机制
 windows和Liunx都用到了线程机制
 线程(thread)的优点
 1、系统资源消耗低
 2、速度快
 3、线程之间的共享比进程间容易的多
 
 Liunx下的多线程遵循POSIX标准，所以叫pthread;
 线程就是轻量级线程，进程和线程的区别
 线程创建函数
 void* (*start_routine) (void *);//线程执行函数
  int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
  void *(*start_routine) (void *), void *arg);
  功能：创建线程（实际上就是确定调用该线程函数的入口点），在线程创建以后，就开始运行相关的线程函数。
    说明：thread：线程标识符；
          attr：线程属性设置；默认NULL
          start_routine：线程函数的起始地址；
          arg：传递给start_routine的参数；
          返回值：成功，返回0；出错，返回-1。
线程退出函数
	void pthread_exit(void *retval);
	
用于等待一个线程结束函数
    int pthread_join(pthread_t thread, void **value_ptr);
	thread：等待退出线程的线程号。
	value_ptr：退出线程的返回值。pthread_exit(void *retval)
	线程共享子进程的代码段，数据段，但是不共享堆栈**************
	线程取消函数pthread_cancel(pthread_t thread);
	设置线程属性：pthread_attr_init()必须在create前使用
	 int pthread_attr_init(pthread_attr_t *attr);
	 attr：线程属性结构体，具体设置查资料pthread_attr_t attr
	 删除线程属性
     int pthread_attr_destroy(pthread_attr_t *attr);
	 线程优先级设置函数：先获取，在设置 
	  int pthread_attr_setschedparam(pthread_attr_t *attr,
                                      const struct sched_param *param);
      int pthread_attr_getschedparam(pthread_attr_t *attr,
                                      struct sched_param *param);
	 struct sched_param {
               int sched_priority;     //优先级1-256
           };
线程的分离状态：正常分离，非正常分离，正常分离是用等待函数pthread_join()
等待函数正常释放资源，当设置相应分离参数后，不用使用等待结束函数也能正常
释放资源
线程间互斥：
 int pthread_mutex_destroy(pthread_mutex_t *mutex);//互斥销毁函数
       int pthread_mutex_init(pthread_mutex_t *restrict mutex,//互斥初始化函数
              const pthread_mutexattr_t *restrict attr);
       pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;初始化宏定义
 int pthread_mutex_lock(pthread_mutex_t *mutex);//锁定互斥
 int pthread_mutex_trylock(pthread_mutex_t *mutex);//互斥预锁定(锁定互斥的非阻塞版本)
 int pthread_mutex_unlock(pthread_mutex_t *mutex);解锁互斥
 pthread_mutex_lock是阻塞的，当他尝试锁定一个被锁定资源时就会发生阻塞
 只有等此资源解锁后才可再加锁，而trylock不会阻塞，当他尝试去锁定一个已经被锁定
 临界资源时，就不会阻塞，理解返回一个提示信息，正常锁定则返回0
 互斥过程
 pthread_mutex_lock(pthread_mutex_t *mutex)
 临界资源
 pthread_mutex_unlock(pthread_mutex_t *mutex);
 
 线程间信号量(semaphore)
 线程间信号量和和进程间信号量类似，但是线程的信号量可以高效的完成基于线程的资源计数
 信号量其实是一个非负整数，用来实现对公共资源的控制，在公共资源增加的时候，
 信号量值增加，反之减少，只有当信号量大于0时，才能访问信号量所代表的资源
 主要函数:
 #include <semaphore>
 线程信号量初始化：
 int sem_init(sem_t *sem, int pshared, unsigned int value);
 初始化信号量:sem信号量结构的一个指针， pshared用于表示信号量的类型
 不为0则代表在不同进程间共享，为0是表示只能在当前进程的多个线程内共享
 value 用于设置信号量初始化时候信号量的值
 
 线程信号量增加函数：
  int sem_post(sem_t *sem);
此函数使信号量加一
线程信号量等待(减少)函数
 int sem_wait(sem_t *sem);
 当信号量的值为0时阻塞，等到信号量值不为0时将信号量减一
 int sem_trywait(sem_t *sem);
以上函数的非阻塞版本
还有一个超时非阻塞函数
线程信号量销毁函数
 int sem_destroy(sem_t *sem);
销毁线程信号量
获得信号量的值函数
 int sem_getvalue(sem_t *sem, int *sval);
sval当前信号量的值
步骤:
1、初始化信号量
2、增加信号量
临界资源
3、减少信号量
4、销毁信号量
**********************************************************************
网络部分
一、网络结构模型
OSI标准模型(开放互联模型)
这种结构模型有助于更清晰地了解网络协议内部的架构；
ISO/OSI开放互联模型采用7层结构
——————————————————————————————————————————————
应用层<-------应用层协议------->应用层
——————————————————————————————————————————————
表示层<-------表示层协议------->表示层
——————————————————————————————————————————————
会话层<-------会话层协议------->会话层
——————————————————————————————————————————————
传输层<-------传输层协议------->传输层
——————————————————————————————————————————————
网络层<-------网络层协议------->网络层
——————————————————————————————————————————————
数据链路层<---数据链路层协议------->数据链路层
——————————————————————————————————————————————
物理层<-------物理层协议------->物理层
——————————————————————————————————————————————
主机A                            主机B

在OSI七层协议中，每一层与本层的上下两层从逻辑上是分开的，这种
方式使得每一层为上层提供服务，依赖于下层的数据并为上一层提供接口
同时各层之间又是相互独立，例如数据格式，通信方式等，着称为本层协议
物理层的传输数据比特流(按位传输)
TCP/IP协议栈

————————————————————————————————————————————————————————————
   应用层 |Telent FTP HTTP P2P | SAMP TFTP NFS P2P
————————————————————————————————————————————————————————————
   传输层 |       TCP          |        UDP
————————————————————————————————————————————————————————————
   网络层 |  ARP |                 IP    |ICMP
————————————————————————————————————————————————————————————
          |以  令|TDDI  HDLC  PPP
   网络接 |太  牌|------------------------------------------
   口层   |网  网|802.2     802.3
————————————————————————————————————————————————————————————
应用层：Http、Telnet、FTP和e-mail等 负责把数据传输到传输层或接
收从传输层返回的数据

传输层 TCP和UDP 主要为两台主机上的应用程序提供端到端的通信，
TCP为两台主机提供高可靠性的数据通信。它所做的工作包括把应用程序
交给它的数据分成合适的小块交给下面的网络层，确认接收到的分组，
设置发送最后确认分组的超时时钟等。UDP则为应用层提供一种非常简单
的服务。它只是把称作数据报的分组从一台主机发送到另一台主机，但并
不保证该数据报能到达另一端。

网络层 ICMP、IP 和 IGMP 有时也称作互联网层，主要为数据包选择路由，
其中IP是TCP/IP协议族中最为核心的协议。所有的TCP、UDP、ICMP及IGMP
数据都以IP数据报格式传输

 网络接口层：ARP 、RARP和设备驱动程序及接口卡 发送时将IP包作为帧发送；
接收时把接收到的位组装成帧；提供链路管理；错误检测等
*******************
IP头 : 20个字节
TCP头: 20Byte
UDP头: 8Byte
ICMP头 8Byte
以太网头: 14Byte
MTU(最大传输单元)1500-46
****************************************
IP协议(网际协议):
IP层的功能：
数据传输：将数据从一个之际传到另一个主机
寻址：根据子网划分和IP地址，发现正确的主机地址
路由选择：选择数据在互联网上的传输路径
数据报文的分段：当传输数据大于MTU时，将数据进行分段发送和接收
并组装。
***************************************
网际控制报文协议(ICMP)
ICMP：用于发送网络的诊断，错误，控制信息。就是一个“错误侦测与回报机制”，
其目的就是让我们能够检测网路的连线状况﹐也能确保连线的准确性

ICMP协议的数据位于IP字段的数据部分，他是在IP报文的内部被传输的
|<---------------IP数据报文------------------------->|
| IP头部(20Byte)            |       ICMP报文                 
-----------------------------------------------------
0------7--8--------15-16------------------------------
类型(8b)|代码(8b)      |          校验和(16b)
-------------------------------------------------------
ICMP报文头(8Byte)
******************************************
TCP协议(传输控制协议)
TCP是一种基于IP协议的可靠传输协议
|<---------------IP数据报文------------------------->|
                |<-------TCP数据-------------------->
| IP头部(20Byte)|TCP头部(20Byte)|TCP数据                 
-----------------------------------------------------

TCP协议的主要功能是完成对数据报的确认、流量控制和网络拥塞；
自动检测数据报，并提供错误重发的功能；将多条路径传送的数据
报按照原来的顺序进行排列，并对重复数据进行择取；控制超时重发，
自动调整超时值；提供自动恢复丢失数据的功能。(可靠传输协议)

TCP建立连接的三次握手
          建立TCP连接
主机A------------------------->主机B
A----------SYN(1234)---------->B(1)
A<---------SYN(9876)-----------B(2)
A<---------ack(1234 + 1)-------B(2)
A----------ack(9876 + 1)------>B(3)
(1)主机A发送一个SYN段告诉主机B想要连接的端口，以及初始
的序列号(ISN 1234) 'u7
(2)主机B应答，主机B向A发送一个应答位ack,ack为主机A的
ISN + 1,并发送SYN段请求连接A
(3)主机A将主机B发送过来SYN段加1作为确认号返回给主机B作为
应答
以上三个步骤完成TCP连接，建立连接后，主机A和主机B就可以
进行TCP的数据的接收和发送了

释放TCP的四次握手
A----------FIN(1234)---------->B(1)
A<---------ack(1234 + 1)-------B(2)
A<---------FIN(9876)-----------B(3)
A----------ack(9876)---------->B(3)

TCP的封装和解封过程:
    |                                       解封
    |                    |数据              /|\
    |               TCP头|数据               |
    |          IP头|TCP头|数据			     |
	| 以太网头|IP头|TCP头|数据|以太网尾部    |
   \|/                                       |
   封装                                      |
当网络接口层接收到以太网数据时，去除以太网头部和尾部
，进行CRC校验后，发送给网络层，取出IP头，对数据进行
校验，发送给传输层，TCP层取出TCP头，根据应用程序的的
标识符确定是否要发送此数据给应用程序，封装是解封的一个
相反过程
用户数据报文协议(UDP)
UDP是一种基于IP协议的不可靠网络传输协议
|<---------------IP数据报文------------------------->|
                |<-------udp数据-------------------->
| IP头部(20Byte)|udp头部(8Byte)|udp数据                 
-----------------------------------------------------
地址解析协议(ARP协议)(相反协议RARP逆地址转换协议)
在以太网为基础的局域网中，每个网络接口都有一个硬件地址，这是一个
48b的值，标识不同的以太网设备，在局域网中的必须知道网络设备的硬件地址
才能向目的主机发送数据。而在网际网中数据传输的目的地址是IP，数据要能
真正传输，必须建立IP地址和硬件地址之间的对应关系，ARP就是起这个作用
ARP--------------------->48b的硬件地址
********
IP地址分类与TCP/UDP端口
目前使用最为广泛的IP地址是IPv4(IP第四版本)长度32b，用4组十进制表示，点分二进制
IP地址的组成:类别 + 网络号 + 主机号
IP地址通常分为5类A、B、C、D、E
A类:网络号占一字节，最高位为0，这样就有127个网络，主机号占用3字节每个网络可容
纳1670万台主机(超大型大型网络)
B类：最高两位10，网络标识占用14位，最后2字节为主机号(大型网络)
C类：最常见的IP地址，最高位110，网络好占用三字节，主机号一字节(小型局域网)
D类：最高位1110，剩下28b为多播地址，此类地址用于组播，例如路由器修改，视频会议等
E类：最高位1111，此类地址为保留地址，目前没有使用
开始字段值:A:000~127 B:128~191 C:192~233 D:234~239  E：240~255
特殊IP地址
主机号全为0,192.168.1.0 他不分配给任何主机，仅用于某个网络的网络地址。例如192.168.1.0
其中主机为192.168.1.1!192.168.1.254
主机号全为1，192.168.1.255，这个地址不分配给任何主机，仅用作广播地址，发送给此地址的数据将会被
该网络中所有的节点接收
IP地址32b全为1，255.255.255.255，为有限广播地址，这个地址常用在无盘工作站启动时启用
IP地址全为0，代表主机本身，发往此的数据，由本机接收
IP地址为127.0。0.1的地址是一个特殊的回环接口，他常用在本地软件测试，Liunx下的
etc/hosts,其中一行代码定义了localhost的IP地址
127.0.0.1 localhost

*******
子网掩码：32b字段，利用此字段来屏蔽原来网络地址的划分情况
从而获得一个范围较小的，可以使用的网络
子网掩码使用点分十进制，其中为0的部分对应于IP地址的主机ID部分，
值为1的部分为网络地址部分，与IP进行相与后，得到的值为为网络地址
和子网地址，主机ID将不存在，利用此特性可判断两个网络是否在是否
在同一个子网
3类网的子网掩码：
A:255.0.0.0
B:255.255.0.0
C：255.255.255.0
Liunx更改IP和Mask命令:ifconfig eth0 192.168.3.250 netmask 255.255.255.128
*****
端口号
端口号是操作系统标识应用程序的一种方法，如果是一个服务程序，则需要与一个端口绑定
这样客户端才可以根据此端口来与客户端交互数据了
**************
主机字节序和网络字节序
字节序：是指整数在内存中保存的顺序
主机字节序:大端(X86)和小端(POWPC)
网络字节序:标准为大端模式,不同平台会对主机字节序进行转换，转换成网络字节序
后再进行转换，接收到网络数据再转换成主机字节序
htons：把unsigned short类型从主机序转换到网络序
htonl：把unsigned long类型从主机序转换到网络序
ntohs：把unsigned short类型从网络序转换到主机序
ntohl：把unsigned long类型从网络序转换到主机序
实质上就是大小端的转换

****************
应用层网络服务简介
HTTP(超文本传输协议)建立在TCP协议基础上的当前使用最广泛的一种协议，实现客户端到服务器(Web服务器)之间的
数据传输
HTTP协议的内部过程
交换信息的四个过程
	   
客户端     <-------建立连接------>   服务器
客户端     ---------请求--------->   服务器
客户端     ----------响应---------   服务器
客户端     --------关闭连接-------   服务器

FTP(文件传输协议)建立在TCP协议上的历史悠久的一种文件传输协议，至今任然流行。
FTP协议的步骤
1、用户通过FTP接口输入命令，让FTP客户端连接远方的FTP服务器主机
2、连接成功后，远程主机要求客户端输入用户名和密码，在得到验证后，
进入正常的FTP下载过程
3、余本地文件系统相似，可以在远程FYP服务器上进行文件目录的转换
进入合适的目录，进行相关操作
4、对目标文件的下载，需要使用FTP的特定命令格式，才能被正确解析
5、文件传输成功后，客户端关闭与服务器之间的TCP连接

Ubuntu构建ftp服务器
1、sudo apt-get install vsftpd (安装ftp服务器) vsftp(Very Secure FTP)
是一种在Unix/Linux中非常安全且快速稳定的FTP服务器 
2、vsftp会自动建立一个用户ftp 设置密码命令sudo passwd ftp
3如果vsftp没有自动建立用户，自己添加一个用户ttp sudo useradd ftp 并设置密码
4、修改默认端口，默认为21，为了安全，可修改/etc/services文件(这个文件包含了
UNIX/Liunx下的服务器的所有默认端口port)
5、修改vsftpd配置文件vsftpd.conf 添加默认指定端口Listen_port=21
6、启动FTP服务service vsftpd restart 检查FTP服务service vsftpd status
FTP有两种工作模式(主动模式，被动模式)，在FTP工作时开启两个端口命令端口
数据端口，主动模式，客户端服务器建立连接后，客户端告诉服务器我开辟了数据端口
，你就往这个端口发数据吧，被动模式，建立连接后服务器告诉客户端我开辟了一个数据端口
你自己来下载
Liunx创建一个新用户(建了一下午)
useradd -m -s /bash/bash -g usergroup -G othergroup username
passwd username
groupadd usergroup
*****************
telnet远程登陆协议 基于TCP协议
telnet远程登陆协议是TCP/IP协议族中的一种，使用TELNET协议能够把本地用户所使用的主机
变成远程主机的一个终端
安装telnet服务器
1、先要安装xinetd(超级Internet超级守护进程)因为telnet是通过xinetd来管理的
2、安装telnet server apt-get install telnetd
3、配置相应文件
4、重启配置文件sudo /etc/init.d/xinetd restart
*******************
NFS协议其实是一个比较简单的协议，他本身没有提供信息传输的协议和功能，之所以
NFS能够让主机之间进行资源共享，这是因为NFS使用了一些其他传输的协议，主要用到
了RPC功能所以启动NFS服务器的时候需要启动PRC服务
安装NFS服务器步骤
1、安装nfs-kernel-server sudo apt-get install nfs-kernel-server
2、配置 /etc/exports 格式:共享目录 主机名称或IP(参数1， 参数2)
3、重启配置文件
4、在客户端挂载服务器上的共享目录 mount -t nfs 主机名或主机IP地址:共享目录 要
挂载的目录
Liunx清空防火墙命令:iptables -F
*****************************
TCP编程
进行套接字编程需要指定套接字的地址作为参数，不同的协议族有不同的地址结构
定义方式，这些地址结构通常以sockaddr_开头，每一个协议族都有一个唯一的后缀，
以太网后缀in，socketaddr_in
通用套接字地址类型定义，他可以在不同的协议族上进行强制转换
struct sockaddr{
	as_family_t sa_family; //协议族
	char sa_data[14];  //协议族数据
}
以太网socketaddr_in
struct sockaddr_in { 
　　 short int sin_family; //协议族类型
　　 unsigned short int sin_port; //端口号(需转换成网络字节序)
     struct in_addr sin_addr;  //ip地址(需转换成网络字节序)
 unsigned char sin_zero[8]; //保留未用
}
struct in_addr { 
    unsigned long s_addr; //ip地址
           }
基于TCP（面向连接）的socket编程，分为客户端和服务器端。



服务器端的流程如下：

（1）创建套接字（socket）
int socket(int domain, int type, int protocol);//成功返回套接字描述符.出错返回-1
TCP：(AF_INET, SOCK_DGRAM, 0)
UDP：(AF_INET, SOCK_STREAM, 0)
（2）将套接字绑定到一个本地地址和端口上（bind）
int bind(int sockfd, const struct sockaddr *addr, socklen_t len);//成功返回0.出错返回-1
    bind函数用于将地址绑定到一个套接字。服务器需要给一个接收客户端
	请求套接字绑定一个众所周知的地址，而客户端可以让系统选一个默认
	地址绑定(无须绑定)。
	AF_UNIX用于建立本地套接字，用于本地通信，地址为一个套接字文件
	socklen_t len = sizeof(struct socketaddr)
（3）将套接字设为监听模式，准备接收客户端请求（listen）
int listen(int sockfd, int backlog);//成功返回0，出错返回-1
    一旦服务器调用listen，套接字就能接收连接请求。backlog用
	于表示该进程所要入队的连接请求数量，实际值由系统决定，但
	上限由SOMAXCONN指定。一旦队列满，系统会拒绝多余连接请求。
	排队的过程
	listen只支持SOCK_STREAM SOCK_SEQPACKET
	不支持SOCK_GDRAM
（4）等待客户请求到来；当请求到来后，接受连接请求，
     返回一个新的对应于此次连接的套接字（accept）
//成功返回套接字描述符，出错返回-1
int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict len);
（5）用返回的套接字和客户端进行通信（send/recv）
recv send write read
（6）返回，等待另一个客户请求。

（7）关闭套接字。
 close(int socket);
 int shutdown(int sockfd, int how);
 可以用更多的方式来关闭套接字，允许单方向切断通信或切断双方的通信
 sockfd 打开套接字
 how：关闭的方式
 SHUT_RD 值为0， 切断读，以后不能对此套接字进行读
 SHUT_WR 值为1， 切断写，以后不能对此套接字进行写
 SHUT_RDWR 值为2， 切断读写，以后不能对此套接字进行读写与close相同

客户端的流程如下：

（1）创建套接字（socket）

（2）向服务器发出连接请求（connect）
//成功返回0，出错返回-1
int connect(int sockfd, const struct sockaddr *addr, socklen_t len);
    addr是想与之通信的服务器地址，如果sockfd没有绑定到一个地址，connect
	会给调用者绑定一个默认的地址。成功连接需要以下条件：要连接的机器开启
	且正在运行，服务器绑定到一个想与之连接的地址，服务器的等待连接队列有
	足够的空间。
（3）和服务器端进行通信（send/recv）

（4）关闭套接字
               三次握手
connect -------------------------->accept

SIGPIPE信号
如果正在读写套接字的时候，当读取段段关闭，可以得到一个SIGPIPE信号，信号SIGPIPE
会终止该进程，这时资源还没释放，所以需要编写相应的信号处理函数来处理这些资源
例如当服务器意外关闭，此时客户端尝试向服务器写入时会得到SIGPIPE信号
SIGINT(ctrl + C)
也可设置信号处理函数来释放资源

*******************
字节序问题：
计算机上根据不同的处理器，数据有不同的存储方式
但是网络上传输的数据必须是大端字节序，所以在传输时就需要转换
字节序转换函数
 uint32_t htonl(uint32_t hostlong);  //主机字节序到网络字节序的长整型转换
 uint16_t htons(uint16_t hostshort)  //主机字节序到网络字节序的短整型转换
 uint32_t ntohl(uint32_t netlong);  //网络字节序到主机字节序的长整型转换
 uint16_t ntohs(uint16_t netshort);  //网络字节序到主机字节序的短整型转换
这些函数其实就是一些字节序的转换函数，他就是一个倒置字节序的函数。
value = 0x12345678 htonl(value) = 0x78563412
字符串IP地址和二进制IP地址的转换：

int inet_aton(const char *cp, struct in_addr *inp);
in_addr_t inet_addr(const char *cp);
in_addr_t inet_network(const char *cp);
char *inet_ntoa(struct in_addr in);
struct in_addr inet_makeaddr(int net, int host);
in_addr_t inet_lnaof(struct in_addr in);
in_addr_t inet_netof(struct in_addr in);
 typedef uint32_t in_addr_t;
  struct in_addr {
	  in_addr_t s_addr;
  };

 由于inet_addr()会返回-1和255.255.255.255相同，这在网络通信中不安全
 所以有比较完善的转换函数
 int inet_pton(int af, const char *src, void *dst);
af：网络协议族
src:源地址,点分十进制
dst：struct in_addr 指针

 const char *inet_ntop(int af, const void *src,
                             char *dst, socklen_t size);
与pton相反返回指向dst的地址，size为缓冲区大小要能够装下dst >= 15
判断文件描述符是否套接字描述符，可以利用函数fstat(fd, &st) 获得描述符状态
再和S_IFMT 向与是否等于S_IFSOCK
DNS域名系统
IP地址的别名
gethostbyname()根据主机名或IP地址获取主机信息，例如www.baidu.com,使用
gethostbyname("www.baidu.com")获取信息
struct hostent *gethostbyname(const char *name);
struct hostent *gethostbyaddr(const void *addr,socklen_t len, int type);
struct hostent 存放主机信息的结构体类型，需要时查询
 struct hostent {
               char  *h_name;            /* official(官方) name of host */
               char **h_aliases;         /* alias list(别名列表) */
               int    h_addrtype;        /* host address type */
               int    h_length;          /* length of address */
               char **h_addr_list;       /* list of addresses(地址列表) */
           }
可重入函数和不可重入函数：
可重入函数主要用于多任务环境中，一个可重入的函数简单来说就是可以被中断的函数，
也就是说，可以在这个函数执行的任何时刻中断它，转入OS调度下去执行另外一段代码，
而返回控制时不会出现什么错误；而不可重入的函数由于使用了一些系统资源，比如全
局变量区，中断向量表等，所以它如果被中断的话，可能会出现问题，这类函数是不能
运行在多任务环境下的。
不可重入函数，函数调用完毕后要及时取出结果
协议族处理函数：
xxxprotoxxx函数
可通过函数获得协议的名称，编号，和协议类型。
*****************************************************************************
数据的IO和复用
IO函数
recv:用于接收数据，recv函数从套接字接收数据放到缓冲区buf中，
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
sockfd:套接字描述符
buf:接收信息的缓冲区
len:指定接收的大小，
flag:接收消息的方式，常用0，非阻塞方式MSG_DONTWAIT,即使没有数据也立即返回
MSG_ERRQUEUE:错误消息从套接字错误队列接收
KSG_TRUNC:返回所有数据，及时指定缓冲区过小
MSG_WAITALL:等待所有消息，阻塞方式
返回值是成功接收到的字节数，返回-1时发生错误
recv()函数从内核的接收缓冲区中复制数据到指定缓冲区，当内核中的数据比指定的缓冲区小时，
一般情况下(没有采用WAITALL选项时)会复制缓冲区中所有数据到用户缓冲区，并返回数据长度
当内核数据比指定len大时，会将用户指定长度len的接收缓冲区中的数据复制到用户指定地址
其余的数据等下次接收时再复制，内核在复制用户指定数据后，***//会销毁已经复制完毕的数据，
并进行调整
send()用于发送消息，
 ssize_t send(int sockfd, const void *buf, size_t len, int flags);
sockfd:套接字描述符
buf:接收信息的缓冲区
len:指定接收的大小，
flag:常用0非阻塞
readv用于接收多个缓冲区数据，函数原型:
 ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
 fd:文件描述符
 iov:接收消息缓冲区结构体
  struct iovec {
               void  *iov_base;    /* Starting address */
               size_t iov_len;     /* Number of bytes to transfer */
           };
iovcnt:需要接收的块数
在调用readv时必须先指定iovec的iov_base长度，放在iov_len中，count整个内存区大小
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
与上相同
返回-1错误，成功返回接收/发送的字节数
以下两函数与readv()和writev使用方式相同，只不过接收缓冲区的结构体不同
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
IO函数比较：
1、read()/write()和readv()/writev()可对所有文件描述符使用；recv()/send()/
recvfrom()/sendto()/recvmsg()/sendmsg()只能操作套接字描述符
2、readv()/writev()/recvmsg()/sendmsg()可操作多个缓冲区，其他操作单个缓冲区
3、recv()/send()/recvfrom()/sendto()/recvmsg()/sendmsg()有可选标志flag;
4、recvfrom()/sendto()/recvmsg()/sendmsg()可指定对方IP地址

//IO模型：IO的方式有阻塞IO,非阻塞IO，IO复用，信号驱动IO，异步IO等
1、阻塞IO模型：最常见的IO模型，使用这种模型进行数据接收的时候，在数据没到来之前会
一直阻塞，直到内核有数据到来。

2、非阻塞IO：常见的IO模型，使用这种模型进行数据接收的时候，在数据没到来会返回一个
错误而不阻塞，这种模型往往需要轮询检测

3、复用IO：使用IO复用模型可以在等待是加入超时检测，当时间没有达到又没有数据，阻塞，
超时没数据，非阻塞

4、信号驱动IO：信号驱动IO在进程开始的时候注册一个信号处理回调函数，进程继续执行，当
有数据到来时，产生SIGIO信号，回调信号处理函数调用接收数据函数进行数据接收

5、异步IO：异步IO和信号驱动IO相似，信号驱动IO是数据到来时产生信号，而异步IO是
内核完成数据复制时才产生信号

select和pselect函数用于IO复用，它们监视多个文件描述符的集合，判断是否有符合条件
的事件发生
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
注意事项：
把关心的文件描述符添加FD_SET(fd, fd_set *)进集合
进行轮询select()将知道是那个描述符发生了改变,select将改变了的置一，
然会检测我们关心的集合有没有改变，FD_ISSET(fd, fd_set*) 
改变了就去执行相应的操作
注意细节
pselect()函数		
 int pselect(int nfds, fd_set *readfds, fd_set *writefds,
                   fd_set *exceptfds, const struct timespec *timeout,
                   const sigset_t *sigmask);
比select多了一个sigmask,当sigmask==NULL 时和select一样
与信号处理有关
poll函数(水平触发方式)
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

非阻塞编程：
fcntl(fd, F_SETFL, NONBOLCK);
非阻塞网络编程需要使用轮询，占用CPU，不推荐使用

*********************************************
基于UDP的编程
UDP(用户数据报协议)是一种无连接，不可靠的网络协议
UDP编程架构:
          server(UDP) 											client(UDP)
          -----------											-----------
		    socket()            								 socket()  
		  ----------- 											-----------                               
			   |													|
			   |													|
			  \|/												    |				
		  -----------												|		
		    bind()(必须绑定服务器地址)													|					
		  -----------												|														
			   |													|	
			   |													|		
			  \|/												   \|/									  
		  -----------						客户端请求		  -----------						
		  recvfrom()(阻塞：收到客户端数据)<-------------------	sendto()									
		  -----------										   -----------						
			   |													|													
			   |(处理请求)													|							
			  \|/												   \|/										  
		  -----------				服务器应答				    -----------					
		   sendto()	------------------------------------------->recvfrom()					
		  -----------										    -----------						
			   |													|									
			   |													|						
			  \|/												   \|/					  
          -----------										    -----------					
		   close()												 close()							
		  -----------											-----------							  
注意：使用套接字类型，SOCK_DGRAM
注意recvfrom 最后一个参数是地址传递
 ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);
udp中不存在pipe信号，因为是无连接的
UDP在传输过程中会发生的问题及解决策略

UDP会发生数据报丢失，如果在发送数据包过程中发生数据报丢失，有一方的recvfrom()
将一直阻塞，
解决对策：设置超时检测

UDP会发生数据乱序：由于路由器的存储转发和路由的路径选择会导致数据乱序
解决对策：对于乱序解决方法可采用在发送端的数据段中加入数据报序号的方法，这样在
接收端进行简单的处理就可以重新获得原始的顺序

缺乏流量控制机制
UDP在接受到数据到来时会放入缓冲区，当缓冲区满时，后面来的数据会覆盖之前的数据，
造成数据丢失，TCP当缓冲区满时，发送过程将发生阻塞

****************************************************
高级套接字
UNIX域的协议族是在同一台计算机上的客户端/服务器通信时使用的一种方法。
查找指定头文件里的头文件定义 find /usr/include/ *.h | xargs grep "sockaddr_un"
通常Linux长放头文件文件夹/usr/include/ /usr/include/Linux/ usr/include/sys/
哈希表(Hash Table)：就是通过key建立一个与key相关的位置对应关系，通过对应关系(f：哈希函数)
查找
可能通过哈希函数得到多条符合信息(冲突)
要有处理冲突的的适当方法
哈希表的两个重要任务：
1、建立合适的哈希函数(Hash)
2、建立冲突处理方法

***************************************
设置套接字选项
在进行网络编程的时候，经常需要查看或设置套接字的特性，例如设置地址复用
、读写数据的超时时间、对读写缓冲区大小进行调整
 int getsockopt(int sockfd, int level, int optname,
                      void *optval, socklen_t *optlen);
 int setsockopt(int sockfd, int level, int optname,
                      const void *optval, socklen_t optlen);
opt(含义:option)
参数：sockfd 网络套接字
level：选项所在协议层，套接字层：SOL_SOCKET, TCP层：TCP
optname:选项名称；
optval：操作内核缓冲区。对于getsockopt指向用于获取返回选项的缓冲区
对于setsockopt，指向设置缓冲区大部分选项的数据类型为int，部分为结构体
optlen：第四个参数的长度，对于getsockopt，地址传递，因为是获取参数
所以len用于装缓冲区最大长度
成功:0 失败:-1

***
套接字选项:(三大类)
1、通用套接字选项 level的值为SOL_SOCKET， 用于设置一些或获得一些通用的参数
，例如接收缓冲区大小，地址重用等等
2、IP选项,level：IPPROTO_P ,用于设置或获取一些IP层参数
3、TCP选项：参数level值为IPPROTO_TCP 用于获得或设置一些TCP协议层的一些参数

SOL_SOCKET协议族选项：该协议族可用的选项较多，SO_BROADCAST, SO_KEEPALIVE
SO_LINGE, SO_OOCIMLINE

1、SO_BROADCAST选项
该选项用于进行广播设置，Linux默认情况下广播是关闭的，因为容易造成网络
灾难。这是要打开广播，设置optval为1(允许)0(禁止)

2、SO_DEBUG选项：该选项表示允许调试套接字，此选项仅支持TCP套接字

3、SO_DONTPOUTE：不经过路由选项
该选项设置的套接字发出的数据不经过正常的路由机制，分组将安装发送的
目的地址和子网掩码，选择一个合适的网络接口进行发送

4、SO_ERROR选项，只能获得，不能设置

5、SO_KEEPALIVE保持连接选项
该选项用于设置TCP连接的保持，当此选项设置后，连接会测试连接状态
，这个选项用于可能长时间没有数据的连接，，通常只会在服务器设置，

struct ifreq 用来配置ip地址，激活接口，配置MTU等接口信息的。其中包含了一个接
口的名 字和具体内容——（是个共用体，有可能是IP地址，广播地址，子网掩码，
MAC号，MTU或其他内容）。ifreq包含在ifconf结构中。而 ifconf结构通常是用
来保存所有接口的信息的。

路由器,交换机,集线器
集线器:将零散的计算机组成一个局域网
交换机:作用与集线器大体相同。但是两者在性能上有区别：集线器采用的式共享带宽的工作方式，而交换机是独享带宽。(两层交换机，三层交换机)
路由器:接不同的网段并且找到网络中数据传输最合适的路径

创建守护进程的步骤:
1.创建子进程，父进程退出fork
2.创建新会话 setsid()
3.改变工作目录 chdir()
4.改变权限掩码 umask( )
5.关闭文件描述符 close();

C语言宏定义,
#define _SOCKADDR_COMMON(sa_perfix) sa_family_t sa_perfix##family
##//表示连接
_SOCKADDR_COMMON(sun_) 表示 sa_family_t sun_family


















 
 

















































































