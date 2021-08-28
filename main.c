// Main that enters into an event loop for the program to run

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <spawn.h>
#include <sys/wait.h>
#include "text_processing.h"
#include "inbuilt.h"
#include "processes.h"

/* CONSTANTS */
// determines max # lines to be read into command line
#define MAX_LINE_CHARS 1024

// display prompt
#define DISPLAY "~: "

/* FUNCTIONS */
void execute_command(char ** command, char ** path);
void run_command(char ** command, char ** path);
char * assemble_path(char * file, char * path);

/*
int is_executable(char * full_path);
char * assemble_path(char * file, char * path);
void spawn_process(char * full_path, char ** argv);
*/

int main(int argc, char * argv[])
{
    char input[MAX_LINE_CHARS];

    // get the path variables to pass to execute command
    char * path = getenv("PATH");
    char ** path_tokens = tokenize(path);

    while(1)
    {
        // start of line for user input
        printf("%s", DISPLAY);
        fgets(input, MAX_LINE_CHARS, stdin);

        char ** command_tokens = tokenize(input);

        execute_command(command_tokens, path_tokens);

        free_tokens(command_tokens);
    }

    free_tokens(path_tokens);

    return 0;
}

// attempts to execute the given command
void execute_command(char ** command, char ** path)
{
    // assumes command[0] is the actual command and the rest are arguments

    /* Inbuilt Functions */
    // closes the terminal
    if(strcmp(command[0], "exit") == 0)
    {
        exit(1);

        return;
    }

    // prints the current working directory
    if(strcmp(command[0], "pwd") == 0)
    {
        pwd();

        return;
    }

    // changes to the root directory or the directory specified by 
    if(strcmp(command[0], "cd") == 0)
    {
        cd(command);

        return;
    }
    
    /* External Functions */
    run_command(command, path);

    return;
}

// Function which checks for file existence then attempts to open them
void run_command(char ** command, char ** path)
{
    // test if we're given a path instead of a command
    // if the path is executable, attempt to execute
    if(command[0][0] == '/')
    {
        if(is_executable(command[0]))
        {
            spawn_process(command[0], command);

            return;
        }

        return;
    }

    // iterate through each path
    // assemble a path to an exectuable with the command
    // test if this full path is executable
    // attempt to execute if it is 
    int i = 0;
    while(path[i] != NULL)
    {
        char * full_path = assemble_path(command[0], path[i]);

        if(is_executable(full_path))
        {
            spawn_process(full_path, command);
            
            return;
        }

        i++;
    }

    return;
}



// assembles a path from a file and a path and returns a ptr to a str containing it
char * assemble_path(char * file, char * path)
{
    static char full_path[MAX_LINE_CHARS + PATH_MAX];
    strcpy(full_path, path);
    strcat(full_path, "/");
    strcat(full_path, file);

    return full_path;
}

/*
// determines if a file is executable, returning 1 if so and 0 otherwise
int is_executable(char * full_path)
{
    struct stat statbuf;
    
    if(stat(full_path, &statbuf) == 0)
    {
        // stat ran successfully
        if(statbuf.st_mode & S_IXUSR)
        {
            // file is executable
            return 1;
        }
        else
        {
            // file is not executable
            return 0;
        }
    }
    else
    {
        // stat errored
        return 0;
    }
}

// attempts to create a child process with the given path and arguments
void spawn_process(char * full_path, char ** argv)
{
    pid_t pid;
    int  exit_status;

    // runs the process
    if(posix_spawn(&pid, full_path, NULL, NULL, argv, NULL) != 0)
    {
        fprintf(stderr, "Spawning process failed\n");
    }

    // wait for process to terminate
    if(waitpid(pid, &exit_status, 0) == -1)
    {
        fprintf(stderr, "Process waiting failed\n");
    }

    return;
}
*/
