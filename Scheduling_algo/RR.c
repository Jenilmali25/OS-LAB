#include <stdio.h>

int main() {
    int n, i, tq;
    int at[10], bt[10], rt[10];   // arrival, burst, remaining times
    int wt[10], tat[10];          // waiting time, turnaround time
    int completed = 0, time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time of each process:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    printf("Enter burst time of each process:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        rt[i] = bt[i];  // initialize remaining time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Until all processes finish
    while(completed < n) {
        int done = 0;
        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0) {
                // process can run
                done = 1;
                if(rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    // process finishes
                    time += rt[i];
                    tat[i] = time - at[i];       // Turnaround time
                    wt[i] = tat[i] - bt[i];      // Waiting time
                    rt[i] = 0;
                    completed++;
                }
            }
        }
        if(!done) { 
            // if no process arrived yet, move time forward
            time++;
        }
    }

    // Display results
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], wt[i], tat[i]);
    }

    return 0;
}
