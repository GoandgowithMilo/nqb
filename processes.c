#include "processes.h"

// determines if a file is executable, returning 1 if so and 0 otherwise
int is_executable(char * full_path)
{
    struct stat statbuf;
    
    if(stat(full_path, &statbuf) == 0)
    {
        // stat ran successfully
        if(statbuf.st_mode & S_IXUSR)
        {
            // file is executable
            return 1;
        }
        else
        {
            // file is not executable
            return 0;
        }
    }
    else
    {
        // stat errored
        return 0;
    }
}

// attempts to create a child process with the given path and arguments
void spawn_process(char * full_path, char ** argv)
{
    pid_t pid;
    int  exit_status;

    // runs the process
    if(posix_spawn(&pid, full_path, NULL, NULL, argv, NULL) != 0)
    {
        fprintf(stderr, "Spawning process failed\n");
    }

    // wait for process to terminate
    if(waitpid(pid, &exit_status, 0) == -1)
    {
        fprintf(stderr, "Process waiting failed\n");
    }

    return;
}
