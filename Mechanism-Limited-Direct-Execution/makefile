CC = gcc
CFLAGS = -Wall -g

SRC_FILES = q1.c q2.c 
EXEC_FILES = q1 q2 

all: $(EXEC_FILES)

q1: q1.c
	$(CC) $(CFLAGS) q1.c -o q1

q2: q2.c
	$(CC) $(CFLAGS) q2.c -o q2

clean:
	rm -f $(EXEC_FILES)
