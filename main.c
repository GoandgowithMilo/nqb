// Main that enters into an event loop for the program to run

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* CONSTANTS */
// determines max # lines to be read into command line
#define MAX_LINE_CHARS 1000

/* FUNCTIONS */
char ** tokenize(char * input);

int main(int argc, char * argv[])
{
    char input[MAX_LINE_CHARS];

    while(1)
    {
        // start of line for user input
        printf("~: ");
        fgets(input, MAX_LINE_CHARS, stdin);

        //TODO tokenize here
        char ** tokens = tokenize(input);
        //TODO execute command here

        fputs(input, stdout); //TODO remove - this is a test print
    }

    return 0;
}


// returns an array of strings
char ** tokenize(char * input)
{
    char ** tokens = calloc(strlen(input), sizeof(char));

    // iterate through input character by character

    // allocate memory for returned array - we can assume that we'll have at most # of characters
    // tokens and later reallocate to the proper amount
    // iterate through the input and use strcspn + strspn to separate
    //TODO will need to free any memory I allocate here (might need a sep function for this)

    // reallocate the required memory here
    // Null terminate the function

    return tokens;
}

// tokenize function
// should take in a word and split it into as many seperate words as possible
// will likely be a WIP as I work out different commands
