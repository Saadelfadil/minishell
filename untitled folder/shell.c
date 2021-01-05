#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_WORD 10
#define MAX_CHAR 100
#define DEL " "

int input_redirection_flag = 0;
int output_redirection_flag = 0;
int piping_flag = 0;
char *input_file = NULL;
char *output_file = NULL;

int process_line(char *temp[], char *line)
{
    int i;

    i = 0;
    temp[i] = strtok(line,DEL);
    while(temp[i] != NULL)
    {
        temp[++i] = strtok(NULL, DEL);
    }
    return 1;
}

void remove_endOfLine(char *line)
{
    int i;

    i = 0;
    while(line[i] != '\n')
        i++;
    line[i] = '\0';
}

void read_line(char *line)
{
    char *ret = fgets(line, MAX_CHAR, stdin);
    remove_endOfLine(line);
    if (strcmp(line, "exit") == 0 || ret == NULL)
        exit(0);
}

int pipe_add_redirection_checking(char *temp[])
{
    int i;

    i = 0;
    while(temp[i] != NULL)
    {
        if (strcmp(temp[i], ">") == 0)
        {
            output_redirection_flag = 1;
            output_file = temp[i + 1];
            return i;
        }
        if (strcmp(temp[i], "<") == 0)
        {
            input_redirection_flag = 1;
            input_file = temp[i + 1];
            return i;
        }
        if (strcmp(temp[i], "|") == 0)
        {
            piping_flag = 1;
            return i;
        }
        i++;
    }
    return i;
}

void check_line(char **temp)
{
    int i;
    int input_redirection_cnt;
    int output_redirection_cnt;
    int piping_cnt;
    int total;

    total = 0;
    piping_cnt = 0;
    output_redirection_cnt = 0;
    input_redirection_cnt = 0;
    i = 0;
    if (temp[i] == NULL)
    {
        printf("NO COMMAND\n");
        return;
    }
    while(temp[i] != NULL)
    {
        if (strcmp(temp[i], ">") == 0)
            output_redirection_cnt++;
        if (strcmp(temp[i], "<") == 0)
            input_redirection_cnt++;
        if (strcmp(temp[i], "|") == 0)
            piping_cnt++;
        i++;   
    }
    total = output_redirection_cnt + input_redirection_cnt + piping_cnt;
    if (total > 1)
    {
        printf("error ...........");
        temp[0] = NULL;
    }
}

int read_parse_line(char **args,char *line,char *piping_args)
{
    char *temp[MAX_WORD];
    int pos;
    int i;
    int j;

    i = 0;
    j = 0;
    read_line(line);
    process_line(temp, line);
    check_line(temp);
    pos = pipe_add_redirection_checking(temp);
    while(i < pos)
    {
        args[i] = temp[i];
        i++;
    }
    args[i] = NULL;
    if (piping_flag == 1)
    {
        while(temp[i] != NULL)
        {
            piping_args[j] = temp[i];
            i++;
            j++;
        }
    }
    return 1;
}

void piping_handle(char **args, char **piping_args, int *pipefd)
{
    int pid;
    int i;

    pid = fork();
    if (pid == 0)
    {
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        execve(args[0], args, NULL);
        perror(args[0]);
    }
    else
    {
        dup2(pipefd[0], 0);
        close(pipefd[1]);
        execve(piping_args[0], piping_args, NULL);
        perror(piping_args[0]);
    }
}

int main()
{
    char *args[MAX_WORD];
    char line[MAX_CHAR];
    char *piping_args[MAX_WORD];
    int pipefd[2];
    pipe(pipefd);

    while(read_parse_line(args,line,piping_args))
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            if (input_redirection_flag == 1 && input_file != NULL)
                dup2(open(input_file, O_RDWR|O_CREAT, 0777), 0);
            if (output_redirection_flag == 1 && output_file != NULL)
                dup2(open(output_file, O_RDWR|O_CREAT, 0777), 1);
            if (piping_flag == 1)
            {
                piping_handle(args,piping_args,pipefd);
                exit(0);
            }
            execve(args[0],args, NULL);
            // execve(args[0], args, NULL);
        }
        else
        {
            waitpid(pid, 0,0);
            input_redirection_flag = 0;
            output_redirection_flag = 0;
            piping_flag = 0;
            input_file = NULL;
            output_file = NULL;
        }
    }
    return 0;
}
