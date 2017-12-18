==========================Study On Ceph =================================================

不管你是想为云平台提供Ceph 对象存储和/或 Ceph 块设备，还是想部署一个 Ceph 文件系统或者把 Ceph 作为他用，所有 Ceph 存储集群的部署
都始于部署一个个 Ceph 节点、网络和 Ceph 存储集群。 Ceph 存储集群至少需要一个 Ceph Monitor 和两个 OSD 守护进程。而运行 Ceph 文件系
统客户端时，则必须要有元数据服务器（ Metadata Server ）。
		OSDs ---------------  Monitor ------------Metadata Server(MDS)

1.Ceph OSDs: Ceph OSD 守护进程（ Ceph OSD ）的功能是存储数据，处理数据的复制、恢复、回填、再均衡，并通过检查其他OSD 守护进程的心
跳来向 Ceph Monitors 提供一些监控信息。当 Ceph 存储集群设定为有2个副本时，至少需要2个 OSD 守护进程，集群才能达到 active+clean 状态
（ Ceph 默认有3个副本，但你可以调整副本数）。
2..Monitors: Ceph Monitor维护着展示集群状态的各种图表，包括监视器图、 OSD 图、归置组（ PG ）图、和 CRUSH 图。 Ceph 保存着发生在Monitors 、
 OSD 和 PG上的每一次状态变更的历史信息（称为 epoch ）。
2..MDSs: Ceph 元数据服务器（ MDS ）为 Ceph 文件系统存储元数据（也就是说，Ceph 块设备和 Ceph 对象存储不使用MDS ）。元数据服务器使得 POSIX 
文件系统的用户们，可以在不对 Ceph 存储集群造成负担的前提下，执行诸如 ls、find 等基本命令。

Ceph 把客户端数据保存为存储池内的对象。通过使用 CRUSH 算法， Ceph 可以计算出哪个归置组（PG）应该持有指定的对象(Object)，然后进一步计算出哪个
OSD 守护进程持有该归置组。 CRUSH 算法使得 Ceph 存储集群能够动态地伸缩、再均衡和修复。
OpenStack Object Storage(swift)
Amazon Simple Storage Service (Amazon S3 亚马逊简单存储服务) 是一种对象存储，它具有简单的 Web 服务接口，可用于在 Web 上的任何位置存储和检索任意数量的数据。它能
够提供 99.999999999% 的持久性，并且可以在全球大规模传递数万亿对象。
Ceph包含以下组件。
·分布式对象存储系统RADOS库，即LIBRADOS。
·基于LIBRADOS实现的兼容Swift和S3的存储网关系统RADOSGW。
·基于LIBRADOS实现的块设备驱动RBD。
·兼容POSIX的分布式文件Ceph FS。
·最底层的分布式对象存储系统RADOS。
Ceph存储系统的逻辑层次结构大致划分为4部分：基础存储系统RADOS、基于RADOS实现
的Ceph FS，基于RADOS的LIBRADOS层应用接口、基于LIBRADOS的应用接口RBD、
RADOSGW。
1）基础存储系统RADOS
RADOS这一层本身就是一个完整的对象存储系统，事实上，所有存储在Ceph系统中的用户
数据最终都是由这一层来存储的。物理上，RADOS由大量的存储设备节点组成，每个节点拥
有自己的硬件资源（CPU、内存、硬盘、网络），并运行着操作系统和文件系统。
2）基础库LIBRADOS
LIBRADOS层的功能是对RADOS进行抽象和封装，并向上层提供API，以便直接基于
RADOS进行应用开发。需要指明的是，RADOS是一个对象存储系统，因此，LIBRADOS实现的
API是针对对象存储功能的。
3）上层应用接口
Ceph上层应用接口涵盖了RADOSGW（RADOS Gateway）、RBD（Reliable Block
Device）和Ceph FS（Ceph File System），其中，RADOSGW和RBD是在LIBRADOS库的基础上
提供抽象层次更高、更便于应用或客户端使用的上层接口。
4）应用层
应用层就是不同场景下对于Ceph各个应用接口的各种应用方式，例如基于LIBRADOS直接
开发的对象存储应用，基于RADOSGW开发的对象存储应用，基于RBD实现的云主机硬盘等。

