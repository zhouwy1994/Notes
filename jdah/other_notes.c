<<<<<<< HEAD
************************Keep Note********************************
������װcentos minimal release��ɺ�sudo install net-tools ��װ�����๤��
�������� vi /etc/sysconfig/network-scripts/ifcfg-ens33 ����ip���䷽ʽdhcp static device name=eth0
�������� sudo systemctl restart network.service PS�����л���redhat������Linux release����rhel7֮�����з����
֮ǰ��service servername start �ĳ�ͳһ������systemctl start servername.service�ķ�ʽ����
һ����Ҫ�����⣬�ҵ�����device name��Ȼ����eth0�����Һܲ�ϰ�ߣ��ҽ�devicename�ĳ�eth0�ٽ�ifcfg-ens33�ĳ�ifcfg-eth0����
���ֻ���ens33
�����ϲ���һ�£�������rhel6/centos6��ʼ������***�豸��Ԥ����������***,��Ž��ͣ�֮ǰ��ͳ��linux��ö��������ʽ(eth0 eth1..)
�����������豸������Щ���Ʋ���һ������ʵ�ʵ�Ӳ����ۣ�PCIλ�ã�USB�ӿ������ȣ���������һ��**����Ԥ֪������**���⣨���磬���ڲ�
ȷ�����豸̽����Ϊ��������ܻᵼ�²�ͬ���������ô������磬������Ľӿڸ�������Ľ�ֹ�ӿڻ��߷���ǽ��·����
����rhel6��Ȼ�������豸��Ԥ���������򣬵���Ĭ����û��enable����Ҫ�ֶ���rhel7֮�������Ĭ�Ͽ���

������Ԥ����������ĺô�:��Ԥ�������������豸��Ӳ����ۣ�PCIλ�ã��ӿ����Ʊ��Զ����ڹ̼������˽ṹ��λ����Ϣ��ȷ�������ڣ�
��ʹ��ӻ��Ƴ������豸���ӿ�������Ȼ���̶ֹ�������������ö�٣��ͻ�����Ӳ�������޷��滻������˵ϵͳ����Ա���Ը����豸������ȷ��λ
Ӳ����������1\2\3��������ʽ
����֮ǰ��ϰ����ö�������������С��鲻��Ӧ�ˣ����沽����Ի�ԭö����������
1�����ȣ������������øÿ�Ԥ������������Ҫ������ʱ���ݡ�net.ifnames=0�����ں˲���������ͨ���༭/etc/default/grub������
��net.ifnames=0 biosdevname=0����GRUB_CMDLINE_LINUX������ʵ�ֵ�
2��ʹ������Ч�Ը����ں˲���
sudo grub2-mkconfig -o /boot/grub2/grub.cfg
3��sudo vi /etc/sysconfig/network-scripts/ifcfg-ens33 ����devive=eth0 ����sudo mv ifcfg-ens33 ifcfg-eth0
4������:sudo reboot ��ifconfig �鿴�Ƿ��޸ĳɹ�

�رշ���ǽsudo systemctl disable firewall
����selinux vi /etc/selinux/config ��SELINUX=enforcing�ĳ�disable
linux ֮���ssh���ܵ�½���÷�ʽ����ͨ��ssh��½github������
��ssh�ͻ���~/.sshĿ¼��ʹ��ssh-keygen -t rsa����һ��id_rsa.pub�ļ��������ļ������ݿ�����ssh��������.sshĿ¼�µ�authorized_keys
�м���ʵ�����ܵ�½
rehl�������Դ mv /etc/yum.repo/Centos-Bash.repo /etc/yum.repo/Centos-Bash.repo.back 
wget http://mirrors.163.com/.help/CentOS7-Base-163.repo ��yum.repoĿ¼��
sudo yum clean all ���֮ǰ����� sudo yum makecache ��������ļ�
fdisk /dev/sda ��sda���̷���
mkfs.ext4 /dev/sda1 ��ʽ������(�ȷ����ٸ�ʽ����windows�е�����)
��������vi /etc/rc.local (����ִ�еĽű�)
PS:�����linux����ķ��񿪻�������������chkconfig on service or systemctl enable service��
�󲿷�LINUX release���ɽ���������ŵ�/etc/rc.local��
samba�������ļ���/etc/samba/smb.conf
������������ln -s source destion
��װctdb sudo yum -y install ctdb

linux����������/etc/rc.local��ԭ�������ӦΪrc.localû��xȨ��chmod +x rc.local
smb��������û�sudo smbpasswd -a username
�κ��ٿ�������ִ��ʧ�ܶ�Ҫ�ټ�sudo��ִ��һ��
�Ƽ�����ַ���ģʽ:������Infrastructure��������ʩ��-as-a-Service��Platform��ƽ̨��-as-a-Service��Software�������-as-a-Service��
iaas:t�ṩ�ײ�Ӳ�����������
paas:�ṩ������Լ�����ϵͳ�ȿ���ƽ̨�����ϲ�Ӧ���ṩapi�ӿ�
saas:�����Ӧ�ü���
ubuntuĬ�ϰ�װʱglusterfs3.4���Ҫ��װglusterfs3.8��������ppaԴ������source.list�����glusterfs���Դ
ubuntu�ķ���ǽufw

ͨ��cifs����glusterfs samba����
sudo mount -t cifs -o username=zhouwy,password=1 //192.168.0.141/public /mnt/cifs_export
����cifs��������(common internet file system)ͨ�������ļ�ϵͳ��ʽwindows�ϳ��õ�һ�ִ�ӡ�����ļ�����Э��
username password�ǵ�½samba���û���������,��glusterfs-server��ͨ��sudo smbpasswd -a username����
192.168.0.141 glusterfs-server��public ipadders����ʵ�ʵ�ip����ctdb�ṩ
/mnt/cifs_export ����Ŀ¼


