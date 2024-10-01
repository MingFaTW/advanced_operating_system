#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    int rc = fork(); 
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process is running\n");
        int status;
        printf("wait(&status): %d\n",wait(&status));
        if(wait(&status)){
            printf("No more child process here.\n");
        }
    } else { 
        wait(NULL); 
    }
    return 0;
}
