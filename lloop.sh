#!/bin/bash

outfile="lloop.out"

while true; do
  echo "================" >> $outfile
  echo $(date) >> $outfile
  echo "----------------" >> $outfile
  top -bn1 -p $(pidof dpe) >> $outfile
  echo "----------------" >> $outfile
  free -g >> $outfile
  echo "----------------" >> $outfile
  numastat >> $outfile
  echo "----------------" >> $outfile
  numactl -H >> $outfile
  echo "----------------" >> $outfile
  onestor-dpe module dse.$(hostname) dump_mempools | grep -A2 bluestore_cache >> $outfile
  echo "----------------" >> $outfile
  onestor-dpe module dse.$(hostname) engine all db row stat | grep -A5 engine | grep -e engine -e block_cache  >> $outfile
  echo "----------------" >> $outfile
  ts=$(date +%m%d%H%M)
  cmd_client < umm.cmd > umm.out.$ts
  sleep 600
done
