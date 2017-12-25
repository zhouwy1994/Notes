************************Keep Note********************************
今天在装centos minimal release完成后，sudo install net-tools 安装网络类工具
配置网络 vi /etc/sysconfig/network-scripts/ifcfg-ens33 设置ip分配方式dhcp static device name=eth0
重启网络 sudo systemctl restart network.service PS：所有基于redhat的所有Linux release，自rhel7之后所有服务从
之前的service servername start 改称统一的命令systemctl start servername.service的方式启动
一个重要的问题，我的网卡device name居然不是eth0这让我很不习惯，我将devicename改成eth0再将ifcfg-ens33改成ifcfg-eth0重启
后发现还是ens33
在网上查了一下，发现自rhel6/centos6开始引入了***设备可预测命名规则***,大概解释：之前传统的linux以枚举命名方式(eth0 eth1..)
来命名网络设备，但这些名称并不一定符合实际的硬件插槽，PCI位置，USB接口数量等，这引入了一个**不可预知的命名**问题（例如，由于不
确定的设备探测行为），这可能会导致不同的网络配置错误（例如，由无意的接口改名引起的禁止接口或者防火墙旁路）。
所有rhel6虽然引入了设备可预测命名规则，但是默认是没有enable，需要手动，rhel7之后这项功能默认开启

开启可预测命名规则的好处:可预测命名规则将以设备的硬件插槽，PCI位置，接口名称被自动基于固件，拓扑结构和位置信息来确定。现在，
即使添加或移除网络设备，接口名称仍然保持固定，而无需重新枚举，和坏掉的硬件可以无缝替换。所以说系统管理员可以根据设备名来精确定位
硬件，不会是1\2\3的命名方式
但是之前用习惯了枚举型命名规则的小伙伴不适应了，下面步骤可以还原枚举命名规则
1、首先，让我们来禁用该可预测命名规则。需要在启动时传递“net.ifnames=0”的内核参数。这是通过编辑/etc/default/grub并加入
“net.ifnames=0 biosdevname=0”到GRUB_CMDLINE_LINUX变量来实现的
2、使配置生效以更新内核参数
sudo grub2-mkconfig -o /boot/grub2/grub.cfg
3、sudo vi /etc/sysconfig/network-scripts/ifcfg-ens33 更改devive=eth0 并且sudo mv ifcfg-ens33 ifcfg-eth0
4、重启:sudo reboot ，ifconfig 查看是否修改成功

关闭防火墙sudo systemctl disable firewall
禁用selinux vi /etc/selinux/config 将SELINUX=enforcing改成disable
linux 之间的ssh免密登陆设置方式包括通过ssh登陆github等设置
在ssh客户端~/.ssh目录下使用ssh-keygen -t rsa生成一个id_rsa.pub文件，将该文件的内容拷贝到ssh服务器的.ssh目录下的authorized_keys
中即可实现免密登陆
rehl更新软件源 mv /etc/yum.repo/Centos-Bash.repo /etc/yum.repo/Centos-Bash.repo.back 
wget http://mirrors.163.com/.help/CentOS7-Base-163.repo 在yum.repo目录下
sudo yum clean all 清除之前缓存包 sudo yum makecache 更新软件文件
fdisk /dev/sda 给sda磁盘分区
mkfs.ext4 /dev/sda1 格式化分区(先分区再格式化和windows有点类似)
开机挂载vi /etc/rc.local (开机执行的脚本)
PS:如果是linux自身的服务开机启动可用命令chkconfig on service or systemctl enable service等
大部分LINUX release都可将启动命令放到/etc/rc.local中
samba的配置文件在/etc/samba/smb.conf
建立符号连接ln -s source destion
安装ctdb sudo yum -y install ctdb

linux开机不启动/etc/rc.local的原因可能是应为rc.local没有x权限chmod +x rc.local
smb添加已有用户sudo smbpasswd -a username
任何琴况下命令执行失败都要再加sudo再执行一遍
云计算的种服务模式:依次是Infrastructure（基础设施）-as-a-Service，Platform（平台）-as-a-Service，Software（软件）-as-a-Service。
iaas:t提供底层硬件和网络服务
paas:提供虚拟机以及操作系统等开发平台，向上层应用提供api接口
saas:顶层的应用集合
ubuntu默认安装时glusterfs3.4如果要安装glusterfs3.8必须配置ppa源，再在source.list里添加glusterfs软件源
ubuntu的防火墙ufw

