#!/bin/bash

ThunderBD 是一个Block Storage,Object Storage的软件解决方案，顶层基于ThunderUI为用户提供一个可视化界面，底层由Ceph实现

UI初始化日志在/var/log/denali/server/log.txt
UI错误日志在/var/log/denali/server/errro.txt
Ceph 的操作日志在/usr/share/denali-ceph/ceph_script_cluster.log(ui操作对其影响)
Ceph传统日志 /var/log/ceph/下 mon.log osd.log client.admin.log.....
Ceph数据日志 /var/lib/ceph/osd/

******************************************************************************************************************************************
ThunderBD UI的初始化步骤(log.txt):
1.输入集群各节点IP地址management_network:192.168.28.141 192.168.28.141 192.168.28.141
2.输入密钥："test"
3.输入user_network:75.75.0.0/24 backend_network 40.40.0.0/24
4.选择时区+8.0

UI初始化执行ansible文件:
1.初始化集群
sudo -u denali ansible-playbook /usr/share/denali-ansible/initializeCluster.yml -e '{"clusterName":"ceph_learn",
"memberIPAddrs":["192.168.28.141","192.168.28.142","192.168.28.143"],"VIP":"","backendNetwork":"75.75.0.0/24","netmask":24}'
2.初始化数据库Cassandra
sudo -u denali ansible-playbook /usr/share/denali-ansible/runCassandraContainers.yml -e '{"ipAddresses":["192.168.28.141",
"192.168.28.142","192.168.28.143"],"auto_bootstrap":"false","VIP":""}'
3.更新登陆界面
sudo -u denali ansible-playbook /usr/share/denali-ansible/updateLogging.yml -e '{"ipAddresses":["192.168.28.141","192.168.28.142",
"192.168.28.143"],"auto_bootstrap":"false","VIP":"","cassDatabase":"useDatabase"}'
4.设置时区
sudo -u denali ansible-playbook /usr/share/denali-ansible/setTimezone.yml -e '{"resourceParams":{"timezonePath":"/usr/share/zoneinfo/Asia/Kuching"}}'
5.重启server.js
sudo -u denali ansible-playbook /usr/share/denali-ansible/updateNodeJSTimezone.yml

UI资源管理
1.新建pool_new:name pool_new 百分比:30% 副本数:3
sudo /usr/share/denali-ceph/ceph_create_pool.sh -p 'pool_new' -d 30 -s 3
2.删除新建池pool_new
sudo /usr/share/denali-ceph/ceph_delete_pool.sh -p 'pool_new'
3.新建镜像image_new,name:image_new pool:poo_new image_size:1000M
sudo /usr/share/denali-ceph/ceph_create_image.sh -p 'pool_new' -n 'image_new' -s 1000
4.删除镜像image_new
sudo /usr/share/denali-ceph/ceph_delete_image.sh -p 'pool_new' -n 'image_new'
5.批量创建image，就是多次调用ceph_delete_image.sh,自动在镜像名后加数字1....n

ThunderBD 重启服务:直接start stop restart status命令开头
**********************************************************************************************************************************************

ThnuderBD Ceph初始化步骤(ceph_script_cluster.log):

1.node-01 creating /etc/ceph/ceph.conf
#根据模板ceph.conf.template创建ceph的配置文件ceph.conf 

2./usr/share/denali-ceph/ceph_create_cluster_check_env.sh -c 192.168.29.0/23 -p 192.168.29.0/23 -m
#创建集群并检查环境

3. checking params...
#检查ceph.conf.template里面的参数，再加上UI给的public_network cluster_network

4./usr/share/denali-ceph/ceph_create_monitor_local.sh
#创建本地Monitor节点

5./usr/share/denali-ceph/ceph_create_osds_local.sh -n 1 -f
#创建osd群osd.0 osd.1 osd.2

6.create partition in '/dev/sdd' OK(ceph-0-wal 10M 522M).
 create partition in '/dev/sdd' OK(ceph-0-db 522M 1034M).
 create partition in '/dev/sdd' OK(ceph-0-block 1034M 4086M).