nfs-ganeshe���Բ�ͨ���ں�ֱ����FUSEͨ��,����������ں˿�֧�������gluster�ķ�������
libgfapi.so ��gluster3.4֮�������ͨ�Ż��ƣ�ͨ��libgfapi.so��ʽ�ķ��ʿ��Բ�����kernel fuseֱ����glusterdͨ�š�
�����������ͨ��fuse���ʷ�ʽ������˵���������
free �����ʹ��,free�Ǽ���ڴ�ʹ�����������,
-b����ByteΪ��λ��ʾ�ڴ�ʹ������� 
-k����KBΪ��λ��ʾ�ڴ�ʹ������� 
-m����MBΪ��λ��ʾ�ڴ�ʹ������� 
-o������ʾ�����������У� 
-s<�������>�������۲��ڴ�ʹ��״���� 
-t����ʾ�ڴ��ܺ��У� 
-V����ʾ�汾��Ϣ��
total���ڴ������� u
sed���Ѿ�ʹ�õ��ڴ����� 
free�����е��ڴ����� 
shared����ǰ�Ѿ��������ã�
buffers Buffer�������ڴ����� 
cached Page�������ڴ�����

total = used + free
(-buffers/cache) used�ڴ�������һ����Mem���е� used �C buffers �C cached 
(+buffers/cache) free�ڴ���: ��һ����Mem���е� free + buffers + cached
�ɼ�-buffers/cache��ӳ���Ǳ�����ʵʵ���ڳԵ����ڴ棬
��+buffers/cache��ӳ���ǿ���Ų�õ��ڴ�������
 
����$ sudo dpkg -purge glusterfs����������ļ���
gluster��һ���������þ������Ǵ�LVM(Logical Vlome Manager)�߼������
pvcreate vgcreate lvcreate pvdisplay vgdisplay lvdisplay
���brick��brick�ϴ���
RPC(remote procedure call protocol)Զ�̹��̵���Э�飬��һ��ͨ��������Զ�̼������������Э��
glusterfs��self heal deamon����/var/log/glusterfs/glustershd.logÿ���������϶���һ���������
GlusterFS����չ��ܻ��ھ������õ�LVM���ա�Ҫʹ�ÿ��չ��ܣ�GlusterFS��Ӧ�����������Ⱦ�������
ÿ��ש��Ӧ���ڶ����ı�����LVM�ϡ�
Brick LVM��Ӧ�ð���ש������������ݡ�
û��һ��שӦ����һ����ʵ��LVM�ϡ�
��������汾ӦΪ3.6�����ϡ�
NFS-Ganesha��NFSЭ����û��ռ��ļ���������֧��NFSv3��v4��v4.1��pNFS�����ṩ��FUSE���ݵ��ļ�ϵ
ͳ����㣨FSAL�����������ļ�ϵͳ������Ա�����Լ��Ĵ洢���ƣ������κ�NFS�ͻ��˷�������NFS-Ganesha��
��ͨ����FSALֱ�ӷ���FUSE�ļ�ϵͳ�����������ں˸����κ����ݣ��Ӷ��п��ܸ�����Ӧʱ�䡣
tail һ�����ڲ鿴��־�ļ�,��Ϊ��־�ļ����µ��ں���
tail -f ����tailf���Զ�̬�쿴��־
ִ����������ɹ�����NFS����
sudo -u denali ansible-playbook /usr/share/denali-ansible/createNFSExport.yml -e '{"resourceParams":{"Name":"gluster-export-replica","After":"nfs,copy","ExportName":"gluster-export-replica","ExportPseudo":"","GlusterVolume":"gluster-volume-replica","VolumeFrom":"copy","ExportAccessType":"NONE","Partitions":["proto1"],"ExportProtocols":"3","ExportTransports":"UDP,TCP","ExportID":"3","ExportDisableACL":"True","ExportSquash":"No_Root_Squash","Service":"nfs","ExportType":"glusterfs","AuxService":"gluster","Groups":[{"Clients":["192.168.*"],"Access_type":"RW"}]}}'
�޸�vagrant�������ļ���,Ҫʹ��vagrant reload ����Ż���Ч
ansible��һ���Զ�����ά���ߣ�����phthon���Ա�д������һ�����ͨ��sshԶ�̵�¼��Ⱥִ������������ִ���������������playbook��yml�ű�
char *const ptr;//ָ�볣������ָ����һ������,ָ����only read
char const *ptr OR const char *ptr//����ָ�룬��ָ����ָ��һ��������������only read
�쿴Ubuntu�Ѿ���װ�������,dpkg -l �鿴·��dpkg -L

��洢 ����洢 �ļ��洢
1.��洢:���̴洢����ͳ�洢block��ceph
2.����洢 object storage
3.�ļ��洢��NFS CIFS FTP

