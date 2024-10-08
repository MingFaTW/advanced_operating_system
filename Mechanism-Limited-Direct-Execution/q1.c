#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>

#define iterationsForSystemCall 100000
#define toNarrowSeconds 1000000000

long getTimeInterval(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * toNarrowSeconds + (end.tv_nsec - start.tv_nsec);
}

void measure_time_getpid() {
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < iterationsForSystemCall; i++) {
        getpid();
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("getpid() average time: %ld ns\n", getTimeInterval(start, end) / iterationsForSystemCall);
}

void measure_time_read() {
    int fd = open("./tempText.txt", O_RDONLY);
    if (fd < 0) {    
        perror("open failed");
        return;
    }

    struct timespec start, end;
    char buffer[1];

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < iterationsForSystemCall; i++) {
        read(fd, buffer, 0); 
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    close(fd);
    printf("read() average time: %ld ns\n", getTimeInterval(start, end) / iterationsForSystemCall);
}

void measure_time_write() {
    int fd = open("./tempText.txt", O_WRONLY);
    if (fd < 0) {
        perror("open failed");
        return;
    }

    struct timespec start, end;
    char buffer[1] = {0};

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < iterationsForSystemCall; i++) {
        write(fd, buffer, 0); 
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    close(fd);
    printf("write() average time: %ld ns\n", getTimeInterval(start, end) / iterationsForSystemCall);
}

void measure_time_open_close() {
    int file_directory[iterationsForSystemCall];
    long totalTimeForOpenAndClose, totalTimeForClose;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < iterationsForSystemCall; i++) {
        file_directory[i] = open("./tempText.txt", O_RDONLY);  
        if (file_directory[i] < 0) {
            perror("open failed");
        }
        close(file_directory[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    totalTimeForOpenAndClose = getTimeInterval(start, end);
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < iterationsForSystemCall; i++) {
        close(file_directory[i]); 
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    totalTimeForClose = getTimeInterval(start, end);
    printf("open() average time: %ld ns\n", (totalTimeForOpenAndClose - totalTimeForClose) / iterationsForSystemCall);
    printf("close() average time: %ld ns\n", (totalTimeForClose / iterationsForSystemCall));
}


int main() {
    printf("Measuring the average costs for five different system calls. :)~YA\n");

    measure_time_getpid();     
    measure_time_read();       
    measure_time_write();      
    measure_time_open_close();  

    return 0;
}
