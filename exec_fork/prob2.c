// Write a program that opens a file (with the open() system call) and then calls fork() to create a new process.
// Can both the child and parent access the file descriptor returned by open()?
// What happens when they are writing to the file concurrently, i.e., at the same time?

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

extern int errno;

int main(int argc, char *argv[])
{
    int w;
    int f = open("results.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    //printf("hello (pid:%d)\n", (int) getpid());

    int forkk = fork();
    if (forkk < 0)
    {
        printf("fork failed\n");
        exit(1);
    }
    else if (forkk == 0)
    {
        printf("child (pid:%d)\n", (int) getpid());
        w = write(f, "hello from child", sizeof("hello from child"));
        printf("Wrote in child\n");
    }
    else
    {
        printf("parent of %d (pid:%d)\n", forkk, (int) getpid());
        w = write(f, "helloFrom Parent", sizeof("helloFrom Parent"));
        printf("Wrote in Parent\n");
    }
    return 0;
}
// My output has the parent writing first to the file then the child writing to the file
// --> parent of 7064 (pid:7063)
// --> child (pid:7064)
// --> Wrote in Parent
// --> Wrote in child

//This is probably due to the IO routines that occur
// When both processes want to write to the file it is a race condition
// Meaning the child at somepoint could write to the file first
// Special synchonizations can be used to allow one to be printed before the other.