RADOS架构
1）OSD：由数目可变的大规模OSD（Object Storage Devices）组成的集群，负责存储所有
的Objects数据。
2）Monitor：由少量Monitors组成的强耦合、小规模集群，负责管理Cluster Map。其中，
Cluster Map是整个RADOS系统的关键数据结构，管理集群中的所有成员、关系和属性等信息以
2.2.1　Monitor介绍
正如其名，Ceph Monitor是负责监视整个群集的运行状况的，这些信息都是由维护集群成员
的守护程序来提供的，如各个节点之间的状态、集群配置信息。Ceph monitor map包括OSD
Map、PG Map、MDS Map和CRUSH等，这些Map被统称为集群Map。
1）Monitor Map。Monitor Map包括有关monitor节点端到端的信息，其中包括Ceph集群ID，
监控主机名和IP地址和端口号，它还存储了当前版本信息以及最新更改信息，可以通过以下命
令查看monitor map。 ceph mon dump
2）OSD Map。OSD Map包括一些常用的信息，如集群ID，创建OSD Map的版本信息和最
后修改信息，以及pool相关信息，pool的名字、pool的ID、类型，副本数目以及PGP，还包括
OSD信息，如数量、状态、权重、最新的清洁间隔和OSD主机信息。可以通过执行以下命令查
看集群的OSD Map。ceph osd dump
3）PG Map。PG Map包括当前PG版本、时间戳、最新的OSD Map的版本信息、空间使用
比例，以及接近占满比例信息，同时，也包括每个PG ID、对象数目、状态、OSD的状态以及深
度清理的详细信息，可以通过以下命令来查看PG Map。ceph pg dump
4）CRUSH Map。CRUSH Map包括集群存储设备信息，故障域层次结构和存储数据时定义
失败域规则信息；可以通过以下命令查看CRUSH Map。ceph osd cursh dump
5）MDS Map。MDS Map包括存储当前MDS Map的版本信息、创建当前Map的信息、修改
时间、数据和元数据POOL ID、集群MDS数目和MDS状态，可通过以下命令查看集群MDS Map
信息。ceph mds dump

与传统的分布式数据存储不同，RADOS最大的特点如下。
①将文件映射到Object后，利用Cluster Map通过CRUSH计算而不是查找表方式定位文件数
据到存储设备中的位置。优化了传统的文件到块的映射和BlockMap管理。
②RADOS充分利用了OSD的智能特点，将部分任务授权给OSD，最大程度地实现可扩展。
2.3　RADOS与LIBRADOS
LIBRADOS模块是客户端用来访问RADOS对象存储设备的。Ceph存储集群提供了消息传递
层协议，用于客户端与Ceph Monitor与OSD交互，LIBRADOS以库形式为Ceph Client提供了这个
功能，LIBRADOS就是操作RADOS对象存储的接口。你可
以用LIBRADOS直接和Ceph交互（如与Ceph兼容的应用程序、Ceph接口等）。

RGW---------RBD---------FUSE(CephFS)
			 |
			 |
		  LIBRADOS
			 |
             |
           RADOS
             |
			OSDC
           Network
			 |
     OSD OSD OSD OSD OSD
             |
			 OS
Ceph架构分为基础存储系统RADOS、基于RADOS实
现的CEPHFS(不经过LIBRADOS)，基于RADOS的LIBRADOS层应用接口、基于LIBRADOS的应用接口RBD、
RADOSGW
ceph数据存储的流程(三次映射)
        条带                    hash&mask            crush(pgid)
