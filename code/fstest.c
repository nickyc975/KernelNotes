#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 20
#define FILE_NAME "test.txt"
#define OPEN_FAILED_MSG(name) "Open file " name " failed\n"

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