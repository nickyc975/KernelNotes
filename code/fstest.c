#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

#define BUFFER_SIZE 20
#define FILE_NAME "test.txt"
#define OPEN_FAILED_MSG(name) "Open file " name " failed!\n"

int main()
{
    char buff[BUFFER_SIZE] = {0};
    int fd = syscall(SYS_open, FILE_NAME, O_RDONLY);
    if (fd < 0)
    {
        const char *msg = OPEN_FAILED_MSG(FILE_NAME);
        syscall(SYS_write, STDOUT_FILENO, msg, strlen(msg));
        return 0;
    }

    ssize_t nread = syscall(SYS_read, fd, buff, BUFFER_SIZE);
    syscall(SYS_write, STDOUT_FILENO, buff, nread);
    syscall(SYS_close, fd);
    return 0;
}