通过cifs挂载glusterfs samba导出
sudo mount -t cifs -o username=zhouwy,password=1 //192.168.0.141/public /mnt/cifs_export
解释cifs挂载类型(common internet file system)通用网络文件系统，式windows上常用的一种打印机，文件共享协议
username password是登陆samba的用户名和密码,在glusterfs-server上通过sudo smbpasswd -a username配置
192.168.0.141 glusterfs-server的public ipadders不是实际的ip，有ctdb提供
/mnt/cifs_export 挂载目录


nfs-ganeshe可以不通过内核直接与FUSE通信,这大大减少了内核开支，提高了gluster的访问性能
libgfapi.so 是gluster3.4之后引入的通信机制，通过libgfapi.so方式的访问可以不经过kernel fuse直接与glusterd通信。
其性能相比与通过fuse访问方式理论来说有相对优势
free 命令的使用,free是检测内存使用情况的命令,
-b：以Byte为单位显示内存使用情况； 
-k：以KB为单位显示内存使用情况； 
-m：以MB为单位显示内存使用情况； 
-o：不显示缓冲区调节列； 
-s<间隔秒数>：持续观察内存使用状况； 
-t：显示内存总和列； 
-V：显示版本信息。
total：内存总数； u
sed：已经使用的内存数； 
free：空闲的内存数； 
shared：当前已经废弃不用；
buffers Buffer：缓存内存数； 
cached Page：缓存内存数。

total = used + free
(-buffers/cache) used内存数：第一部分Mem行中的 used – buffers – cached 
(+buffers/cache) free内存数: 第一部分Mem行中的 free + buffers + cached
可见-buffers/cache反映的是被程序实实在在吃掉的内存，
而+buffers/cache反映的是可以挪用的内存总数。
 
运行$ sudo dpkg -purge glusterfs以清除配置文件。
gluster的一个精简配置卷首先是从LVM(Logical Vlome Manager)逻辑卷管理
pvcreate vgcreate lvcreate pvdisplay vgdisplay lvdisplay
最后brick在brick上创建
RPC(remote procedure call protocol)远程过程调用协议，是一种通过网络向远程计算机请求服务的协议
glusterfs的self heal deamon名字/var/log/glusterfs/glustershd.log每个服务器上都有一个这个进程
GlusterFS卷快照功能基于精简配置的LVM快照。要使用快照功能，GlusterFS卷应该满足以下先决条件：
每个砖块应该在独立的薄配置LVM上。
Brick LVM不应该包含砖以外的其他数据。
没有一块砖应该在一个厚实的LVM上。
葡萄牙语版本应为3.6及以上。
NFS-Ganesha是NFS协议的用户空间文件服务器，支持NFSv3，v4，v4.1，pNFS。它提供与FUSE兼容的文件系
统抽象层（FSAL），以允许文件系统开发人员插入自己的存储机制，并从任何NFS客户端访问它。NFS-Ganesha可
以通过其FSAL直接访问FUSE文件系统，而无需向内核复制任何数据，从而有可能改善响应时间。
tail 一般用于查看日志文件,因为日志文件最新的在后面
tail -f 或者tailf可以动态察看日志
执行以下命令成功创建NFS导出
sudo -u denali ansible-playbook /usr/share/denali-ansible/createNFSExport.yml -e '{"resourceParams":{"Name":"gluster-export-replica","After":"nfs,copy","ExportName":"gluster-export-replica","ExportPseudo":"","GlusterVolume":"gluster-volume-replica","VolumeFrom":"copy","ExportAccessType":"NONE","Partitions":["proto1"],"ExportProtocols":"3","ExportTransports":"UDP,TCP","ExportID":"3","ExportDisableACL":"True","ExportSquash":"No_Root_Squash","Service":"nfs","ExportType":"glusterfs","AuxService":"gluster","Groups":[{"Clients":["192.168.*"],"Access_type":"RW"}]}}'
修改vagrant的配置文件后,要使用vagrant reload 命令才会生效
ansible是一款自动化运维工具，给予phthon语言编写，它是一款可以通过ssh远程登录集群执行任务，它可以执行批量化任务基于playbook，yml脚本
char *const ptr;//指针常量，该指针是一个常量,指针是only read
char const *ptr OR const char *ptr//常量指针，该指针所指向一个常量，常量是only read
察看Ubuntu已经安装的软件包,dpkg -l 查看路径dpkg -L

