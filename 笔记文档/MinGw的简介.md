

## 概述

MinGW(Minimalist GNU for Windows)是一个在 Windows 上提供 GNU 工具集的开源项目。它提供了一组编译器、链接器、库和工具，可以让开发者在 Windows 平台上编译 C、C++或者其他语言的程序。换句话说，MinGW 是基于 GCC(GNU Compiler Collection) 编译器的一个移植版本。

> 备注说明：
>
> 1.首先，gcc官网提供的 gcc 编译器是无法直接安装到 windows 平台上的，若要在windows下使用gcc编译器，可以安装gcc的移植版本。当前适用于windows的主流的gcc移植版本主要是 MinGW 和 Cygwin，MinGW 侧重于在windows下可以使用gcc编译环境，生成可在windows下运行的可执行程序，且体积小使用方便。但是， Cygwin 则可以提供一个完整的 Linux 环境，借助它不仅可以在 windows平台上使用 GCC 编译器，理论上可以运行 Linux 平台上所有的程序。



也有人这么理解：

> 编译工具我们选用gcc（全称GNU Compiler Collection 意思是GNU编译器套件），不过不是原版的gcc，而是它在Windows下的特制版**MinGW**(全称Minimalist GNU on Windows）。它实际上是将GCC 移植到了 Windows 平台下，并且包含了 Win32API ，因此可以将源代码编译为可在 Windows 中运行的可执行程序。而且还可以使用一些 Windows 不具备的，Linux平台下的开发工具。MinGW又分为MinGW-w64 与 MinGW ，区别在于 MinGW 只能编译生成32位可执行程序，而 **MinGW-w64** 则可以编译生成 64位 或 32位 可执行程序。MinGW 现已被 MinGW-w64 所取代，且 MinGW 也已停止了更新。



## 下载地址

> MinGW下载(`mingw-get-setup.exe`)： https://osdn.net/projects/mingw/
>
> MinGW-W64下载( `MinGW-W64-install.exe`)： https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/ 







## 在线安装

双击`MinGW-W64-install.exe`运行安装程序，启动在线下载安装。



### 安装选项

安装前会弹出版本选择页面，并提供有不同的选项。

- version : 

​	GCC编译器版本选择。一般选择最高版本即可。

- Architecture: 

​	电脑系统架构选择。指的是电脑系统是32位还是64位,根据自己的电脑系统自行选择。64位选择x86_64;32位选择i686。

- Threads：

    操作系统接口协议选择。开发windows程序选择win32，否则选择posix。

- Exception:

    异常处理模型选择。前面选择了64位系统架构的话，可以选择seh和sjlj，seh比较新性能比较好，但是不支持32位。我选择seh。

- Build revision：

    不知道。选择默认选项



### 环境变量

首先选择安装目录，如D:\mingw-64。然后需要将D:\mingw-64\mingw64\bin目录添加到环境变量。















