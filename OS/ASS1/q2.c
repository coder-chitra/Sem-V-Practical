#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX_LINE_LEN 1024

// Function to search for a pattern in a file
void search_file(char mode, char *filename, char *pattern) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LEN];
    int found = 0;
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        char *pos = strstr(line, pattern);
        if (pos) {
            if (mode == 'f') {
                printf("First occurrence: %s", line);
                found = 1;
                break;
            } else if (mode == 'a') {
                printf("Found: %s", line);
                found = 1;
            } else if (mode == 'c') {
                count++;
            }
        }
    }

    if (mode == 'c') {
        printf("Number of occurrences: %d\n", count);
    } else if (!found) {
        printf("Pattern not found in the file.\n");
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
        n = sscanf(command, "%s %s %s %s", t1, t2, t3, t4);
        if (strcmp(t1, "exit") == 0) {
            printf("Exiting myShell...\n");
            return 0;
        }
        if (strcmp(t1, "search") == 0) {
            if (n == 4) {
                search_file(t2[0], t3, t4);
            } else {
                printf("Usage: search <mode> <filename> <pattern>\n");
            }
        } else {
            printf("Unknown command: %s\n", t1);
        }
    }
    return 0;
}
