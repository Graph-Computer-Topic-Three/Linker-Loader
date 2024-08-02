# Funny Little Executable (Python)

南京大学蒋炎岩老师 “自行设计” 了能实现 (静态) 链接和加载的二进制文件格式，以及相应的编译器、链接器 (复用 gcc/ld) 和加载器。FLE 文件直接将一段可读、可写、可执行的位置无关代码连通数据映射到内存并跳转执行。

# Funny Little Executable (C++)

在原有 Python 实现基础上，复用 fle 格式，本项目给出了 C++ 版本实现 (fle-cpp)。