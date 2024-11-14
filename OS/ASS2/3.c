#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define IO_WAIT 2

struct Process {
    int id;
    int arrivalTime;
    int cpuBurst;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

// Function to generate a random burst time
int generateRandomBurst() {
    return rand() % 10 + 1;
}

// Function to calculate turnaround and waiting times
void calculateTimes(struct Process processes[], int n, double *avgTurnaroundTime, double *avgWaitingTime) {
    int clock = 0;
    *avgTurnaroundTime = 0;
    *avgWaitingTime = 0;
    int remaining = n;

    while (remaining > 0) {
        int minRemainingTime = __INT_MAX__;
        int index = -1;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= clock && processes[i].remainingTime > 0 && processes[i].remainingTime < minRemainingTime) {
                minRemainingTime = processes[i].remainingTime;
                index = i;
            }
        }

        if (index != -1) {
            // Process the selected process
            processes[index].remainingTime--;
            clock++;
            
            // Check if process is completed
            if (processes[index].remainingTime == 0) {
                processes[index].completionTime = clock;
                processes[index].turnaroundTime = processes[index].completionTime - processes[index].arrivalTime;
                processes[index].waitingTime = processes[index].turnaroundTime - processes[index].cpuBurst;

                *avgTurnaroundTime += processes[index].turnaroundTime;
                *avgWaitingTime += processes[index].waitingTime;
                remaining--;
            }
        } else {
            // Increment clock if no process is available
            clock++;
        }
    }

    *avgTurnaroundTime /= n;
    *avgWaitingTime /= n;
}

// Function to print the Gantt chart
void printGanttChart(struct Process processes[], int n) {
    int clock = 0;

    // Print the top border
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf(" --------");
    }
    printf("\n|");

    // Print process IDs in the middle
    for (int i = 0; i < n; i++) {
        printf("   P%d   |", processes[i].id);
    }

    // Print the bottom border
    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf(" --------");
    }

    // Print the timeline below the chart
    printf("\n%d", processes[0].arrivalTime);
    clock = processes[0].completionTime;
    for (int i = 0; i < n; i++) {
        printf("        %d", processes[i].completionTime);
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
    int clock = 0;

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("\nEnter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);

        // User-provided burst time
        int userBurstTime;
        printf("Enter initial CPU burst time for Process %d: ", i + 1);
        scanf("%d", &userBurstTime);

        // Generate a random burst time and overwrite the user-provided burst time
        processes[i].cpuBurst = generateRandomBurst();
        processes[i].remainingTime = processes[i].cpuBurst;
        printf("Generated CPU burst time for Process %d: %d (Original Input: %d)\n", i + 1, processes[i].cpuBurst, userBurstTime);
    }

    // Sort processes by arrival time
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    calculateTimes(processes, n, &avgTurnaroundTime, &avgWaitingTime);
    printGanttChart(processes, n);

    printf("\nProcess Details:\n");
    printf("|-----------------------------------------------------------------|\n");
    printf("| Process | Arrival Time | CPU Burst | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("|-----------------------------------------------------------------|\n");
    for (int i = 0; i < n; i++) {
        printf("|    P%-2d  |     %2d       |     %2d    |       %2d       |       %2d        |      %2d     |\n",
               processes[i].id, processes[i].arrivalTime, processes[i].cpuBurst, processes[i].completionTime,
               processes[i].turnaroundTime, processes[i].waitingTime);
    }
    printf("|-----------------------------------------------------------------|\n");
    printf("| Average Turnaround Time: %5.2lf                                 |\n", avgTurnaroundTime);
    printf("| Average Waiting Time: %5.2lf                                    |\n", avgWaitingTime);
    printf("|-----------------------------------------------------------------|\n");

    /*printf("\nDo you want to continue? (1 for yes, 0 for no): ");
    scanf("%d", &choice);*/

    return 0;
}