File --------->oid(object id)-------------->pdid--------------->osd
一个ceph集群可以有多个pool，每个pool是逻辑上的隔离单位，不同的pool可以有完全不一样的数据处理方式，
比如Replica Size（副本数）、Placement Groups、CRUSH Rules、快照、所属者等。列举pool:ceph osd lspools
pool 由pg组成也可设置副本数
PG（Placement Groups）
是Ceph数据管理（包括复制、修复等动作）单元。当客户端把读写请求（对象单元）推送到
Ceph时，通过CRUSH提供的Hash算法把对象映射到PG。PG在CRUSH策略的影响下，最终会被
映射到OSD上。
PGP是PG的逻辑承载体，是CRUSH算法不可缺少的部分。在Ceph集群里，增加PG数量，
PG到OSD的映射关系就会发生变化，但此时存储在PG里的数据并不会发生迁移，只有当PGP的
数量也增加时，数据迁移才会真正开始。
在Ceph集群里，当有数据对象要写入集群时，需要进行两次映射。第一次从object→PG，
第二次是PG→OSD set。每一次的映射都是与其他对象无相关的。以上充分体现了CRUSH的独
立性（充分分散）和确定性（可确定的存储位置）。***有一种说法是经过三次映射,第一次是
从file到[object(条带化stripe),将一个大文件条带为多个小object**************
PG OSD pool Object的关系
|——————————————————————————————————————————————————
|Pool
|		|————————————————
|		|				|
|		|PG_num PGP_num |
|		|Replica_num    |
|		|Crush_Rule		|
|	    ————————————————
|		OSD OSD OSD OSD------Object
|___________________________________________________

ceph osd create n//创建osd.n
ceph osd out n//删除osd.n
ceph osd crush remove osd.4//移出tree
从mon节点启动其他节点sudo service ceph -a strat osd.n //不加-a不生效，没在其他节点尝试过
ceph pg num通用计算方法：(total osd num * 100)/replia_num 尽量是2的次方 example：9 * 100 / 3 = 300 就取256

***************************************************
Ceph提供iSCSI存储
iSCSI由IBM公司和Cisco公司开发，允许在硬件设备、IP协议上层运行SCSI指令集
（SCSI over TCP）。iSCSI最大的特点就是，可以实现在IP网络上运行SCSI协议，使其能够在
100/1000/10000Mbps的以太网上进行传输。
iSCSI的工作过程如下。
1.iSCSI主机应用程序发出数据读写请求，操作系统会生成一个相应的SCSI命令。
2.该SCSI命令在iSCSI initiator层被封装成iSCSI消息包并通过TCP/IP传送到存储设备的以太网
口。
3.存储设备的以太网口的iSCSI target层会解开iSCSI消息包，获得SCSI命令的内容，存储设备
获得的SCSI命令，传送给SCSI设备执行。
4.存储设备执行SCSI命令后的响应，在经过iSCSI target层时被封装成iSCSI响应PDU，通过以
太网传送给主机的iSCSI initiator层。
5.iSCSI initiator会从iSCSI响应PDU里解析出SCSI响应并传送给操作系统，操作系统再响应给
应用程序
Open-iSCSI（http://www.open-iscsi.org/ ）是比较常用的Linux iSCSI Initor工具，担当iSCSI客
户端角色。类似Rados Gateway方式，通过iSCSI Gateway方法实现Ceph/RBD提供iSCSI协议存储
访问.
在众多实现iSCSI对接Ceph/RBD的方案中，Tgt（https://github.com/fujita/tgt ）支持基于用户
态Librbd实现后端存储的访问，实现过程较为简单。

Tgtd+Ceph部署步骤
1.安装环境
sudo apt-get install gcc librbd-dev
2.获取Tgt
git clone clone https://github.com/fujita/tgt.git
3.修改配置文件
vi Makefile
将export CEPH_RADM 改为export CEPH_RBD = 1
vim scripts/tgtd.spec
增加%{_initrddir}/tgtd
usr/lib/tgt/backing-store/bs_rbd.so
etcbash_completion.d/tgt
4.sudo make && sudo make install
5.出错test -z "/usr/bin/xsltproc" || /usr/bin/xsltproc -o manpages/tgtadm.8 
http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl tgtadm.8.xml
6.安装依赖sudo apt-get install xsltproc docbook-xsl docbook-xml
以上步骤没能生成tgtd服务,apt-get install tgt
以上步骤必须在每个节点进行
在客户端上安装iscsi-initiator
7.sudo apt-get install open-iscsi
8.在客户端扫描iSCSI Target。
9.iscsiadm -m discovery -t sendtargets -p 192.168.29.85
result:192.168.29.85:3260,1 zhouwy.rbd.test.com:iscsi-01
10.登录iSCSI Target。
iscsiadm -m node -T zhouwy.rbd.test.com:iscsi-01 -p 192.168.29.85 --login
11.发现本地设备 sudo fdisk -l。
12.分区fdisk /dev/sdaa n--p----w
13.格式化mkfs.xfs -f /dev/sdaa1
14.挂载mount  /dev/sdaa1 /mnt/iscsi-data

*******************************************************
Ceph与KVM
KVM虚拟化技术是当前流行的虚拟化技术之一。KVM虚拟化技术本质是利用CPU硬件虚拟
化技术在Linux等操作系统内核上添加代理模块，让运行在QEMU模拟器的客户机二进制指令通
过KVM模块传递给CPU硬件虚拟化，并返回运行指令。相比纯QEMU模拟器，KVM模块能让客
户机不需要进行二进制翻译过程，而直接使用CPU硬件虚拟化特性，大大提高了QEMU的运行
速度。

1.检查 CPU 是否支持安装 KVM：(这是安装虚拟机的前提)
 egrep -o '(vmx|svm)' /proc/cpuinfo
2.安装 KVM 所需要的软件包
apt-get install qemu-kvm libvirt-bin virt-manager bridge-utils
其中：virt-manager 为 GUI 管理窗口，bridge-utils:用于网络桥接(如果只是字符界面可不用安装virt-manager)
3.下是否安装成功：
# lsmod | grep kvm
1.首先要检查当前操作系统自带的qemu-kvm（Fedora/RHEL/CentOS/）或者qemu-system-
x86_64（Debian/Ubuntu）是否支持RBD作为虚拟磁盘后端存储。
qemu-img --help | grep rbd
①把/etc/ceph/ceph.conf复制到kvm-node1节点相同的路径位置。
②把/etc/ceph/ceph.client.admin.keyring复制到kvm-node1节点相同的路径位置。
4.kvm安装ubuntu:
5.qemu-img create -f qcow2 /home/zhouwy/images/disk.qcow2 10G\\创建qcow2格式磁盘
6.virt-install --virt-type kvm --name ubuntu345 --ram 1024 --cdrom=/home/zhouwy/iso/ubuntu.iso  \
--disk path=/home/zhouwy/images/disk.qcow2,size=10,format=qcow2 --network network=default --graphics vnc,listen=0.0.0.0,port=6876 \
--noautoconsole --os-type=linux --os-variant=ubuntutrusty//vnc方式
注意:安装只有第一次可以进行
--extra-args='console=tty0 console=ttyS0' \\字符界面方式
qemu-kvm的配置文件在/etc/libvir/.xml
virt-clone克隆虚拟机
virt-clone --connect=qemu:///system -o ubuntutest -n ubuntunew -f ./disk2.img -m 52:54:00:66:87:73
也可以直接通过xml定义virsh define new.xml 需要修改的参数:domain name;uuid;mac;disk
disk 一定是已经装过操作系统的disk
qemu-img convert -f qcow2 -O raw disk.qcow2 rbd:pool/image
其中，上面运行qemu-img镜像导入命令时，将qcow2转化成raw格式。这是由于KVM虚拟
化访问Ceph RBD存储时将会配置raw的访问格式，故在此步骤中转换成raw格式。

7.配置文件xml
<disk type='network' device='disk'>
<driver name='qemu' type='raw'/>
<source protocol='rbd' name='vmpool1/root-image1'>
<host name='ceph-mon1' port='6789'/>
</source>
<target dev='vdb' bus='virtio'>
<disk>

8.virsh define ubuntu.xml
9.virsh start ubuntu

***************************************************************
ceph 命令(ThunderBD):
一、集群
1.启动一个 ceph 进程
start ceph-all(table key)
restart ceph-all
status ceph-all
ceph 可更换成osd mon mds
2、查看机器的监控状态
[root@client ~]# ceph health
3、查看 ceph 的实时运行状态
[root@client ~]# ceph -w
4、检查信息状态信息
[root@client ~]# ceph -s
5、查看 ceph 存储空间
[root@client ~]# ceph df or rados df
6、删除一个节点的所有的 ceph 数据包
[root@node1 ~]# ceph-deploy purge node1
[root@node1 ~]# ceph-deploy purgedata node1
7、为 ceph 创建一个 admin 用户并为 admin 用户创建一个密钥，把密钥保存到/etc/ceph
目录下：
ceph auth get-or-create client.admin mds 'allow' osd 'allow *' mon 'allow *' -o /etc/ceph/ceph.client.admin.keyring
ps:名字规则:client.name 
8、为 osd.0 创建一个用户并创建一个 key
[root@client ~]#ceph auth get-or-create osd.0 mon 'allow rwx' osd 'allow *' -o /var/lib/ceph/osd/ceph-0/keyring
ps:osd 可更换成mon mds
10、查看 ceph 集群中的认证用户及相关的 key
ceph auth list
11、删除集群中的一个认证用户
ceph auth del osd.0
12、查看集群的详细配置
[root@node1 ~]# ceph daemon mon.node-01 config show | more
13、查看集群健康状态细节
[root@admin ~]# ceph health detail
14、查看 ceph log 日志所在的目录
[root@node1 ~]# ceph-conf --name mon.node-01 --show-config-value log_file

二、MON（Monitor）
1、查看 mon 的状态信息
[root@client ~]# ceph mon stat
mon 可更换成osd mds
2、查看 mon 的选举状态
[root@client ~]# ceph quorum_status（法定节点）
{"election_epoch":20,"quorum":[0,1,2],"quorum_names":["node-01","node-02","node-03"],"quorum_leader_name":"node-01","monmap":{
以上信息可看出leader 为node-01 领导(主)
3、查看 mon 的映射信息
[root@client ~]# ceph mon dump
mon 可更换成osd mds，osd crush
4、删除一个 mon 节点
[root@node1 ~]# ceph mon remove node1
mon 可更换成osd mds
5、获得一个正在运行的 mon map，并保存在 1.txt 文件中
[root@node3 ~]# ceph mon getmap -o 1.txt
6、查看上面获得的 map
[root@node3 ~]# monmaptool --print 1.txt
7、查看上面获得的 map
[root@node3 ~]# monmaptool --print 1.txt
8、查看 mon 的 amin socket
root@node1 ~]# ceph-conf --name mon.node1 --show-config-value admin_socket
/var/run/ceph/ceph-mon.node-01.asok
9、查看 mon 的详细状态
[root@node1 ~]# ceph daemon mon.node-01 mon_status
三、MDS(metadata server)
四、OSD(object stroage device)
1、查看 ceph osd 运行状态
[root@client ~]# ceph osd stat
2、查看 osd 映射信息
[root@client ~]# ceph osd dump
3、查看 osd 的目录树
[root@client ~]# ceph osd tree
4、down 掉一个 osd 硬盘
[root@node1 ~]# ceph osd down 0 #down 掉 osd.0 节点
5、在集群中删除一个 osd 硬盘
[root@node4 ~]# ceph osd rm 0
6、在集群中删除一个 osd 硬盘 crush map
[root@node1 ~]# ceph osd crush rm osd.0
7、在集群中删除一个 osd 的 host 节点
[root@node1 ~]# ceph osd crush rm node-01
8、查看最大 osd 的个数
[root@node1 ~]# ceph osd getmaxosd
result:max_osd = 9 in epoch 105
8、设置最大的 osd 的个数（当扩大 osd 节点的时候必须扩大这个值）
[root@node1 ~]# ceph osd setmaxosd 10
9、设置 osd crush 的权重为 1.0
ceph osd crush set {id} {weight} [{loc1} [{loc2} ...]]
例如：[root@admin ~]# ceph osd crush set 3 3.0 host=node4
ceph osd tree查看权重值
10或者用下面的方式
[root@admin ~]# ceph osd crush reweight osd.3 1.0
11、把一个 osd 节点逐出集群
[root@admin ~]# ceph osd out osd.3
13、暂停 osd （暂停后整个集群不再接收数据）
[root@admin ~]# ceph osd pause
14、再次开启 osd （开启后再次接收数据）
[root@admin ~]# ceph osd unpause
15、查看一个集群 osd.2 参数的配置
ceph --admin-daemon /var/run/ceph/ceph-osd.2.asok config show | less

五、PG(Placement group)
1、查看 pg 组的映射信息
[root@client ~]# ceph pg dump
2、查看一个 PG 的 map
[root@client ~]# ceph pg map 0.3f
初步认为0 osd-id 3 pg-num
3、查看 PG 状态
[root@client ~]# ceph pg stat
4、查询一个 pg 的详细信息
[root@client ~]# ceph pg 0.26 query
5、查看 pg 中 stuck 的状态
[root@client ~]# ceph pg dump_stuck unclean
ok
[root@client ~]# ceph pg dump_stuck inactive
ok
[root@client ~]# ceph pg dump_stuck stale
ok
6、显示一个集群中的所有的 pg 统计
ceph pg dump --format plain
7、恢复一个丢失的 pg
ceph pg {pg-id} mark_unfound_lost revert
8、显示非正常状态的 pg
ceph pg dump_stuck inactive|unclean|stale

六、pool
1、查看 ceph 集群中的 pool 数量
[root@admin ~]# ceph osd lspools
2、在 ceph 集群中创建一个 pool
ceph osd pool create jiayuan 100 #这里的 100 指的是 PG 组
3、为一个 ceph pool 配置配额
ceph osd pool set-quota data max_objects 10000
4、在集群中删除一个 pool
ceph osd pool delete jiayuan jiayuan --yes-i-really-really-mean-it #名字需要重复两次
5、显示集群中 pool 的详细信息
[root@admin ~]# rados df
6、给一个 pool 创建一个快照
[root@admin ~]# ceph osd pool mksnap data date-snap
7、删除 pool 的快照
[root@admin ~]# ceph osd pool rmsnap data date-snap
8、查看 data 池的 pg 数量
[root@admin ~]# ceph osd pool get data pg_num
9、设置 data 池的最大存储空间为 100T（默认是 1T)
[root@admin ~]# ceph osd pool set data target_max_bytes 100000000000000
set pool 0 target_max_bytes to 100000000000000
10、设置 data 池的副本数是 3
[root@admin ~]# ceph osd pool set data size 3
11、设置 data 池能接受写操作的最小副本为 1
[root@admin ~]# ceph osd pool set data min_size 1
12、查看集群中所有 pool 的副本尺寸
[root@admin mycephfs]# ceph osd dump | grep 'replicated size'
13、设置一个 pool 的 pg 数量
[root@admin ~]# ceph osd pool set data pg_num 100
14、设置一个 pool 的 pgp 数量
[root@admin ~]# ceph osd pool set data pgp_num 100
15、设置一个池中 object 的大小
[root@B2801-ceph-0 ~]# ceph osd pool set-quota data max_objects

七、rados 和 rbd 指令
1、rados 命令使用方法
（1）、查看 ceph 集群中有多少个 pool （只是查看 pool)
[root@node-44 ~]# rados lspools
（2）、查看 ceph 集群中有多少个 pool,并且每个 pool 容量及利用情况
[root@node-44 ~]# rados df
（3）、创建一个 pool
[root@node-44 ~]#rados mkpool test
(4)、查看 ceph pool 中的 ceph object （这里的 object 是以块形式存储的）
[root@node-44 ~]# rados ls -p volumes | more
（5）、创建一个对象 object
[root@admin-node ~]# rados create test-object -p test
（6）、删除一个对象
[root@admin-node ~]# rados rm test-object-1 -p test
2、rbd 命令的用法
（1）、查看 ceph 中一个 pool 里的所有镜像
[root@node-44 ~]# rbd ls images
（2 ）、查看 ceph pool  中一个镜像的信息
[root@node-44 ~]# rbd info -p pools image
（3 ）、在 test  池中创建一个命名为 zhanguo 的 的 10000M  的镜像
[root@node-44 ~]# rbd create -p test --size 10000 zhanguo
（4 ）、删除一个镜像
[root@node-44 ~]# rbd rm -p test lizhanguo
（5 ）、调整一个镜像的尺寸
[root@node-44 ~]# rbd resize -p test --size 20000 zhanguo
（6 ）、给一个镜像创建一个快照
[root@node-44 ~]# rbd snap create test/zhanguo@zhanguo123 #池/镜像@快照
（7 ）、查看一个镜像文件的快照
[root@os-node101 ~]# rbd snap ls -p pools images
（8 ）、删除一个镜像文件的一个快照快照
[root@os-node101 ~]# rbd snap rm pools/image@image_snap
（9 ）删除一个镜像文件的所有快照
[root@os-node101 ~]# rbd snap purge -p pool images
（10 ）、把 ceph pool  中的一个镜像导出导出镜像
[root@node-44 ~]# rbd export -p pools images@image_snap
（11 ）、把一个镜像导入 ceph  中  （但是直接导入是不能用的，
因为没有经过 openstack,openstack  是看不到的）
[root@node-44 ~]# rbd import /root/aaa.img -p pools image

