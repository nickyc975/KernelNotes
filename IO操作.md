# Linux系统IO操作的实现

## 例程

```c
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 20
#define FILE_NAME "test.txt"
#define OPEN_FAILED_MSG(name) "Open file " name " failed!\n"

int main()
{
    char buff[BUFFER_SIZE] = {0};
    int fd = open(FILE_NAME, O_RDONLY);
    if (fd < 0)
    {
        const char *msg = OPEN_FAILED_MSG(FILE_NAME);
        write(STDOUT_FILENO, msg, strlen(msg));
        return 0;
    }

    ssize_t nread = read(fd, buff, BUFFER_SIZE);
    write(STDOUT_FILENO, buff, nread);
    close(fd);
    return 0;
}
```

## 打开文件

### VFS层

* 分配文件描述符

* 文件路径解析、符号链接处理、权限检查

* 在dentry缓存中查找文件对应的inode：
  
  + 若找到，则直接返回
  
  + 若找不到，则创建一个dentry对象放到缓存中，并将其作为参数调用底层文件系统实现的lookup函数找到相应的inode

* 调用底层文件系统实现的open函数填充struct file结构体

* 将文件添加到当前进程的打开文件表中

### 文件系统实现层(以ext4为例)

* lookup函数：

  + 将文件名转化为inode号
  
  + 在super_block的inode列表中根据inode号找到相应的inode
  
  + 若找不到，则创建一个新的inode实例，并从磁盘上读取数据对其进行填充
    
    - 从磁盘上读取数据需要通过sb_getblk获取块设备上的数据块
    
    - sb_getblk通过super_block实例访问对应块设备的内存映射地址空间，获取读入的内存页，并找到相应的数据块
    
    - 内存页的管理属于Linux内存管理模块
  
  + 将inode实例与dentry项相关联，然后返回给VFS；

* open函数：处理日志和事务相关的任务