ssh ��Կ��½ ��client .sshĿ¼�µ�id_rsa.pub���ݿ�����server .sshĿ¼�µ�authorized_keys Ȼ������/etc/ssh/ssh_conf ���
RSAAuthentication yes        # ���� RSA ��֤��Ĭ��Ϊyes
PubkeyAuthentication yes     # ���ù�Կ��֤��Ĭ��Ϊyes
Զ��ִ������ssh -p $port $uesrname@$remote_id 'cmd'
port һ��Ϊ22
ldconfig�������;��Ҫ����Ĭ����ѰĿ¼/lib��/usr/lib�Լ���̬�������ļ�/etc/ld.so.conf�����е�Ŀ¼�£��������ɹ���Ķ�
̬���ӿ⣨��ʽ��lib*.so*��,������������̬װ�����(ld.so)��������Ӻͻ����ļ��������ļ�Ĭ��Ϊ/etc/ld.so.cache�����ļ���
�����ź���Ķ�̬���ӿ������б�Ϊ���ö�̬���ӿ�Ϊϵͳ�����������ж�̬���ӿ�Ĺ�������ldconfig����ִ�г�������/sbinĿ¼�¡�
�ļ��ض���C���Ժ���fp = freopen("error.log", "w+", stderr);//����׼��������ض���error.log
�����fd�Ĳ������Ƕ�stderr�Ĳ���
umask������:����ͨ�ļ���xλû�����ã�ֻ��Ŀ¼��xλ������
������س���wrong fs type, bad option,//֤��û�и����͹��ߵĹ�������,�� mount -t nfs����Ҫ�Ȱ�װnfs-common
ssh denali@${Vm_ip}�����������û�����¼
ssh -p 22 denali@${VM_ip} 'cmd'Զ��ִ�����ǰ���ǹ�Կ��½
wget -O ָ�������� url
scp Զ�̸���,����sshЭ�� scp username@hostname:path localhost:path
xshell5ѡ�����ϲ�֮��Ͳ�����ͬһ������ʾ,����ջ�,������Ϊ�Ựѡ�û��ѡ��,ѡ��鿴---->�Ựѡ�
����:ÿ�봫���λ��20M,1M=1000000b 20M=20000000b/s=2M/s,20G����=2G/s
������Ϊÿ�봫���������
�������ʹ��������:����Ϊÿ������ܴ������������������Ϊÿ��ʵ�ʴ���ֵ��eg��һ��·һ����ͨ��100���������Ǵ�����ĳһ������56��ͨ���������ʵ��������
fuser�������ڱ������ʹ�õ��ļ��������׽��֡�fuser�����г��˱��ؽ��̵Ľ��̺ţ���Щ���ؽ���ʹ��file������ָ���ı��ػ�Զ���ļ������������ر��豸��������
�г���ʹ�ø��豸���κ��ļ��Ľ��̡�
fuser -k /mnt/nfs_test ���豸æʱ��ǿ��ɱ��

vagrant �½������,Ҫ������֮ǰ�ľɰ汾,vagrant box list,vagrant box remove
��vagrant up
lsof�������ڲ鿴����̿�����ļ������ļ��Ľ��̣����̴򿪵Ķ˿�(TCP��UDP)���һ�/�ָ�ɾ�����ļ�����ʮ�ַ����ϵͳ���ӹ��ߣ�
��Ϊlsof������Ҫ���ʺ����ڴ�͸����ļ���������Ҫroot�û�ִ�С�
lsof -p PID �鿴���̴򿪵�fd socket ռ�ö˿���Ϣ��
glusterfs���ٲþ�Ҳ��Ҫ�洢��Դ������UI����ʾûռ�ռ�(ThunderStor)
ΪʲôVIP��Ư�Ƶ�����һ̨����������ͬ�Ĳ���
��Ϊ3̨�ڵ�󲿷ֲ�������ÿһ���ڵ��϶������ظ��Ĳ�����ͬ����NFS����ͬ����CIFS����
�ٲ�brickֻ��Ԫ����
sataӲ����������,sda sdb ����sdz�ʹ�sdaa sdab..��ʼ
UI��NFS�����ͨ��export.confȷ����CIFSͨ��smb.confȷ��
���·������sudo route add default gw 192.168.28.254 eth0 or ip route add default via 192.168.28.254 default�ɸ�Ϊ�ض�ip
�鿴ָ���������� ethtool eth0 
��������Ӳ��
vboxmanage createhd --filename new.vdi --size 4096//����������̾���(virtual disk image)
vboxmanage storageattach node-01 --storagectl SATAController --port 26 --type hdd --medium new.vdi//���½��Ĵ��̾�����ӵ�sata������SATAContrller
//node-01:���������  SATAController:SATA����������
�޸�vdi��С
vboxmanage modifyhd $hdd-id --resize 20480

initctl -- init daemon control tool//Linux�ػ����̹�����
--list //�г������ػ�����
start                       Start job.
  stop                        Stop job.
  restart                     Restart job.
  reload                      Send HUP signal to job.
  status                      Query status of job.
  list                        List known jobs.
ssh ��������root�û���¼����ȫ�Կ���sshd_config /etc/ssh/sshd_config ��PermitRootLogin yes service sshd restart
ansible copyģ�齫�����������ļ����Ƶ�Զ�̽ڵ�
ansible cluster -m copy -s -a "src=/etc/apt/sources.list dest=/etc/apt/sources.list" //-s sudo
lsblk�鿴��ǰ�������д���
pgrep -u root,daemon �鿴��������root���ػ����̣�����ָ���û��Ľ���
pkill ɱ�����ҵ��Ľ���,(���ݽ�����)
virtualbox Vrde Զ������������ò���
���������
1.VBoxManage createvm --name ocentos --ostype RedHat --register --basefolder/data/vmos/
virtualbox name:centos
ostype RedHat vboxmanage list ostypes
2.VBoxManage modifyvm ocentos --memory 512 --vram 8 --acpi on --ioapic on --
boot1 disk --boot2 dvd --nic1 bridged --nictype1 Am79C973 --bridgeadapter1
eth0 --mouse usb --keyboard usb //�������ӵ����ͨ������Ĺ���
3.VBoxManage storagectl ocentos --add sata --name "SATA Controller" --controller
IntelAhci --bootable on //���SATA������
4.VBoxManage createhd --filename /data/vmos/ocentos/ocentos.vdi --size 20480 --format vdi --variant Fixed//����һ�����̾���(vdi)��20G
5.VBoxManage storageattach ocentos --storagectl "SATA Controller" --port 0 --device 0 --type hdd --medium /data/vmos/ocentos/ocentos.vdi
//�������Ĵ��̾�����ӽ�SATA������
6.VBoxManage storageattach ocentos --storagectl "SATA Controller" --port 1 --
device 0 --type dvddrive --medium /home/hto/sf/os/centos-5.8-i386-netinstall.iso
//���dvd��������������ӽ�SATA������
���ϲ���ſ��Դ���һ�������
����vrde
vboxmanage modifyvm centos --vrde on --vrdeport 3389 --vrdeaddress 0.0.0.0
���������vboxmanage -s centos --vrde on
vboxmanage modifyvm vmname --cpus 3 �޸�cpu����Ϊ3
windows ʹ��TightVNC�ͻ���http://www.tightvnc.com/download.php
����������ַ(Ҳ�����������Ӧ������ �˿�)������ ֱ��ȷ��

