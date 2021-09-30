#include "history.h"

FILE * buffer_history(char * input)
{
	char * home = getenv("HOME");
	char pathname[1024];
	FILE * history;

	strcpy(pathname, home);
	strcat(pathname, "/");
	strcat(pathname, ".nqb_history");

	history = fopen(pathname, "a+");

	fprintf(history, "%s", input);

	return history;
}

void write_history(FILE * history)
{
	fclose(history);

	return;
}