# 将sdd盘分成三个分区 wal db block(bluestor 存储引擎所需)

7./usr/share/denali-ceph/ceph_create_radosgw_local.sh -n client.node-01-1 -i 192.168.29.85 -p 9000
#创建本地radosgw

8.
[06/26 05:26:59] INFO ceph osd pool create .rgw.root 8 8
[06/26 05:26:59] INFO ceph osd pool set .rgw.root size 2
[06/26 05:27:00] INFO ceph osd pool create default.rgw.data.root 8 8
[06/26 05:27:01] INFO ceph osd pool set default.rgw.data.root size 2
[06/26 05:27:02] INFO ceph osd pool create default.rgw.control 8 8
[06/26 05:27:03] INFO ceph osd pool set default.rgw.control size 2
[06/26 05:27:04] INFO ceph osd pool create default.rgw.gc 8 8
[06/26 05:27:05] INFO ceph osd pool set default.rgw.gc size 2
[06/26 05:27:07] INFO ceph osd pool create default.rgw.lc 8 8
[06/26 05:27:07] INFO ceph osd pool set default.rgw.lc size 2
[06/26 05:27:09] INFO ceph osd pool create default.rgw.log 8 8
[06/26 05:27:10] INFO ceph osd pool set default.rgw.log size 2
[06/26 05:27:11] INFO ceph osd pool create default.rgw.usage 8 8
[06/26 05:27:12] INFO ceph osd pool set default.rgw.usage size 2
[06/26 05:27:13] INFO ceph osd pool create default.rgw.users.keys 8 8
[06/26 05:27:14] INFO ceph osd pool set default.rgw.users.keys size 2
[06/26 05:27:15] INFO ceph osd pool create default.rgw.users.uid 8 8
[06/26 05:27:16] INFO ceph osd pool set default.rgw.users.uid size 2
[06/26 05:27:17] INFO ceph osd pool create default.rgw.buckets.index 128 128
[06/26 05:27:18] INFO ceph osd pool set default.rgw.buckets.index size 2
[06/26 05:27:19] INFO ceph osd pool create default.rgw.buckets.data 1024 1024
[06/26 05:27:20] INFO ceph osd pool set default.rgw.buckets.data size 2

#创建系统所需默认池，并设置副本数

9. /usr/share/denali-ceph/ceph_s3.sh -all
#循环执行ceph_s3.sh

**********************************************************************************************************************************************
ThunderBD Ceph 底层脚本操作格式
**********************************************************************************************************************************************
1.创建集群:sudo bash /usr/share/denali-ceph/ceph_create_cluster_check_env.sh -c 192.168.29.0/23 -p 192.168.29.0/23 -m
2.创建本地Monitor节点:sudo bash /usr/share/denali-ceph/ceph_create_monitor_local.sh #-a add a monitor -u unformat
3.创建OSDsudo bash /usr/share/denali-ceph/ceph_create_osds_local.sh -n 1 -f
4.创建radosgw:sudo bash /usr/share/denali-ceph/ceph_create_radosgw_local.sh -n client.node-01-1 -i 192.168.29.85 -p 9000
5.创建池:sudo bash /usr/share/denali-ceph/ceph_create_pool.sh -p test_pools -d 22 -s 2 #-d容量百分比 -s副本数
6.删除池:sudo bash /usr/share/denali-ceph/ceph_delete_pool.sh -p test_pools #-p 指定池
7.创建image:sudo bash /usr/share/denali-ceph/ceph_create_image.sh -p pools -n image1 -s 100 #-p 指定池 -n image name -s image size(MB)
8.删除池:sudo bash /usr/share/denali-ceph/ceph_delete_image.sh -p pools -n image1 #-p 指定池 -n image name
9.创建image snapshot：sudo bash ceph_create_image_snap.sh -p pools -n fdfdf -s test_snzp ##-p 指定池 -n 指定镜像 -s snapname
10.删除image snap:sudo bash ceph_delete_image_snap.sh -p pools -n fdfdf -s test_snzp ##-p 指定池 -n 指定镜像 -s snapname
11.创建池镜像:sudo bash ceph_create_pool_snap.sh -p pools -n pools_snap #目前ThunderBD 没有针对pool snapshot
12.获得池参数：sudo bash eph_get_pool_parameter.sh -p pools -n size #-p 指定池 -n 需要获得的项
13.获取池配额：sudo bash ceph_get_pool_quota.sh -p pools #-p 指定池 
14.获取image信息:sudo bash ceph_info_image.sh -p pools -n images #-p 指定池 -n 指定images
15.列出指定pool的镜像：sudo bash ceph_list_image.sh -p pools #-p 指定池 
16.列出系统中所有image：sudo bash ceph_list_image_all.sh
17.列出系统中所有image(大小)： sudo bash ceph_list_image_by_pool.sh
18.列出指定池snap:sudo bash ceph_list_image_snap.sh -p pools -n fdfdf
19.修改public_net cluster_net：sudo bash ceph_make_conf.sh -c 0.10.20.0/24 -p 10.10.40.0/24
20.查看池状态:sudo bash ceph_stats_pool.sh 
21.设置pool配额:sudo bash ceph_set_pool_quota.sh -p pools -n parameter-name(max_objects|max_bytes) -v size
22.查看imags状态信息：sudo bash ceph_status_image.sh -p pools -n fdfdf

