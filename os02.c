#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Selection Sort (Ascending)
void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[min])
                min = j;
        int t = a[i];
        a[i] = a[min];
        a[min] = t;
    }
}
// Bubble Sort (Descending)
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

// General Sorting Function
void sort(int a[], int n, int asc) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((asc && a[j] > a[j + 1]) ||
                (!asc && a[j] < a[j + 1])) {
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
    int a[20], n, ch;
    pid_t pid;

    printf("\nENTER NUMBER OF INTEGERS: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > 20) {
        printf("Invalid size!\n");
        return 1;
    }

    printf("ENTER ARRAY ELEMENTS: ");

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("\n========== MENU ==========\n");
    printf("1. Selection Sort and Bubble Sort\n");
    printf("2. Zombie Process\n");
    printf("3. Orphan Process\n");
    printf("==========================\n");

    printf("Enter choice: ");

    if (scanf("%d", &ch) != 1 || ch < 1 || ch > 3) {
        printf("Invalid choice!\n");
        return 1;
    }

    pid = fork();

    if (pid == 0) {
        // CHILD PROCESS

        if (ch == 1) {
            bubbleSort(a, n);

            printf("\n[Child] PID = %d, Parent PID = %d\n",
                   getpid(), getppid());

            printf("[Child] Bubble Sort (Descending): ");
            print(a, n);
        }

        else if (ch == 2) {
            // Zombie Process
            exit(0);
        }

        else {
            // Orphan Process
            printf("\n### THIS IS AN ORPHAN STATE ###\n");

            sleep(5);

            printf("\nCHILD PROCESS PID : %d", getpid());
            printf("\nPARENT PROCESS PPID : %d\n", getppid());

            system("ps -el | grep init");

            printf("\nARRAY IN ASCENDING ORDER: ");

            sort(a, n, 1);
            print(a, n);
        }
    }

    else if (pid > 0) {
        // PARENT PROCESS

        if (ch == 1) {
            selectionSort(a, n);

            printf("\n[Parent] PID = %d, Child PID = %d\n",
                   getpid(), pid);

            printf("[Parent] Selection Sort (Ascending): ");
            print(a, n);

            wait(NULL);
        }

        else if (ch == 2) {
            // Zombie Process
            printf("\n### THIS IS A ZOMBIE STATE ###\n");

            sleep(2);

            system("ps -el | grep Z");

            wait(NULL);

            printf("\nTERMINATED CHILD PID : %d", pid);
            printf("\nPARENT PID (MAIN) : %d", getpid());
            printf("\nPARENTS PARENT PPID (BASH) : %d", getppid());

            printf("\n\nARRAY IN DESCENDING ORDER: ");

            sort(a, n, 0);
            print(a, n);
        }

        else {
            // Orphan Process
            printf("\nParent process is terminating...\n");
            exit(0);
        }
    }

    else {
        printf("\nERROR IN FORK!!\n");
        return 1;
    }

    return 0;
}
