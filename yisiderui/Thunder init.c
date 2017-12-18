ThunderStor 底层实现过程
sudo vagrant up 开启虚拟机集群，此时还没有建立集群关系，每个节点都是独立的
ui的日志文件/var/log/nginx/ 目录下，有两个文件access.log记录站点日志，error.log记录错误日志
cluster 的所有日志文件将在/var/log/denali/下 
所有服务日志在/var/log/denali/server/下 error.log记录错误信息 log.txt记录cluster的所有行为记录 log4js.txt记录暂时不清楚
ganesha 配置文件在/etc/ganesha/下
ganesha的export.conf在/etc/denali/nfs/export下
CTDB配置文件在/usr/local/etc/ctdb/下该目录下的nodes 和pubipaddrs是一个符号连接在/etc/denali/ctdb/下
samba配置文件/etc/samba/smb.conf
ui的所有文件在/usr/share/nginx/html/下
 /etc/local/bin/find_ssd.sh 它用于检查 zpool 中是否存在任何问题。如果有任何问题，请尝试使用备用 ssd 来替换它
 节点重启时在做什么事，在执行/etc/bootinit.sh脚本
 denalios的系统脚本在/denali-setup下
 
 ganesha 日志文件可通过ps -ef | grep ganesha.nfsd查看 /etc/ganesha.log
ctdb 日志文件可通过ps -ef | grep ctdbd查看 /etc/log/log.ctdb
所有yml配置文件在/usr/share/denali-ansible/下
netstat -apn 查看节点端口占用情况
Cassandra 是一套开源分布式NoSQL数据库系统，非关联型数据库，初始化的时候要启用
由/var/log/denali/server/log.txt
可以看见集群初始化信息
(1).sudo -u denali ansible-playbook /usr/share/denali-ansible/initializeCluster.yml -e '{"clusterName":"Thunder_Cluster",
"memberIPAddrs":["192.168.28.141","192.168.28.142","192.168.28.143"],"VIP":"192.168.28.199","backendNetwork":"192.168.28.0/24","netmask":24}'

解释:主要执行initializeCluster.yml完成Cluster的初始化包括集群名称，各节点IP，后端网络地址及子网掩码

(2)sudo -u denali ansible-playbook /usr/share/denali-ansible/runCassandraContainers.yml -e '{"ipAddresses":["192.168.28.141","192.168.28.142",
"192.168.28.143"],"auto_bootstrap":"false","VIP":"192.168.28.199"}'

解释:主要执行runCassandraContainers.yml 初始化Cassandra数据库

(3)sudo -u denali ansible-playbook /usr/share/denali-ansible/updateLogging.yml -e '{"ipAddresses":["192.168.28.141","192.168.28.142","192.168.28.143"],
"auto_bootstrap":"false","VIP":"192.168.28.199","cassDatabase":"useDatabase"}'

解释:主要执行updateLogging.yml更新日志记录

(4)sudo -u denali ansible-playbook /usr/share/denali-ansible/createZFSPool.yml -e '{"resourceParams":{"Name":"denali-pool-raid50","VolumeFrom":"
denali-volumes","After":"resource-manifest","PoolAShift":12,"PoolConfig":"raidz1 /dev/sdy /dev/sdf /dev/sdo /dev/sdw /dev/sdd raidz1 /dev/sdm 
/dev/sdu /dev/sdb /dev/sdk /dev/sds raidz1 /dev/sdi /dev/sdq /dev/sdz /dev/sdg /dev/sdx raidz1 /dev/sde /dev/sdn /dev/sdv /dev/sdc /dev/sdl 
raidz1 /dev/sdt /dev/sdj /dev/sdr /dev/sdh /dev/sdp","Partitions":["proto1"]}}'

解释:主要执行createZFSPool.yml创建zpool

(5)sudo -u denali ansible-playbook /usr/share/denali-ansible/setZFSPoolQuota.yml -e '{"resourceParams":{"Name":"denali-pool-raid50","Pool":"denali_pool",
"Quota":"78444738724"}}'

解释:主要执行setZFSPoolQuota.yml设置ZFS zpool配额

(6)sudo -u denali ansible-playbook /usr/share/denali-ansible/createNFSService.yml -e '{"resourceParams":{"Name":"nfs","After":"resource-manifest",
"VolumeFrom":"denali-volumes","Partitions":["proto1"],"MaxRPCRecvBufferSize":"524288","MaxRPCSendBufferSize":"524288","Nbworker":"64","NFSProtocols":
"3,4"},"ipAddresses":["192.168.28.141","192.168.28.142","192.168.28.143"]}' && sudo -u denali ansible-playbook /usr/share/denali-ansible/
createGlusterService.yml -e '{"resourceParams":{"Name":"gluster","After":"resource-manifest,denali-pool-raid50","VolumeFrom":"denali-volumes"
,"Partitions":["proto1"]}}'

