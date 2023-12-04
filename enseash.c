#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>

#define MAX_COMMAND_LENGTH 100


/*Welcom function*/
void welcome(){
    char welcome_message = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'. \n";
    //Here, we write the welcome message, it must be printed just after the opening of our shell
    write(STDOUT_FILENO, welcome_message, sizeof(welcome_message) - 1);
    //We use "write" for print the message, this function take 3 arguments : 
    //                              The description of the file (for example here, is an out file)
    //                              The *buf, a pointer to the memory buf which contains the message
    //                              The size of the message
}

/*Function to execute our command*/
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

    else if (pid < 0) {
        //If there is an error, we display an error message
        perror("enseash");
    } 
    
    else {
        // parent process
        //Waiting for the execute end of the command in son process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
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

//main function
int main(int argc, char *argv[]) {

    char user_input[MAX_COMMAND_LENGTH];

    //display of the welcom message
    welcome_message();

    while (1) {
        // Display prompt for user input
        write(1, "enseash % ", 11);

        // Use of read function to read user input
        ssize_t bytes_read = read(0, user_input, sizeof(user_input));

        // delete of line break at command end
        // without this command, "enseash %" stay display even after have write "exit"
        user_input[strcspn(user_input, "\n")] = 0;
    
        //verification of the exit command to leave the shell
        if (strcmp(user_input, "exit") == 0 || bytes_read == 0) {
            // Display of departure message
            write(1, "Good bye!\n", 11);
            // Exit of the infinite loop
            break;
        }

        // Execution of user input command 
        execute_command(user_input);

    }
    

    // Fin du programme
    return 0;
}
