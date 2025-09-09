#include <stdio.h>

int main() {
    int n, i;
    int at[10], bt[10], rt[10];   // arrival, burst, remaining
    int ct[10], tat[10], wt[10];
    int tq[3];                    // time quantum for 3 queues
    int completed = 0, time = 0;
    int total_tat=0, total_wt=0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Times:\n");
    for(i=0; i<n; i++) scanf("%d", &at[i]);

    printf("Enter CPU Burst Times:\n");
    for(i=0; i<n; i++) {
        scanf("%d", &bt[i]);
        rt[i] = bt[i];  // remaining time
    }

    printf("Enter Time Quantum for Queue1, Queue2, Queue3: ");
    scanf("%d %d %d", &tq[0], &tq[1], &tq[2]);

    printf("\n--- Gantt Chart ---\n");

    // Keep looping until all processes are done
    while(completed < n) {
        int progress = 0;
        // Iterate over queues one by one
        for(int q=0; q<3; q++) {
            for(i=0; i<n; i++) {
                if(at[i] <= time && rt[i] > 0) {
                    progress = 1;
                    if(rt[i] > tq[q]) {
                        printf("| P%d (%d to %d) ", i+1, time, time+tq[q]);
                        time += tq[q];
                        rt[i] -= tq[q];
                    } else {
                        printf("| P%d (%d to %d) ", i+1, time, time+rt[i]);
                        time += rt[i];
                        rt[i] = 0;
                        ct[i] = time;                 // completion time
                        tat[i] = ct[i] - at[i];       // turnaround
                        wt[i] = tat[i] - bt[i];       // waiting
                        total_tat += tat[i];
                        total_wt += wt[i];
                        completed++;
                    }
                }
            }
        }
        if(!progress) time++; // if no process has arrived yet
    }
    printf("|\n");

    // Print results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", (float)total_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt/n);

    return 0;
}


// Enter number of processes: 3
// Enter Arrival Times:
// 0 1 2
// Enter CPU Burst Times:
// 5 4 2
// Enter Time Quantum for Queue1, Queue2, Queue3: 2 4 6


// --- Gantt Chart ---
// | P1 (0 to 2) | P2 (2 to 4) | P3 (4 to 6) | P1 (6 to 9) | P2 (9 to 11) |

// Process AT  BT  CT  TAT WT
// P1      0   5   9   9   4
// P2      1   4   11  10  6
// P3      2   2   6   4   2

// Average Turnaround Time = 7.67
// Average Waiting Time = 4.00


