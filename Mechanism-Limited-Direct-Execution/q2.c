#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>

#define iterationsForSystemCall 100000
#define stringSize 16
#define toNarrowSeconds 1000000000

long averageReadWriteTime, averageProcessTime;

void measure_time_readAndWrite() {
    int pipe_fd[2];
    pipe(pipe_fd);
    struct timespec start, end;
    char pipeWrite[stringSize] = "mingfaisgoodman"; 
    char pipeRead[stringSize] = "mingfaisgoodman";
    long readAndWriteTime = 0;
    clock_gettime(CLOCK_MONOTONIC, &start);  
    for (int i = 0; i < iterationsForSystemCall; i++) {
        write(pipe_fd[1], pipeWrite, stringSize); 
        read(pipe_fd[0], pipeRead, stringSize); 
    }
    clock_gettime(CLOCK_MONOTONIC, &end);  
    
    readAndWriteTime = (end.tv_sec - start.tv_sec) * toNarrowSeconds + (end.tv_nsec - start.tv_nsec);
    close(pipe_fd[0]);
    close(pipe_fd[1]);    
    averageReadWriteTime = readAndWriteTime / (iterationsForSystemCall);
    printf("Read&Write average time: %ld ns\n", averageReadWriteTime); 
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
    char dataForParent[stringSize] = "mingfaisgoodman"; 
    char dataForChild[stringSize] = "mingfaisgoodman";  
    if (pid == 0) {
        for (int i = 0; i < iterationsForSystemCall; i++) {
            read(pipe_fd[0], dataForChild, stringSize); 
            write(pipe_fd[1], dataForChild, stringSize); 
        }
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
        long ProcessTime = ( (end.tv_sec - start.tv_sec) * toNarrowSeconds + (end.tv_nsec - start.tv_nsec) );
        averageProcessTime = ProcessTime / (iterationsForSystemCall * 2);
        printf("Process average time: %ld ns\n", averageProcessTime); 
    } 
}

int main() {
    measure_time_readAndWrite();
    measure_time_context_switch();
    printf("Context switch average time: %ld ns\n", averageProcessTime - averageReadWriteTime);
    return 0;
}