块存储 对象存储 文件存储
1.块存储:磁盘存储，传统存储block，ceph
2.对象存储 object storage
3.文件存储：NFS CIFS FTP

ssh 公钥登陆 将client .ssh目录下的id_rsa.pub内容拷贝至server .ssh目录下的authorized_keys 然后设置/etc/ssh/ssh_conf 添加
RSAAuthentication yes        # 启用 RSA 认证，默认为yes
PubkeyAuthentication yes     # 启用公钥认证，默认为yes
远程执行命令ssh -p $port $uesrname@$remote_id 'cmd'
port 一般为22
ldconfig命令的用途主要是在默认搜寻目录/lib和/usr/lib以及动态库配置文件/etc/ld.so.conf内所列的目录下，搜索出可共享的动
态链接库（格式如lib*.so*）,进而创建出动态装入程序(ld.so)所需的连接和缓存文件。缓存文件默认为/etc/ld.so.cache，此文件保
存已排好序的动态链接库名字列表，为了让动态链接库为系统所共享，需运行动态链接库的管理命令ldconfig，此执行程序存放在/sbin目录下。
文件重定向C语言函数fp = freopen("error.log", "w+", stderr);//将标准错误输出重定向到error.log
后面对fd的操作就是对stderr的操作
umask作用域:对普通文件的x位没有作用，只对目录的x位有作用
如果过载出现wrong fs type, bad option,//证明没有该类型工具的挂在命令,如 mount -t nfs，需要先安装nfs-common
ssh denali@${Vm_ip}可先行设置用户名登录
ssh -p 22 denali@${VM_ip} 'cmd'远程执行命令，前提是公钥登陆
wget -O 指定下载名 url
scp 远程复制,基于ssh协议 scp username@hostname:path localhost:path
xshell5选项卡界面合并之后就不能在同一界面显示,这很恼火,这是因为会话选项卡没被选中,选择查看---->会话选项卡
带宽:每秒传输的位数20M,1M=1000000b 20M=20000000b/s=2M/s,20G带宽=2G/s
吞吐量为每秒传输的数据量
吞吐量和带宽的区别:带宽为每秒最多能传输的数据量，吞吐量为每秒实际传输值，eg：一条路一次能通过100辆车，这是带宽，在某一秒正有56辆通过，这就是实际吞吐量
fuser命令用于报告进程使用的文件和网络套接字。fuser命令列出了本地进程的进程号，那些本地进程使用file，参数指定的本地或远程文件。对于阻塞特别设备，此命令
列出了使用该设备上任何文件的进程。
fuser -k /mnt/nfs_test 当设备忙时，强行杀死

vagrant 新建虚拟机,要先清理之前的旧版本,vagrant box list,vagrant box remove
再vagrant up
lsof命令用于查看你进程开打的文件，打开文件的进程，进程打开的端口(TCP、UDP)。找回/恢复删除的文件。是十分方便的系统监视工具，
因为lsof命令需要访问核心内存和各种文件，所以需要root用户执行。
lsof -p PID 查看进程打开的fd socket 占用端口信息等
glusterfs的仲裁卷也是要存储资源，但在UI上显示没占空间(ThunderStor)
为什么VIP的漂移到任意一台机器都是相同的操作
因为3台节点大部分操作都在每一个节点上都做了重复的操作，同样的NFS导出同样的CIFS导出
仲裁brick只存元数据
sata硬盘命名规则,sda sdb 超过sdz就从sdaa sdab..开始
UI的NFS检测是通过export.conf确定，CIFS通过smb.conf确定
添加路由命令sudo route add default gw 192.168.28.254 eth0 or ip route add default via 192.168.28.254 default可改为特定ip
查看指定网卡带宽 ethtool eth0 
虚拟机添加硬盘
vboxmanage createhd --filename new.vdi --size 4096//创建虚拟磁盘镜像(virtual disk image)
vboxmanage storageattach node-01 --storagectl SATAController --port 26 --type hdd --medium new.vdi//将新建的磁盘镜像添加到sata控制器SATAContrller
//node-01:虚拟机名称  SATAController:SATA控制器名称
修改vdi大小
vboxmanage modifyhd $hdd-id --resize 20480

