
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Sort requests in ascending order
void sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

// =====================================
// SSTF (Shortest Seek Time First)
// =====================================

void SSTF(int a[], int n, int head) {
    int done[MAX] = {0};
    long total = 0;

    printf("\nSSTF Order: ");

    for (int i = 0; i < n; i++) {
        int min = 999999, pos = -1;

        for (int j = 0; j < n; j++) {
            if (!done[j] && abs(head - a[j]) < min) {
                min = abs(head - a[j]);
                pos = j;
            }
        }

        total += abs(head - a[pos]);
        head = a[pos];
        done[pos] = 1;

        printf("%d ", head);
    }

    printf("\nSSTF Total Head Movement = %ld\n", total);
}

// =====================================
// SCAN (Elevator Algorithm)
// =====================================

void SCAN(int a[], int n, int head, int disk_size) {
    int split = 0;
    long total = 0;
    int current = head;

    while (split < n && a[split] < head)
        split++;

    printf("\nSCAN Order (Higher cylinders first): ");

    // Move towards higher cylinders
    for (int i = split; i < n; i++) {
        printf("%d ", a[i]);
        total += abs(a[i] - current);
        current = a[i];
    }

    // Move to the last cylinder
    if (current != disk_size - 1) {
        total += (disk_size - 1) - current;
        current = disk_size - 1;
    }

    // Reverse direction
    for (int i = split - 1; i >= 0; i--) {
        printf("%d ", a[i]);
        total += abs(current - a[i]);
        current = a[i];
    }

    printf("\nSCAN Total Head Movement = %ld\n", total);
}

// =====================================
// C-LOOK (Circular LOOK)
// =====================================

void CLOOK(int a[], int n, int head) {
    int split = 0;
    long total = 0;
    int current = head;

    while (split < n && a[split] < head)
        split++;

    printf("\nC-LOOK Order (Higher cylinders first): ");

    // Move towards higher cylinders
    for (int i = split; i < n; i++) {
        printf("%d ", a[i]);
        total += abs(a[i] - current);
        current = a[i];
    }

    // Circular jump to the lowest request
    if (split > 0) {
        total += abs(current - a[0]);
        current = a[0];

        for (int i = 0; i < split; i++) {
            printf("%d ", a[i]);

            if (i > 0)
                total += abs(a[i] - current);

            current = a[i];
        }
    }

    printf("\nC-LOOK Total Head Movement = %ld\n", total);
}

// =====================================
// MAIN FUNCTION
// =====================================

int main() {
    int a[MAX], n, head, disk_size;

    printf("Enter number of requests: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of requests!\n");
        return 1;
    }

    printf("Enter request queue: ");

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1)
            return 1;
    }

    printf("Enter initial head position: ");

    if (scanf("%d", &head) != 1 || head < 0)
        return 1;

    printf("Enter total number of cylinders: ");

    if (scanf("%d", &disk_size) != 1 ||
        disk_size < 2 || head >= disk_size) {
        printf("Invalid disk/head size!\n");
        return 1;
    }

    // Validate requests
    for (int i = 0; i < n; i++) {
        if (a[i] < 0 || a[i] >= disk_size) {
            printf("Request outside disk range!\n");
            return 1;
        }
    }

    // Sort request queue for SCAN and C-LOOK
    sort(a, n);

    printf("\n========== DISK SCHEDULING ==========\n");

    SSTF(a, n, head);
    SCAN(a, n, head, disk_size);
    CLOOK(a, n, head);

    printf("\n=====================================\n");

    return 0;
}
