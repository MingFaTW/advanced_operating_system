#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd[2]; 
    pipe(pipefd);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { 
        printf("hello\n"); 
        write(pipefd[1], "finished", 8); 
        close(pipefd[1]); 
        exit(0);
        
    } else { 
        char buffer[4];
        read(pipefd[0], buffer, 8); 
        printf("goodbye\n"); 
        close(pipefd[0]); 
        exit(0);
    }
    return 0;
}
