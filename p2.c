
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

struct msg {
    int end;
    char text[512];
};

int main() {
    struct msg m;
    char buf[512], last = '\n';
    int ch = 0, words = 0, lines = 0, inword = 0;

    int r = open("fifo1", O_RDONLY);
    int w = open("fifo2", O_WRONLY);

    FILE *fp = fopen("result.txt", "w");

    while (read(r, &m, sizeof(m)) == sizeof(m)) {
        if (m.end) break;

        fprintf(fp, "%s", m.text);

        for (int i = 0; m.text[i]; i++) {
            char c = m.text[i];
            ch++;
            if (c == '\n') lines++;

            if (isspace((unsigned char)c))
                inword = 0;
            else if (!inword) {
                words++;
                inword = 1;
            }
            last = c;
        }
    }

    if (last != '\n' && ch > 0) lines++;

    fprintf(fp, "\nCharacters: %d\nWords: %d\nLines: %d\n",
            ch, words, lines);
    fclose(fp);
    close(r);

    fp = fopen("result.txt", "r");
    int n;
    while ((n = fread(buf, 1, sizeof(buf), fp)) > 0)
        write(w, buf, n);

    fclose(fp);
    close(w);
    return 0;
}
