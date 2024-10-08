#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>

#define iterationsForSystemCall 100000
#define stringSize 17  
#define toNarrowSeconds 1000000000

long getTimeInterval(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * toNarrowSeconds + (end.tv_nsec - start.tv_nsec);
}

void measure_time_context_switch() {
    int pipe_fd[2];
    pipe(pipe_fd);

    struct timespec start, end;
    int pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    
    char dataForParent[stringSize] = "mingfaisgoodgood"; 
    char dataForChild[stringSize];  
    
    if (pid == 0) {
        for (int i = 0; i < iterationsForSystemCall; i++) {
            read(pipe_fd[0], dataForChild, stringSize); 
            write(pipe_fd[1], dataForChild, stringSize); 
        }
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        exit(0);
    } else { 
        clock_gettime(CLOCK_MONOTONIC, &start);  
        for (int i = 0; i < iterationsForSystemCall; i++) {
            write(pipe_fd[1], dataForParent, stringSize);  
            read(pipe_fd[0], dataForParent, stringSize);   
        }
        clock_gettime(CLOCK_MONOTONIC, &end);  

        wait(NULL); 
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        
        printf("Context switch average time: %ld ns\n", getTimeInterval(start, end) / (iterationsForSystemCall * 2)); 
    }
}

int main() {
    measure_time_context_switch();
    return 0;
}