initctl -- init daemon control tool//Linux守护进程管理工具
--list //列出所有守护进程
start                       Start job.
  stop                        Stop job.
  restart                     Restart job.
  reload                      Send HUP signal to job.
  status                      Query status of job.
  list                        List known jobs.
ssh 不允许以root用户登录，安全性考虑sshd_config /etc/ssh/sshd_config 将PermitRootLogin yes service sshd restart
ansible copy模块将控制主机的文件复制到远程节点
ansible cluster -m copy -s -a "src=/etc/apt/sources.list dest=/etc/apt/sources.list" //-s sudo
lsblk查看当前机器所有磁盘
pgrep -u root,daemon 查看所有属于root的守护进程，查找指定用户的进程
pkill 杀死查找到的进程,(根据进程名)
virtualbox Vrde 远程桌面控制设置步骤
创建虚拟机
1.VBoxManage createvm --name ocentos --ostype RedHat --register --basefolder/data/vmos/
virtualbox name:centos
ostype RedHat vboxmanage list ostypes
2.VBoxManage modifyvm ocentos --memory 512 --vram 8 --acpi on --ioapic on --
boot1 disk --boot2 dvd --nic1 bridged --nictype1 Am79C973 --bridgeadapter1
eth0 --mouse usb --keyboard usb //让虚拟机拥有普通计算机的功能
3.VBoxManage storagectl ocentos --add sata --name "SATA Controller" --controller
IntelAhci --bootable on //添加SATA控制器
4.VBoxManage createhd --filename /data/vmos/ocentos/ocentos.vdi --size 20480 --format vdi --variant Fixed//创建一个磁盘镜像(vdi)，20G
5.VBoxManage storageattach ocentos --storagectl "SATA Controller" --port 0 --device 0 --type hdd --medium /data/vmos/ocentos/ocentos.vdi
//将创建的磁盘镜像添加进SATA控制器
6.VBoxManage storageattach ocentos --storagectl "SATA Controller" --port 1 --
device 0 --type dvddrive --medium /home/hto/sf/os/centos-5.8-i386-netinstall.iso
//添加dvd控制器并将其添加进SATA控制器
以上步骤九可以创建一个虚拟机
开启vrde
vboxmanage modifyvm centos --vrde on --vrdeport 3389 --vrdeaddress 0.0.0.0
启动虚拟机vboxmanage -s centos --vrde on
vboxmanage modifyvm vmname --cpus 3 修改cpu数量为3
windows 使用TightVNC客户端http://www.tightvnc.com/download.php
输入主机地址(也就是虚拟机对应的主机 端口)无密码 直接确认

kvm VNC 
1.  修改qemu.conf
# vi /etc/libvirt/qemu.conf 
vnc_listen = "0.0.0.0"
说明1：vnclisten 默认绑定127.0.0.1 在配置文件里指定VNC 绑定0.0.0.0IP,就不用在安装kvm虚拟机时指定vnclisten参数了。
说明2：在虚拟主机上有很多个虚拟机的时候，需要指定每个虚拟机的端口，否则将会很乱。
2.  修改虚拟机配置文件
# virsh edit oeltest01
<graphics type='vnc' port='5910' autoport='no' listen='0.0.0.0'>       
  <listen type='address' address='0.0.0.0'/>        
</graphics>

