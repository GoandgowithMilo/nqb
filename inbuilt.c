#include "inbuilt.h"

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

// calls exit on the shell and performs any cleanup required
void exit_shell()
{
	exit(1);
}
