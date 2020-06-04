ceph命令自己实现输出：
```
 echo $(ceph --completion "")
```
 或者复杂点的
```
[root@node118 ~]# declare -a args=("mds" "set");
[root@node118 ~]# COMPREPLY=($(ceph --completion "${args[@]}" 2>/dev/null));
[root@node118 ~]# echo "${COMPREPLY[@]}"
set set_max_mds set_state
[root@node118 ~]# declare -a args=("mds" "");
[root@node118 ~]# COMPREPLY=( $(ceph --completion "${args[@]}" 2>/dev/null) );
[root@node118 ~]# echo "${COMPREPLY[@]}"
add_data_pool caps cluster_down cluster_up compat count-metadata deactivate dump fail getmap metadata newfs remove_data_pool repaired rm rm_data_pool rmfailed set set_max_mds s
et_state stat stop tell versions
 ```
