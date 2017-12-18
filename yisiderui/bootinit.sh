:' ThunderStor 的任意节点启动时都会执行此脚本，大概功能就是检查各项服务
的状态,如果某项服务没有开启，该脚本会尝试去启动，如果某项service启动失败
脚本退出。这些服务主要有几项
cassandra:数据库服务，还没研究
server:UI后台服务
rpcbind:ganesha.nfs启动前提服务
ganesha.nfsd:nfs共享
gluster peer：检查集群状态
zpool_shre:zfs池服务
glusterd:gluster状态
CTDB：故障转移服务
SAMB：CIFS导出
NFS：nfs导出服务

以下是对该文件的注释
'
#!/bin/bash

retry()
{
        local n=0
        local try=$1
        local cmd="${@: 2}"
        [[ $# -le 1 ]] && {
        echo "Usage $0 <retry_number> <Command>"; }

        until [[ "$n" -ge "$try" ]]
        do
                echo "running $cmd $n th time"
                $cmd && break || {
                        n=$((n+1))
                        sleep 1;
                        }

        done
        [ $n -lt "$try" ] || return 1
}

check_brick_process()
{
        return $([ `ls -1 /var/denali/resources/bricks/ | wc -l` -le `ps hf -opid,cmd -C "glusterfsd" | wc -l` ])
}
#日志处理，处理执行bootinit.sh过程中的日志记录，如果没指定文件，默认在/var/log/denail/bootinit.log
log()
{
        echo $(date) '['$$']:' $1 >> $logfile;#date：获取实时时间，shell中执行slell命令$(cmd),$$:输出当前进程ID $1是传进参数，也是显示的主要内容
}

scriptname=$(basename $0 .sh)#获取脚本名bootinit,basename $0 .sh 取得文件名截断目录部分以及制定内容.sh

logfile=$1;#如果提供日志文件，则将该文件作为执行该脚本的日志文件
if [ -z $logfile ]; then #如果没有提供，logfile变量为空
    logfile=/var/log/denali/"$scriptname".log #指定日志文件，脚本名.log，也即是bootinit.log
fi

log "$scriptname started" #向日志文件写入内容"bootinit started"

#检测/var/denali-files/cassandra-driver/app.js 这个demon是否启动
if ! pgrep -f "daemon .* node /var/denali-files/cassandra-driver/app.js" > /dev/null; then #如果没启动，则执行以下内容
    if sudo -H -u denali daemon -O /var/log/denali/cassandra-driver/log.txt -E \
	/var/log/denali/cassandra-driver/error.txt node /var/denali-files/cassandra-driver/app.js; then #启动app.js
        log "Started cassandra-driver daemon" #记录日志
    else #如果启动失败，退出脚本，并记录日志
        rc=$?
        log "Could not start cassandra-driver daemon, exiting with $rc"
        exit $rc
    fi
else #如果之前就已经启动，记录日志
    log "Daemon for cassandra-driver already exists"
fi

#检测/var/denali-mw/server.js 这个demon是否启动
if ! pgrep -f "daemon .* node /var/denali-mw/server.js" > /dev/null; then #如果没启动，则执行以下内容
    if sudo -H -u denali daemon -O /var/log/denali/server/log.txt -E \ 
	/var/log/denali/server/error.txt node /var/denali-mw/server.js; then #启动server.js
        log "Started node daemon" #记录日志
    else #如果启动失败，退出脚本，并记录日志
        rc=$?
        log "Could not start node daemon, exiting with $rc"
        exit $rc
    fi
else #如果之前就已经启动，记录日志
    log "Daemon for node already exists"
fi

#检测ganesha.nfs进程是否启动
if ! pgrep ganesha.nfsd > /dev/null; then
    log "Restarting rpcbind" #如果ganesha.nfs没启动，重启rpcbind服务
    if ! service rpcbind restart 1>>$logfile 2>&1; then #重启rpcbind服务1>>$logfile 2>&1，将stdout 与 stderr都重定向到日志
        rc=$?
        log "restarting rpcbind returned error, exiting with $rc" #如果启动rpcbind失败
        exit $rc
    fi
fi

sleep 5
# Ganesha daemon should always be up in the machine
if ! pgrep -f "/usr/bin/ganesha.nfsd" > /dev/null; then #检测ganesha.nfs进程是否启动
    if /usr/bin/ganesha.nfsd -f /etc/ganesha/ganesha.conf -L /var/log/ganesha.log; then #启动ganesha.nfs
        log "Started ganesha.nfsd"
    else #启动失败，记录日志
        rc=$?
        log "Could not start ganesha.nfsd, exiting with $rc"
        exit $rc
    fi
else  #如果之前就已经启动，记录日志
    log "ganesha.nfsd already exists"
fi 

# Only run the configuration if there are enough gluster peers (ie. not less than 2)
# UI Server will fix it otherwise

#只有集群(存储池)中节点个数大于等于3时才执行配置，否则UI会尝试修复

sleep 15
if [ ! $(/usr/local/sbin/gluster pool list 2> /dev/null | wc -l) -lt 3 ]; then #pool list返回的结果大于等于3才执行以下内容
    # Handle brick remount #重新挂载brick
    brick_files=$(ls /var/denali/resources/bricks/ 2>/dev/null); #获得当前系统中的所以brick,(只包括通过UI创建的brick),手动创建的将不会记录到
	#该目录下，实质是一个脚本，该脚本内容如下
:'
zfs create -o sync=disabled -o primarycache=metadata -o secondarycache=none -o atime=off -o acltype=noacl -o compression=off -o \
dedup=off -o xattr=sa -o mountpoint=/mnt/gluster-brick-replica_10 -o reservation=none -o refquota=1050G -o quota=1150G \
denali_pool/gluster-brick-replica_10
'
#-o option：zfs的选项
#mountpoint:挂载点
#quota:配额
    WERE_BRICKS_MOUNTED=""
    if [ ! -z "$brick_files" ]; then #如果存在brick
        for bf in $brick_files; do #循环处理每个brick
            tmp_mount=$(grep -oP 'mountpoint=\K[\/\w-]+' "/var/denali/resources/bricks/$bf") #取得挂载目录
            # Lets make sure that it contains exports in the volumemount
			#让我们确保它包含在volumemount中的导出
            if [[ "$tmp_mount" =~ '/'$ ]]; then #如果$tmp_mount最后一个字符是'/'
                tmp_mount=${tmp_mount: : -1} #只取除/前面的部分
            fi
            mount | grep -q "on $tmp_mount" && continue #如果挂载了指定brick就继续下一个
            rm -rf "$tmp_mount" #如果没有挂载，就将此目录删除
            log "removed dir $tmp_mount that was not mounted"
            WERE_BRICKS_MOUNTED="yes" #记录标志位
        done
		
		#挂载所有zfs卷
        /sbin/zfs mount -a # Needed to mount the pool, even if there were no bricks
        if [ ! -z "$WERE_BRICKS_MOUNTED" ]; then #如果有brick被删除
            sleep 5
            log "restarting zfs-share"
            if ! service zfs-share restart 1>>$logfile 2>&1; then #重启zfs-share服务
                rc=$?
                log "restarting zfs-share returned error, exiting with $rc"
                exit $rc
            fi
            sleep 5
            #service glusterfs-server restart
            log "restarting glusterd"
            if ! service glusterd restart 1>>$logfile 2>&1; then #重启zfs-share服务
                rc=$?
                log "restarting glusterd returned error, exiting with $rc"
                exit $rc
            fi
            #TODO: Find a better way to ensure all bricks are up
            retry 10 check_brick_process #执行检查brick函数
        fi
    fi
    # Handle ctdb VIP recreation
    WAS_VIP_RECREATED=""
    for vip_create in $(ls /var/denali/resources/vips/ 2>/dev/null); do #获得vip配置文件
        vip_mountpoint=$(grep -oP 'mount -t glusterfs \K[\/\w-:]+' "/var/denali/resources/vips/$vip_create") #获得ctdb卷
        if ! mount | grep -q "$vip_mountpoint"; then #检查ctdb卷是否挂载
            sleep 2
            if /var/denali/resources/vips/"$vip_create"; then #如果没挂载执行挂载
                log "created VIP"
            else
                rc=$?
                log "create VIP failed, exiting with $rc"
                exit $rc
            fi
            WAS_VIP_RECREATED="yes"
        fi
    done
    if [ ! -z "$WAS_VIP_RECREATED" ]; then #重启ctdb服务
        log "restarting ctdb"

        if ! service ctdb restart 1>>$logfile 2>&1; then
            rc=$?
            log "restarting ctdb returned error, exiting with $rc"
            exit $rc
        fi
    fi

    # Handle nfs share recreation (info shouldn't be lost because gluster volumes are persistent
    # Wait for ganesha
    if retry 5 showmount -e; then #检查nfs是否导出成功
        log "showmount -e succeeded, assuming ganesha is initialized"
    else
        rc=$?
        log "showmount -e failed, exiting with $rc"
        exit $rc
    fi

    log "Re-creating nfs-ganesha exports"
    CREATE_EXPORTS=""
    for nfs_create in $(ls /var/denali/resources/nfs_exports/ 2>/dev/null); do
        share_id=$(grep -oP 'Export_Id=\K[\/\d]+' "/var/denali/resources/nfs_exports/$nfs_create") 
        if dbus-send --print-reply --system --dest=org.ganesha.nfsd /org/ganesha/nfsd/ExportMgr \
		org.ganesha.nfsd.exportmgr.DisplayExport uint16:"$share_id" > /dev/null; then #导出nfs
            log "Ganesha export $share_id already exists, skipping re-creation"
            continue
        fi
        CREATE_EXPORTS="yes"
        if retry 3 "/var/denali/resources/nfs_exports/$nfs_create"; then
            log "Ganesha export $share_id re-created"
        else
            rc=$?
            log "Ganesha export $share_id could not be re-created, exiting with $rc"
            exit $rc
        fi
    done

    log "Re-creating cifs exports"
    for smb_create in $(ls /var/denali/resources/cifs_exports/ 2>/dev/null); do
        smb_mountpoint=$(grep -oP 'mount -t glusterfs \K[\/\w-:]+' "/var/denali/resources/cifs_exports/$smb_create")
        if mount | grep -q "$smb_mountpoint"; then
            log "CIFS export $smb_mountpoint already is mounted, skipping re-creation"
        else
            if /var/denali/resources/cifs_exports/"$smb_create"; then #导出cifs
                log "CIFS export $smb_mountpoint re-created"
            else
                rc=$?
                log "CIFS export $smb_mountpoint could not be re-created, exiting with $rc"
                exit $rc
            fi
        fi
    done
    if [ ! -z "$CREATE_EXPORTS" ]; then
        [ $(showmount -e | wc -l) -gt 1 ] && wall --nobanner <<< "[$(date)] NFS Exports ready" || wall --nobanner <<< "[$(date)] NFS Exports recreation failure"
    fi
fi

log "$scriptname completed"
exit 0
