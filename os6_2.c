#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main() {
    char msg[1000], result[1000];
    int fd, ch = 0, words = 0, lines = 0, inword = 0;

    fd = open("fifo1", O_RDONLY);
    int n = read(fd, msg, sizeof(msg) - 1);
    close(fd);

    if (n < 0) return 1;
    msg[n] = '\0';

    for (int i = 0; msg[i] != '\0'; i++) {
        ch++;

        if (msg[i] == '\n')
            lines++;

        if (isspace((unsigned char)msg[i]))
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
    int size = fread(result, 1, sizeof(result) - 1, fp);
    result[size] = '\0';
    fclose(fp);

    fd = open("fifo2", O_WRONLY);
    write(fd, result, strlen(result) + 1);
    close(fd);

    return 0;
}
