
#include <stdio.h>

int main() {
    int n, m, i, j, k;
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], finish[10] = {0}, safe[10], count = 0;

    printf("Enter processes and resources: ");
    scanf("%d%d", &n, &m);

    printf("Enter allocation matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter maximum matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            if (!finish[i]) {
                for (j = 0; j < m; j++)
                    if (need[i][j] > avail[j]) break;

                if (j == m) {
                    for (j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    safe[count++] = i;
                    finish[i] = 1;
                }
            }

    if (count == n) {
        printf("System is in safe state.\nSafe sequence: ");
        for (i = 0; i < n; i++)
            printf("P%d ", safe[i]);
    } else
        printf("System is in unsafe state.");

    printf("\n");
    return 0;
}
