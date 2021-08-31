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

    return globbed(tokens, counter); //TODO note this is currently passing in the length
	// including the NULL element, might need to cut this one short
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

// matches all wildcard patterns and returns an array of strings including them
char ** globbed(char ** tokens, int token_count)
{
	// Step 1 - make new array of length = to tokens
	// Step 2 - iterate through tokens and attempt to glob each element
	// Step 2a - if the result of gl_pathc is 0, just add tokens element to new array
	// Step 2b - if gl_pathc > 0, reallocate memory of new array to extra size then add
	// all elements to new array
	// Step 3 - Null terminate new array and return it

	// allocates memory for the array of strings
	char ** globbed_tokens = malloc((sizeof(char *)) * token_count);
	char * token;

	// counter for globbed_tokens
	int new_token_counter = 0;


	int i = 0;
	while(tokens[i] != NULL)
	{
		glob_t globbuf;

		glob(tokens[i], 0, NULL, &globbuf);

		// case 1 - no matches >>> do not need to increase memory here
		if(globbuf.gl_pathc == 0)
		{
			// allocates memory for the string
			token = (char *) malloc(sizeof(strlen(tokens[i])));
			strcpy(token, tokens[i]);
			globbed_tokens[new_token_counter] = token;

			new_token_counter++;
		}
		// case 2 - add all matches to new arrayb >>> increase memory to store new strings
		else
		{
			// increasing size of memory for tokens
			realloc(globbed_tokens, sizeof(char *) * (token_count + globbuf.gl_pathc)); //TODO this is not going to allocat ethe correct amount. Either need another counter or a better method for doing this

			for(int k = 0; k < globbuf.gl_pathc; k++)
			{
				token = (char *) malloc(sizeof(strlen(globbuf.gl_pathv[k])));
				strcpy(token, globbuf.gl_pathv[k]);
				globbed_tokens[new_token_counter] = token;

				new_token_counter++;
			}
		}

		i++;
	}

	globbed_tokens[new_token_counter + 1] = NULL;

	int j = 0;
	while(globbed_tokens[j] != NULL)
	{
		printf("%s\n", globbed_tokens[j]);
		j++;
	}

	//TODO should free the original tokens at the end of this since we're no
	// longer using them

	return tokens;
}

