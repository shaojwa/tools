    // ifconfig is used to configure the kernel-resident network interfaces.
    // if no arguments are given, ifconfig displays the status of the currently active interfaces.
    
    alias interfaces
    ifconfig eth1:0 down // remove alias
    ifconfig eth1:0 172.16.84.199/24
