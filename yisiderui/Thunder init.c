ThunderStor �ײ�ʵ�ֹ���
sudo vagrant up �����������Ⱥ����ʱ��û�н�����Ⱥ��ϵ��ÿ���ڵ㶼�Ƕ�����
ui����־�ļ�/var/log/nginx/ Ŀ¼�£��������ļ�access.log��¼վ����־��error.log��¼������־
cluster ��������־�ļ�����/var/log/denali/�� 
���з�����־��/var/log/denali/server/�� error.log��¼������Ϣ log.txt��¼cluster��������Ϊ��¼ log4js.txt��¼��ʱ�����
ganesha �����ļ���/etc/ganesha/��
ganesha��export.conf��/etc/denali/nfs/export��
CTDB�����ļ���/usr/local/etc/ctdb/�¸�Ŀ¼�µ�nodes ��pubipaddrs��һ������������/etc/denali/ctdb/��
samba�����ļ�/etc/samba/smb.conf
ui�������ļ���/usr/share/nginx/html/��
 /etc/local/bin/find_ssd.sh �����ڼ�� zpool ���Ƿ�����κ����⡣������κ����⣬�볢��ʹ�ñ��� ssd ���滻��
 �ڵ�����ʱ����ʲô�£���ִ��/etc/bootinit.sh�ű�
 denalios��ϵͳ�ű���/denali-setup��
 
 ganesha ��־�ļ���ͨ��ps -ef | grep ganesha.nfsd�鿴 /etc/ganesha.log
ctdb ��־�ļ���ͨ��ps -ef | grep ctdbd�鿴 /etc/log/log.ctdb
����yml�����ļ���/usr/share/denali-ansible/��
netstat -apn �鿴�ڵ�˿�ռ�����
Cassandra ��һ�׿�Դ�ֲ�ʽNoSQL���ݿ�ϵͳ���ǹ��������ݿ⣬��ʼ����ʱ��Ҫ����
��/var/log/denali/server/log.txt
���Կ�����Ⱥ��ʼ����Ϣ
(1).sudo -u denali ansible-playbook /usr/share/denali-ansible/initializeCluster.yml -e '{"clusterName":"Thunder_Cluster",
"memberIPAddrs":["192.168.28.141","192.168.28.142","192.168.28.143"],"VIP":"192.168.28.199","backendNetwork":"192.168.28.0/24","netmask":24}'

����:��Ҫִ��initializeCluster.yml���Cluster�ĳ�ʼ��������Ⱥ���ƣ����ڵ�IP����������ַ����������

(2)sudo -u denali ansible-playbook /usr/share/denali-ansible/runCassandraContainers.yml -e '{"ipAddresses":["192.168.28.141","192.168.28.142",
"192.168.28.143"],"auto_bootstrap":"false","VIP":"192.168.28.199"}'

����:��Ҫִ��runCassandraContainers.yml ��ʼ��Cassandra���ݿ�

(3)sudo -u denali ansible-playbook /usr/share/denali-ansible/updateLogging.yml -e '{"ipAddresses":["192.168.28.141","192.168.28.142","192.168.28.143"],
"auto_bootstrap":"false","VIP":"192.168.28.199","cassDatabase":"useDatabase"}'

����:��Ҫִ��updateLogging.yml������־��¼

(4)sudo -u denali ansible-playbook /usr/share/denali-ansible/createZFSPool.yml -e '{"resourceParams":{"Name":"denali-pool-raid50","VolumeFrom":"
denali-volumes","After":"resource-manifest","PoolAShift":12,"PoolConfig":"raidz1 /dev/sdy /dev/sdf /dev/sdo /dev/sdw /dev/sdd raidz1 /dev/sdm 
/dev/sdu /dev/sdb /dev/sdk /dev/sds raidz1 /dev/sdi /dev/sdq /dev/sdz /dev/sdg /dev/sdx raidz1 /dev/sde /dev/sdn /dev/sdv /dev/sdc /dev/sdl 
raidz1 /dev/sdt /dev/sdj /dev/sdr /dev/sdh /dev/sdp","Partitions":["proto1"]}}'

����:��Ҫִ��createZFSPool.yml����zpool

