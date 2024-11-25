#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LINE_LEN 1024

// Function to display lines from a file
void typeline_file(char *mode, int n, char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LEN];
    int total_lines = 0;

    // Count the total lines in the file for `-` and `a` modes
    if (strcmp(mode, "a") == 0 || strcmp(mode, "-") == 0) {
        while (fgets(line, sizeof(line), file)) {
            total_lines++;
        }
        rewind(file);
    }

    int current_line = 0;
    if (strcmp(mode, "n") == 0) {
        while (fgets(line, sizeof(line), file) && current_line < n) {
            printf("%s", line);
            current_line++;
        }
    } else if (strcmp(mode, "-") == 0) {
        int start_line = total_lines - n;
        while (fgets(line, sizeof(line), file)) {
            if (current_line >= start_line) {
                printf("%s", line);
            }
            current_line++;
        }
    } else if (strcmp(mode, "a") == 0) {
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
    } else {
        printf("Invalid option for typeline command\n");
    }

    fclose(file);
}

int main() {
    char command[80], t1[20], t2[20], t3[20], t4[20];
    int n;

    system("clear");
    while (1) {
        fflush(stdin);
        printf("myShell$ ");
        fgets(command, 80, stdin);
        int cmd_count = sscanf(command, "%s %s %s %s", t1, t2, t3, t4);

        if (strcmp(t1, "exit") == 0) {
            printf("Exiting myshell...\n");
            return 0;
        }

        if ((cmd_count == 3 || cmd_count == 4) && strcmp(t1, "typeline") == 0) {
            if (strcmp(t2, "n") == 0) {
                n = atoi(t3);
                typeline_file("n", n, t4);
            } else if (strcmp(t2, "-") == 0) {
                n = atoi(t3);
                typeline_file("-", n, t4);
            } else if (strcmp(t2, "a") == 0) {
                typeline_file("a", 0, t3);
            } else {
                printf("Invalid typeline command format.\n");
            }
        } else {
            printf("Unknown command or invalid format.\n");
        }
    }

    return 0;
}
