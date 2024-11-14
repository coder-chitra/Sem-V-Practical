#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define IO_WAIT 2

struct Process {
    int id;
    int arrivalTime;
    int priority;
    int cpuBurst;
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

// Function to find the next process to execute
int findNextProcess(struct Process processes[], int n, int currentTime) {
    int minPriority = INT_MAX;
    int idx = -1;

    for (int i = 0; i < n; i++) {
        if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime && processes[i].priority < minPriority) {
            minPriority = processes[i].priority;
            idx = i;
        }
    }
    return idx;
}

// Function to calculate turnaround and waiting times
void calculateTimes(struct Process processes[], int n, double *avgTurnaroundTime, double *avgWaitingTime) {
    int clock = 0;
    int completed = 0;
    *avgTurnaroundTime = 0;
    *avgWaitingTime = 0;

    while (completed != n) {
        int idx = findNextProcess(processes, n, clock);

        if (idx != -1) {
            if (processes[idx].remainingTime == processes[idx].cpuBurst) {
                clock += IO_WAIT; // Simulating I/O waiting time before the first burst
            }
            
            processes[idx].remainingTime--;
            clock++;

            // If the process is completed
            if (processes[idx].remainingTime == 0) {
                processes[idx].completionTime = clock;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].cpuBurst;
                processes[idx].isCompleted = true;
                completed++;

                *avgTurnaroundTime += processes[idx].turnaroundTime;
                *avgWaitingTime += processes[idx].waitingTime;
            }
        } else {
            clock++; // Idle time if no process is ready
        }
    }

    *avgTurnaroundTime /= n;
    *avgWaitingTime /= n;
}

// Function to print the Gantt chart
void printGanttChart(struct Process processes[], int n) {
    int clock = 0;

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

        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);

        // User-provided burst time
        int userBurstTime;
        printf("Enter initial CPU burst time for Process %d: ", i + 1);
        scanf("%d", &userBurstTime);

        // Generate a random burst time and overwrite the user-provided burst time
        processes[i].cpuBurst = generateRandomBurst();
        processes[i].remainingTime = processes[i].cpuBurst;
        processes[i].isCompleted = false;
        printf("Generated CPU burst time for Process %d: %d (Original Input: %d)\n", i + 1, processes[i].cpuBurst, userBurstTime);
    }

    calculateTimes(processes, n, &avgTurnaroundTime, &avgWaitingTime);
    printGanttChart(processes, n);

    printf("\nProcess Details:\n");
    printf("|-----------------------------------------------------------------|\n");
    printf("| Process | Arrival Time | Priority | CPU Burst | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("|-----------------------------------------------------------------|\n");
    for (int i = 0; i < n; i++) {
        printf("|    P%-2d  |     %2d       |    %2d   |    %2d    |       %2d       |       %2d        |      %2d     |\n",
               processes[i].id, processes[i].arrivalTime, processes[i].priority, processes[i].cpuBurst,
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

