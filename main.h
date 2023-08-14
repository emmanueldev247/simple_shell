#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

int main(void);
int main(int argc, char *argv[]);
int main(int argc, char *argv[], char *envp[]);

#endif