free和top显示的情况为什么不同：
free命令显示的内容，第一行的数据是以系统视角看的，第二行的数据是以应用程序的视角看的。
第一行的used一项，其数据不单包含程序使用的内存，还包含buffers跟cached的内存，因此看上去可用的内存很少。
第二行的数据，分别是used-buffers-cached，跟free+buffers+cached，算了一下程序总的内存使用率是
(total - free - buffers - cached) / total = 0.038 左右，因此top显示一列0.0也没什么问题。

kvm安装ubuntu
qemu-img create -f qcow2 /home/zhouwy/images/disk.qcow2 10G\\创建qcow2格式磁盘
virt-install --virt-type kvm --name ubuntu345 --ram 1024 --cdrom=/home/zhouwy/iso/ubuntu.iso  \
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
当网络某个网段处于DHCP时，就不可设置静态ip，只要该网段IP还没分配完，且mac地址保持不变的情况下，一般所得到的地址不会变
ubuntu查看服务列表代码  
sudo service --status-all
sudo initctl list
*************************************
重要:改变日志时间与dateS时间不一致
*************************************
设置时区:tzselect,根据提示设置时区Asia--->China----->Beijing--->Save

pidof pidof -- find the process ID of a running program.查找一个正在运行进程的进程号
与pgrep作用相同，和pgrep相比，pidof必须给出进程的全名。
ubuntu干净卸载软件sudo apt-get autoremove app-name --purge //删除配置文件

用户免密执行sudo命令
更改 chmod +w /etc/sudoers sudo visudo 
在最后行家 username ALL=NOPASSWD:ALL
chmod -w /etc/sudoers
sshpass 参数 SSH命令(ssh，sftp，scp等)。
    参数:
        -p password    //将参数password作为密码。
        -f passwordfile //提取文件passwordfile的第一行作为密码。
        -e        //将环境变量SSHPASS作为密码。

    比如说：
        scp abc@192.168.0.5:/home/xxx/test /root   这个命令的作用是将服务器端文件test传到本地文件夹/root下。
        利用sshpass，假设密码为efghi，则可写作：
        ssh -p efghi scp abc@192.168.0.5:/home/xxx/test /root

另外，对于ssh的第一次登陆，会提示：“Are you sure you want to continue connecting (yes/no)”，这时用sshpass会不好使，解决方法：
1.可以在ssh命令后面加上 -o StrictHostKeyChecking=no来解决。比如说上面的命令，就可以写作ssh -p efghi scp abc@192.168.0.5:/home/xxx/test /root -o StrictHostKeyChecking=no。
2.或者写入配置文件：把 StrictHostKeyChecking no 加到/etc/ssh/sshconfig 可以让ssh客户端自动接受新主机的hostkey,不用每次都自己输入yes

更换源命令 sed -i 's/\([[:alnum:]]\+\.\)\+com/mirrors.163.com/g' /etc/apt/sources.list
ssh-copy-id -i .ssh/id_rsa.pub remotemast
推送密钥

sudo -s获得root权限但保持原先环境变量
shll scripts 尽量用vi检查语法，notdpad++语法检查不完整
修改虚拟机路径:vboxmanage setproperty machinefolder "/mnt/vdisk/VMs"

Linux增加交换分区(swap)的方法
1.新建一个文件或者分区(大小为你需要增加swap的大小)
dd if=/dev/zero of=file.swap bs=1M count=4096 //4G
or
fdisk /dev/sd* -->n  //4G

2.格式化文件或分区
mkswap file.swap or mkswap /dev/sd*
3.挂载swap分区
swapon file.swap or swapon /dev/sd*

4.关闭swap分区
swapoff file.swap or swapon /dev/sd*
以上方法开机实效，可在fstab 里面添加swapon命令

virtualbox建立的虚拟机在没装无线网卡驱动时不是能通过桥接方式连接无线网(有线可以)
这时只能通过网络地址转换(NAT)方式接入外网但是NAT存在一个问题，它被分配网址10.0.2.15
xshell是不能识别此地址的，只有设置网络端口转发
将物理机的端口影射虚假拟机的22端口，然后在xshell ssh $username@$ip $port
在网路设置中设置

