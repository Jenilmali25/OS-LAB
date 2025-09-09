// receiver.c - Reads the message from shared memory

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>   // for ftok(), shmget()
#include <sys/shm.h>   // for shmget(), shmat(), shmdt(), shmctl()
#include <sys/types.h> // for key_t
#include <unistd.h>

int main() {
    // Generate same key as sender
    key_t key = ftok("shmfile", 65);
    int shmid;

    // Locate the shared memory created by sender
    shmid = shmget(key, 1024, 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory to process
    char *str = (char*) shmat(shmid, NULL, 0);

    // Read message from shared memory
    printf("Data read from memory: %s\n", str);

    // Detach shared memory
    shmdt(str);

    // Destroy shared memory (only receiver removes it)
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