解释:主要执行createNFSService.yml配置集群的NFS服务

(7)sudo -u denali ansible-playbook /usr/share/denali-ansible/createCIFSService.yml -e '{"resourceParams":{"Name":"cifs","After":"resource-manifest,
denali-pool-raid50","VolumeFrom":"denali-volumes","Partitions":["proto1"],"Addresses":["192.168.28.141","192.168.28.142","192.168.28.143"]}}'

解释:主要执行createCIFSService.yml配置集群的CIFS服务

(8)runInUbuntu: sudo -u denali ansible-playbook /usr/share/denali-ansible/createVIP.yml -e '{"memberIPAddrs":["192.168.28.141","192.168.28.142",
"192.168.28.143"],"vipEntries":["192.168.28.199"],"mask":24,"interface":"eth1"}'

解释:主要执行createVIP.yml配置集群的CTDB服务

(9)sudo -u denali ansible-playbook /usr/share/denali-ansible/setTimezone.yml -e '{"resourceParams":{"timezonePath":"/usr/share/zoneinfo/Asia/Shanghai"}}'

解释:主要执行setTimezone.yml.yml配置集群的NTP服务

(10)sudo -u denali ansible-playbook /usr/share/denali-ansible/updateNodeJSTimezone.yml

解释:主要执行pdateNodeJSTimezone.yml更新时区

登陆进入UI，后端会不断刷新集群状态log.txt记录命令
sudo gluster --mode=script peer status //查询节点状态
sudo zfs get quota -rpH denali_pool -o name,value//查询zpool配额状态

创建卷replica 20G之后log出现信息
(11)sudo -u denali ansible-playbook /usr/share/denali-ansible/createVolume.yml -e '{"resourceParams":{"Name":"gluster-brick-replica0","After":
"denali-pool-raid50","VolumeFrom":"denali-pool-raid50","VolumeMount":"/mnt/gluster-brick-replica0","Service":"denali-pool-raid50","VolumeTag":
"glusterfs-brick-replica0","Compression":"off","Dedup":"off","Partitions":["proto1"],"RefQuota":"21G","Quota":"23G","Reservation":"none",
"VolumeType":"fs","ACLType":"noacl","XAttr":"sa"}}'

解释:主要执行createVolume.yml,初步分析是建立brick

(12)sudo -u denali ansible-playbook /usr/share/denali-ansible/createGlusterVolume.yml -e '{"resourceParams":{"Name":"gluster-volume-replica",
"VolumeFrom":"gluster","After":"gluster,gluster-brick-replica0","GlusterBricks":["/mnt/gluster-brick-replica0"],"Partitions":["proto1"],"Service":
"gluster","HardQuota":"20GB","SoftQuota":85,"VolumeType":"replica","ReplicaCount":"3","ArbiterCount":"1"}}'

解释:主要执行createVolume.yml,初步分析是建立volume
(13)
runInUbuntu: find /etc/denali/nfs/exports// -regex '.*.conf' 2>>/dev/null //将export配置文件置空
runInUbuntu: sudo dbus-send --print-reply --system --dest=org.ganesha.nfsd /org/ganesha/nfsd/ExportMgr org.ganesha.nfsd.exportmgr.ShowExport

暂不太清楚这条命令，可能是将之前的所有nfs服务重置

(14) runInUbuntu: ansible-playbook /usr/share/denali-ansible/getSnapshotUsage.yml -e '{"variable_hosts":"thisNode:node-02:node-03"}' || true

解释:主要执行getSnapshotUsage.yml,初步分析是获取快照信息

(15)sudo -u denali ansible-playbook /usr/share/denali-ansible/createNFSExport.yml -e \'{"resourceParams":{"Name":"gluster-export-replica","After":
"nfs,replical","ExportName":"gluster-export-replica","ExportPseudo":"","GlusterVolume":"replical","VolumeFrom":"replical","ExportAccessType":"NONE",
"Partitions":["proto1"],"ExportProtocols":"3","ExportTransports":"UDP,TCP","ExportID":"2","ExportDisableACL":"True","ExportSquash":"No_Root_Squash",
"Service":"nfs","ExportType":"glusterfs","AuxService":"gluster","Groups":[]}}\'',
解释:主要执行createNFSExport.yml,创建NFS导出
倒是这个版本有问题，创建导出失败
/var/log/denali/server/error.log马上有了信息
查找错误原因，因为/etc/denali/nfs/exports/gluster-volume-replica.conf中的volume 名字没有gluster前缀

