// sender.c - Writes a message to shared memory

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>   // for ftok(), shmget()
#include <sys/shm.h>   // for shmget(), shmat(), shmdt()
#include <sys/types.h> // for key_t
#include <unistd.h>

int main() {
    // Generate a unique key using ftok
    key_t key = ftok("shmfile", 65);  // "shmfile" must exist, use any filename
    int shmid;

    // Create shared memory of size 1024 bytes
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory to process
    char *str = (char*) shmat(shmid, NULL, 0);

    // Write message into shared memory
    printf("Enter a message to store in shared memory: ");
    fgets(str, 1024, stdin); // user input
    str[strcspn(str, "\n")] = '\0'; // remove newline

    printf("Data written in memory: %s\n", str);

    // Detach shared memory
    shmdt(str);

    return 0;
}
