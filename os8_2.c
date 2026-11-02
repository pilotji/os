#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

int main() {
    char msg[1000], result[1000];
    int fd1, fd2, ch = 0, words = 0, lines = 0, inword = 0;

    fd1 = open("fifo1", O_RDONLY);
    read(fd1, msg, sizeof(msg));
    close(fd1);

    for (int i = 0; msg[i] != '\0'; i++) {
        ch++;

        if (msg[i] == '\n')
            lines++;

        if (isspace(msg[i]))
            inword = 0;
        else if (!inword) {
            words++;
            inword = 1;
        }
    }

    FILE *fp = fopen("result.txt", "w");
    fprintf(fp, "Characters: %d\nWords: %d\nLines: %d\n",
            ch, words, lines);
    fclose(fp);

    fp = fopen("result.txt", "r");
    fread(result, 1, sizeof(result) - 1, fp);
    fclose(fp);

    fd2 = open("fifo2", O_WRONLY);
    write(fd2, result, strlen(result) + 1);
    close(fd2);

    return 0;
}