************************************************************************************************************************************
Ceph 测试工具学习
************************************************************************************************************************************
1.对于10000转速的SATA硬盘来说，一般寻道时间是7 ms，旋转时间是3 ms，64KB的传输时间是0.8 ms，则SATA硬盘每秒可以进行随机IO操作是1000/（7+3+0.8）=93。
所以，我们估算SATA硬盘64KB随机写的IOPS是93。一般的硬盘厂商都会标明顺序读写的MBPS（吞吐量）。
我们在列出IOPS时，需要说明IO大小、寻址空间、读写模式、顺序/随机和队列深度。一般常用的IO大小是4KB，这是因为文件系统常用的块大小是4KB。

2.2.使用dd测试硬盘的Mbps吞吐量
sudo dd if=/dev/zero of=/dev/sdy bs=4k count=30000 oflag=direct
30000+0 records in
30000+0 records out
122880000 bytes (123 MB) copied, 8.65263 s, 14.2 MB/s
Mbps = 14.2MB/s
在dd测试的同时也要对系统IO进行监控，使用iostat命令对系统IO进行查看。
iostat -x sdy 5 10
为什么这块硬盘的MBPS只有68MB/s？这是因为磁盘利用率是78%，没有到达95%以上，还有部分时间是空闲的。当dd在前一个IO响应之后，在准备发起下一个IO时，
SATA硬盘是空闲的。那么，如何才能提高利用率，让磁盘不空闲呢？只有一个办法，那就是增加硬盘的队列深度。相对于CPU来说，硬盘属于慢速设备，所有操作
系统会给每个硬盘分配一个专门的队列用于缓冲IO请求。

