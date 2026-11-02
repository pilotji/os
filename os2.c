#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// Selection Sort
void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min])
                min = j;
        }

        int t = a[i];
        a[i] = a[min];
        a[min] = t;
    }
}

// Bubble Sort
void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] < a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

// Print Array
void print(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[10], n;

    printf("Enter number of integers: ");
    scanf("%d", &n);

    if (n < 1 || n > 10) {
        printf("Invalid size!\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    pid_t pid = fork();

    if (pid == 0) {
        // Child Process
        bubbleSort(a, n);

        printf("\n[Child] PID = %d, Parent PID = %d\n",
               getpid(), getppid());

        printf("[Child] Bubble Sort (Descending): ");
        print(a, n);
    }
    else if (pid > 0) {
        // Parent Process
        selectionSort(a, n);

        printf("\n[Parent] PID = %d, Child PID = %d\n",
               getpid(), pid);

        printf("[Parent] Selection Sort (Ascending): ");
        print(a, n);

        wait(NULL);
    }
    else {
        printf("Error in fork!\n");
    }

    return 0;
}
