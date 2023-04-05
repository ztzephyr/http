### NFS(网络文件系统)介绍

 xxxxxxx

通常用在两台Linux系统之间共享文件

将服务器上的目录作为NFS文件系统，客户机可通过mount该文件系统，使用它。





### Linux中配置NFS服务



安装NFS服务

```bash
# NSF的核心服务程序
sudo apt-get install nfs-kernel-server 
# NFS的客户程序
sudo apt-get install nfs-common
```



在服务器上添加NFS配置

```bash
# 在/etc/exports中添加
# [共享的目录]   客户端ip(参数1,参数2...)
/home/share/nfs   *(rw,sync,no_root_squash,no_subtree_check)
```

>   假设要将服务器的/home/share/nfs目录设置NFS文件系统，*指定所有主机均可访问。
>
>   rw：设置该目录可读写，也可设置为ro，表示只读。
>
>   sync：将数据同步写入内存缓冲区与磁盘中，可以保证数据的一致性。
>
>   no_root_squash：不将root用户及所属用户组都映射为匿名用户或用户组
>
>   no_subtree_check：即使输出目录为子目录，也不检查器父目录的权限。





NFS服务的启动与停止

```bash
# 方式一
/etc/init.d/nfs-kernel-server start
# 方式二
service nfs-kernel-server start
```

>   如果需要停止NFS服务将start改为stop即可，方式二启动NFS服务无回显信息





### 客户端挂载NFS



```bash
# ARM单板上挂载服务器上的NFS到/mnt下
mount  -o nolock  192.168.0.103:/home/share/nfs   /mnt
```

ARM单板和Linux服务器必须在同一个网段