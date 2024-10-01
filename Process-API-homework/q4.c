#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Child process is going to run /bin/ls\n");
    int rc = fork(); 
    if (rc == 0) { 
        printf("Running execl\n");
        execl("/bin/ls", "ls", NULL); 
        perror("excel error QAQ.");
        exit(1); 
    }
    rc = fork(); 
    if (rc == 0) { 
        printf("Running execle\n");
        char * env[] = {"User=MingfaUser", NULL};
        execle("/bin/ls", "ls", NULL,env); 
        perror("excel error QAQ.");
        exit(1); 
    }
    rc = fork(); 
    if (rc == 0) { 
        printf("Running execlp\n");
        execlp("ls", "ls", "-l", NULL); 
        perror("excelp error QAQ.");
        exit(1); 
    }
    rc = fork();
    if (rc == 0) { 
        printf("Running execv\n");
        char *args[] = {"ls", "-l", NULL}; 
        execv("/bin/ls", args); 
        perror("excev error QAQ.");
        exit(1); 
    }
    rc = fork();
    if (rc == 0) { 
        printf("Running execvp\n");
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args); 
        perror("execvp error QAQ.");
        exit(1); 
    }
    return 0;

    printf("All Processes finished.");
}