kvm VNC 
1.  �޸�qemu.conf
# vi /etc/libvirt/qemu.conf 
vnc_listen = "0.0.0.0"
˵��1��vnclisten Ĭ�ϰ�127.0.0.1 �������ļ���ָ��VNC ��0.0.0.0IP,�Ͳ����ڰ�װkvm�����ʱָ��vnclisten�����ˡ�
˵��2���������������кܶ���������ʱ����Ҫָ��ÿ��������Ķ˿ڣ����򽫻���ҡ�
2.  �޸�����������ļ�
# virsh edit oeltest01
<graphics type='vnc' port='5910' autoport='no' listen='0.0.0.0'>       
  <listen type='address' address='0.0.0.0'/>        
</graphics>

free��top��ʾ�����Ϊʲô��ͬ��
free������ʾ�����ݣ���һ�е���������ϵͳ�ӽǿ��ģ��ڶ��е���������Ӧ�ó�����ӽǿ��ġ�
��һ�е�usedһ������ݲ�����������ʹ�õ��ڴ棬������buffers��cached���ڴ棬��˿���ȥ���õ��ڴ���١�
�ڶ��е����ݣ��ֱ���used-buffers-cached����free+buffers+cached������һ�³����ܵ��ڴ�ʹ������
(total - free - buffers - cached) / total = 0.038 ���ң����top��ʾһ��0.0Ҳûʲô���⡣

kvm��װubuntu
qemu-img create -f qcow2 /home/zhouwy/images/disk.qcow2 10G\\����qcow2��ʽ����
virt-install --virt-type kvm --name ubuntu345 --ram 1024 --cdrom=/home/zhouwy/iso/ubuntu.iso  \
--disk path=/home/zhouwy/images/disk.qcow2,size=10,format=qcow2 --network network=default --graphics vnc,listen=0.0.0.0,port=6876 \
--noautoconsole --os-type=linux --os-variant=ubuntutrusty//vnc��ʽ
ע��:��װֻ�е�һ�ο��Խ���
--extra-args='console=tty0 console=ttyS0' \\�ַ����淽ʽ
qemu-kvm�������ļ���/etc/libvir/.xml
virt-clone��¡�����
virt-clone --connect=qemu:///system -o ubuntutest -n ubuntunew -f ./disk2.img -m 52:54:00:66:87:73
Ҳ����ֱ��ͨ��xml����virsh define new.xml ��Ҫ�޸ĵĲ���:domain name;uuid;mac;disk
disk һ�����Ѿ�װ������ϵͳ��disk
qemu-img convert -f qcow2 -O raw disk.qcow2 rbd:pool/image
���У���������qemu-img����������ʱ����qcow2ת����raw��ʽ����������KVM����
������Ceph RBD�洢ʱ��������raw�ķ��ʸ�ʽ�����ڴ˲�����ת����raw��ʽ��
������ĳ�����δ���DHCPʱ���Ͳ������þ�̬ip��ֻҪ������IP��û�����꣬��mac��ַ���ֲ��������£�һ�����õ��ĵ�ַ�����
ubuntu�鿴�����б����  
sudo service --status-all
sudo initctl list
*************************************
��Ҫ:�ı���־ʱ����dateSʱ�䲻һ��
*************************************
����ʱ��:tzselect,������ʾ����ʱ��Asia--->China----->Beijing--->Save

pidof pidof -- find the process ID of a running program.����һ���������н��̵Ľ��̺�
��pgrep������ͬ����pgrep��ȣ�pidof����������̵�ȫ����
ubuntu�ɾ�ж�����sudo apt-get autoremove app-name --purge //ɾ�������ļ�

�û�����ִ��sudo����
���� chmod +w /etc/sudoers sudo visudo 
������м� username ALL=NOPASSWD:ALL
chmod -w /etc/sudoers
sshpass ���� SSH����(ssh��sftp��scp��)��
    ����:
        -p password    //������password��Ϊ���롣
        -f passwordfile //��ȡ�ļ�passwordfile�ĵ�һ����Ϊ���롣
        -e        //����������SSHPASS��Ϊ���롣

    ����˵��
        scp abc@192.168.0.5:/home/xxx/test /root   �������������ǽ����������ļ�test���������ļ���/root�¡�
        ����sshpass����������Ϊefghi�����д����
        ssh -p efghi scp abc@192.168.0.5:/home/xxx/test /root

���⣬����ssh�ĵ�һ�ε�½������ʾ����Are you sure you want to continue connecting (yes/no)������ʱ��sshpass�᲻��ʹ�����������
1.������ssh���������� -o StrictHostKeyChecking=no�����������˵���������Ϳ���д��ssh -p efghi scp abc@192.168.0.5:/home/xxx/test /root -o StrictHostKeyChecking=no��
2.����д�������ļ����� StrictHostKeyChecking no �ӵ�/etc/ssh/sshconfig ������ssh�ͻ����Զ�������������hostkey,����ÿ�ζ��Լ�����yes

����Դ���� sed -i 's/\([[:alnum:]]\+\.\)\+com/mirrors.163.com/g' /etc/apt/sources.list
ssh-copy-id -i .ssh/id_rsa.pub remotemast
������Կ

