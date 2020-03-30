#### cmake 什么作用

跨平台，可用来构建软件，可用来安装软件。

#### CMakeLists.txt 是什么

是cmake的输入文件， cmake 通过 CMakeLists.txt 生成 Makefile文件和其他。

#### cmake的输出是什么

比如mds目录下的：
```
CMakeFiles  cmake_install.cmake  CTestTestfile.cmake  Makefile
// CMakeFiles 目录
// cmake_install.cmake
// CTestTestfile.cmake
// Makefile
```

#### .cmake文件是什么

#### 内部编译和外部编译
```
内部编译 in-source build， CMAKE_BINARY_DIR 等于 CMAKE_SOURCE_DIR
外部编译 out-of-source build， CMAKE_BINARY_DIR单独指定，不等于 CMAKE_SOURCE_DIR
```

#### 调试输出

```
message(STATUS "dbg: WITH_LIBCEPHFS: ${WITH_LIBCEPHFS}")
return()
```

## 工程命令

#### add_executable

添加一个可执行目标, 编译时最常碰到的两种目标之一，另外一种是库文件。

```
add_executable(<name> [WIN32] [MACOSX_BUNDLE]  [EXCLUDE_FROM_ALL]  source1 [source2 ...])
```

#### add_library

* 添加一个库目标，库有静态库、共享库、模块等分类

```
add_library(<name> [STATIC | SHARED | MODULE]  [EXCLUDE_FROM_ALL]  source1 [source2 ...])
add_library(<name> OBJECT <src>...)
```

STATIC：静态库，链接时直接将代码嵌入其他目标。
SHARED：共享库，动态链接到其他目标，执行文件启动时加载。
MODULE: 插件，不会链接到其他目标，执行文件运行时通过dopen等动态加载。
示例：

```
add_library(cls_ceph_quota SHARED ${cls_ceph_quota_srcs})
```

cls_ceph_quota 就是一个 library target

其中库名默认是 lib<target_name>，但是可以通过set_target_properties()来重新设置。

## add_custom_target

添加一个没有输出的build目标，所以每次都会执行，即认为永远过期。

## add_subdirectory

* 把一个目录添加进build目录进行build

```
add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
```

source_dir 指定 CMakelist.txt文件以及代码的所在位置，所以src下的代码要编译需要有 add_subdirectory(src)

binary_dir 指定输出文件位置，不指定，就用source_dir。

## add_dependencies

```
add_dependencies(cython_rados rados)
```

意思是一个顶层target，这里是cython_rados，依赖于另外一个顶层target，这里是rados。

添加依赖可以保证被依赖的target先于target被构建。

还有文件层的依赖，ADD_CUSTOM_TARGET and ADD_CUSTOM_COMMAND。

## install

添加一条install 规则：

```
install(TARGETS ceph-osd DESTINATION bin)
```

TARGETS 表明 ceph-osd 是一个 target名，DESTINATIO 是目标目录， bin 是目录名。

```
install(PROGRAMS mount.fuse.ceph DESTINATION ${CMAKE_INSTALL_SBINDIR})
```

PROGRAMMS 表明，安装一个可执行文件。

```
install(DIRECTORY  "${CMAKE_SOURCE_DIR}/src/include/cephfs" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# ${CMAKE_SOURCE_DIR} 源码顶层目录, CMAKE_INSTALL_INCLUDEDIR 默认路径在是 include
```

## target_link_libraries

把目标链接到库 

```
target_link_libraries(ceph-mds mds ${CMAKE_DL_LIBS} global-static common Boost::thread)
```

target文件必须是已经存在的，比如通过add_executable，或者 add_library 创建的文件。与库文件进行链接, ceph-mds是已经存在的文件。该命令并不是创建target。

## set_source_files_properties

```
set_source_files_properties([file1 [file2 [...]]] PROPERTIES prop1 value1 [prop2 value2 [...]])
```

设置源代码属性，这个属性可以影响这些源码如何被编译


# 属性

#### RUNTIME_OUTPUT_DIRECTORY 

# 脚本命令

####  function() 

定义一个函数。

#### list()

链表相关操作。

####  set

设置一个环境变量