**********************************************************************************************************************************************
脚本分析：
ceph_create_cluster_check_env.sh 
功能：创建ceph集群并检查环境
**********************************************************************************************************************************************

#!/bin/bash

set -e #写的每个脚本都应该在文件开头加上set -e,这句语句告诉bash如果任何语句的执行结果不是true则应该退出。防止错误越来越多

SHELL_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )" #获取脚本所在目录名称BSSH_SOURCE[0]表示当前脚本名称，和$0相同，和C与C++
#相似，shell中也有类似__FUNCNAME__的宏，shell中用常量表示，是一个数组，FUNCNAME，BASH_SOURCE[0]
source $SHELL_DIR/common_fun #包含common_fun 和C语言的include相同

add_log #add_log 函数是写入日志函数
add_log "INFO" "`hostname` creating $ceph_conf" 
#[07/03 21:39:39] INFO node-01 Get rgw PERCENTAGE, CAPACITY, NUM, BYTECOUNT...

add_log "INFO" "$0 $*"
#[07/03 21:39:39] INFO /usr/share/denali-ceph/ceph_s3.sh -all

#usage 帮助提示函数 -h 参数时执行，输出帮助信息
function usage()
{
        echo "Usage:$0 -c|--cluster-net <cluster net>"\
	"-p|--public-net <public net>"\
	"[-m|--monitor-check]"\
	"[-o|--osd-check]"\
	"[-h|--help]"

        echo "-c, --cluster-net<cluster net>"
        echo -e "\teg. -c 10.10.20.0/24,10.10.30.0/24, use ',' to seperate multi-net, only support 24 bits mask now, not support ipv6 or lookback net"

        echo "-p, --public-net<public net>"
        echo -e "\teg. -p 10.10.40.0/24,10.10.50.0/24, use ',' to seperate multi-net, only support 24 bits mask now, not support ipv6 or lookback net"

        echo "-m, --monitor-check"
        echo -e "\tcheck monitor env"

        echo "-o, --osd-check"
        echo -e "\tcheck osd node env"

        echo "-u, --unformat"
        echo -e "\twhen other shell call this shell, print result to parent shell without format"

        echo "[-h, --help]"
        echo -e "\tget this help info"
}

RESULT_ERROR="Create cluster check environment on $hostname failed."  #创建失败返回语句
RESULT_OK="Create cluster check environment on $hostname successfully." #创建成功返回语句

if ! temp=$(getopt -o c:p:umoh --long cluster-net:,public-net:,unformat,monitor-check,osd-check,help -n 'note' -- "$@" 2>&1)
#getopt函数获取脚本参数，如果参数错误则输出错误信息
then
	#usage > &2
	my_exit 1 "$RESULT_ERROR" "parse arguments failed, $temp"
