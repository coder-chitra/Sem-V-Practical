#include <stdio.h>
#include <limits.h>

typedef struct
{
    int id;
    int arrivaltime;
    int bursttime;
    int remainingtime;
    int completiontime;
    int turnaroundtime;
    int waitingtime;
} Process;

void calculateandDisplay(Process processes[], int n)
{
    int currentTime = 0;
    int completed = 0;
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

    // Gantt chart tracking
    int ganttChart[100];
    int ganttSize = 0;

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++)
    {
        processes[i].remainingtime = processes[i].bursttime;
    }

    while (completed != n)
    {
        int shortestIndex = -1;
        int shortestTime = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivaltime <= currentTime && processes[i].remainingtime > 0 && processes[i].remainingtime < shortestTime)
            {
                shortestTime = processes[i].remainingtime;
                shortestIndex = i;
            }
        }

        if (shortestIndex != -1)
        {
            // Execute the process with the shortest remaining time
            ganttChart[ganttSize++] = processes[shortestIndex].id;
            processes[shortestIndex].remainingtime--;
            currentTime++;

            if (processes[shortestIndex].remainingtime == 0)
            {
                completed++;
                processes[shortestIndex].completiontime = currentTime;
                processes[shortestIndex].turnaroundtime = processes[shortestIndex].completiontime - processes[shortestIndex].arrivaltime;
                processes[shortestIndex].waitingtime = processes[shortestIndex].turnaroundtime - processes[shortestIndex].bursttime;

                totalTurnaroundTime += processes[shortestIndex].turnaroundtime;
                totalWaitingTime += processes[shortestIndex].waitingtime;
            }
        }
        else
        {
            // No process is ready to execute; increment time
            currentTime++;
        }
    }

    // Display results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrivaltime,
               processes[i].bursttime,
               processes[i].completiontime,
               processes[i].turnaroundtime,
               processes[i].waitingtime);
    }

    printf("\nAverage Turnaround Time: %.2f", (float)totalTurnaroundTime / n);
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < ganttSize; i++)
    {
        if (i == 0 || ganttChart[i] != ganttChart[i - 1])
        {
            printf(" P%d |", ganttChart[i]);
        }
    }
    printf("\n");
    int prevProcess = -1;
    for (int i = 0; i < ganttSize; i++)
    {
        if (i == 0 || ganttChart[i] != prevProcess)
        {
            printf("    %d", currentTime - (ganttSize - i));
            prevProcess = ganttChart[i];
        }
    }
    printf("\n");
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
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrivaltime, &processes[i].bursttime);
    }

    calculateandDisplay(processes, n);

    return 0;
}
