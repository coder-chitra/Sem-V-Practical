#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *cmd, char *arg1, char *arg2, char *arg3) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execlp(cmd, cmd, arg1, arg2, arg3, NULL);
        perror("execlp failed");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        wait(NULL); // Wait for the child process to complete
    } else {
        perror("fork failed");
    }
}

void search_command(char *mode, char *filename, char *pattern) {
    if (strcmp(mode, "f") == 0) {
        // Search first occurrence
        printf("First occurrence of '%s' in %s:\n", pattern, filename);
        execute_command("grep", "-m1", pattern, filename);
    } else if (strcmp(mode, "a") == 0) {
        // Search all occurrences
        printf("All occurrences of '%s' in %s:\n", pattern, filename);
        execute_command("grep", pattern, filename, NULL);
    } else if (strcmp(mode, "c") == 0) {
        // Count occurrences
        printf("Number of occurrences of '%s' in %s:\n", pattern, filename);
        execute_command("grep", "-c", pattern, filename);
    } else {
        printf("Invalid mode for search command. Use 'f', 'a', or 'c'.\n");
    }
}

void typeline_command(char *mode, char *n, char *filename) {
    if (strcmp(mode, "n") == 0) {
        // Display first n lines
        printf("First %s lines of %s:\n", n, filename);
        execute_command("head", "-n", n, filename);
    } else if (strcmp(mode, "-") == 0) {
        // Display last n lines
        printf("Last %s lines of %s:\n", n, filename);
        execute_command("tail", "-n", n, filename);
    } else if (strcmp(mode, "a") == 0) {
        // Display all lines
        printf("All lines of %s:\n", filename);
        execute_command("cat", filename, NULL, NULL);
    } else {
        printf("Invalid mode for typeline command. Use 'n', '-', or 'a'.\n");
    }
}

void list_command(char *mode, char *dirname) {
    if (strcmp(mode, "n") == 0) {
        // List filenames
        printf("Filenames in directory %s:\n", dirname);
        execute_command("ls", dirname, NULL, NULL);
    } else if (strcmp(mode, "c") == 0) {
        // Count entries
        printf("Number of entries in directory %s:\n", dirname);
        execute_command("ls", "-1", dirname, "|", "wc -l");
    } else if (strcmp(mode, "i") == 0) {
        // List filenames and inode numbers
        printf("Filenames and inode numbers in directory %s:\n", dirname);
        execute_command("ls", "-i", dirname, NULL);
    } else {
        printf("Invalid mode for list command. Use 'n', 'c', or 'i'.\n");
    }
}

void execute_shell_command(char *input) {
    char command[20], mode[10], arg1[100], arg2[100];
    int num_args = sscanf(input, "%s %s %s %s", command, mode, arg1, arg2);

    if (num_args >= 2 && strcmp(command, "search") == 0) {
        if (num_args == 4) {
            search_command(mode, arg1, arg2);
        } else {
            printf("Usage: search <f/a/c> <filename> <pattern>\n");
        }
    } else if (num_args >= 2 && strcmp(command, "typeline") == 0) {
        if ((strcmp(mode, "n") == 0 || strcmp(mode, "-") == 0) && num_args == 4) {
            typeline_command(mode, arg1, arg2);
        } else if (strcmp(mode, "a") == 0 && num_args == 3) {
            typeline_command(mode, NULL, arg1);
        } else {
            printf("Usage: typeline <n/-/a> [n] <filename>\n");
        }
    } else if (num_args >= 2 && strcmp(command, "list") == 0) {
        if (num_args == 3) {
            list_command(mode, arg1);
        } else {
            printf("Usage: list <n/c/i> <dirname>\n");
        }
    } else {
        // Execute general shell commands
        pid_t pid = fork();
        if (pid == 0) {
            char *args[] = {"/bin/sh", "-c", input, NULL};
            execvp(args[0], args);
            perror("execvp failed");
            exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            perror("fork failed");
        }
    }
}

int main() {
    char input[200];

    while (1) {
        printf("myshell$ ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Exit on EOF
        }

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Exit shell if the command is "exit"
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Execute the entered command
        execute_shell_command(input);
    }

    printf("Exiting myshell.\n");
    return 0;
}
