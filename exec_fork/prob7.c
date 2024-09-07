// Write a program that creates a child process,
// and then in the child closes standard output (STDOUT FILENO).
// What happens if the child calls printf() to print some output after closing the descriptor?


// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main (){

    pid_t pid = fork();

    if (pid < 0){
        printf("ERROR\n");
        exit(1);
    }
    else if (pid == 0){
        close(STDOUT_FILENO); // this should close the std output
        printf("This should not print to STD out\n");
    }
    else{
        wait(NULL);
        printf("Child process has finshed\n");
    }

    return 0;
}

// the output:
//-->DataStruct/ $ ./prob7
//-->Child process has finshed

//from the above output when the new process is created
// the new process closes the STD_out and then the printf statement is never printed out