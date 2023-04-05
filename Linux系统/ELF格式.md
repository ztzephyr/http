

查看ELF文件的ELF Header

```bash
readelf -h hello.o
```



查看ELF文件的Section

```bash
read -SW hello.o
```





查看可执行文件的反汇编

```bash
gcc -g -c hello.o
objdump -S hello.o
```

