#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    char msg[1000], result[1000];
    int fd1, fd2;

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    printf("Enter sentences (type END to stop):\n");

    fd1 = open("fifo1", O_WRONLY);
    fgets(msg, sizeof(msg), stdin);
    write(fd1, msg, strlen(msg) + 1);
    close(fd1);

    fd2 = open("fifo2", O_RDONLY);
    read(fd2, result, sizeof(result));
    printf("\nResult from Receiver:\n%s", result);
    close(fd2);

    return 0;
}
