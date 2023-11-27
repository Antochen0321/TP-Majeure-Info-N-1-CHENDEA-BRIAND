// for this question, we just change the main fonction 

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
    
        //verification of the exit command to leave the shell, here we put a 'or' = || for implement the ctrl+d action for exit the sheel.
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
