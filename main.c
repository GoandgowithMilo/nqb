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
void run_command(char ** command, char ** path);
int is_executable(char * full_path);

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

    // TODO
    // check if the first element of the command is a '\'
    // if so we're doing run from path variant
    // might be better to just call posix_spawn function here regadless
    // then have something within that function that handles it

    run_command(command, path);

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
    if(command[1] != NULL && command[2] != NULL)
    {
        fprintf(stderr, "-nqb: %s: too many arguments\n", command[0]);
        return;
    }

    // case when not given a path
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
        // Note: chdir command handles cases for things like ., .. or ~ given as well
        int successful_change = chdir(command[1]);

        if(successful_change == -1)
        {
            fprintf(stderr, "-nqb: %s: %s: No such file or directory\n"
                ,command[0], command[1]);
        }
        else
        {
            return;
        }
    }

    return;
}


// Function which checks for file existence then attempts to open them
void run_command(char ** command, char ** path)
{
    // iterate through each path
    // assemble a path to an exectuable with the command
    // test if this full path is executable
    // if exectuable, 
    int i = 0;
    while(path[i] != NULL)
    {
        char full_path[MAX_LINE_CHARS + 20];
        strcpy(full_path, path[i]);
        strcat(full_path, "/");
        strcat(full_path, command[0]);

 d        //TODO test if full path leads to a file that is executable
        //TODO call posix_spawn if it is 

        i++;
    }

    return;

    // iterate through the paths
    // for each attempt to execute the file
    // need to be able to detect if the file can be executed
    // TODO implement a way to check if a file is executable
    // TODO if hte file is executable, execute it
}

int is_executable(char * full_path)
{
    ;
}