sudo -s���rootȨ�޵�����ԭ�Ȼ�������
shll scripts ������vi����﷨��notdpad++�﷨��鲻����
�޸������·��:vboxmanage setproperty machinefolder "/mnt/vdisk/VMs"

Linux���ӽ�������(swap)�ķ���
1.�½�һ���ļ����߷���(��СΪ����Ҫ����swap�Ĵ�С)
dd if=/dev/zero of=file.swap bs=1M count=4096 //4G
or
fdisk /dev/sd* -->n  //4G

2.��ʽ���ļ������
mkswap file.swap or mkswap /dev/sd*
3.����swap����
swapon file.swap or swapon /dev/sd*

4.�ر�swap����
swapoff file.swap or swapon /dev/sd*
���Ϸ�������ʵЧ������fstab �������swapon����

virtualbox�������������ûװ������������ʱ������ͨ���Žӷ�ʽ����������(���߿���)
��ʱֻ��ͨ�������ַת��(NAT)��ʽ������������NAT����һ�����⣬����������ַ10.0.2.15
xshell�ǲ���ʶ��˵�ַ�ģ�ֻ����������˿�ת��
��������Ķ˿�Ӱ����������22�˿ڣ�Ȼ����xshell ssh $username@$ip $port
����·����������

vi ��ʽ�������
����һ:
ESC
gg=G

������:
shift -v ���ӻ�ģʽ
ѡ�д���
=
LVM(Logical Vlome Manager)�߼������
�������õĴ�����
��������:
*����洢���ʣ�PhysicalStorageMedia��
ָϵͳ������洢�豸�����̣��磺/dev/hda��/dev/sda�ȣ��Ǵ洢ϵͳ��ײ�Ĵ洢��Ԫ��
*�����Physical Volume��PV��
ָ���̷�������߼�������̷�������ͬ�����ܵ��豸����RAID������LVM�Ļ����洢�߼��飬���ͻ���������洢���ʣ�����������̵ȣ��Ƚϣ�ȴ��������LVM��صĹ��������
*���飨Volume Group��VG��
�����ڷ�LVMϵͳ�е�������̣�����һ�����������PV��ɡ������ھ����ϴ���һ������LV���߼�����
*�߼���Logical Volume��LV��
�����ڷ�LVMϵͳ�еĴ��̷������߼������ھ���VG֮�ϡ����߼���LV֮�Ͽ��Խ����ļ�ϵͳ������/home����/usr�ȣ���
*����飨Physical Extent��PE��
ÿһ�������PV������Ϊ��ΪPE��Physical Extents���Ļ�����Ԫ������Ψһ��ŵ�PE�ǿ��Ա�LVMѰַ����С��Ԫ��PE�Ĵ�С�ǿ����õģ�Ĭ��Ϊ4MB�����������PV���ɴ�С��ͬ�Ļ�����ԪPE��ɡ�
*�߼��飨Logical Extent��LE��
�߼���LVҲ������Ϊ�ɱ�Ѱַ�Ļ�����λ����ΪLE����ͬһ�������У�LE�Ĵ�С��PE����ͬ�ģ�����һһ��Ӧ��
��Ӧ����:
1�����������:
pvcreate /dev/sdb1 //������洢����/dev/sdb1������һ�������
2����������:
vgcreate vg_name /dev/sdb1 /dev/sdb2 ...
3���������
Ϊ������ʹ�þ����������������ϵͳ������ʹ��vgchange��������飺
#vgchange -ay web_document
5������µ������������
��ϵͳ��װ���µĴ��̲��������µ��������Ҫ������ӵ����о���ʱ������Ҫʹ��vgextend���
lvextend   web_document /dev/hdc1 //��Ӵ��̵��߼�����
#vgextend web_document /dev/hdc1
6���Ӿ�����ɾ��һ�������
Ҫ��һ��������ɾ��һ�����������Ҫȷ��Ҫɾ���������û�б��κ��߼�������ʹ�ã���Ҫʹ��pvdisplay����쿴һ�����������Ϣ��
���ĳ����������ڱ��߼�����ʹ�ã�����Ҫ�������������ݱ��ݵ������ط���Ȼ����ɾ����ɾ������������Ϊvgreduce��
#vgreduce web_document /dev/hda1
7�������߼���
�����߼��������Ϊlvcreate��
#lvcreate -L1500 -n www1 web_document
��������ھ���web_document�ϴ�������Ϊwww1����СΪ1500M���߼��������豸���Ϊ /dev/web_document/www1��web_documentΪ��������www1Ϊ�߼���������
���ϣ������һ��ʹ��ȫ��������߼������� Ҫ���Ȳ쿴�þ����PE����Ȼ���ڴ����߼���ʱָ����
#vgdisplay web_document | grep"TotalPE"
TotalPE45230
#lvcreate -l45230 web_document -n www1

��ldd�鿴һ��hcsh���ӵĿ�Բ��� ��������nm�鿴һ�¶�Ӧ��������û�������������

vim�ظ���������:
1�������������Ҫע�͵��ĵ�һ������->ESC->qa->i->#->ESC->j->q
����qa: q�ǿ�ʼ¼�ƣ�����������֣�������a,Ҳ����������
���һ��q��ʾ����¼��
@a���ظ��ո�¼�Ƶ�a
10@a���ظ�10��
 
2������һ�ַ��������ǿ����:
Ctrl+v, ѡ���У�I, #, ESC
��ʼ��ʱ��о��ǲ��У����������Ǻ����� I �Ǵ�д�ġ�:)

3��v����virtualģʽ��ѡ�������У�crtl+v������ģʽ(shift+v��ģʽ)����дI������֮ǰ����ע�ͣ���������ESC,���в���
shell����UI�ӿ�(http)
curl "http://"
crul -d "name=pool&type=replica" "http://"�ύ������HTTP POST��ʽ��������

crtl +r ������ʷ����

