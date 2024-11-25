#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    int arrivaltime;
    int bursttime;
    int completiontime;
    int turnaroundtime;
    int waitingtime;
} Process;

int generateNextBurst()
{
    return (rand() % 10) + 1;
}

// for FCFS we have to sort the process on the basis of there arrival time

void sortProcessesOnAT(Process processes[], int n)
{
    // using bubble sort to sort processes
    Process temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrivaltime > processes[j + 1].arrivaltime)
            {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    return;
}

void calculateandDisplay(Process processes[], int n)
{
    int currentTime = processes[0].arrivaltime;
    int totalturnaroundtime = 0;
    int totalwaitingtime = 0;

    printf("\nProcess\t\tArrival\t\t Burst Time\tCompletion Burst\t Turnaround Time\tWaiting Time \n");
    for (int i = 0; i < n; i++)
    {
        int minBrustTime = processes[i].bursttime;
        int minIndex = i;

        for(int j = i+1; j < n; j++){
            if(processes[j].arrivaltime <= currentTime && processes[j].bursttime < minBrustTime) {
                minBrustTime = processes[j].bursttime;
                minIndex = j;
            }
        }

        Process temp = processes[i];
        processes[i] = processes[minIndex];
        processes[minIndex] = temp;
        processes[i].completiontime = currentTime + processes[i].bursttime;
        currentTime = processes[i].completiontime;
        processes[i].turnaroundtime = processes[i].completiontime - processes[i].arrivaltime;
        processes[i].waitingtime = processes[i].turnaroundtime - processes[i].bursttime;

        totalturnaroundtime += processes[i].turnaroundtime;
        totalwaitingtime += processes[i].waitingtime;

        printf("P%d:\t\t%d\t\t %d\t\t %d\t\t\t%d\t\t\t%d\n",
               processes[i].id,
               processes[i].arrivaltime,
               processes[i].bursttime,
               processes[i].completiontime,
               processes[i].turnaroundtime,
               processes[i].waitingtime);
    }

    printf("\nAverage Turnaround Time: %.2f unit", (float)totalturnaroundtime / n);
    printf("\nAverage Waiting Time:%.2f unit\n", (float)totalwaitingtime / n);
}

// function to print Gantt Chart

void printGanttChart(Process processes[], int n)
{

    int time = processes[0].arrivaltime;
    printf("\n\n --------------------Printing Gantt Chart------------------\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("| P%d  |", processes[i].id);
    }

    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d    ", time);
        time = processes[i].completiontime;
    }
    printf("%d   ", time);
    printf("\n");
}

int main()
{
    char continueS;

    int n;

    printf("\nEnter Number of Processes:");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("Enter arrival time and first CPU burst time for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrivaltime, &processes[i].bursttime);
    }

    // 1st sorting process on the basis of there arrival time
    sortProcessesOnAT(processes, n);

    // Calculate times, averages, and generate Gantt chart
    calculateandDisplay(processes, n);

    // printing Gantt Chart

    printGanttChart(processes, n);

    do
    {

        printf("\nDo you wish to continue:Y:yes and N:No\n");
        scanf(" %c", &continueS);

        if (continueS == 'y' || continueS == 'Y')
        {

            // If user wants to continue, regenerate burst times randomly
            for (int i = 0; i < n; i++)
            {
                processes[i].bursttime = generateNextBurst();
                // Randomly generate new burst time
            }
            calculateandDisplay(processes, n);
            printGanttChart(processes,n);
        }

    } while (continueS == 'y' || continueS == 'Y');

    return 0;
}
