#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, tq;
    cin >> n >> tq;   // Input number of processes and time quantum

    // Arrays for storing process details
    int at[100], bt[100], rt[100], wt[100], tat[100], id[100];

    // Input Arrival Time and Burst Time for each process
    for (int i = 0; i < n; i++) {
        cin >> at[i] >> bt[i];
        rt[i] = bt[i];       // Remaining time initially = Burst Time
        id[i] = i + 1;       // Process IDs (P1, P2, ...)
        wt[i] = tat[i] = 0;  // Initialize waiting and turnaround times
    }

    // Sort processes by Arrival Time (simple bubble sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                swap(at[i], at[j]);
                swap(bt[i], bt[j]);
                swap(rt[i], rt[j]);
                swap(id[i], id[j]);
            }
        }
    }

    queue<int> q;   // Ready Queue for Round Robin
    int t = 0;      // Current time
    int i = 0;      // Tracks how many processes have been added to queue

    // Run until all processes are finished
    while (i < n || !q.empty()) {
        // If CPU is idle (queue empty), jump to next process arrival
        if (q.empty() && i < n && t < at[i])
            t = at[i];

        // Add all processes that have arrived by current time
        while (i < n && at[i] <= t)
            q.push(i++);

        // Take the first process from the queue
        int j = q.front();
        q.pop();

        // Case 1: Process still needs more than one time quantum
        if (rt[j] > tq) {
            t += tq;       // Run for one quantum
            rt[j] -= tq;   // Reduce remaining time

            // Check if new processes have arrived during this time
            while (i < n && at[i] <= t)
                q.push(i++);

            q.push(j);     // Put unfinished process back into the queue
        }
        // Case 2: Process finishes within this time quantum
        else {
            t += rt[j];                    // Run till completion
            wt[j] = t - bt[j] - at[j];     // Waiting Time = Finish - Burst - Arrival
            tat[j] = t - at[j];            // Turnaround Time = Finish - Arrival
            rt[j] = 0;                     // Mark process as finished
        }
    }

    // Print results
    cout << "PID\tAT\tBT\tWT\tTAT\n";
    double total_wt = 0, total_tat = 0;

    for (int k = 0; k < n; k++) {
        cout << id[k] << "\t" 
             << at[k] << "\t" 
             << bt[k] << "\t" 
             << wt[k] << "\t" 
             << tat[k] << "\n";

        total_wt += wt[k];
        total_tat += tat[k];
    }

    // Print averages
    cout << "Average WT  = " << total_wt / n << endl;
    cout << "Average TAT = " << total_tat / n << endl;

    return 0;
}
