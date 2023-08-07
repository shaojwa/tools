#!/bin/bash


# 注意事项:
# (1)在执行dump-logs命令时需要注意ssh执行时的用户名
# (2)在执行check-logs命令时需要指定正确的pool_name名字
pool_name=.diskpool_ssd_ahci.rbd
#pool_name=defaultDatepool

# (3) 两次probe之间的时间间隔(单位:秒)
probe_interval=300


# 操作步骤:
# 1. probe命令检测集群中的可能残留日志(当前采用间隔5分钟的两次查询取交集的方式获取).
# 2. 对probe命令的输出进行确认(通过查询lsm时里当前正在使用的seq和probe探测到的seq进行比较).
# 3. 确认日志为残留之后用dump-logs命令把日志对象dump出来(默认在osd-id节点的/var/lib/ceph/osd目录下).
# 4. 用decode命令解码dump出来的日志文件.
# 5. 用check命令比较日志文件中的每个op的mtime和集群对象的mtime(一般情况下不会出现个op都pass的情况).
#    只有日志对象中每个op的操作时间都比集群中用户对象的mtime大(不能相等)才认为该日志对象需要保留.


RED='\033[0;31m'
GRN='\033[0;32m'
YEL='\033[1;33m'
NC='\033[0m'



#
# 需要指定一个结果输出文件(不指定为probe.logs)
probe() {
  outfile=probe.logs
  if [[ $# == 1 ]]; then
    outfile=$1
  fi
  csd_list=$(ceph osd tree | awk '{print $3}' | grep osd)
  #echo "list log objs in csds: $csd_list" 
  all_logs=probe.all
  if [[ -e "$all_logs" ]]; then
    rm $all_logs
  fi
  for csd_id in $csd_list; do
    record=$(sudo ceph tell $csd_id list_objs | grep -e pool_id -e engine_id -e pg_id -e seq -e lsm_id -e epoch)
    if [[ "$record" == "" ]]; then
     continue
    fi
    echo "$record" | awk '{ print $2;}' | xargs -n6 | awk  'BEGIN{FS=","} {print $1,$2,$3,$4,$5}' \
      | awk 'BEGIN{OFS="."}{printf("%s.%s.%s %s %s %s ", $1,$2,$5,$4,$3,$6); system("printf %x "$3); printf("\n")}' >> $all_logs
  done
  cat $all_logs | sort | uniq > $outfile
  rm $all_logs
}


#
# 尝试检测出老的日志(当前的算法在有的场景会有误判)
detect_oldlogs() {
  if [[ $# != 1 ]]; then
    echo "need input-file to detect logs!"
    return
  fi
  infile=$1
  old_list=$(cat $infile | awk 'BEGIN{ id=""; seq=""; pg_id=""; epoch=""; }
    {
        if ($1 != id) {
            print "pool_id.engine_id.lsm_id.pg_id.epoch.seq="$1"."$3"."$4"."$2; 
        } else { 
            if ($2 != seq + 1) {
                print "pool_id.engine_id.lsm_id.pg_id.epoch.seq="$1"."$3"."$4"."$2;
            }
        }
        id=$1; seq=$2; pg_id=$3; epoch=$4;
    }')
  
  outfile=probe.old
  if [[ "$old_logs" == "" ]]; then
    echo "no old logs" | tee $outfile
    return
  fi
  echo "$old_logs" | uniq | sort > $outfile
}


#
# 在每行日志后追加 pg_id 和 osd_set
trans_logs() {
  if [[ $# != 1 ]]; then
    echo "need input-log-file to trans!"
    return
  fi
  infile=$1
  outfile=probe.out
  cat $infile | awk '{print $1"."$3"."$4"."$2; }' | \
      awk 'BEGIN{FS="."} {printf("%s.%s.%s.%s.%s %s %s.", $1, $2, $4, $6, $3, $5, $1); system("printf %x "$4); printf("\n"); }' | \
      awk '{printf("%s %s %s ", $1,$2,$3); system("sudo ceph pg map "$3); }' | awk '{print $1,$2,$11}' >  $outfile
}


#
# 默认情况下从probe.out中读取log信息并查询集群中对应engine中的csd_seq
check_seq() {
  infile="probe.out"
  if [[ $# == 1 ]]; then
    infile="$1"
  fi
  while read line; do
    #echo "$line"
    pool_id=$(echo "$line" | awk -F "." '{ print $1}');
    ((pool_id++)) # using data-pool id
    engine_id=$(echo "$line" | awk -F "." '{ print $2}');
    engine_id=$(printf %x $engine_id); # dec to hex
    lsm_id=$(echo "$line" | awk '{print $1;}' | awk -F "." '{ print $NF;}');
    query_csd_seq='sudo ceph daemon dse.$(hostname) engine '"${pool_id}.${engine_id} dcache lsm stat ${lsm_id} | grep csd_writting_seq" 
    hostip=$(get_hostip_by_engine ${pool_id}.${engine_id})
    hostip=$(echo $hostip | awk -F\" '{print $2}')
    #echo "'$query_csd_seq'" on "$hostip"
    csd_seq=$(ssh -n $hostip "$query_csd_seq")
    csd_seq=$(echo "$csd_seq" | awk -F"," '{print $1;}')
    log_seq=$(echo "$line" | awk -F "." '{ print $4}');
    echo "seq in log: $log_seq, seq in query: $csd_seq"
  done < "$infile"
}



get_hostip_by_engine() {
  if [[ $# != 1 ]]; then
    echo ""
  fi
  host_ip=$(sudo ceph engine find $1 | grep "ip" | awk '{print $2;}' | awk -F: '{print $1}')
  echo "$host_ip"
}


get_hostip_by_osd() {
  if [[ $# != 1 ]]; then
    return ""
  fi
  host_ip=$(sudo ceph osd find $1 | grep "ip" | awk '{print $2;}' | awk -F: '{print $1}' | awk -F'"' '{print $2;}')
  echo "$host_ip"
}


set_all_engine_through() {
  sudo ceph daemon dse.$(hostname) engine all dcache ctrl mode through
}


set_all_engine_normal() {
  sudo ceph daemon dse.$(hostname) engine all dcache ctrl mode normal
}


show_all_engine_mode() {
  sudo ceph daemon dse.$(hostname) engine all dcache ctrl stat | grep "through mode"
}



show_log_count() {
  sudo ceph daemon dse.$(hostname) engine all dcache lsm stat | grep "count of written logs"
}

show_used_quota() {
  sudo ceph daemon dse.$(hostname) engine all dcache qm stat | grep "used_quota_in_bytes"
}


show_obj_count() {
  csd_list=$(ceph osd tree | awk '{print $3}' | grep osd)
  # echo "$csd_list" 
  for csd_id in $csd_list; do 
    echo -n "csd obj count in $csd_id: " 
    sudo ceph tell $csd_id list_objs | grep -B 1 bytes | grep obj
  done
}

list_obj() {
  if [[ $# != 1 ]]; then
    usage
    return
  fi
  echo "list log objs in osd-id: $1" 
  sudo ceph tell $1 list_objs
}


list_log() {
  if [[ $# == 0 ]]; then 
    csd_list=$(ceph osd tree | awk '{print $3}' | grep osd)
    #echo "$csd_list" 
  elif [[ $# == 1 ]]; then
    csd_list=$1
  else
    usage
    return
  fi
  #echo "list log objs in osd-id: $1" 
  for csd_id in $csd_list; do 
    sudo ceph tell $csd_id list_objs | grep -e pool_id -e engine_id -e pg_id -e seq -e lsm_id -e epoch \
        | awk '{ print $2;}' | xargs -n6 | awk  'BEGIN{FS=","} {print $1,$2,$3,$4,$5}' \
        | awk 'BEGIN{OFS="."}{print $1,$2,$3,$4,$5" "$6}' 
  done
}


get_pgmap() {
  if [[ $# != 1 ]]; then
    usage
    return
  fi
  echo "get pgmap by pg: $1" 
  sudo ceph pg map $1 
}


#
# dump出一个log对象并拷贝到本地
dump_log() {
  if [[ $# != 3 ]]; then
    usage
    return
  fi
  obj_file=$2_${1#*.}
  echo "osd-id: $1, obj: $2, epoch: $3, osd-file: $2_${1#*.}" 
  sudo ceph tell $1 data_obj $2 read $3
  # get host ip of osd
  hostip=$(get_hostip_by_osd $1)
  echo "scp log-file from $hostip"
  # 根据具体的环境这里的SDS_Admin可能需要改成root
  sudo scp root@$hostip:/var/lib/ceph/osd/$2* . 
}


#
# 默认将probe.out中所有log对象dump出来
dump_logs() {
  infile="probe.out"
  if [[ $# == 1 ]]; then
    infile="$1"
  fi
  while read line; do
    #echo "$line"
    osd_id=$(echo "$line" | awk '{print $NF;}' | awk -F"," '{print $1;}'| awk -F'[' '{print $2;}')
    obj_id=$(echo "$line" | awk '{ print $1}');
    epoch=$(echo "$line" | awk '{ print $2}');
    dump_log osd.$osd_id $obj_id $epoch
  done < "$infile"
}


del_log() {
  if [[ $# != 3 ]]; then
    usage
    return
  fi
  echo "del log objs on osd-id: $1, obj: $2, epoch: $3"
  sudo ceph tell $1 data_obj $2 delete $3
}

del_logs() {
  infile="probe.out"
  if [[ $# == 1 ]]; then
    infile="$1"
  fi
  while read line; do
    #echo "$line
    osds=$(echo "$line" | awk '{print $NF;}' | awk 'BEGIN{FS="[],[]";}{ for(i=1;i<=NF;i++)print $i}')
    obj_id=$(echo "$line" | awk '{ print $1}');
    epoch=$(echo "$line" | awk '{ print $2}');
    for id in $osds; do
      #echo "del log: osd.$id, $obj_id, $epoch"
      del_log osd.$id $obj_id $epoch
    done
  done < "$infile"
}


decode_log_file() {
  if [[ $# != 1 ]]; then
    usage
    return
  fi
  if [[ ! -e "$1" ]]; then
   echo "error: no file: $1"
   exit
  fi
  output=$1.de
  echo "decode log-file $1, out-put: $output" 
  ./lsm-decode list $1 > $output
}


#
# check pass: 日志对象中的每个op的mtime都要大于(不包含相等)数据对象的mtime,日志对象保留
#
check_decoded_file() {
  if [[ $# != 1 ]]; then
    usage
    return
  fi
  infile=$1.de
  echo "check decoded-file: $infile" 
  while read line; do
    logtime=$(echo $line | awk '{print $NF}')
    obj=$(echo $line | awk '{print $4}')
    stat=$(sudo rados -p $pool_name stat $obj)
    #echo "$stat" 
    d=$(echo $stat | awk '{print $3}')
    t=$(echo $stat | awk '{print $4}' | awk -F, '{print $1}')
    datatime=$(date -d "$d $t" +%s)
    echo -n "$obj logtime $logtime ->  $datatime [$d $t] " 
    if [[ $logtime -gt $datatime ]]; then
      echo -e "${GRN}pass${NC}"
    elif [[ $logtime -eq $datatime ]]; then
      echo -e "${YEL}same${NC}"
    else
      echo -e "${RED}fail${NC}"
    fi
  done < "$infile"
}


usage() {
  echo "usage: $0 { probe }"
  echo "usage: $0 { check-seq }"
  echo "usage: $0 { dump-logs }"
  echo "usage: $0 { check-log <log-file> }"
  echo "usage: $0 { del-logs }"
  echo "usage: $0 { del-log <osd-id> <pool-id>.<engine-id>.<pg-id>.<seq>.<lsm-id> <epoch> }"
  echo "usage: $0 { dump-log <osd-id> <pool-id>.<engine-id>.<pg-id>.<seq>.<lsm-id> <epoch> }"
  echo "usage: $0 { list-obj <osd-id> }"
  echo "usage: $0 { list-log <osd-id> }"
  echo "usage: $0 { pgmap <pg-id> }"
  echo "usage: $0 { set-through | set-normal | show-mode | show-quota | show-log-count | show-obj-count }"
}

main() {
  op="set"
  if [[ $# -ne 0 ]]; then
    op=$1
  fi
  case $op in 
    "probe")
      echo "do first-probe..."
      probe  "probe.log1"
      echo "waiting $probe_interval second to do second-probe..."
      sleep $probe_interval
      echo "do second-probe..."
      probe  "probe.log2"
      echo "do trans..."
      comm -12 probe.log1 probe.log2 > probe.comm
      trans_logs "probe.comm"
      echo "done."
      ;;
    "check-seq")
      check_seq
      ;;
    "set-through")
      set_all_engine_through
      ;;
    "set-normal")
      set_all_engine_normal
      ;;
    "show-mode")
      show_all_engine_mode
      ;;
    "show-quota")
      show_used_quota
      ;;
    "show-log-count")
      show_log_count
      ;;
    "show-obj-count")
      show_obj_count
      ;;
    "list-obj")
      shift
      list_obj $@
      ;;
    "list-log")
      shift
      list_log $@
      ;;
    "pgmap")
      shift
      get_pgmap $@
      ;;
    "dump-log")
      shift
      dump_log $@
      ;;
    "dump-logs")
      shift
      dump_logs $@
      ;;
    "del-log")
      shift
      del_log $@
      ;;
    "del-logs")
      shift
      del_logs $@
      ;;
    "decode")
      shift
      decode_log_file $@
      ;;
    "check-log")
      shift
      decode_log_file $@
      check_decoded_file $@
      ;;
    *)
      usage
      ;;
  esac
}

main $@