fi

mon_check=0
osd_check=0
format=1
ceph_conf_tpl=$SHELL_DIR/ceph.conf.template
#将规范化后的命令行参数分配至位置参数（ $1,$2,...)
eval set -- "$temp"
while true #循环检查参数
do
        case "$1" in
                -c|--cluster-net) arr_cluster_net=(${2//,/ }); cluster_net=$2; shift 2;;#从上可知 shift(shift 2) 
				#命令每执行一次，变量的个数($#)减一（之前的$1变量被销毁,之后的$2就变成了$1），而变量值提前一位。
                -p|--public-net) arr_public_net=(${2//,/ }); public_net=$2; shift 2;;
                -u|--unformat) format=0; shift 1;;   
                -m|--monitor-check) mon_check=1; shift 1;;
                -o|--osd-check) osd_check=1; shift 1;;#赋值参数
                -h|--help) usage; exit 1;;#调用usage处理帮助信息
                --) shift; break;;#??
                 *) my_exit 1 "$RESULT_ERROR" "unkown arguments $1";;
        esac
done

#检查所有节点是否存在ceph.conf在/etc/ceph/下
function check_all_node_not_exist_conf()
{
	local ret=0
	if ls $ceph_conf &> /dev/null #如果存在ceph.conf
	then
		add_log "ERROR" "$hostname exists $ceph_conf, you should remove it" $print_log #屏幕打印提示信息
		LAST_ERROR_INFO="$hostname exists $ceph_conf, you should remove it."
		ret=1
	fi
	return $ret
}

#检查所有节点是否存在ceph-mon 和 ceph-osd守护进程
function check_all_node_not_exist_ceph_daemon()
{
	local ret=0
	if pidof ceph-mon &> /dev/null #如果ceph-mon存在 pidof 与 pgrep功能大致相同
	then
		add_log "ERROR" "$hostname ceph-mon is running" $print_log #屏幕打印提示信息
		LAST_ERROR_INFO="$hostname ceph-mon is running."
		ret=1
	fi

	if pidof ceph-osd &> /dev/null
	then
		add_log "ERROR" "$hostname ceph-osd is running" $print_log #屏幕打印提示信息
		LAST_ERROR_INFO="$hostname ceph-osd is running."
		ret=1
	fi

	return $ret
}

#检查所有节点是否存在public_net 和 cluster_net
function check_all_node_exist_pubnet_and_clstnet()
{
	if [ $osd_check -eq 1 ] 
	then
		local inet_cidr=$(inet_to_cidr "$cluster_net")
		if ! get_ip_from_net "$inet_cidr" > /dev/null
		then
			LAST_ERROR_INFO="cluster net check: ${LAST_ERROR_INFO}"
			return 1
		fi
	fi

	local inet_cidr_pub=$(inet_to_cidr "$public_net")
	if ! get_ip_from_net "$inet_cidr_pub" > /dev/null
	then
		LAST_ERROR_INFO="public net check: ${LAST_ERROR_INFO}"
		return 1
	fi

	return 0
}

function check_all_storage_nvme()
{
	local ret_err=""
	local has_err=0

	#check nvme device
	ret_err=$(dev_operation_prompt || :)

	#check execute result
	#no nvme device, mounted or has partiontion
	if echo "$ret_err" |grep "no device" > /dev/null ||
	   echo "$ret_err" |grep "mounted" > /dev/null
	then
		has_err=1
		LAST_ERROR_INFO="$node `echo "$ret_err" |awk '{if(NR==1){printf $0}else{printf ", "$0}}'`."
		add_log "ERROR" "$node `echo "$ret_err" |awk '{if(NR==1){printf $0}else{printf ", "$0}}'`" $print_log
	elif echo "$ret_err" |grep "has partition" > /dev/null
	then
		has_err=1
		LAST_ERROR_INFO="$node `echo "$ret_err" |awk '{if(NR==1){printf $0}else{printf ", "$0}}'`.${SEG}${LAST_ERROR_INFO}"
		add_log "ERROR" "$node `echo "$ret_err" |awk '{if(NR==1){printf $0}else{printf ", "$0}}'`" $print_log
		##if has error, no need to wait for $print_log, because we will return error after for
		#if [ $has_err -eq 1 ]
		#then
		#	continue
		#elif ! wait_for_yes "some devices in $node has partitions, your data will be destroyed, continue"
		#then
		#	return 1
		#fi
	fi

	return $has_err
}

