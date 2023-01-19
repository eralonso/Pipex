#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

extern int counter;

int main(void)
{
    int fd = open("tmp.txt", O_CREAT | O_WRONLY | O_APPEND);

    printf("tmp.txt fd = %d\n", fd);
    int dup_fd = dup2(fd, 1);
    dprintf(2, "dup_fd = %d\n", dup_fd);
    int dup_fd2 = dup2(fd, 1);
    dprintf(2, "dup_fd2 = %d\n", dup_fd2);
    printf("This string will be printed in tmp.txt file\n");
	return (0);
}
