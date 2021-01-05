
void loop(void) {
    char *line;
    char **args;
    int status;

    //read the commands entered by user
    //it will parse the commands computer can understand the commands
    //exucute the commands

    do {
        printf("%s","Overwatch@root >");
        line = read();
        //args is an array of strings
        //echo samagra is good
        args = parse(line);
        status = execute(args);

        //freeing the memory
        free(line);
        free(args);

    } while (status);
}



int main(int argc, char  *argv[])
{
    //load the configuration

    //run and repl loop
    loop();
    //perform any shutdown cleanup
    return 0;
}
