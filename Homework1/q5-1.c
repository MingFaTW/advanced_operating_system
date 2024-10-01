#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process (PID: %d) is running.\n", getpid());
        sleep(2); 
        printf("Child process (PID: %d) is done.\n", getpid());
        exit(0); 
    } else {
        printf("Parent process (PID: %d) is waiting for child process (PID: %d) to finish.\n", getpid(), rc);
        int status;
        printf("wait the child process PID: %d\n",wait(&status));
        if(wait(&status)){
            printf("Child process exited with wait(&status) returned: %d\n", wait(&status));
        }
        printf("Parent process (PID: %d) is done. : )\n", getpid());
    }

    return 0;
}
