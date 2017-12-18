********************************Study on CTDB***************************

CTDB(Cluster Trivial Database)是一个轻量级的集群服务器实现,目前支持多种共享协议,如Samba, NFS, HTTPD, VSFTPD, ISCSI, WINBIND
等,支持多种分布式文件系统,如GPFS,GFS(2),Glusterfs, Luster, OCFS(2)等,CTDB与集群系统相结合,将可以提供一种简单高效的HA集群解决
方案,CTDB的主要有以下功能:

1.提供TDB数据库的集群版本，在节点故障时自动重建和恢复数据库。

2.监视群集中的节点和运行在每个节点上的服务(NFS,SAMBA等)。

3.管理用于向客户端提供服务的公共IP地址池。

CTDB也可以与LVS结合,可提高分布式文件系统的高可用性能与负载均衡的性能

数据的高可用理解：
数据高可用(HA)，在集群某些节点工作在非常规工作模式下，整个集群仍能正常工作，通常可分为三个层次：
1.磁盘级别高可用：即在一个节点上部分磁盘损坏的情况下数据仍能访问，这种方案通常使用磁盘矩阵实现,如raid10,raid01,raid5等方式

2.服务器级别高可用：即在集群中某台节点宕机的情况下，集群认可工作在正常状态，这就得依靠分布式文件系统提供的数据副本方式实现
例如Gluster提供的Relica Volume机制

3.共享层次高可用：即分布式文件系统提供的统一命名空间，最后通过共享协议的方式导出，如NFS，SAMBA，若提供全局统一存储空间的节点
宕机，这就会导致共享中断，这就涉及到了共享层的高可用。这种方式就可通过结合CTDB转移故障

CTDB的工作方式：
通常向外提供统一命名空间的不对外直接提供共享，也就是不使用物理IP(Private IP)对外提供服务，都是通过对外提供一组虚拟IP(Public IP )
实现共享服务，这组虚拟IP与物理IP存在映射关系，用户通过虚拟IP实现数据访问，并不关心节点的物理IP，当某个实际节点宕机之后，对应的
虚拟 IP 会转移到其他的实际节点上去，这一过程对于用户来说是透明的，不会影响共享的使用。

CTDB主要配置文件
1./etc/sysconfig/ctdb

CTDB_RECOVERY_LOCK="/mnt/gluster/ctdb/lockfile"
CTDB_NODES=/etc/ctdb/nodes
CTDB_PUBLIC_ADDRESSES=/etc/ctdb/public_addresses
CTDB_MANAGES_SAMBA=yes
CTDB_MANAGES_WINBIND=yes
CTDB_MANAGES_NFS=no
CTDB_DEBUGLEVEL=ERR
CTDB_PUBLIC_INTERFACE=eth0

以上为CTDB的主要配置文件，主要说明了CTDB所需的lockfile、nodes，public_addresses文件所在路径，以及CTDB所托管的服务

2.lockfile
恢复锁文件主要针对在某些节点宕机的情况下防止脑裂的情况出现，需制定一台节点作为集群的恢复主机

3.nodes
该文件指出集群中各节点的Private IP,该IP是每个物理节点上唯一的，该地址唯一标识集群中的物理节点，并且是CTDB守护程序将
用于与其他节点上的CTDB守护程序进行通信的地址。

4.public_addresses
公共IP用于向客户提供服务。并不与特定节点永久关联。相反，它们由CTDB管理，并在运行时分配给物理节点上的接口。

ctdb相关命令
ctdb status #查看每个节点的状态
ctdb pnn #查看各个节点的pnn
ctdb listnodes#查看各节点的Private ip
ctdb uptime #显示ctdb运行时间
ctdb natgw #显示ctdb的网关状况

LVS(Linux Virtual Server)
LVS与集群服务器结合，主要是对当前集群的资源作一个负载均衡的作用，LVS向外提供一个IP用于外部共享，LVS主要通过RRDNS方式支配
客户端对集群资源的访问，以这种轮询的方式达到一个负载均衡的作用




















