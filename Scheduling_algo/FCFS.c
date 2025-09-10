#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;   // number of processes

    int pid[20], at[20], bt[20], ct[20], tat[20], wt[20];

    // Input: AT BT
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        
        cin >> at[i] >> bt[i];
    }

    // Sort by Arrival Time (bubble sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                swap(pid[j], pid[j+1]);
                swap(at[j], at[j+1]);
                swap(bt[j], bt[j+1]);
            }
        }
    }

    int time = 0;

    // FCFS execution
    for (int i = 0; i < n; i++) {
        if (time < at[i]) time = at[i];  // CPU idle until process arrives
        time += bt[i];
        ct[i] = time;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // Output table
    cout << "P\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << "\n";
    }

    return 0;
}
