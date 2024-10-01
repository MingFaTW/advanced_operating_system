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
        close(STDOUT_FILENO);
        printf("This message will not be printed to the terminal.\n"); 
        exit(0);
    } else { 
        int status;
        waitpid(rc, &status, 0);
        printf("Child process has finished. :)\n");
    }

    return 0;
}
