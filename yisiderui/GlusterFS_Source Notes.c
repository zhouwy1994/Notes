=====================StudyonGlusterFSSource========================
						Author:Zhouwy
						Date:2017-05-24
======================================================================
GlusterFS工作时候共有四种应用程序需要运行，它们分别是gluster,glusterd,glusterfsd,glusterfs
其中glusterd,glusterfs为glusterfsd的链接文件，通过修改该应用程序名称，来区分不同的功能（代码内部根据执行文件名称走不同函数流程）。

1.gluster为cli命令行界面工具，即命令行执行工具，该应用负责把对glusterFS的操作请求发送到glusterd去执行。

2.glusterd为damon程序，该damon负责接收gluster发送过来的操作请求，并执行相关的操作，例如调用glusterfsd启动brick服务。

3.glusterfsd为服务进程，由glusterd启动。根据卷配置信息执行由glusterfs发送过来的请求。过通过rpc连接glusterd获取该服务的卷信息。

4.glusterfs为客户端程序。根据卷配置信息将fuse过来的操作请求逐层专递到最底层的的protocol/client translater上，该translater通过RPC与
与glusterfsd连接，将请求发送到glusterfsd服务端继续执行。过通过rpc连接glusterd

Glusterfs的数据传输都基于一棵translator(翻译器)树，该树是一个结构清晰的具有较强结构层次的树，树根节点在为fuse，
当有数据请求时，如ls -l，数据流向如下
ls -l --------> VFS(Virtual File System) -------->FUSE(User space File System) ---------->/dev/fuse ----------->client(fuse-translator树根节点)
当树根节点接收请求之后，向叶子节点发送指令，叶子节点受到命令后返回应答给树根节点，开始整个传输流程
每个节点都是一个 xlator_t 结构，生成的每个node都参考.vol配置文件
GlusterFS中重要的两个数据结构
glusterfs_ctx_t *ctx //ctx(context)程序上下文，也就算环境的意思，一般是存放一些全局的东西在里面，里面包含日志文件，日志级别，定时器，poll 类型等等，
//使用dict 实现。服务端和客户端可以使用守护进程方式（deamon 精灵），也可以作为应用程序来启动
struct _xlator//这个结构定义了每个 xlator_t节点的信息，以下内容
//a) 普通的数据处理函数指针（用于正常的数据处理）
//b) 回调函数指针，用于处理结果的返回。
//c) 管理类函数指针从源代码中可以看到， FUSE 对这三类指针的定义为空，因为 FUSE是树根节点，所以没有定义这些处理函数。
禅道安装
