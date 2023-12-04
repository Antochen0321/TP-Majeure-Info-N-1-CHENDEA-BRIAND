
/*Function to execute our command*/
void execute_command(char *command) {
    pid_t pid, wpid;
    int status;

    //Creation of the clock_gettime structure. We also create 2 timespec start_time and end_time for get the time of the execution.
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    /*Creation of a new process with fork()*/
    pid = fork();

    if (pid == 0) {//code of the Q1-2-3 Questions
        ...
    }

    //end of time measure
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    //Now, we calculate the difference betwen the beggining and the end of the timer.
    long long elapsed_time = (end_time.tv_sec - start_time.tv_sec)*1000 + (end_time.tv_nsec - start_time.tv_nsec)/1000000;
    // Display of return code or signal in the prompt
    if (WIFEXITED(status)) {
        // if the process finished normally
        write(1, "[exit:", 6);
        char exit_status_str[5];
        // the sheel send an exit message with the value of the memory block used by the call after the exit. 
        //Especialy 1 when the call generate an error like 'No such file directory'
        snprintf(exit_status_str, sizeof(exit_status_str), "%d", WEXITSTATUS(status));
        write(1,exit_status_str, strlen(exit_status_str));
        write(1, "|",1);
        char elapsed_time_str[10];
        snprintf(elapsed_time_str, sizeof(elapsed_time_str), "%ld", elapsed_time);
        write(1, elapsed_time_str, strlen(elapsed_time_str));
        write(1, "ms] ", 5);
    } else if (WIFSIGNALED(status)) {
        // if the process was interrupted by un signap
        write(1, "[sign:", 6);
        char signal_number_str[5];
        //the sheel will send a sign message when the call generate a segmentation false error like
        snprintf(signal_number_str, sizeof(signal_number_str), "%d", WTERMSIG(status));
        write(1, signal_number_str, strlen(signal_number_str));
        char elapsed_time_str[10];
        write(1, "|", 1);
        snprintf(elapsed_time_str, sizeof(elapsed_time_str), "%ldms", elapsed_time);
        write(1, elapsed_time_str, strlen(elapsed_time_str));
        write(1, "ms] ", 5);
    }
}
