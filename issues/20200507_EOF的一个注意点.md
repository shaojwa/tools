用here-doc的时候，一定要注意结尾的EOF要定格写且不能有多余的空格和注释字符等： 
until a line containing only delimiter (with no  trailing  blanks) is seen.   
```
ssh root@$node <<EOF
  mds_id=$(basename $(ls /var/lib/ceph/mds/)  | egrep -o mds[0-9])
  echo "mds-id is ${mds_id}"

  #cephfs-journal-tool journal reset
  #ceph mds repaired 0

  echo "reset-failed"
  systemctl reset-failed ceph-mds@${mds_id}.service
  echo "restart"
  systemctl restart ceph-mds.target
EOF
```
所以，如果here-doc中的字符不扩展，需要将<<之后的work中的任何一个字符加上引号（If any characters in word are quoted, the delimiter is the result of quote removal on word, and the lines in the here-document are not expanded.）。
