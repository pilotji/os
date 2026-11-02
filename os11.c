#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) {
                int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
            }
}

int main(void) {
    int req[MAX], n, head, disk_size;
    int split = 0;
    long scan_move = 0, clook_move = 0;

    printf("Enter number of requests: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of requests.\n"); return 1;
    }
    printf("Enter request queue: ");
    for (int i = 0; i < n; i++)
        if (scanf("%d", &req[i]) != 1) return 1;

    printf("Enter initial head position: ");
    if (scanf("%d", &head) != 1) return 1;
    printf("Enter total number of cylinders (0 to size-1): ");
    if (scanf("%d", &disk_size) != 1 || disk_size < 2 ||
        head < 0 || head >= disk_size) {
        printf("Invalid disk/head size.\n"); return 1;
    }

    for (int i = 0; i < n; i++)
        if (req[i] < 0 || req[i] >= disk_size) {
            printf("Request outside disk range.\n"); return 1;
        }

    sort(req, n);
    while (split < n && req[split] < head) split++;

    /* Assumption: "away from spindle" means toward larger cylinder numbers. */
    printf("\nSCAN order (toward higher cylinders first): ");
    int current = head;
    for (int i = split; i < n; i++) {
        printf("%d ", req[i]);
        scan_move += abs(req[i] - current);
        current = req[i];
    }
    if (current != disk_size - 1) {
        scan_move += (disk_size - 1) - current;
        current = disk_size - 1;
    }
    for (int i = split - 1; i >= 0; i--) {
        printf("%d ", req[i]);
        scan_move += abs(current - req[i]);
        current = req[i];
    }
    printf("\nSCAN total head movement = %ld\n", scan_move);

    printf("\nC-LOOK order (toward higher cylinders first): ");
    current = head;
    for (int i = split; i < n; i++) {
        printf("%d ", req[i]);
        clook_move += abs(req[i] - current);
        current = req[i];
    }
    if (split > 0) {
        /* C-LOOK jumps from highest pending request to lowest pending request. */
        clook_move += abs(current - req[0]);
        current = req[0];
        for (int i = 0; i < split; i++) {
            printf("%d ", req[i]);
            if (i > 0) clook_move += abs(req[i] - current);
            current = req[i];
        }
    }
    printf("\nC-LOOK total head movement = %ld\n", clook_move);
    return 0;
}
