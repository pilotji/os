#include <stdio.h>
#include <stdlib.h>

int main() {
    int a[100], n, head, size, total = 0;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    printf("Enter initial head and disk size: ");
    scanf("%d%d", &head, &size);

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) {
                int t = a[i]; a[i] = a[j]; a[j] = t;
            }

    printf("SCAN: %d ", head);
    int cur = head;
    for (int i = 0; i < n; i++)
        if (a[i] >= head) {
            total += abs(cur - a[i]);
            cur = a[i];
            printf("%d ", cur);
        }
    total += abs(cur - (size - 1));
    cur = size - 1;
    printf("%d ", cur);
    for (int i = n - 1; i >= 0; i--)
        if (a[i] < head) {
            total += abs(cur - a[i]);
            cur = a[i];
            printf("%d ", cur);
        }
    printf("\nSCAN total movement = %d\n", total);

    total = 0;
    cur = head;
    printf("C-LOOK: %d ", head);
    int first = 1;
    for (int i = 0; i < n; i++)
        if (a[i] >= head) {
            total += abs(cur - a[i]);
            cur = a[i];
            printf("%d ", cur);
            first = 0;
        }
    for (int i = 0; i < n; i++)
        if (a[i] < head) {
            if (!first) {
                total += abs(cur - a[i]);
                cur = a[i];
                printf("%d ", cur);
            } else {
                total += abs(cur - a[i]);
                cur = a[i];
                printf("%d ", cur);
            }
            first = 0;
        }
    printf("\nC-LOOK total movement = %d\n", total);
    return 0;
}