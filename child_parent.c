#include <stdio.h>
#include <unistd.h>     // for fork, pipe, read, write, getpid, getppid
#include <string.h>     // for strlen

int main() {
    int pipefd[2];
    int pid;
    char msg[] = "Hello from Parent!";
    char buffer[50];

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid > 0) {
        // Parent process
        close(pipefd[0]); 
        write(pipefd[1], msg, strlen(msg) + 1);
        close(pipefd[1]);

        printf("Parent (PID: %d) finished.\n", getpid());
    }
    else {
        // Child process
        close(pipefd[1]);
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child (PID: %d, PPID: %d) received: %s\n",
               getpid(), getppid(), buffer);
        close(pipefd[0]);
    }

    return 0;
}
