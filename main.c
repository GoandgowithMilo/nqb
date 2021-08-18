// Main that enters into an event loop for the program to run

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void execute_command(char ** path, char ** command);

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

        execute_command(path_tokens, command_tokens);

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
void execute_command(char ** path, char ** command)
{
    // assumes command[0] is the actual command and the rest are arguments

    if(strcmp(command[0], "exit") == 0)
    {
        exit(1);
    }

    return;
}
