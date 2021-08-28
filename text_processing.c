#include "text_processing.h"

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

