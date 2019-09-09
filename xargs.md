#### 常用法
    
    cat hosts | xargs -I{} ssh root@{} hostname
    sudo locate -br ^.*\\.sh$  | xargs -i bash -c 'echo {} >> total.sh; cat {} >> total.sh'
