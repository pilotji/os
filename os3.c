#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sort(int a[], int n, int asc) {
    int i, j, t;
    for(i=0; i<n; i++)
        for(j=0; j<n-i-1; j++)
            if((asc && a[j]>a[j+1]) || (!asc && a[j]<a[j+1])) {
                t=a[j]; a[j]=a[j+1]; a[j+1]=t;
            }
}

void print(int a[], int n) {
    for(int i=0; i<n; i++) printf("\t%d", a[i]);
    printf("\n");
}

int main() {
    int a[20], n, ch, i;
    pid_t pid;

    printf("\nHOW MANY NOS DO YOU WANT IN ARRAY : ");
    scanf("%d", &n);
    if(n<1 || n>20) return 1;

    printf("ENTER ARRAY ELEMENT : ");
    for(i=0; i<n; i++) scanf("%d", &a[i]);

    printf("\n1. ZOMBIE PROCESS\n2. ORPHAN PROCESS\n");
    printf("Enter choice: ");
    scanf("%d", &ch);

    if(ch!=1 && ch!=2) return 1;

    pid=fork();

    if(pid==0) {
        if(ch==1) exit(0);

        printf("\n###THIS IS AN ORPHAN STATE###\n");
        sleep(5);
        printf("\nCHILD PROCESS PID : %d", getpid());
        printf("\nPARENT PROCESS PPID : %d\n", getppid());
        system("ps -el | grep init");

        printf("\n\nARRAY IN ASCENDING ORDER : ");
        sort(a,n,1);
        print(a,n);
    }
    else if(pid>0) {
        if(ch==1) {
            printf("\n###THIS IS A ZOMBIE STATE###\n");
            sleep(2);
            system("ps -el | grep Z");
            wait(NULL);
            printf("\nTERMINATED CHILD PID : %d",pid);
            printf("\nPARENT PID (MAIN) : %d",getpid());
            printf("\nPARENTS PARENT PPID (BASH) : %d",getppid());
            printf("\n\nARRAY IN DESCENDING ORDER : ");
            sort(a,n,0);
            print(a,n);
        }
        else {
            printf("\nParent process is terminating...\n");
            exit(0);
        }
    }
    else printf("\nERROR IN FORK!!\n");

    return 0;
}
