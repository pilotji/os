#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int p1[2], p2[2], pid;
    char file[100], data[4096];
    pipe(p1);
    pipe(p2);

    pid = fork();

    if (pid == 0) {
        close(p1[1]); close(p2[0]);
        read(p1[0], file, sizeof(file));
        FILE *f = fopen(file, "r");
        int n = f ? fread(data, 1, sizeof(data), f) : 0;
        if (f) fclose(f);
        write(p2[1], data, n);
        close(p1[0]); close(p2[1]);
    } else {
        close(p1[0]); close(p2[1]);
        printf("Enter file pathname: ");
        scanf("%99s", file);
        write(p1[1], file, strlen(file) + 1);
        close(p1[1]);
        int n = read(p2[0], data, sizeof(data));
        printf("\nFile contents:\n");
        if (n > 0) write(1, data, n);
        close(p2[0]);
        wait(NULL);
    }
    return 0;
}
