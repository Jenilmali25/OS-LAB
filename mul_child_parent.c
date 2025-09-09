#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int n = 2;                     // number of children
    int pipefd[2][2];              // 2D array for multiple pipes
    int pid;
    char buffer[50];

    // Create multiple pipes
    for (int i = 0; i < n; i++) {
        if (pipe(pipefd[i]) == -1) {
            perror("Pipe failed");
            return 1;
        }
    }

    // Create multiple child processes
    for (int i = 0; i < n; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return 1;
        }
        else if (pid == 0) {
            // Child process
            close(pipefd[i][1]);   // close write end
            read(pipefd[i][0], buffer, sizeof(buffer));
            printf("Child %d (PID: %d, PPID: %d) received: %s\n",
                   i+1, getpid(), getppid(), buffer);
            close(pipefd[i][0]);
            return 0;   // child exits
        }
        else {
            // Parent process
            char msg[50];
            sprintf(msg, "Hello Child %d!", i+1);

            close(pipefd[i][0]);   // close read end
            write(pipefd[i][1], msg, strlen(msg) + 1);
            close(pipefd[i][1]);   // close write end
        }
    }

    // Parent waits for all children
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("Parent (PID: %d) finished.\n", getpid());
    return 0;
}