#检查参数列表
function check_params_and_env()
{
	add_log "INFO" "checking params..." $print_log

	if [ $mon_check -eq 0 ] && [ $osd_check -eq 0 ]
	then
		add_log "ERROR" "argument -m or -o must give at least one" $print_log
		my_exit 1 "$RESULT_ERROR" "argument -m or -o must give at least one" $format
	fi

	add_log "INFO" "public net=${arr_public_net[*]}" $print_log
	add_log "INFO" "cluster net=${arr_cluster_net[*]}" $print_log

	if [ ${#arr_public_net[@]} -eq 0 ]
	then
		add_log "ERROR" "public net is empty" $print_log
		my_exit 1 "$RESULT_ERROR" "public net is empty" $format
	fi

	if [ ${#arr_cluster_net[@]} -eq 0 ]
	then
		add_log "ERROR" "cluster net is empty" $print_log
		my_exit 1 "$RESULT_ERROR" "cluster net is empty" $format
	fi

	for net in ${arr_cluster_net[@]}
	do
		if ! is_valid_net "$net"
		then
			add_log "ERROR" "invalid cluster net $net" $print_log
			my_exit 1 "$RESULT_ERROR" "invalid cluster net $net" $format
		fi
	done

	for net in ${arr_public_net[@]}
	do
		if ! is_valid_net "$net"
		then
			add_log "ERROR" "invalid public net $net" $print_log
			my_exit 1 "$RESULT_ERROR" "invalid public net $net" $format
		fi
	done

	check_all_node_not_exist_ceph_daemon || my_exit $? "$RESULT_ERROR" "$LAST_ERROR_INFO" $format
	check_all_node_not_exist_conf || my_exit $? "$RESULT_ERROR" "$LAST_ERROR_INFO" $format
	check_all_node_exist_pubnet_and_clstnet || my_exit $? "$RESULT_ERROR" "$LAST_ERROR_INFO" $format
	if [ $osd_check -ne 0 ]
	then
		check_all_storage_nvme || my_exit $? "$RESULT_ERROR" "$LAST_ERROR_INFO" $format
	fi
}

check_params_and_env

my_exit 0 "$RESULT_OK" "$LAST_ERROR_INFO" $format

**********************************************************************************************************************************************
脚本分析：
/usr/share/denali-ceph/ceph_create_monitor_local.sh
功能：创建一个mon节点
**********************************************************************************************************************************************
#!/bin/bash

set -e

SHELL_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
source $SHELL_DIR/common_fun

mkdir "$mon_dir" -p

add_log
add_log "INFO" "$hostname: local creating monitor..."
add_log "INFO" "$0 $*"

add_mon_flag=0

function usage()
{
        echo "Usage:$0 [-a|--add] [-u|--unformat] [-h|--help]"

        echo "-a, --add"
        echo -e "\tspecify it's adding monitor not creating monitor"

        echo "-u, --unformat"
        echo -e "\twhen other shell call this shell, print result to parent shell without format"

        echo "[-h, --help]"
        echo -e "\tget this help info"
}

RESULT_ERROR="Create monitor on $hostname failed."
RESULT_OK="Create monitor on $hostname successfully."

if ! temp=$(getopt -o auh --long add,unformat,help -n 'note' -- "$@" 2>&1)
then
	add_log "ERROR" "parse arguments failed, $temp" $print_log
	my_exit 1 "$RESULT_ERROR" "Parse arguments failed. $temp" 1
fi

#[ ! -d "$conf_dir" ] && mkdir $conf_dir -p

format=1
eval set -- "$temp"
while true
do
        case "$1" in
                -a|--add) add_mon_flag=1; shift 1;;
                -u|--unformat) format=0; shift 1;;
                -h|--help) usage; exit 1;;
                --) shift; break;;#??
                *) my_exit 1 "$RESULT_ERROR" "Parse arguments failed." 1;;
        esac
