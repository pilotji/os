#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define PATH_SIZE 1024
#define BUF_SIZE 4096

int main(void) {
    int p_to_c[2], c_to_p[2];
    pid_t pid;
    char path[PATH_SIZE];

    printf("Enter file path: ");
    if (!fgets(path, sizeof(path), stdin)) return 1;
    path[strcspn(path, "\n")] = '\0';

    if (pipe(p_to_c) == -1 || pipe(c_to_p) == -1) {
        perror("pipe"); return 1;
    }

    pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        close(p_to_c[1]);
        close(c_to_p[0]);

        char received[PATH_SIZE];
        ssize_t n = read(p_to_c[0], received, sizeof(received) - 1);
        close(p_to_c[0]);
        if (n <= 0) _exit(1);
        received[n] = '\0';

        int fd = open(received, O_RDONLY);
        if (fd == -1) {
            const char *msg = "Child: unable to open the requested file.\n";
            write(c_to_p[1], msg, strlen(msg));
        } else {
            char buffer[BUF_SIZE];
            while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
                ssize_t sent = 0;
                while (sent < n) {
                    ssize_t k = write(c_to_p[1], buffer + sent, (size_t)(n - sent));
                    if (k <= 0) break;
                    sent += k;
                }
                if (sent < n) break;
            }
            close(fd);
        }
        close(c_to_p[1]);
        _exit(0);
    }

    close(p_to_c[0]);
    close(c_to_p[1]);

    size_t len = strlen(path), sent = 0;
    while (sent < len) {
        ssize_t n = write(p_to_c[1], path + sent, len - sent);
        if (n <= 0) { perror("write path"); break; }
        sent += (size_t)n;
    }
    close(p_to_c[1]);

    printf("\n--- File contents received from child ---\n");
    char buffer[BUF_SIZE];
    ssize_t n;
    while ((n = read(c_to_p[0], buffer, sizeof(buffer))) > 0)
        fwrite(buffer, 1, (size_t)n, stdout);
    close(c_to_p[0]);
    waitpid(pid, NULL, 0);
    return 0;
}