(16) sudo -u denali ansible-playbook /usr/share/denali-ansible/createCIFSExport.yml -e '{"resourceParams":{"Name":"replica","After":"cifs,
gluster-volume-replica","ExportName":"replica","GlusterVolume":"gluster-volume-replica","VolumeFrom":"gluster-volume-replica","Partitions":
["proto1"],"HostsAllow":"","HostsDeny":"","Service":"cifs","AuxService":"gluster","Readonly":"no"}}'
解释:主要执行createCIFSExport.yml,创建CIFS导出

(17)
sudo -u denali ansible-playbook /usr/share/denali-ansible/createNFSExport.yml -e \'{"resourceParams":{"Name":"gluster-export-replica","After":
"nfs,replica","ExportName":"gluster-export-replica","ExportPseudo":"","GlusterVolume":"replica","VolumeFrom":"replica","ExportAccessType":"NONE",
"Partitions":["proto1"],"ExportProtocols":"3","ExportTransports":"UDP,TCP","ExportID":"2","ExportDisableACL":"True","ExportSquash":"No_Root_Squash",
"Service":"nfs","ExportType":"glusterfs","AuxService":"gluster","Groups":[{"Clients":["192.*"],"Access_type":"RW"}]}}\'

sudo -u denali ansible-playbook /usr/share/denali-ansible/createNFSExport.yml -e     
'{"resourceParams":{"Name":"'$NFS_EXPORT_NAME'", "After":"'$VOLUME_NAME'", "ExportName":"'$NFS_EXPORT_NAME'", "GlusterVolume":
"'$VOLUME_NAME'", "VolumeFrom": "'$VOLUME_NAME'", "ExportAccessType":"RW", "Partitions":["proto1"], "ExportProtocols":"3", "ExportTransports":
"UDP,TCP", "ExportID":"'$NFS_EXPORT_ID'", "ExportDisableACL":"True", "ExportSquash":"No_Root_Squash", "Service":"nfs", "ExportType":"glusterfs", 
"Groups": [{"Clients":["'$ALLOW_CLIENTS'"], "Access_type":"RW"}]}}'

创建卷两步：
1.创建brick(zfs)
sudo -u denali ansible-playbook /usr/share/denali-ansible/createVolume.yml -e '{"resourceParams":{"Name":"gluster-brick-test20","After":
"denali-pool-raid50","VolumeFrom":"denali-pool-raid50","VolumeMount":"/mnt/gluster-brick-test20","Service":"denali-pool-raid50","VolumeTag"
:"glusterfs-brick-test20","Compression":"off","Dedup":"off","Partitions":["proto1"],"RefQuota":"10.5G","Quota":"11.5G","Reservation":"none",
"VolumeType":"fs","ACLType":"noacl","XAttr":"sa"}}'
2。创建volume
sudo -u denali ansible-playbook /usr/share/denali-ansible/createGlusterVolume.yml -e '{"resourceParams":{"Name":"gluster-volume-test2","VolumeFrom"
:"gluster","After":"gluster,gluster-brick-test20","GlusterBricks":["/mnt/gluster-brick-test20"],"Partitions":["proto1"],"Service":"gluster",
"HardQuota":"10GB","SoftQuota":85,"VolumeType":"replica","ReplicaCount":"3","ArbiterCount":"1"}}'
集群反初始化步骤
1.
1.删除gluster所有卷，主要是ctdb() //先停止，再删除
2.执行反初始化脚本sudo -u denali ansible-playbook /usr/share/denali-ansible/destroyCluster.yml(最好每个节点都尝试一次)
3.重启server.js(ui 服务)
ps aux|grep node|grep server.js|awk '{print $2}'|xargs kill || daemon -O
/var/log/denali/server/log.txt -E /var/log/denali/server/error.txt node /var/denali-mw/server.js
4.解除相关挂载sudo umount /etc/denail/ctdb
5.重启ctdb vip节点(解除vip) sudo service ctdb restart
6.重启整个集群
要学会尝试看错误信息

在底层导出cifs共享时，带有特殊字符（在UI上通不过）在底层也能成功，在UI也能正常显示，就是不能删除，底层建立时也不应该包含特殊字符


