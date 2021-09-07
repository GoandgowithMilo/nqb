#include "history.h"

void buffer_history(char * input)
{
	char * home = getenv("HOME");
	char pathname[1024];
	FILE history;

	strcpy(pathname, home);
	strcat(pathname, "/");
	strcat(pathname, ".nqb_history");

	history = fopen(pathname, "a+");

	fclose(history);

	// need to build the pathname here;

	return;
}

void write_history()
{
	return;
}