(5)sudo -u denali ansible-playbook /usr/share/denali-ansible/setZFSPoolQuota.yml -e '{"resourceParams":{"Name":"denali-pool-raid50","Pool":"denali_pool",
"Quota":"78444738724"}}'

����:��Ҫִ��setZFSPoolQuota.yml����ZFS zpool���

(6)sudo -u denali ansible-playbook /usr/share/denali-ansible/createNFSService.yml -e '{"resourceParams":{"Name":"nfs","After":"resource-manifest",
"VolumeFrom":"denali-volumes","Partitions":["proto1"],"MaxRPCRecvBufferSize":"524288","MaxRPCSendBufferSize":"524288","Nbworker":"64","NFSProtocols":
"3,4"},"ipAddresses":["192.168.28.141","192.168.28.142","192.168.28.143"]}' && sudo -u denali ansible-playbook /usr/share/denali-ansible/
createGlusterService.yml -e '{"resourceParams":{"Name":"gluster","After":"resource-manifest,denali-pool-raid50","VolumeFrom":"denali-volumes"
,"Partitions":["proto1"]}}'

����:��Ҫִ��createNFSService.yml���ü�Ⱥ��NFS����

(7)sudo -u denali ansible-playbook /usr/share/denali-ansible/createCIFSService.yml -e '{"resourceParams":{"Name":"cifs","After":"resource-manifest,
denali-pool-raid50","VolumeFrom":"denali-volumes","Partitions":["proto1"],"Addresses":["192.168.28.141","192.168.28.142","192.168.28.143"]}}'

����:��Ҫִ��createCIFSService.yml���ü�Ⱥ��CIFS����

(8)runInUbuntu: sudo -u denali ansible-playbook /usr/share/denali-ansible/createVIP.yml -e '{"memberIPAddrs":["192.168.28.141","192.168.28.142",
"192.168.28.143"],"vipEntries":["192.168.28.199"],"mask":24,"interface":"eth1"}'

����:��Ҫִ��createVIP.yml���ü�Ⱥ��CTDB����

(9)sudo -u denali ansible-playbook /usr/share/denali-ansible/setTimezone.yml -e '{"resourceParams":{"timezonePath":"/usr/share/zoneinfo/Asia/Shanghai"}}'

����:��Ҫִ��setTimezone.yml.yml���ü�Ⱥ��NTP����

(10)sudo -u denali ansible-playbook /usr/share/denali-ansible/updateNodeJSTimezone.yml

����:��Ҫִ��pdateNodeJSTimezone.yml����ʱ��

��½����UI����˻᲻��ˢ�¼�Ⱥ״̬log.txt��¼����
sudo gluster --mode=script peer status //��ѯ�ڵ�״̬
sudo zfs get quota -rpH denali_pool -o name,value//��ѯzpool���״̬

������replica 20G֮��log������Ϣ
(11)sudo -u denali ansible-playbook /usr/share/denali-ansible/createVolume.yml -e '{"resourceParams":{"Name":"gluster-brick-replica0","After":
"denali-pool-raid50","VolumeFrom":"denali-pool-raid50","VolumeMount":"/mnt/gluster-brick-replica0","Service":"denali-pool-raid50","VolumeTag":
"glusterfs-brick-replica0","Compression":"off","Dedup":"off","Partitions":["proto1"],"RefQuota":"21G","Quota":"23G","Reservation":"none",
"VolumeType":"fs","ACLType":"noacl","XAttr":"sa"}}'

����:��Ҫִ��createVolume.yml,���������ǽ���brick

(12)sudo -u denali ansible-playbook /usr/share/denali-ansible/createGlusterVolume.yml -e '{"resourceParams":{"Name":"gluster-volume-replica",
"VolumeFrom":"gluster","After":"gluster,gluster-brick-replica0","GlusterBricks":["/mnt/gluster-brick-replica0"],"Partitions":["proto1"],"Service":
"gluster","HardQuota":"20GB","SoftQuota":85,"VolumeType":"replica","ReplicaCount":"3","ArbiterCount":"1"}}'

����:��Ҫִ��createVolume.yml,���������ǽ���volume
(13)
runInUbuntu: find /etc/denali/nfs/exports// -regex '.*.conf' 2>>/dev/null //��export�����ļ��ÿ�
runInUbuntu: sudo dbus-send --print-reply --system --dest=org.ganesha.nfsd /org/ganesha/nfsd/ExportMgr org.ganesha.nfsd.exportmgr.ShowExport

