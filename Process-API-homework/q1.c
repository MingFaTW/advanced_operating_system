#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int x=100;
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        printf("x was %d ", x);
        x=222;
        printf(",but I have changed it to 222...\n");
        printf("Now, x is %d!\n", x);
    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n",
	       rc, (int) getpid());
        printf("x was %d ", x);
        x=111;
        printf(",but I have changed it to 111...\n");
        printf("Now, x is %d!\n", x);
    }
    return 0;
}