加大队列深度→提高利用率→获得IOPS和MBPS峰值→注意响应时间在可接受的范围内。增加队列深度的办法有很多，如下。
1.使用异步IO，同时发起多个IO请求，相当于队列中有多个IO请求。
2多线程发起同步IO请求，相当于队列中有多个IO请求。
3.增大应用IO大小，到达底层之后，会变成多个IO请求，相当于队列中有多个IO请求队列深度增加了。
example:增加应用IO大小bs=100M
denali@node-01:~$ sudo dd if=/dev/zero of=/dev/sdy bs=100M count=30 oflag=direct
30+0 records in
30+0 records out
3145728000 bytes (3.1 GB) copied, 1.40642 s, 2.2 GB/s
队列深度可以增加IO利用率

4.使用fio测试硬盘

现在，我们来测试SATA硬盘的4KB随机写的IOPS。因为环境是Linux，所以使用fio来测试。

$fio -ioengine=libaio -bs=4k -direct=1 -thread -rw=randwrite -size=1000G -filename=/dev/vdb -name="EBS 4K randwrite test" -iodepth=64 -runtime=60

简单介绍一下fio的参数如下。
1.Ioengine：负载引擎，我们一般使用libaio，发起异步IO请求。
2.bs：IO大小。
3.direct：直写，绕过操作系统Cache。因为我们测试的是硬盘，而不是操作系统的Cache，所以设置为1。
4.rw：读写模式，有顺序写write、顺序读read、随机写randwrite和随机读randread等。
5.size：寻址空间，IO会落在[0,size）这个区间的硬盘空间上。这是一个可以影响IOPS的参数。一般设置为硬盘的大小。
6.filename：测试对象。
7.iodepth：队列深度，只有使用libaio时才有意义。这是一个可以影响IOPS的参数。
8.runtime：测试时长。
9.name：测试备注
10.thread以进程的方式去测试

5.队列深度对IOPS的影响
下面我们做两次测试，分别测试iodepth=1和iodepth=4的情况。图9-12是iodepth=1的测试结
果。

5.寻址空间对IOPS的影响
我们继续测试SATA硬盘，前面我们提到寻址空间参数也会对IOPS产生影响，下面我们测试
当size=1GB时的情况，如图9-14所示。
我们发现，当设置size=1GB时，IOPS会显著提高到568，IO平均响应时间会降到7ms（队列深度为4）。这是因为当寻址空间为1GB时，磁头需要移动的距离变小了，每次IO请求的服务时
间就降低了，这就是空间局部性原理。假如我们测试的RAID卡或者是磁盘阵列（SAN），它们可能会用Cache把这1GB的数据全部缓存，极大降低了IO请求的服务时间（内存的写操作比硬盘
的写操作快1000倍）。所以设置寻址空间为1GB的意义不大，因为我们是要测试硬盘的全盘性能，而不是Cache的性能。

#fio -ioengine=libaio -bs=4k -direct=1 -thread -rw=randwrite -size=100G -filename=/dev/vdb \
-name="EBS 4KB randwrite test" -iodepth=32 -runtime=60

ThunderBD 的CEPH 采用的存储引擎为bluestore,ceph 有几种存储引擎:filestore kvstore memstore 以及最新的bluestore
前默认使用的
filestore，但是因为 filestore 在写数据前需要先写 journal，会有一倍的写放大，并且 filestore 一开始只是对于机械盘进行设计的，没有专门针对 ssd
做优化考虑，因此诞生的 bluestore 初衷就是为了减少写放大，并针对 ssd 做优化，而且直接管理裸盘，从理论上进一步减少文件系统如 ext4/xfs 等部分的
开销
Ceph.conf
[osd.8]
	host = node-03
	osd data = /var/lib/ceph/osd/ceph-8
	bluestore block wal path = /dev/disk/by-partlabel/ceph-8-wal
	bluestore block db path = /dev/disk/by-partlabel/ceph-8-db
	bluestore block path = /dev/disk/by-partlabel/ceph-8-block
ll /dev/disk/by-partlabel/

lrwxrwxrwx 1 root root  10 Jul  3 17:40 ceph-8-block -> ../../sdc4
lrwxrwxrwx 1 root root  10 Jul  3 17:40 ceph-8-db -> ../../sdc3
lrwxrwxrwx 1 root root  10 Jul  3 17:40 ceph-8-wal -> ../../sdc2

denali@node-03:~$ ll -h /var/lib/ceph/osd/ceph-8/
total 48K
drwxr-xr-x 2 root root 4.0K Jul  3 17:40 ./
drwxr-xr-x 5 root root 4.0K Jul  3 17:40 ../
lrwxrwxrwx 1 root root   35 Jul  3 17:40 block -> /dev/disk/by-partlabel/ceph-8-block
lrwxrwxrwx 1 root root   32 Jul  3 17:40 block.db -> /dev/disk/by-partlabel/ceph-8-db
lrwxrwxrwx 1 root root   33 Jul  3 17:40 block.wal -> /dev/disk/by-partlabel/ceph-8-wal
-rw-r--r-- 1 root root    2 Jul  3 17:40 bluefs
-rw-r--r-- 1 root root   37 Jul  3 17:40 ceph_fsid
.........

从上面信息可看出bluestore的一个特点，直接操作裸盘

