C������д��ʽ�ؼ��ֺ�() {}��ؼ���֮�䶼Ӧ����һ���ո�
for (i < 0) {
	...
}

�޽������������vboxmanage --startvm --type headless
�鿴ĳ�������Ķ˿���Ϣ netstat -anp | grep $servername

�̰߳�ȫ���Ƕ��̷߳���ʱ�������˼������ƣ���һ���̷߳��ʸ����ĳ������ʱ��
���б����������̲߳��ܽ��з���ֱ�����̶߳�ȡ�꣬�����̲߳ſ�ʹ�á������������
��һ�»���������Ⱦ�� �̲߳���ȫ���ǲ��ṩ���ݷ��ʱ������п��ܳ��ֶ���߳��Ⱥ�
��������������õ��������������ݡ�

linux���̼߳�ͬ������:�������������������ź���
linux�½��̼�ͨ�ŷ�ʽ���ܵ�(�����ܵ��������ܵ�)���źš������ڴ桢��Ϣ���С�socket���ź���


notepad++����ע�Ϳ�ݼ�ctrl + k ctrl + q ȡ������ע��:ctrl + shift + k

SSL �����׽���Э��㣨һ�ּ��ܵ�ͨѶЭ��������ʹ������������֮�䣬Security Socket Layer��
�����׽��ֲ��һ�ּ���Э�飬��˽��Կ�ԣ������ͨ����Կ������Ϣ��ʹ��˽Կ����

ssh��ȫ���ò���:
��װsshd sudo apt-get install openssh-server
���� ֹͣ �������� ״̬ sudo service ssh start stop restart
�����Ǹ��˵�VPS������ҵ���������ʵķ��������������22�˿ڵ�SSH�����¼��֤��ʽ�����ڶ�ڿͱ����½�ͱ�ƾջ�Ҳ�����Ǿ��������ĲҾ硣
��ҵ����ͨ������ǽ�������ƣ���ͨ�û�Ҳ���ܽ����޸�22�˿ں�ǿ��������ȷ�ʽ��������Ŀǰ��԰�ȫ�ͼ򵥵ķ���������SSHʹ����Կ��¼����
ֹ�����¼��

�޸������ļ� sudo vim /etc/ssh/sshd_config
#����������֤
PasswordAuthentication no
#������Կ��֤
RSAAuthentication yes
PubkeyAuthentication yes
#ָ����Կ���ݿ��ļ�
AuthorsizedKeysFile .ssh/authorized_keys

����ssh���� sudo service ssh restart Ϊ�˷�ֹ���ù��������������¼������ǰ���ú���Կ��֤��¼
�޸Ķ˿� sudo vim /etc/ssh/sshd_config
#Port
Port = 22
Port = 31422 //new port
���ڷ���ǽ�������ƣ������õĶ˿��ǲ���Խ������ǽ�ģ�������û��ͨ���¶˿ڵ�¼�ɹ�ǰ���벻Ҫɾ��22�˿�
����ssh���� sudo service ssh restart 
netstat -an | grep "LISTEN" //�������¼�¼���˿ڼ����ɹ�
tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN     
tcp        0      0 0.0.0.0:31422           0.0.0.0:*               LISTEN     
�������ǽ����(ubuntu ufw Ϊ��)
ʹ�÷���
1 ����
 sudo ufw enable
 sudo ufw default deny 
���ã������˷���ǽ����ϵͳ����ͬʱ�ر������ⲿ�Ա����ķ��ʣ����������ⲿ��������
2 �ر�
 sudo ufw disable 
2 �鿴����ǽ״̬
 sudo ufw status 
3 ����/������Ӧ�˿ڻ�������
 sudo ufw allow 80 �����ⲿ����80�˿�
 sudo ufw delete allow 80 ��ֹ�ⲿ����80 �˿�
 sudo ufw allow from 192.168.1.1 �����IP�������еı����˿�
 sudo ufw deny smtp ��ֹ�ⲿ����smtp����
 sudo ufw delete allow smtp ɾ�����潨����ĳ������
 sudo ufw deny proto tcp from 10.0.0.0/8 to 192.168.0.1 port 22 Ҫ�ܾ����е�TCP������10.0.0.0/8 ��192.168.0.1��ַ��22�˿�
 ������������RFC1918���磨������/���߾������ģ��������������/8,/16,/12��һ������ּ�����
sudo ufw allow from 10.0.0.0/8
sudo ufw allow from 172.16.0.0/12
sudo ufw allow from 192.168.0.0/16
�Ƽ�����
 sudo apt-get install ufw
 sudo ufw enable
 sudo ufw default deny 
���������Ѿ��ܰ�ȫ�������������Ҫ������ʹ��sudo ufw allow������Ӧ����
ע��:��������Ҫ���ð�ȫ�飬����ͨ���ⲿ�˿ڷ���


windows��װgit�����git bash(������) �� git GUI(git ����)
������Ҫ��ť:
1.rescan(����ɨ���ļ��仯)
2.stage changed(����Ѿ��仯���ļ���������git add)
3.sign off(�ǳ�(logout)github ����git������)
4.commit (�ǵ�д�ϱ�ע)
5.push(�ϴ����뵽������)
6.�˵��� remote ---> fetch from �ӷ���������update
�󲿷���������ڲ˵���

windows ��С����ǰ���� alt + space + N
��С�����д��� win + D

