

    

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

        