done

function parse_and_check_params()
{
	pidof ceph-mon &> /dev/null && my_exit 1 "$RESULT_ERROR" "existed one monitor on $hostname" $format
	return 0
}

function get_ip_from_pubnet()
{
	local pubnet=
	if ! pubnet=$(grep "public network = " $ceph_conf | awk -F" = " '{print $2}')
	then
		LAST_ERROR_INFO="get 'public network' from $ceph_conf failed."
		add_log "ERROR" "get 'public network' from $ceph_conf failed" $print_log
		return 1
	fi

	if ! get_ip_from_net "$pubnet"
	then
		return 1
	fi

	return 0
}

function set_conf()
{
	create_roll_back_conf || :
	back_conf || :
	host=$(hostname)
	mon_id=$host

	if ! mon_addr=$(get_ip_from_pubnet) #获取mon ip
	then
		return 1
	fi

	local pos="\[osd\]"
	local mon_line=
	if ! mon_line=$(grep "$pos" $ceph_conf | cut -d : -f 1)
	then
		LAST_ERROR_INFO="no find $pos in $ceph_conf."
		add_log "ERROR" "no find $pos in $ceph_conf" $print_log
		return 1
	fi

	local line_sec_mon="\[mon.$mon_id\]"
	sed -i "/$pos/i$line_sec_mon" $ceph_conf 
	
	local line_mon_host="\\\\tmon host = $host"
	sed -i "/$pos/i$line_mon_host" $ceph_conf 

	local line_mon_addr="\\\\tmon addr = $mon_addr"
	sed -i "/$pos/i$line_mon_addr" $ceph_conf 

	local line_mon_data="\\\\tmon data = $mon_dir/ceph-$mon_id"
	sed -i "/$pos/i$line_mon_data" $ceph_conf 
}

function get_fsid()
{
	local find_fsid=
	if ! find_fsid=$(grep "fsid = " $ceph_conf | awk -F" = " '{print $2}')
	then
		LAST_ERROR_INFO="no find fsid in $ceph_conf."
		add_log "ERROR" "no find fsid in $ceph_conf" $print_log
		return 1
	elif [ x"$find_fsid" = x ]
	then
		LAST_ERROR_INFO="fsid is empty in $ceph_conf."
		add_log  "ERROR" "fsid is empty in $ceph_conf" $print_log
		return 1
	fi
	echo $find_fsid
	return 0
}

function create_monitor()
{
	if pidof ceph-mon >/dev/null 2>&1
	then
		LAST_ERROR_INFO="ceph-mon was running."
		add_log "ERROR" "ceph-mon was running" $print_log
		return 1
	fi

	if ! fsid=$(get_fsid)
	then
		return 1
	fi

	local ret_err=
	if ! ret_err=$(ceph-authtool --create-keyring /tmp/ceph.mon.keyring --gen-key -n mon. --cap mon 'allow *' 2>&1)
	then
		LAST_ERROR_INFO="$ret_err"
		add_log "ERROR" "$LAST_ERROR_INFO" $print_log
		return 1
	fi

	if ! ret_err=$(ceph-authtool --create-keyring $conf_dir/ceph.client.admin.keyring --gen-key -n client.admin --set-uid=0 --cap mon 'allow *' --cap osd 'allow *' --cap mds 'allow' 2>&1)
	then
		LAST_ERROR_INFO="$ret_err"
		add_log "ERROR" "$LAST_ERROR_INFO" $print_log
		return 1
	fi

	if ! ret_err=$(ceph-authtool /tmp/ceph.mon.keyring --import-keyring $conf_dir/ceph.client.admin.keyring 2>&1)
	then
		LAST_ERROR_INFO="$ret_err"
		add_log "ERROR" "$LAST_ERROR_INFO" $print_log
		return 1
	fi 

	if ! ret_err=$(monmaptool --create --add $mon_id $mon_addr --fsid $fsid /tmp/monmap 2>&1)
	then
		LAST_ERROR_INFO="$ret_err"
		add_log "ERROR" "$LAST_ERROR_INFO" $print_log
		return 1
	fi

	mkdir -p $mon_dir/ceph-$mon_id

	if ! ret_err=$(ceph-mon --mkfs -i $mon_id --monmap /tmp/monmap --keyring /tmp/ceph.mon.keyring 2>&1)
	then
		LAST_ERROR_INFO="$ret_err"
		add_log "ERROR" "$LAST_ERROR_INFO" $print_log
		return 1
	fi

	touch $mon_dir/ceph-$mon_id/done $mon_dir/ceph-$mon_id/upstart > /dev/null 2>&1 || return 1

	if ! ret_err=$(initctl emit ceph-mon id=$mon_id 2>&1)
	then
		LAST_ERROR_INFO="$ret_err"
		add_log "ERROR" "$LAST_ERROR_INFO" $print_log
		return 1
	fi
	
	if ! ret_err=$(status ceph-mon id=$mon_id 2>&1)
	then
		LAST_ERROR_INFO="$ret_err"
		add_log "ERROR" "$LAST_ERROR_INFO" $print_log
		return 1
	fi
	return 0
}