�git���������裺
githubΪ������git������,��֮�ϴ�ķ�����Ϊ��Ϊ���֣���Ѱ���շѰ棬��Ѱ�Ϊǿ�ƿ�Դ���շѰ�Ϊ˽�вֿ�
���ǽ��������Ǵ�ķ�����Ϊliunx �µ�git������
����:
ubuntu16.04
1.��װgit
sudo apt-get install git
2.����git�û�(��ʡ��)
sudo adduser git
3.ѡ��һ��Ŀ¼��Ϊ�����Ŀ¼�������Ŀ¼ִ��
git init --bare wallet.git //������Ϊwallet�Ĵ����(��ֿ�)
4.�޸Ĳֿ�owner
sudo chown R git:git wallet.git
5.��ֹͨ��git��¼shell
sudo vim /etc/passwd
��git:x:1002:1002:,,,:/home/git:/bin/bash�޸ĳ�git:x:1002:1002:,,,:/home/git:/usr/bin/git-shell
������git�û���������ͨ��sshʹ��git�����޷���¼shell����Ϊ����Ϊgit�û�ָ����git-shellÿ��һ��¼���Զ��˳���
���ϲ�����ɺ�һ�������Ĵ���ֿ�ʹ��������

���²����������һ̨git�ͻ���ִ��
6.��¡Զ�̿�
git clone git@server:repository-directory/wallet.git
����Ҫ������git���룬���Ǵ��ڰ�ȫ���ǣ�һ��ʹ�ù�Կ��¼������/home/git/.ssh/authority����ӹ�Կ

7.��ʱ�Ϳ�������ʹ�ô������

SVN �������
1.Subversio��TortoiseSVN ���
Subversio��飺SVN������
Tortoisesvn���: SVN�ͻ���
SVN��һ���ʽ�汾����ϵͳ��Tortoisesvn�����ڱ��ؽ���һ�����ؿ⣬���ǲ���ͨ�����繲��, Subversio�Ĺ��ܾ��ǽ����ؿ⹲�������磬
�����û�Ȩ�޵�

1.����ؿ�:
��ʱ���ǲ����뽫�⹲��ֻ�Ƿ����Լ���������¼�ύ�汾�ȣ���ʱ���ò���Subversio���ܣ���Tortoisesvn�Ϳ��Դһ�����ؿ�
(1)����������Ŀ¼:mkdir F:/Repository
(2)���ѡ�и�Ŀ¼--->����Ҽ�---->Tortoisesvn--->Create Repository here
(3)�ҵ���Ĵ��빤��Ŀ¼----->����Ҽ�------>Tortoisesvn--->Import
(4)�ڿ�·��������:file:///F:/Repository/source(ע��Ҫ��ǰ׺file:///$repPath)
(5)����������Ŀ¼checkout��


2.���������:
(1).����Subversio��TortoiseSVN�������ְ汾һ�£�����ᱨ"�����ļ�ϵͳ��ʽ�ڡ�1������4��֮�䣻���ָ�ʽ��6��"�ȴ���
���ص�ַ(Subversio1.6.x):http://subversion.tigris.org/servlets/ProjectDocumentList?folderID=11151&expandFolder=11151&folderID=91
���ص�ַ(TortoiseSVN1.6.x):http://tortoisesvn.net/downloads.html
(2).Ĭ�ϰ�װ
(3).  �����ֿ�/�汾�⣨Repository��
����Subversion��������Ҫ����һ���汾�⣨Repository�������������Ŀ���롣
(3.1)�����һ��ļ��� TortoiseSVN-->Create Repository here
(3.2).�����д��� svnadmin create D:\repository (�Ƽ�:��ֹ���ְ汾��ƥ��Ĵ���)

(4).�޸Ŀ�������ļ������½��⣬D:\repository\confg�ļ��У��ҵ�svnserver.conf
 # anon-access = read
 # auth-access = write
 # password-db = passwd
��������ȥ��ע�Ӳ���������(�����ո� ��������)
(5) �޸�D:\repository\confg�� �ҵ�passwd�ļ�
��[user]�������û� ��ʽ : username = password

(6).����SVN���� ��������
svnserver -d -r "D:\repository" //���ַ�ʽ�������񴰿ڲ���رգ�����������ϵͳ�����ķ��񣬷�������
ϵͳ����,
��������һ������ĵط�,-d �� -r��˳���ܵ�������·��Ҫ��˫����(windows server 2008)
sc create subversion_service binpath= "C:/Program Files/Subversion/bin/svnserve.exe --service -r D:\repository" displayname= "Subversion Repository" depend= Tcpip start= auto
������'='��Ӧ����һ���ո�Ⱥ�ǰ�����пո�
���ͣ�subversion_serviceΪ��������ơ����е�ϵͳ���������dos��ͨ�������ֶ�������ֹͣ��������net start subversion_service ֹͣ��net stop subversion_service
binpathΪ��װsubversion��·������ִ���ļ���·����
D:\repository"Ϊ�汾���·����
displayname= "Subversion Repository"Ϊע��ɵ�ϵͳ������ʾ���ƣ�ע��ɹ��󣬿�����ϵͳ�������ҵ�������ơ�
depend= TcpipΪ����TcpipЭ�顣
start= autoΪע��ɵ�ϵͳ������������Ϊ�Զ���
�����ɹ��� �ڼ����--->����---->�����пɿ���Subversion Repository���񣬿�����������

6.���빤��
�һ���Ҫ����Ĺ���Ŀ¼�� TortoiseSVN--->Import,������ĵ�ַ��һ��Ϊsvn://ipaddr/repositroy
��ʾ�����û��������룬����passwd�ļ��������������ļ������֮ǰTortoiseSVN�������ʺţ���Ҫ �һ�TortoiseSVN->Setting-->SaveData-->clearall

7.checkout
Ӧע������:svn://127.0.0.1/ ������Ŀ���ļ��У���Ҫ�ټ�������׺��checkout������֮ǰImport��Ŀ¼��ʽ������㵼��ʱ�� svn://127.0.0.1/repository/Work
������ҲҪ��svn://127.0.0.1/repository/Work

linux ���û������ļ���~/.profile�£����ø��ֱ�����ֵ����������������alias���Զ��������
linux��ʹ�����ļ���Ч���source .profile or . .profile

