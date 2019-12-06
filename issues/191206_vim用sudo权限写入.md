#### 写入方式以及原因说明

    :w  !sudo tee
    
:w 表示把缓存buffer里的数据写入文件，但是w后有空格且有 !{cmd}的情况下，会把buffer中的数据输出，当做cmd的输入，也就是输出给命令。
从write作为输出这个角度来说，输出给文件，和输出给一个命令确实都可以认为是write，所以在:w中使用比较合理。输出给一个命令，也可以理解为当做这个命令的输入。!sudo tee %, 表示新起一个shell执行sudo tee % 命令，其中 % 对应的是文件路径，即vim打开时的路径，比如src/CMakeLists.txt。tee 会从标准输入读入数据，然后输出到标准输出以及文件。所以最终就会把buffer中的内容通过tee写入到 % 对应的 src/CMakeLists.txt 中。
