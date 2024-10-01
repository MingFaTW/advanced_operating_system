#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    //fd : file descripter
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    int rc = fork();
    if (rc < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (rc == 0) { 
        const char *child_message = "Hello from child!\n";
        write(fd, child_message, strlen(child_message));
        printf("Child wrote to file.\n");
    } else {
        const char *parent_message = "Hello from parent!\n";
        write(fd, parent_message, strlen(parent_message));
        printf("Parent wrote to file.\n");
        wait(NULL);
    }

    close(fd);
    return 0;
}