linux�½���������̨����һ�¼��ַ�ʽ�����̨
1��&
2��ctrl + z ��������� ���bg fgʹ��
�������ַ���������������ǰ�նˣ���ǰ�ն��˳������ܵ�SIGHUP�źŶ�����
���·�������ʹ�ն��˳�����Ӱ���̨����
1��nohup����
nohup sh test.sh &>/dev/null &
nohup��������SIGHUP�źţ��Ӷ��ն��˳�ʱ����Ӱ�쵽��̨��ҵ
2������ҵ�ҵ��µĻỰ����
��sh test.sh &>/dev/null &�����߽�sh test.sh &>/dev/null &�ŵ���һ���ű������ж�����ʵ��
��&Ҳ���루�������ǻᷢ�����ύ����ҵ��������ҵ�б��У�Ҳ����˵�����޷�ͨ��jobs���鿴�ģ�
ͨ��ps�鿴�����µ���ҵ��PPID��1�������ն˵�PID�������ն��˳��󲻻�Ӱ�����ǵ���ҵ

Intellij IDEA��װgo���
ѡ��--->File---->Setings--->Plugins--->Browse Repositroy---->Mangage Repositroy--->+��ӿ��url
��װ��https://plugins.jetbrains.com/���صĲ��
ѡ��--->File---->Setings--->Plugins--->Install Plugin form Disk--->ѡ����Ĳ��zip��ʽ����
Ҳ����ֱ�Ӱ�װgo���԰��intellj idea "Goland"


�����������ͬʱ�Ĵ��룬�����ύ�����޸ĵĲ��֣���git pullʱ����������ʾ
error: Your local changes to the following files would be overwritten by merge:
��˼Ϊ����޸Ľ�������
��ʱ�����ְ취���뱣���Լ����޸ĺͲ��뱣���Լ����޸�
�뱣���Լ����޸�:
git stash ---->���Լ����޸ķ��뻺����
git pull ----->update���´��룬��ʱ��Ĵ�����Ƿ��������´��룬�����㱾�ص��޸�֮ǰ�Ѿ��ύ������,���Բ��Ḳ��
git stash pop --> ����֮ǰ�������Ĵ��룬��ʱ�ͻ��Զ��ϲ���  =====>>>>

���뱣���Լ����޸�:
git --reset hard --->�ָ����޸�ǰ��ģ��,Ҳ����ʹ��chechout .
git pull

ubuntu�°�װ�ض��汾���������֪�����ȫ������ʹ��һ�������������
sudo apt-cache search package
�Ϳɳ������������Ӧ�汾
�����һ�����Դ��ppaʱ��sudo add-apt-repsitory ppa:package
��ʵ������/etc/apt/sources.d/��������һ���������sources.list�ļ�(ppa:Personal Package Archives(���˵�����))

��ʹ��git �����汾�⣬Ϊ�˰�ȫ���ǣ��ܶ๫˾��ssh�˿ڲ�������22,��ʱ����git�����������Ӧ���޸�
ssh clone ssh://git@$ip:$port/repositroy.git
���git�������ر�������֤��ֻ�ܽ��Լ��Ĺ�Կ�ϴ���git��������authorized_keys�ļ���


ubuntu ���ö�ʱ����
crontab -l  #�鿴����
crontab -e #���ö�ʱ����

 

*����*����*����*����*����command 
�֡�ʱ���ա��¡��ܡ����� 
��1�б�ʾ����1��59 ÿ������*���� */1��ʾ 
��2�б�ʾСʱ1��23��0��ʾ0�㣩 
��3�б�ʾ����1��31 
��4�б�ʾ�·�1��12 
��5�б�ʶ������0��6��0��ʾ�����죩 
��6��Ҫ���е����� 

 


���ӣ� 
30 21 * * * /usr/local/etc/rc.d/lighttpd restart           #ÿ���21:30����apache�� 
45 4 1,10,22 * * /usr/local/etc/rc.d/lighttpd restart   #ÿ��1��10��22�յ�4 : 45����apache�� 
10 1 * * 6,0 /usr/local/etc/rc.d/lighttpd restart          #ÿ���������յ�1 : 10����apache�� 
0,30 18-23 * * * /usr/local/etc/rc.d/lighttpd restart    #ÿ��18 : 00��23 : 00֮��ÿ��30��������apache�� 
0 23 * * 6 /usr/local/etc/rc.d/lighttpd restart              #ÿ��������11 : 00 pm����apache�� 
0 */1 * * * /usr/local/etc/rc.d/lighttpd restart               #ÿһСʱ����apache 
0 23-7/1 * * * /usr/local/etc/rc.d/lighttpd restart         #����11�㵽����7��֮�䣬ÿ��һСʱ����apache 
0 11 4 * mon-wed /usr/local/etc/rc.d/lighttpd restart  #ÿ�µ�4����ÿ��һ��������11������apache 
0 4 1 jan * /usr/local/etc/rc.d/lighttpd restart               #һ��һ�ŵ�4������apache 

��������ʹ��crontab -e��¼�ڶ�ʱ�������棬�ײ�
��������Ų�����ԭ��:
1.crontab��ʹ�õ�email���Ͷ�ʱ����Ľ���������Ƿ�װemail
2.�������е��û�����ʹ��corntab��Ȩ�ޡ���/etc/cron.allow�²쿴
3.�쿴crontab�Ķ�ʱ�����ʽ�Ƿ���ȷ


//Ubuntu17����������÷����˱仯,ubuntu16֮ǰ�����������ļ�Ϊ/etc/network/interface
Ubuntu17֮�����/etc/netplan
UBuntu18.04��������
��̬IP:
network:
ethernets:
ens33:
addresses: [192.168.1.20/24]
dhcp4: false
gateway4: 192.168.1.1
nameservers:
addresses: [192.168.1.1]
optional: true
version: 2
��̬IP:
network:
ethernets:
ens33:
dhcp4: true
version: 2




























