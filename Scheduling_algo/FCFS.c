#include <stdio.h>

int main() {
    int n, i;
    int at[10], bt[10], io[10];    // arrival, cpu burst, io burst
    int ct[10], tat[10], wt[10], rt[10];
    int total_wt=0, total_tat=0, total_rt=0;
    float throughput;
    int time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time of processes:\n");
    for(i=0; i<n; i++)
        scanf("%d", &at[i]);

    printf("Enter CPU Burst Time of processes:\n");
    for(i=0; i<n; i++)
        scanf("%d", &bt[i]);

    printf("Enter I/O Burst Time of processes:\n");
    for(i=0; i<n; i++)
        scanf("%d", &io[i]);

    // sort by arrival time (FCFS rule)
    for(i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(at[i] > at[j]) {
                int temp;
                temp=at[i]; at[i]=at[j]; at[j]=temp;
                temp=bt[i]; bt[i]=bt[j]; bt[j]=temp;
                temp=io[i]; io[i]=io[j]; io[j]=temp;
            }
        }
    }

    printf("\n--- Gantt Chart ---\n");

    // FCFS scheduling
    for(i=0; i<n; i++) {
        if(time < at[i])   // if CPU is idle, jump time
            time = at[i];

        rt[i] = time - at[i];          // response time
        printf("| P%d (%d to %d) ", i+1, time, time+bt[i]);

        time += bt[i];                 // add CPU burst
        time += io[i];                 // then I/O burst

        ct[i] = time;                  // completion time
        tat[i] = ct[i] - at[i];        // turnaround
        wt[i] = tat[i] - (bt[i] + io[i]);

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
    }
    printf("|\n");

    // Performance table
    printf("\nProcess\tAT\tBT\tIO\tCT\tTAT\tWT\tRT\n");
    for(i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], io[i], ct[i], tat[i], wt[i], rt[i]);
    }

    throughput = (float)n / time;

    printf("\nAverage Waiting Time = %.2f", (float)total_wt/n);
    printf("\nAverage Turnaround Time = %.2f", (float)total_tat/n);
    printf("\nAverage Response Time = %.2f", (float)total_rt/n);
    printf("\nThroughput = %.2f processes/unit time\n", throughput);

    return 0;
}

// Enter number of processes: 3
// Enter Arrival Time of processes:
// 0 2 4
// Enter CPU Burst Time of processes:
// 5 3 2
// Enter I/O Burst Time of processes:
// 2 1 3

// --- Gantt Chart ---
// | P1 (0 to 5) | P2 (7 to 10) | P3 (11 to 13) |

// Process AT  BT  IO  CT  TAT WT  RT
// P1      0   5   2   7   7   0   0
// P2      2   3   1   11  9   5   5
// P3      4   2   3   16  12  7   7

// Average Waiting Time = 4.00
// Average Turnaround Time = 9.33
// Average Response Time = 4.00
// Throughput = 0.19 processes/unit time