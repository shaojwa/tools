#/bin/bash
# by wsh @20231228

timeout=10000 # in us
interval=1000 # in us

set_wdog() {
  for processer_id in {37..40}; do
    echo set $timeout $interval in $processer_id
    sudo onestor-dpe module dse.$(hostname) coro_set_wdog $timeout $interval $processer_id
  done
}


first_pid=0049
last_pid=0084
filter_processer_log() {
  if [[ "$#" -eq 0 ]]; then
    for pid in $(seq -w ${first_pid} ${last_pid}); do
      cat coroutine.log | grep "\[${pid}\]" >$pid.log
    done
  else
    cat coroutine.log | grep "\[$1\]" >$1.log
  fi
}

get_time_cost() {
  if [[ "$#" -eq 0 ]]; then
    for pid in $(seq -w ${first_pid} ${last_pid}); do
      sort_time $pid.log
    done
  else
    sort_time $1.log
   file="$1"
  fi
  #cat "$file" | awk -F] '{print $1 }' | awk -F[ '{print $2 }' | awk -F. '{print $1,$2}' \
  #  | awk 'BEGIN{n=0;}{if(NR%2==0){if($3>n){n=$3-n;}else{n=$3+1000000-n;}; print $2"."$3,n}else{n=$3;}}' >$file.time
  #cat "$file.time" | sort -nr -k2 >$file.sort
}

sort_time() {
  if [[ $# -eq 0 ]]; then
    echo "error: sort-time need processer id"
    return
  fi
  file=$1
  cat "$file" | awk -F] '{print $1 }' | awk -F[ '{print $2 }' | awk -F. '{print $1,$2}' \
    | awk 'BEGIN{n=0;}{if(NR%2==0){if($3>n){n=$3-n;}else{n=$3+1000000-n;}; print $2"."$3,n}else{n=$3;}}' >$file.time
  cat "$file.time" | sort -nr -k2 >$file.sort
}

usage() {
  echo "usage:"
  echo "  $0 { filter <processer_id> | time <logfile> }"
}

main() {
  op="none"
  if [[ $# -ne 0 ]]; then
    op="$1"
  else
   usage
   exit
  fi
  case $op in
    "filter")
     shift
     filter_processer_log $@
     ;;
    "time")
     shift
     get_time_cost $@
     ;;
    *)
     usage
     ;;
 esac
}

main $@



    
