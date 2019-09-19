 #### selinx查询设置
 
 * 三种模式
 * 两种策略：targeted 和 strict
 * 查看状态
 
       sestatus -v
     
 * 查看当前模式
 
       getenforce
 * 设置成permissive 模式
 
       setenfroce 0
        
 * 持久化设置
 
       /etc/selinux/config
       
 * 修改后重启
 
     sudo shutdown -r 0
