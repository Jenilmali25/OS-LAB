#include <stdio.h>
#include <pthread.h>
#include <unistd.h>   // for sleep()

int flag[2] = {0, 0};  // both processes initially not interested
int turn;              // whose turn

void* process0(void* arg) {
    while (1) {
        // Entry section
        flag[0] = 1;         // P0 wants to enter CS
        turn = 1;            // Give turn to P1
        while (flag[1] && turn == 1);  // Wait if P1 also wants CS

        // Critical Section
        printf("Process 0 in Critical Section\n");
        sleep(1);  // simulate work in CS

        // Exit Section
        flag[0] = 0;
        printf("Process 0 exiting Critical Section\n");

        // Remainder Section
        sleep(1);
    }
}

void* process1(void* arg) {
    while (1) {
        // Entry section
        flag[1] = 1;        // P1 wants to enter CS
        turn = 0;           // Give turn to P0
        while (flag[0] && turn == 0);  // Wait if P0 also wants CS

        // Critical Section
        printf("Process 1 in Critical Section\n");
        sleep(1);

        // Exit Section
        flag[1] = 0;
        printf("Process 1 exiting Critical Section\n");

        // Remainder Section
        sleep(1);
    }
}

int main() {
    pthread_t t0, t1;

    // Create two threads (P0 and P1)
    pthread_create(&t0, NULL, process0, NULL);
    pthread_create(&t1, NULL, process1, NULL);

    // Wait (join not needed here since infinite loop, but kept for completeness)
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    return 0;
}


// gcc -o peterson peterson.c -pthread
// ./peterson


// Process 0 in Critical Section
// Process 0 exiting Critical Section
// Process 1 in Critical Section
// Process 1 exiting Critical Section
// Process 0 in Critical Section
// Process 0 exiting Critical Section
// Process 1 in Critical Section
// Process 1 exiting Critical Section
// ...
