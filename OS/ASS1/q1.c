/*
Write a program to implement the simulation of the OS shell. The program
should accept the command at $ prompt displayed by your shell (myshell$).
Any normal shell command should be executed from your shell by creating a
child process corresponding to that command.
Additionally, it should interpret the following command count:

i. myshell$ count c <filename>
It will display the number of characters in given file
ii. myshell$ count w <filename>
It will display the number of words in given file
iii. myshell$ count l <filename>
It will display the number of lines in given file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void count(char c, char *fn)
{
    int lc = 0, wc = 0, cc = 0;
    FILE *fp;
    char ch;
    if ((fp = fopen(fn, "r")) == NULL)
    {
        printf("File %s not found\n", fn);
        return;
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            lc++;
            cc++;
            wc++;
        }
        else if (ch == ' ')
        {
            wc++;
            cc++;
        }
        else
        {
            cc++;
        }
    }
    printf("Character count is %d\n", cc);
    fclose(fp);
    switch (c)
    {
    case 'c':
        printf("Total No.of Characters = %d\n", cc);
        break;
    case 'w':
        printf("Total No.of Words = %d\n", wc);
        break;
    case 'l':
        printf("Total No.of Lines = %d\n", lc);
        break;
    }
}

int main()
{
    char command[80], t1[20], t2[20], t3[20], t4[20];
    int n;
    system("clear");
    while (1)
    {
        printf("myShell$");
        fflush(stdin);
        fgets(command, 80, stdin);
        n = sscanf(command, "%s %s %s %s", t1, t2, t3, t4);
        if (strcmp(t1, "exit") == 0)
        {
            printf("Exiting $myshell............\n");
            return 0;
        }
        switch (n)
        {
        case 1:
            if (!fork())
            {
                execlp(t1, t1, NULL);
                perror(t1);
            }
            break;
        case 2:
            if (!fork())
            {
                execlp(t1, t1, t2, NULL);
                perror(t1);
            }
            break;
        case 3:
            if (strcmp(t1, "count") == 0)
                count(t2[0], t3);
            else
            {
                if (!fork())
                {
                    execlp(t1, t1, t2, t3, NULL);
                    perror(t1);
                }
            }
            break;
        case 4:
            if (!fork())
            {
                execlp(t1, t1, t2, t3, t4, NULL);
                perror(t1);
            }
        }
    }

    return 0;
}
