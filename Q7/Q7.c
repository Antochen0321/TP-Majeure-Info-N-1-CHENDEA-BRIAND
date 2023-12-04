...
void execute_command(char *command_line) {
    pid_t pid, wpid;
    int status;

    //we use strtok for separate the command and all arguments of the call
    char *command_line_copy = strdup(command_line);
    char *command = strtok(command_line, " ");
    int i = 1;
    char *arguments[50];
    arguments[0] = command;
     while (1) {
        char *arg = strtok(NULL, " ");
        if (arg == NULL) {
            arguments[i] = NULL;  // Set the last element to NULL
            break;
        }
        arguments[i] = arg;
        i++;
    }
    free(command_line_copy);
    //Creation of the clock_gettime structure. We also create 2 timespec start_time and end_time for get the time of the execution.
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    /*Creation of a new process with fork()*/
    pid = fork();

    if (pid == 0) {
        // son process
        //Here, we execute the command in son process thanks to execlp
        if (execvp(command, arguments)) {
            //If there is an error, we display an error message
            perror("enseash");
            //Exit of the son process with the failure code
            _exit(EXIT_FAILURE);
        }
    }

    ...
