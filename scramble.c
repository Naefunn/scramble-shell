// gcc scramble.c ./lib/linenoise.c -o scramble

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "./lib/linenoise.h"

#define PROMPT "$ "
#define HISTORY_LENGTH 1024
#define MAX_ARGS 1024

int s_read(char *input, char **args, int max_args)
{
    int i = 0;

    // split the string into tokens using spaces and tabs
    char *token = strtok(input, " \t");

    // keep extracting til there are no more or args is full
    while (token != NULL && i < (MAX_ARGS - 1))
    {
        args[i++] = token;
        token = strtok(NULL, " \t");
    }
    args[i] = NULL;
    return i;
}

int s_execute(char *cmd, char **cmd_args)
{
    fprintf(stdout, "Executing `%s`!\n", cmd);

    int status;
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Could not execute\n");
        return -1;
    }

    if(pid == 0)
    {
        execv(cmd, cmd_args);
    } else
    {
        if (waitpid (pid, &status, 0) != pid)
        {
            fprintf(stderr, "could not wait for kiddo\n");
            return -1;
        }
    }
}

int main(void)
{
    // REPL input
    if (!linenoiseHistorySetMaxLen(HISTORY_LENGTH)) 
    {
        fprintf(stderr, "Could not set linenoise history");
        exit(1);
    }

    char *line;
    char *args[MAX_ARGS];
    
    while ((line = linenoise(PROMPT)) != NULL) 
    {

        // read step
        int args_read = s_read(line, args, MAX_ARGS);

        fprintf(stdout, "read %d args\n", args_read);
        for (int i = 0; i < args_read; i++)
        {
            fprintf(stdout, "arg[%d] = %s\n", i, args[i]);
        }

        // skip empty lines
        if (args_read == 0)
        {
            linenoiseFree(line);
            continue;
        }

        // TODO eval and print step
        char *cmd = args[0];
        char **cmd_args = args;
        s_execute(cmd, cmd_args);

        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }

    return 0;
}
