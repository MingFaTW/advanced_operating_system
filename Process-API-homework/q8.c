#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipeEnd[2]; 
    if (pipe(pipeEnd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    int rc1 = fork();

    if (rc1 < 0) {
        perror("Fork failed for first child");
        exit(1);
    } else if (rc1 == 0) { 
        close(pipeEnd[0]); 
        const char *message = "Hello from child 1";
        write(pipeEnd[1], message, strlen(message) + 1);
        close(pipeEnd[1]); 
        exit(0);
    }

    int rc2 = fork(); 

    if (rc2 < 0) {
        perror("Fork failed for second child");
        exit(1);
    } else if (rc2 == 0) { 
        close(pipeEnd[1]); 
        char buffer[100];
        read(pipeEnd[0], buffer, sizeof(buffer)); 
        printf("Child 2 received: %s\n", buffer); 
        close(pipeEnd[0]); 
        exit(0);
    }

    int status;

    waitpid(rc1, &status, 0); 
    waitpid(rc2, &status, 0);  

    close(pipeEnd[0]); 
    close(pipeEnd[1]); 

    return 0; 
}
