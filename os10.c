#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, a[100], head, done[100] = {0}, total = 0;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    printf("Enter initial head: ");
    scanf("%d", &head);

    for (int i = 0; i < n; i++) {
        int min = 999999, pos = -1;
        for (int j = 0; j < n; j++)
            if (!done[j] && abs(head - a[j]) < min) {
                min = abs(head - a[j]);
                pos = j;
            }
        total += abs(head - a[pos]);
        head = a[pos];
        done[pos] = 1;
        printf("%d ", head);
    }
    printf("\nTotal head movement = %d\n", total);
    return 0;
}