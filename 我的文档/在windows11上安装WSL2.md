### WSL2概念

WSL 2 是适用于 Linux 的 Windows 子系统体系结构的一个新版本，它支持适用于 Linux 的 Windows 子系统在 Windows 上运行 ELF64 Linux 二进制文件。 它的主要目标是**提高文件系统性能**，以及添加**完全的系统调用兼容性**。





### 计算机设置



计算机的CPU必须开启虚拟化功能。使用Ctrl+Alt+Del打开任务管理器，切换到性能标签页，确认虚拟化是已开启状态。如果没有开启，需要进入计算机的BIOS中进行设置。



控制面板->程序->启用或关闭 windows 功能 ->开启 Windows 虚拟化和 Linux 子系统，然后点击确定后会要求重启系统。

控制面板->程序->启用或关闭 windows 功能 ->勾选虚拟机平台







### 安装Linux发行版



在微软商店中，搜索WSL，找想要的发行版，下载然后打开，设置用户名和密码



注意在应用商店直接打开Ubuntu时，可能会出现以下错误：

```bash
Error: 0x800701bc WSL 2 ?????????????????? https://aka.ms/wsl2kernel
```

此时需要使用管理员权限打开powershell, 执行wsl更新：

```bash
wsl --update
```



更新完成后，再通过应用商店点开Ubuntu，此时会显示正在安装，然后提示输入用户名和密码







### 迁移到D盘



```bash
wsl --shutdown

wsl --export Ubuntu-20.04 d:\Ubuntu-20.04.tar

wsl --unregister Ubuntu-20.04

wsl --import Ubuntu-20.04 D:\Linux_Files D:\Ubuntu-20.04.tar --version 2

ubuntu2004 config --default-user zt
```





### 参考资料

https://learn.microsoft.com/zh-cn/windows/wsl/about







### Ubuntu20.04设置





```bash

sudo apt-get install net-tools
```