function add_monitor()
{
	local ret_err=
	add_log "INFO" "will ceph auth get mon."
	ceph auth get mon. -o /tmp/ceph.mon.keyring &> /dev/null || :
	add_log "INFO" "after ceph auth get mon."

	add_log "INFO" "will ceph mon getmap"
	if ! ret_err=$(ceph mon getmap -o /tmp/monmap 2>&1)
	then
		LAST_ERROR_INFO="$ret_err"
		add_log "ERROR" "$LAST_ERROR_INFO" $print_log
		return 1
	fi
	add_log "INFO" "ok ceph mon getmap"

	mkdir -p $mon_dir/ceph-$mon_id

	add_log "INFO" "will ceph-mon --mkfs"
	if ! ret_err=$(ceph-mon -i $mon_id --mkfs --monmap /tmp/monmap --keyring /tmp/ceph.mon.keyring 2>&1)
	then
		LAST_ERROR_INFO="$ret_err"
		add_log "ERROR" "$LAST_ERROR_INFO" $print_log
		return 1
	fi
	add_log "INFO" "ok ceph-mon --mkfs"

	add_log "INFO" "will start ceph-mon daemon"
	touch $mon_dir/ceph-$mon_id/done $mon_dir/ceph-$mon_id/upstart > /dev/null 2>&1 || return 1
	if ! ret_err=$(initctl emit ceph-mon id=$mon_id 2>&1)
	then
		LAST_ERROR_INFO="$ret_err"
		add_log "ERROR" "$LAST_ERROR_INFO" $print_log
		return 1
	fi
	if ! ret_err=$(status ceph-mon id=$mon_id 2>&1)
	then
		LAST_ERROR_INFO="$ret_err"
		add_log "ERROR" "$LAST_ERROR_INFO" $print_log
		return 1
	fi
	add_log "INFO" "ok start ceph-mon daemon"

	return 0
}

parse_and_check_params

set_conf || my_exit 1 "$RESULT_ERROR" "$LAST_ERROR_INFO" $format

if [ $add_mon_flag -eq 1 ]
then
	if ! add_monitor > /dev/null
	then
		rollback_conf
		my_exit 1 "$RESULT_ERROR" "$LAST_ERROR_INFO" $format
	fi
else
	if ! create_monitor > /dev/null
	then
		rollback_conf
		my_exit 1 "$RESULT_ERROR" "$LAST_ERROR_INFO" $format
	fi
fi

create_logrotate_file
my_exit 0 "$RESULT_OK" "$LAST_ERROR_INFO" $format

io goes into the rbd's image journal
onec journaled,asknnowledge the clientwrite to the rbd image occurs
rbd mirror daemon replays the journal conyrnt
at the remote location





























