#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define IO_WAIT 2

struct Process {
    int id;
    int arrivalTime;
    int cpuBurst; // User-provided burst time
    int randomBurst; // Randomly generated burst time
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    bool isCompleted;
};

// Function to generate a random burst time
int generateRandomBurst() {
    return rand() % 10 + 1;
}

// Function to calculate turnaround and waiting times
void calculateTimes(struct Process processes[], int n, double *avgTurnaroundTime, double *avgWaitingTime) {
    int clock = 0;
    int completed = 0;
    int timeQuantum;
    *avgTurnaroundTime = 0;
    *avgWaitingTime = 0;

    printf("\nEnter time quantum (Q): ");
    scanf("%d", &timeQuantum);

    while (completed != n) {
        bool anyProcessExecuted = false;
        
        for (int i = 0; i < n; i++) {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= clock) {
                int burstTime = (processes[i].remainingTime > timeQuantum) ? timeQuantum : processes[i].remainingTime;
                clock += burstTime;
                processes[i].remainingTime -= burstTime;
                
                // Simulating I/O waiting time after the first burst
                if (processes[i].remainingTime > 0) {
                    clock += IO_WAIT;
                }
                
                // If the process is completed
                if (processes[i].remainingTime == 0) {
                    processes[i].completionTime = clock;
                    processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].cpuBurst;
                    processes[i].isCompleted = true;
                    completed++;

                    *avgTurnaroundTime += processes[i].turnaroundTime;
                    *avgWaitingTime += processes[i].waitingTime;
                }
                
                anyProcessExecuted = true;
                break;
            }
        }
        
        if (!anyProcessExecuted) {
            clock++; // Idle time if no process is ready
        }
    }

    *avgTurnaroundTime /= n;
    *avgWaitingTime /= n;
}

// Function to print the Gantt chart
void printGanttChart(struct Process processes[], int n) {
    int clock = 0;

    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf(" --------");
    }
    printf("\n|");

    for (int i = 0; i < n; i++) {
        printf("   P%d   |", processes[i].id);
    }

    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf(" --------");
    }

    printf("\n%d", processes[0].arrivalTime);
    clock = processes[0].arrivalTime;
    for (int i = 0; i < n; i++) {
        clock += processes[i].cpuBurst;
        printf("        %d", clock);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    int n, choice;
    double avgTurnaroundTime, avgWaitingTime;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("\nEnter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);

        // User-provided burst time
        printf("Enter initial CPU burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].cpuBurst);

        // Generate a random burst time and overwrite the user-provided burst time
        processes[i].randomBurst = generateRandomBurst();
        processes[i].remainingTime = processes[i].randomBurst;
        processes[i].isCompleted = false;

        printf("Generated CPU burst time for Process %d: %d (Original Input: %d)\n", i + 1, processes[i].randomBurst, processes[i].cpuBurst);
    }

    calculateTimes(processes, n, &avgTurnaroundTime, &avgWaitingTime);
    printGanttChart(processes, n);

    printf("\nProcess Details:\n");
    printf("|-----------------------------------------------------------------|\n");
    printf("| Process | Arrival Time | User Burst | Generated Burst | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("|-----------------------------------------------------------------|\n");
    for (int i = 0; i < n; i++) {
        printf("|    P%-2d  |     %2d       |     %2d     |       %2d        |       %2d       |       %2d        |      %2d     |\n",
               processes[i].id, processes[i].arrivalTime, processes[i].cpuBurst, processes[i].randomBurst,
               processes[i].completionTime, processes[i].turnaroundTime, processes[i].waitingTime);
    }
    printf("|-----------------------------------------------------------------|\n");
    printf("| Average Turnaround Time: %5.2lf                                 |\n", avgTurnaroundTime);
    printf("| Average Waiting Time: %5.2lf                                    |\n", avgWaitingTime);
    printf("|-----------------------------------------------------------------|\n");

    /*printf("\nDo you want to continue? (1 for yes, 0 for no): ");
    scanf("%d", &choice);*/

    return 0;
}

