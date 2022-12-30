#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

extern int counter;

int main(void) {
    int fd = open("tmp.txt", O_CREAT | O_WRONLY | O_APPEND);

    printf("tmp.txt fd = %d\n", fd);
    int dup_fd = dup(fd);
    printf("dup_fd = %d\n", dup_fd);
    dprintf(dup_fd, "This string will be printed in tmp2.txt file\n");
    exit(EXIT_SUCCESS);
}
