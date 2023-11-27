#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>



/*Welcom function*/
void welcome_message() {
    write(1, "Welcom to the ENSEA Shell.\n", 28);
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
}

//main function
int main(int argc, char *argv[]) {
    
    //display of the welcom message
    welcome_message();
}