�ݲ�̫���������������ǽ�֮ǰ������nfs��������

(14) runInUbuntu: ansible-playbook /usr/share/denali-ansible/getSnapshotUsage.yml -e '{"variable_hosts":"thisNode:node-02:node-03"}' || true

����:��Ҫִ��getSnapshotUsage.yml,���������ǻ�ȡ������Ϣ

(15)sudo -u denali ansible-playbook /usr/share/denali-ansible/createNFSExport.yml -e \'{"resourceParams":{"Name":"gluster-export-replica","After":
"nfs,replical","ExportName":"gluster-export-replica","ExportPseudo":"","GlusterVolume":"replical","VolumeFrom":"replical","ExportAccessType":"NONE",
"Partitions":["proto1"],"ExportProtocols":"3","ExportTransports":"UDP,TCP","ExportID":"2","ExportDisableACL":"True","ExportSquash":"No_Root_Squash",
"Service":"nfs","ExportType":"glusterfs","AuxService":"gluster","Groups":[]}}\'',
����:��Ҫִ��createNFSExport.yml,����NFS����
��������汾�����⣬��������ʧ��
/var/log/denali/server/error.log����������Ϣ
���Ҵ���ԭ����Ϊ/etc/denali/nfs/exports/gluster-volume-replica.conf�е�volume ����û��glusterǰ׺

(16) sudo -u denali ansible-playbook /usr/share/denali-ansible/createCIFSExport.yml -e '{"resourceParams":{"Name":"replica","After":"cifs,
gluster-volume-replica","ExportName":"replica","GlusterVolume":"gluster-volume-replica","VolumeFrom":"gluster-volume-replica","Partitions":
["proto1"],"HostsAllow":"","HostsDeny":"","Service":"cifs","AuxService":"gluster","Readonly":"no"}}'
����:��Ҫִ��createCIFSExport.yml,����CIFS����

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

������������
1.����brick(zfs)
sudo -u denali ansible-playbook /usr/share/denali-ansible/createVolume.yml -e '{"resourceParams":{"Name":"gluster-brick-test20","After":
"denali-pool-raid50","VolumeFrom":"denali-pool-raid50","VolumeMount":"/mnt/gluster-brick-test20","Service":"denali-pool-raid50","VolumeTag"
:"glusterfs-brick-test20","Compression":"off","Dedup":"off","Partitions":["proto1"],"RefQuota":"10.5G","Quota":"11.5G","Reservation":"none",
"VolumeType":"fs","ACLType":"noacl","XAttr":"sa"}}'
2������volume
sudo -u denali ansible-playbook /usr/share/denali-ansible/createGlusterVolume.yml -e '{"resourceParams":{"Name":"gluster-volume-test2","VolumeFrom"
:"gluster","After":"gluster,gluster-brick-test20","GlusterBricks":["/mnt/gluster-brick-test20"],"Partitions":["proto1"],"Service":"gluster",
"HardQuota":"10GB","SoftQuota":85,"VolumeType":"replica","ReplicaCount":"3","ArbiterCount":"1"}}'
��Ⱥ����ʼ������
1.
1.ɾ��gluster���о���Ҫ��ctdb() //��ֹͣ����ɾ��
2.ִ�з���ʼ���ű�sudo -u denali ansible-playbook /usr/share/denali-ansible/destroyCluster.yml(���ÿ���ڵ㶼����һ��)
3.����server.js(ui ����)
ps aux|grep node|grep server.js|awk '{print $2}'|xargs kill || daemon -O
/var/log/denali/server/log.txt -E /var/log/denali/server/error.txt node /var/denali-mw/server.js
4.�����ع���sudo umount /etc/denail/ctdb
5.����ctdb vip�ڵ�(���vip) sudo service ctdb restart
6.����������Ⱥ
Ҫѧ�᳢�Կ�������Ϣ

�ڵײ㵼��cifs����ʱ�����������ַ�����UI��ͨ�������ڵײ�Ҳ�ܳɹ�����UIҲ��������ʾ�����ǲ���ɾ�����ײ㽨��ʱҲ��Ӧ�ð��������ַ�


