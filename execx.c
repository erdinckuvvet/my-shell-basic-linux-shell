#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int isNumeric(const char *str)
{
    while (*str != '\0')
    {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("eksik veya fazla parametre girdiniz\n");
        exit(0);
    }
    if (strcmp(argv[1], "-t") != 0)
    {
        printf("arg 1 hatali\n");
        exit(0);
    }

    if (isNumeric(argv[2]) != 1)
    {
        printf("arg 2 integer olmali\n");
        exit(0);
    }

    char *arguments[argc - 2];

    for (int i = 0; i < argc - 2; i++)
    {
        arguments[i] = argv[i + 3];
    }

    arguments[argc - 3] = NULL;

    for (size_t i = 0; i < atoi(argv[2]); i++)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            printf("\nFailed to fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            if (execv(argv[3], arguments) < 0) // run input program n times
            {
                printf("\nInvalid command..");
            }
        }
        else
        {
            // waiting for child to abort
            wait(&pid);
        }
    }

    return 0;
}