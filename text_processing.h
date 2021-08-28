#ifndef TEXT_PROCESSING_FUNCTIONS
#define TEXT_PROCESSING_FUNCTIONS

#include <string.h>
#include <stdlib.h>

// characters to tokenize on
#define SEPERATORS "<>:' '~$[]|'\n'"   //TODO review whether these are right seperators

char ** tokenize(char * input);
void free_tokens(char ** tokens);

#endif
