    Mem一列是操作系统角度看到的内存占用，所以 used 是包含 buffers 和cached
    -/+ buffers/cache 这一列是应用程序角度看到的内存占用：
    （1）used 是Mem一列减去buffers 和cached的结果。
    （2）free 是Mem一列加上buffers 和cached的结果。
