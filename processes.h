#ifndef PROCESSES
#define PROCESSES

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <spawn.h>
#include <stdio.h>

int is_executable(char * full_path);
void spawn_process(char * full_path, char ** argv);

#endif
