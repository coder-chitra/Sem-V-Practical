#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void count_characters(const char *filename) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execlp("wc", "wc", "-c", filename, NULL);
        perror("execlp failed"); // This executes only if execlp fails
        exit(1);
    } else if (pid > 0) {
        // Parent process
        wait(NULL); // Wait for the child process to complete
    } else {
        perror("fork failed");
    }
}

void count_words(const char *filename) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execlp("wc", "wc", "-w", filename, NULL);
        perror("execlp failed"); // This executes only if execlp fails
        exit(1);
    } else if (pid > 0) {
        // Parent process
        wait(NULL); // Wait for the child process to complete
    } else {
        perror("fork failed");
    }
}

void count_lines(const char *filename) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execlp("wc", "wc", "-l", filename, NULL);
        perror("execlp failed"); // This executes only if execlp fails
        exit(1);
    } else if (pid > 0) {
        // Parent process
        wait(NULL); // Wait for the child process to complete
    } else {
        perror("fork failed");
    }
}

void execute_command(char *input) {
    char command[10], option[10], filename[100];
    int num_args = sscanf(input, "%s %s %s", command, option, filename);

    if (num_args == 3 && strcmp(command, "count") == 0) {
        if (strcmp(option, "c") == 0) {
            printf("Number of characters in %s:\n", filename);
            count_characters(filename);
        } else if (strcmp(option, "w") == 0) {
            printf("Number of words in %s:\n", filename);
            count_words(filename);
        } else if (strcmp(option, "l") == 0) {
            printf("Number of lines in %s:\n", filename);
            count_lines(filename);
        } else {
            printf("Invalid option for count command. Use 'c', 'w', or 'l'.\n");
        }
    } else {
        // For other shell commands, create a child process and execute them
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            char *args[] = {"/bin/sh", "-c", input, NULL};
            execvp(args[0], args); // Execute the command
            perror("execvp failed");
            exit(1);
        } else if (pid > 0) {
            // Parent process
            wait(NULL); // Wait for the child process to complete
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
        execute_command(input);
    }

    printf("Exiting myshell.\n");
    return 0;
}
