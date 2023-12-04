#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>

#define MAX_COMMAND_LENGTH 100


/*Welcom function*/
void welcome_message() {
    write(1, "Welcome to the ENSEA Shell.\n", 28);
    write(1, "To exit, type 'exit'\n", 22);
    /*Here, we write the command to print message.(1) for standard output, then the string,
    then the string size*/
}

/*Function to execute our command*/
void execute_command(char *command) {
    pid_t pid, wpid;
    int status;

    /*Creation of a new process with fork()*/
    pid = fork();

    if (pid == 0) {
        // son process
        //Here, we execute the command in son process thanks to execlp
        if (execlp(command, command, (char *)NULL) == -1) {
            //If there is an error, we display an error message
            perror("enseash");
            //Exit of the son process with the echec code
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

    // Display of return code or signal in the prompt
    if (WIFEXITED(status)) {
        // if the process finished normally
        write(1, "[exit:", 6);
        char exit_status_str[5];
        snprintf(exit_status_str, sizeof(exit_status_str), "%d", WEXITSTATUS(status));
        write(1, exit_status_str, strlen(exit_status_str));
        write(1, "] ", 2);
    } else if (WIFSIGNALED(status)) {
        // if the process was interrupted by un signap
        write(1, "[sign:", 6);
        char signal_number_str[5];
        snprintf(signal_number_str, sizeof(signal_number_str), "%d", WTERMSIG(status));
        write(1, signal_number_str, strlen(signal_number_str));
        write(1, "] ", 2);
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