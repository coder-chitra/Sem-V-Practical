#include <stdio.h>

typedef struct
{
    int id;
    int arrivaltime;
    int bursttime;
    int priority;
    int completiontime;
    int turnaroundtime;
    int waitingtime;
} Process;

// Function to sort processes by arrival time and priority
void sortProcessesOnArrivalAndPriority(Process processes[], int n)
{
    Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrivaltime > processes[j + 1].arrivaltime ||
                (processes[j].arrivaltime == processes[j + 1].arrivaltime &&
                 processes[j].priority > processes[j + 1].priority))
            {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void calculateAndDisplay(Process processes[], int n)
{
    int currentTime = 0;
    int completed = 0;
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    while (completed < n)
    {
        int selectedProcess = -1;
        int highestPriority = 99999;

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivaltime <= currentTime && processes[i].completiontime == 0 &&
                processes[i].priority < highestPriority)
            {
                highestPriority = processes[i].priority;
                selectedProcess = i;
            }
        }

        if (selectedProcess != -1)
        {
            // Process execution
            currentTime += processes[selectedProcess].bursttime;
            processes[selectedProcess].completiontime = currentTime;
            processes[selectedProcess].turnaroundtime = processes[selectedProcess].completiontime - processes[selectedProcess].arrivaltime;
            processes[selectedProcess].waitingtime = processes[selectedProcess].turnaroundtime - processes[selectedProcess].bursttime;

            totalTurnaroundTime += processes[selectedProcess].turnaroundtime;
            totalWaitingTime += processes[selectedProcess].waitingtime;

            printf(" P%d |", processes[selectedProcess].id);
            completed++;
        }
        else
        {
            // No process ready; idle
            currentTime++;
        }
    }

    printf("\n0");
    int time = 0;
    for (int i = 0; i < n; i++)
    {
        if (processes[i].completiontime > time)
        {
            printf("    %d", processes[i].completiontime);
            time = processes[i].completiontime;
        }
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

        // Initialize completion time to 0 (not completed)
        processes[i].completiontime = 0;
    }

    // Sort by arrival time and priority (for tie-breaking)
    sortProcessesOnArrivalAndPriority(processes, n);

    // Calculate and display results
    calculateAndDisplay(processes, n);

    return 0;
}
