#include <stdio.h>
#include <stdbool.h>

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

void calculateAndDisplay(Process processes[], int n, int quantum)
{
    int currentTime = 0, completed = 0, totalTurnaroundTime = 0, totalWaitingTime = 0;
    int queue[n], front = 0, rear = 0;
    bool inQueue[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].remainingtime = processes[i].bursttime;
        inQueue[i] = false;
    }

    // Add the first process to the queue
    queue[rear++] = 0;
    inQueue[0] = true;

    printf("\nGantt Chart:\n|");

    while (completed < n)
    {
        // If the queue is not empty, pick the first process
        int currentProcess = queue[front++];
        front %= n;
        inQueue[currentProcess] = false;

        // Execute the process for the time quantum or until it finishes
        if (processes[currentProcess].remainingtime <= quantum)
        {
            currentTime += processes[currentProcess].remainingtime;
            printf(" P%d |", processes[currentProcess].id);
            processes[currentProcess].remainingtime = 0;
            processes[currentProcess].completiontime = currentTime;

            // Process completed
            processes[currentProcess].turnaroundtime =
                processes[currentProcess].completiontime - processes[currentProcess].arrivaltime;
            processes[currentProcess].waitingtime =
                processes[currentProcess].turnaroundtime - processes[currentProcess].bursttime;

            totalTurnaroundTime += processes[currentProcess].turnaroundtime;
            totalWaitingTime += processes[currentProcess].waitingtime;
            completed++;
        }
        else
        {
            currentTime += quantum;
            printf(" P%d |", processes[currentProcess].id);
            processes[currentProcess].remainingtime -= quantum;
        }

        // Check for newly arrived processes and add them to the queue
        for (int i = 0; i < n; i++)
        {
            if (i != currentProcess && processes[i].arrivaltime <= currentTime &&
                processes[i].remainingtime > 0 && !inQueue[i])
            {
                queue[rear++] = i;
                rear %= n;
                inQueue[i] = true;
            }
        }

        // Re-add the current process to the queue if it is not finished
        if (processes[currentProcess].remainingtime > 0)
        {
            queue[rear++] = currentProcess;
            rear %= n;
            inQueue[currentProcess] = true;
        }
    }

    printf("\n");

    // Print the time below the Gantt Chart
    printf("0");
    for (int i = 0; i < currentTime; i++)
    {
        if (i % quantum == 0 || i == currentTime - 1)
            printf("     %d", i + 1);
    }
    printf("\n");

    // Display process details
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

    // Display averages
    printf("\nAverage Turnaround Time: %.2f", (float)totalTurnaroundTime / n);
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
}

int main()
{
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrivaltime, &processes[i].bursttime);
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Calculate and display results
    calculateAndDisplay(processes, n, quantum);

    return 0;
}
