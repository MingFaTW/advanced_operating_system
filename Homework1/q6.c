#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int rc = fork();  

    if (rc < 0) {
        perror("Fork failed");
        exit(1);
    } else if (rc == 0) { 
        printf("Child process is running. PID=%d\n", getpid());
        sleep(2);  
    } else {  
        int status;
        int waited_pid = waitpid(rc, &status, 0); 
        printf("Parent process is running. PID=%d\n", getpid());
        printf("waitpid() returned: %d\n", waited_pid);
    }

    return 0;
}
