#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

// Function to list files in a directory
void list_directory(char *mode, char *dirname) {
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(mode, "n") == 0) {
            printf("%s\n", entry->d_name);
        } else if (strcmp(mode, "i") == 0) {
            printf("%s - Inode: %lu\n", entry->d_name, entry->d_ino);
        }
        count++;
    }

    if (strcmp(mode, "c") == 0) {
        printf("Number of entries: %d\n", count);
    }

    closedir(dir);
}

int main() {
    char command[80], t1[20], t2[20], t3[20];
    
    system("clear");
    while (1) {
        fflush(stdin);
        printf("myShell$ ");
        fgets(command, 80, stdin);
        int cmd_count = sscanf(command, "%s %s %s", t1, t2, t3);

        if (strcmp(t1, "exit") == 0) {
            printf("Exiting myshell...\n");
            return 0;
        }

        if (cmd_count == 3 && strcmp(t1, "list") == 0) {
            if (strcmp(t2, "n") == 0) {
                list_directory("n", t3);
            } else if (strcmp(t2, "c") == 0) {
                list_directory("c", t3);
            } else if (strcmp(t2, "i") == 0) {
                list_directory("i", t3);
            } else {
                printf("Invalid list command format.\n");
            }
        } else {
            system(command);
        }
    }

    return 0;
}
