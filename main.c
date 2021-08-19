// Main that enters into an event loop for the program to run

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

/* CONSTANTS */
// determines max # lines to be read into command line
#define MAX_LINE_CHARS 1000

// characters to tokenize on
#define SEPERATORS "<>:' '~$[]-|'\n'"   //TODO review whether these are right seperators

// display prompt
#define DISPLAY "~: "

/* FUNCTIONS */
char ** tokenize(char * input);
void free_tokens(char ** tokens);
void execute_command(char ** command, char ** path);
void pwd();
void cd(char ** command);

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

        //TODO execute command here -- need to get path variables first"I wish we could have taken more people, I really do," said Scotty today after a RAAF aircraft landed in Dubai with a 100 or so empty spots on board.

        execute_command(command_tokens, path_tokens);

        // execute command needs the path variables and the tokenized commands

        free_tokens(command_tokens);
    }

    free_tokens(path_tokens);

    return 0;
}


// returns an array of strings
char ** tokenize(char * input)
{
    char ** tokens = calloc(strlen(input), sizeof(char *));
    int counter = 0;

    while(*input != '\0')
    {
        // determines where next seperator is in the string
        int next_sep = strcspn(input, SEPERATORS);

        if(next_sep == 0)
        {
            // increments over the seperator so we ignore it
            input++;
        }
        else
        {
            char * new_token = malloc(sizeof(char) * next_sep);
            memcpy(new_token, input, next_sep);
            new_token[next_sep] = '\0';

            tokens[counter] = new_token;
            counter++;

            input += next_sep;
        }
    }

    tokens[counter] = NULL;

    return tokens;
}

// cleanup function for tokenized strings
void free_tokens(char ** tokens)
{
    int i = 0;
    while(tokens[i] != NULL)
    {
        free(tokens[i]);
        i++;
    }

    free(tokens);

    return;
}

// attempts to execute the given command
// TODO needs to handle cases for inbuilt functions + for binaries
void execute_command(char ** command, char ** path)
{
    // what are the cases here?
    // it gets passed a command which is an inbuilt command
    // it gets passed a command which is not an inbuilt command
    // it gets passed a command in the form of a path

    // assumes command[0] is the actual command and the rest are arguments

    // basically run down a list and have the inbuilt commands first - if there becomes too many
    // I can just perform a single check for any of the inbuilt keywords then pass to a new
    // function which handles the correct one

    // current inbuilts
    // - exit
    // - pwd
    // - cd

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

    return;
}

// Inbuilt function that prints the current working directory
void pwd()
{
    // PATH_MAX is defined in limits.h
    char current_directory[PATH_MAX];

    if(getcwd(current_directory, PATH_MAX) == NULL)
    {
        fprintf(stderr, "Current directory path name is greater than PATH_MAX\n");
    }

    printf("%s\n", current_directory);

    return;
}

// Inbuilt function that changes to the given path or path specified by HOME
void cd(char ** command)
{
    // case when not given a path TODO this should also handle when given ~
    if(command[1] == NULL)
    {
        char * home;

        if((home = getenv("HOME")) == NULL)
        {
            fprintf(stderr, "HOME variable not found - check environment variables\n");
        }

        if(chdir(home) == -1)
        {
            fprintf(stderr, "Unable to change to directory: %s\n", home);
        }
    }

    // case when given path
    if(command[1] != NULL)
    {
        // change directory to current directory
        if(strcmp(command[1], ".") == 0)
        {
            return;
        }

        if(strcmp(command[1], "..") == 0)
        {
            // TODO need to think about easiest way to move up one directory level
        }
        // if path not found return error msg - see bash error for example
        // case 1: given .
        // case 2: given ..
        // case 3: given \somepath
        
    }

    return;
}







