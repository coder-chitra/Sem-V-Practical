#include <stdio.h>
#include <limits.h>

typedef struct
{
    int id;
    int arrivaltime;
    int bursttime;
    int priority;
    int remainingtime;
    int completiontime;
    int turnaroundtime;
    int waitingtime;
} Process;

void calculateAndDisplay(Process processes[], int n)
{
    int completed = 0, currentTime = 0;
    int totalTurnaroundTime = 0, totalWaitingTime = 0;
    int minPriority, selectedProcess;

    printf("\nGantt Chart:\n|");

    while (completed < n)
    {
        minPriority = INT_MAX;
        selectedProcess = -1;

        // Select the process with the highest priority that is ready to execute
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivaltime <= currentTime && processes[i].remainingtime > 0 &&
                processes[i].priority < minPriority)
            {
                minPriority = processes[i].priority;
                selectedProcess = i;
            }
        }

        if (selectedProcess != -1)
        {
            // Execute the selected process for 1 unit of time
            printf(" P%d |", processes[selectedProcess].id);
            processes[selectedProcess].remainingtime--;
            currentTime++;

            if (processes[selectedProcess].remainingtime == 0)
            {
                // Process completed
                processes[selectedProcess].completiontime = currentTime;
                processes[selectedProcess].turnaroundtime =
                    processes[selectedProcess].completiontime - processes[selectedProcess].arrivaltime;
                processes[selectedProcess].waitingtime =
                    processes[selectedProcess].turnaroundtime - processes[selectedProcess].bursttime;

                totalTurnaroundTime += processes[selectedProcess].turnaroundtime;
                totalWaitingTime += processes[selectedProcess].waitingtime;
                completed++;
            }
        }
        else
        {
            // No process is ready; idle
            printf(" Idle |");
            currentTime++;
        }
    }

    printf("\n");

    // Print completion times below the Gantt Chart
    printf("0");
    for (int i = 0; i < currentTime; i++)
    {
        printf("     %d", i + 1);
    }
    printf("\n");

    // Display process details
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrivaltime,
               processes[i].bursttime,
               processes[i].priority,
               processes[i].completiontime,
               processes[i].turnaroundtime,
               processes[i].waitingtime);
    }

    // Display averages
    printf("\nAverage Turnaround Time: %.2f", (float)totalTurnaroundTime / n);
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority (lower is higher) for process P%d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrivaltime, &processes[i].bursttime, &processes[i].priority);

        // Initialize remaining time and other fields
        processes[i].remainingtime = processes[i].bursttime;
        processes[i].completiontime = 0;
        processes[i].turnaroundtime = 0;
        processes[i].waitingtime = 0;
    }

    // Calculate and display results
    calculateAndDisplay(processes, n);

    return 0;
}
