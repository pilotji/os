#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    char msg[1000] = "", line[200], result[1000];
    int fd1, fd2;

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    printf("Enter sentences (type END to stop):\n");

    while (fgets(line, sizeof(line), stdin)) {
        if (strcmp(line, "END\n") == 0 || strcmp(line, "END") == 0)
            break;

        if (strlen(msg) + strlen(line) >= sizeof(msg) - 1) {
            printf("Input limit reached!\n");
            break;
        }

        strcat(msg, line);
    }

    fd1 = open("fifo1", O_WRONLY);
    write(fd1, msg, strlen(msg) + 1);
    close(fd1);

    fd2 = open("fifo2", O_RDONLY);
    read(fd2, result, sizeof(result));
    printf("\nResult from Receiver:\n%s", result);
    close(fd2);

    return 0;
}
