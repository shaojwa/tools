#!/bin/bash -e

ceph_conf=ceph.conf


# $1: module_name $2: processers_num
libgo_conf_append() {
  if [[ $# -ne 2 ]]; then
    echo "error: append libgo_conf need 2 args: <module> <processers_num>" 1>&2
    return
  fi
  if ! grep -q "^libgo_conf" "$ceph_conf"; then
    echo "warn: do nothing: libgo_conf not found"
    return
  fi
  libgo_conf=$(grep "libgo_conf" "$ceph_conf")
  #echo $libgo_conf
  if [[ "$libgo_conf" =~ "$1" ]]; then
    echo "'$1' found in 'libgo_conf', skip"
    return
  fi

  proc_num=$(grep "^libgo_conf" "$ceph_conf" | grep -o "processers_num=[0-9]\+")
  num=$(echo $proc_num | awk -F= '{print $NF}')
  new_num=$(($num+$2))
  new_proc_num="processers_num=$new_num"
  sed -i "/^libgo_conf/s/$proc_num/$new_proc_num/g" $ceph_conf
  module_conf="m_$1=${num}-$((${new_num}-1))"
  sed -i "/^libgo_conf/s/$/, $module_conf/g" "$ceph_conf"
}


# $1: module_name $2: processers_per_engine
proc_alloc_append() {
  if [[ $# -ne 2 ]]; then
    echo "error: append processer_allocation need 2 args: <module> <processers_per_engine>" 1>&2
    return
  fi
  if ! grep -q "^processer_allocation" "$ceph_conf"; then
    echo "warn: do nothing: processer_allocation not found"
    return
  fi
  proc_alloc=$(grep "processer_allocation" "$ceph_conf")
  if [[ "$proc_alloc" =~ "$1" ]]; then
    echo "'$1' found in 'processer_allocation', skip"
    return
  fi
  sed -i "/^processer_allocation/s/$/, $1=$2/g" "$ceph_conf"
}


libgo_conf_append dcache_ctrl 8
proc_alloc_append dcache_ctrl 1
