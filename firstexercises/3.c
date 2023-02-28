#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int status;
    int pid = fork();
    if(pid == 0) {
        int pid2 = fork();
        if(pid2 == 0) {
            printf("I am the grandchild %d\n", getpid());
        }
        else {
            wait(NULL);
            printf("I am the child %d\n", getpid());
        }
    }
    else {
        wait(NULL);
        printf("I am the parent %d\n", getpid());
    }
    return 0;
}