vi 格式化代码段
方法一:
ESC
gg=G

方法二:
shift -v 可视化模式
选中代码
=
LVM(Logical Vlome Manager)逻辑卷管理
精简配置的代名词
基本术语:
*物理存储介质（PhysicalStorageMedia）
指系统的物理存储设备：磁盘，如：/dev/hda、/dev/sda等，是存储系统最底层的存储单元。
*物理卷（Physical Volume，PV）
指磁盘分区或从逻辑上与磁盘分区具有同样功能的设备（如RAID），是LVM的基本存储逻辑块，但和基本的物理存储介质（如分区、磁盘等）比较，却包含有与LVM相关的管理参数。
*卷组（Volume Group，VG）
类似于非LVM系统中的物理磁盘，其由一个或多个物理卷PV组成。可以在卷组上创建一个或多个LV（逻辑卷）。
*逻辑卷（Logical Volume，LV）
类似于非LVM系统中的磁盘分区，逻辑卷建立在卷组VG之上。在逻辑卷LV之上可以建立文件系统（比如/home或者/usr等）。
*物理块（Physical Extent，PE）
每一个物理卷PV被划分为称为PE（Physical Extents）的基本单元，具有唯一编号的PE是可以被LVM寻址的最小单元。PE的大小是可配置的，默认为4MB。所以物理卷（PV）由大小等同的基本单元PE组成。
*逻辑块（Logical Extent，LE）
逻辑卷LV也被划分为可被寻址的基本单位，称为LE。在同一个卷组中，LE的大小和PE是相同的，并且一一对应。
对应命令:
1、创建物理卷:
pvcreate /dev/sdb1 //将物理存储介质/dev/sdb1制作成一个物理卷
2、创建卷组:
vgcreate vg_name /dev/sdb1 /dev/sdb2 ...
3、激活卷组
为了立即使用卷组而不是重新启动系统，可以使用vgchange来激活卷组：
#vgchange -ay web_document
5、添加新的物理卷到卷组中
当系统安装了新的磁盘并创建了新的物理卷，而要将其添加到已有卷组时，就需要使用vgextend命令：
lvextend   web_document /dev/hdc1 //添加磁盘到逻辑卷组
#vgextend web_document /dev/hdc1
6、从卷组中删除一个物理卷
要从一个卷组中删除一个物理卷，首先要确认要删除的物理卷没有被任何逻辑卷正在使用，就要使用pvdisplay命令察看一个该物理卷信息：
如果某个物理卷正在被逻辑卷所使用，就需要将该物理卷的数据备份到其他地方，然后再删除。删除物理卷的命令为vgreduce：
#vgreduce web_document /dev/hda1
7、创建逻辑卷
创建逻辑卷的命令为lvcreate：
#lvcreate -L1500 -n www1 web_document
该命令就在卷组web_document上创建名字为www1，大小为1500M的逻辑卷，并且设备入口为 /dev/web_document/www1（web_document为卷组名，www1为逻辑卷名）。
如果希望创建一个使用全部卷组的逻辑卷，则需 要首先察看该卷组的PE数，然后在创建逻辑卷时指定：
#vgdisplay web_document | grep"TotalPE"
TotalPE45230
#lvcreate -l45230 web_document -n www1

用ldd查看一下hcsh链接的库对不对 另外你用nm查看一下对应库里面有没有这个符号链接

vim重复操作多行:
1、将光标移至想要注释掉的第一行行首->ESC->qa->i->#->ESC->j->q
　　qa: q是开始录制，后面紧跟名字，这里是a,也可以是其他
最后一个q表示结束录制
@a会重复刚刚录制的a
10@a会重复10次
 
2、还有一种方法，就是块操作:
Ctrl+v, 选中行，I, #, ESC
开始的时候感觉是不行，后来发现是忽略了 I 是大写的。:)

3、v进入virtual模式，选中所有行，crtl+v进入列模式(shift+v行模式)，大写I，在行之前插入注释，连续两下ESC,多行操作
shell调用UI接口(http)
curl "http://"
crul -d "name=pool&type=replica" "http://"提交表单访问HTTP POST方式传送数据

