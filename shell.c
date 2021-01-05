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

int process_line(char **temp, char *line)
{
    int i;

    i = 0;
    temp[i] = strtok(line,DEL);
    if (temp[i] == NULL)
        return 1;
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
    while (line[i] != '\n')
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

int pipe_add_redirection_checking(char **temp)
{
    int i;

    i = 0;
    while (temp[i] != NULL)
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

int read_parse_line(char **args,char *line)
{
    int pos;
    int i;
    char *temp[MAX_WORD];

    i = 0;
    read_line(line);
    process_line(temp, line);
    pos = pipe_add_redirection_checking(temp);
    while (i < pos)
    {
        args[i] = temp[i];
        i++;
    }
    return 1;
}

int main()
{
    char *args[MAX_WORD];
    char line[MAX_CHAR];

    while(read_parse_line(args,line))
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            if (input_redirection_flag == 1 && input_file != NULL)
                dup2(open(input_file, O_RDWR|O_CREAT, 0777), 0);
            if (output_redirection_flag == 1 && output_file != NULL)
                dup2(open(output_file, O_RDWR|O_CREAT, 0777), 1);
            execvp(args[0],args);
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
