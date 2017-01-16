#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "linkedl.h"
/*
With help of argument, search through folders on the computer and finds
a file.
*/
void fileSearch(char *path, char *keyword, int optid);
//corrects the path name if it is missing a / at end of name.
void pathNameCorrection(char *f_name);
//adds an directory to the list when dirr is found.
void addDirr(char *file_name, char *path_name, list *l, tracker *t);
//gets the option number if a option was set.
int getOption(int argc, char *argv[]);
//check if path is correct and exists.
int checkPATH(char *argv);
//check if the program has access to dir/file.
int checkIfAccessiblePATH(char *argv);
/*
This function will retrive a void pointer where it checks if the value
of the pointer is null to see if mem-allocation failed.
The input is set to void so that all types of mem-allocated variables
will work.
*/
void checkIfNULLMEM(void *allocdVar);
int checkOPT(char *argv[]);
void *runProgram(int opt, char *key,char *argv[], int argc);
int check_command(char *optarg);
void switchOpt(int optid,char *keyword,struct stat file_info);
void searchDir(char *cdir_name,char *key,struct stat file_info);
void runSearch(int opt, int argc,char* argv[], char* key, int index);
void printCase(int optid,tracker *t, char *keyword,struct stat file_info);
void printInfo(int optid,tracker *t,char* d_name,char *key,struct stat file_info);



/*
This function will retrive a void pointer where it checks if the value
of the pointer is null to see if mem-allocation failed.
The input is set to void so that all types of mem-allocated variables
will work.
*/