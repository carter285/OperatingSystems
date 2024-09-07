// // Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls.
// // See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe().
// //  Why do you think there are so many variants of the same basic call?

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    //pid_t pid = fork();
    int pid = fork();

    if (pid < 0) {
        printf("ERROR!");
        //perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process running...\n");

        // Using execl() -->int execl(const char *path, const char *arg,.../* (char  *) NULL */);
        //execl("/bin/ls", "ls", "-l", NULL);


        // Using execle() --> int execle(const char *path, const char *arg, .../*, (char *) NULL, char * const envp[] */);
        char *envp[] = { "PATH=/bin", NULL };
        execle("/bin/ls", "ls", "-l", NULL, envp);

        // // Using execlp() --> int execlp(const char *file, const char *arg,.../* (char  *) NULL */);
        // execlp("ls", "ls", "-l", NULL);

        // //Using execv() --> int execv(const char *path, char *const argv[]);
        // char *args[] = { "ls", "-l", NULL };
        // execv("/bin/ls", args);

        // // Using execvp() --> int execvp (const char *file, char *const argv[]);
        // char *args[] = { "ls", "-l", NULL };
        // execvp("ls", args);

        // // Using execvpe() --> int execvpe(const char *file, char *const argv[],char *const envp[]);
        // char *args[] = { "ls", "-l", NULL };
        // char *envp[] = { "PATH=/bin", NULL };
        // execvpe("ls", args, envp);

        perror("exec failed");
        exit(1);
    } else {
        // Parent process
        wait(NULL);
        printf("Parent process exiting...\n");
    }

    return 0;
}

// Exec functions replaces the current running process with a new program.
// The exec function can be used to run a C program by using another C program.
// The exec functions allow the child process to run another program from the parent process.
// Exec cab run file if it is binary or a shell script.

//All the exec functions do the same thing relativly. They allow the user to run/execute new programs.
// The diffrence in the function are how they set up the enviorments of the program and execute the calls.
//
//


// https://www.geeksforgeeks.org/exec-family-of-functions-in-c/
// https://linux.die.net/man/3/execvp
//