crtl +r 搜索历史命令

C语言书写格式关键字后() {}与关键字之间都应该有一个空格
for (i < 0) {
	...
}

无界面启动虚拟机vboxmanage stattvm --type headless
查看某个服务邦定的端口信息 netstat -anp | grep $servername

线程安全就是多线程访问时，采用了加锁机制，当一个线程访问该类的某个数据时，
进行保护，其他线程不能进行访问直到该线程读取完，其他线程才可使用。不会出现数据
不一致或者数据污染。 线程不安全就是不提供数据访问保护，有可能出现多个线程先后
更改数据造成所得到的数据是脏数据。

linux下线程间同步机制:互斥锁、条件变量、信号量
linux下进程间通信方式，管道(有名管道，无名管道)，信号、共享内存、消息队列、socket、信号量


notepad++多行注释快捷键ctrl + k ctrl + q 取消多行注释:ctrl + shift + k

SSL 加密套接字协议层（一种加密的通讯协定，用在使用者与网服器之间，Security Socket Layer）
是在套接字层的一种加密协议，公私密钥对，传输层通过公钥加密信息，使用私钥解密

ssh安全配置步骤:
安装sshd sudo apt-get install openssh-server
启动 停止 重新启动 状态 sudo service ssh start stop restart
无论是个人的VPS还是企业允许公网访问的服务器，如果开放22端口的SSH密码登录验证方式，被众多黑客暴力猜解捅破菊花也可能是经常发生的惨剧。
企业可以通过防火墙来做限制，普通用户也可能借助修改22端口和强化弱口令等方式防护，但目前相对安全和简单的方案则是让SSH使用密钥登录并禁
止口令登录。

修改配置文件 sudo vim /etc/ssh/sshd_config
#禁用密码验证
PasswordAuthentication no
#启用密钥验证
RSAAuthentication yes
PubkeyAuthentication yes
#指定公钥数据库文件
AuthorsizedKeysFile .ssh/authorized_keys

重启ssh服务 sudo service ssh restart 为了防止配置过后不能再用密码登录，请提前配置好密钥验证登录
修改端口 sudo vim /etc/ssh/sshd_config
#Port
Port = 22
Port = 31422 //new port
由于防火墙规则限制，新配置的端口是不能越过防火墙的，所以再没有通过新端口登录成功前，请不要删除22端口
重启ssh服务 sudo service ssh restart 
netstat -an | grep "LISTEN" //出现以下记录，端口监听成功
tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN     
tcp        0      0 0.0.0.0:31422           0.0.0.0:*               LISTEN     
加入防火墙规则(ubuntu ufw 为例)
使用方法
1 启用
 sudo ufw enable
 sudo ufw default deny 
作用：开启了防火墙并随系统启动同时关闭所有外部对本机的访问（本机访问外部正常）。
2 关闭
 sudo ufw disable 
2 查看防火墙状态
 sudo ufw status 
3 开启/禁用相应端口或服务举例
 sudo ufw allow 80 允许外部访问80端口
 sudo ufw delete allow 80 禁止外部访问80 端口
 sudo ufw allow from 192.168.1.1 允许此IP访问所有的本机端口
 sudo ufw deny smtp 禁止外部访问smtp服务
 sudo ufw delete allow smtp 删除上面建立的某条规则
 sudo ufw deny proto tcp from 10.0.0.0/8 to 192.168.0.1 port 22 要拒绝所有的TCP流量从10.0.0.0/8 到192.168.0.1地址的22端口
 可以允许所有RFC1918网络（局域网/无线局域网的）访问这个主机（/8,/16,/12是一种网络分级）：
sudo ufw allow from 10.0.0.0/8
sudo ufw allow from 172.16.0.0/12
sudo ufw allow from 192.168.0.0/16
推荐设置
 sudo apt-get install ufw
 sudo ufw enable
 sudo ufw default deny 
这样设置已经很安全，如果有特殊需要，可以使用sudo ufw allow开启相应服务。
注意:阿里云需要配置安全组，才能通过外部端口访问













