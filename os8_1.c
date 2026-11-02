
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

struct msg {
    int end;
    char text[512];
};

int main() {
    struct msg m;
    char buf[512];

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    int w = open("fifo1", O_WRONLY);
    int r = open("fifo2", O_RDONLY);

    while (1) {
        printf("Enter sentence (exit to stop): ");
        if (!fgets(m.text, sizeof(m.text), stdin))
            break;

        m.end = !strcmp(m.text, "exit\n") ||
                !strcmp(m.text, "exit");

        write(w, &m, sizeof(m));
        if (m.end) break;
    }

    close(w);

    int n;
    while ((n = read(r, buf, sizeof(buf))) > 0)
        write(1, buf, n);

    close(r);
    unlink("fifo1");
    unlink("fifo2");
    return 0;
}
