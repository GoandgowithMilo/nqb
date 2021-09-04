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

	char ** globbed_tokens = globbed(tokens);

	free_tokens(tokens);

    return globbed_tokens;
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
char ** globbed(char ** tokens)
{
	// start with no space allocated for memory
	int counter = 0;
	char ** globbed_tokens = (char **) malloc(sizeof(char *) * counter);

	// iterate through and glob each item in tokens
	int i = 0;
	while(tokens[i] != NULL)
	{
		glob_t globbuf;

		glob(tokens[i], GLOB_NOCHECK | GLOB_TILDE, NULL, &globbuf);

		// case #1 - no matches
		if(globbuf.gl_pathc == 0)
		{
			// extending globbed_tokens memory by 1
			globbed_tokens = realloc(globbed_tokens, sizeof(char *) * (counter + 1));
			// copying the ith element into the token variable and setting in array
			char * token = malloc(sizeof(char) * strlen(tokens[i]));
			strcpy(token, tokens[i]);
			globbed_tokens[counter] = token;

			counter++;

			globfree(&globbuf);
		}
		// case #2 - one match
		else if(globbuf.gl_pathc == 1)
		{
			// extending memory by 1
			globbed_tokens = realloc(globbed_tokens, sizeof(char *) * (counter + 1));
			// copying only element in gl_pathv into a token then our array
			char * token = malloc(sizeof(char) * strlen(globbuf.gl_pathv[0]));
			strcpy(token, globbuf.gl_pathv[0]);
			globbed_tokens[counter] = token;

			counter++;

			// globfree(&globbuf);
			//TODO globfree here breaks this and I'm not sure why
		}
		// case #3 - more than one match
		else
		{
			// extending memory by result of gl_pathc
			globbed_tokens = realloc(globbed_tokens, 
				sizeof(char *) * (counter + globbuf.gl_pathc + 1));
			// copying all the elements into our array
			for(int j = 0; j < globbuf.gl_pathc; j++)
			{
				char * token = malloc(sizeof(char) * strlen(globbuf.gl_pathv[j]));
				strcpy(token, globbuf.gl_pathv[j]);
				globbed_tokens[counter] = token;

				counter++;
			}

			globfree(&globbuf);
		}
		i++;
	}

	// null terminating the array
	globbed_tokens[counter] = NULL;

	return globbed_tokens;
}

