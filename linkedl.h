#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <getopt.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0



typedef struct list{

	int read;
	char* dir_name;
	struct list* next;
	struct list* prev;
} list;

typedef struct tracker{
	list* head;
	list* current;
	list* tail;
}tracker;



/*
Creates a linked list which keeps track of directories to search
inside. Creates the list with one directory to begin with.
*/
list* createList(char* dir_name);

/*inserts a directory in the list.
and returns the the newly inserted directory
at the end of list to call.
*/
list *insertDirToList(list* l,tracker *t ,char* dir_name);


/*
Removes the last element from list
and returns the second last element back to call.
*/
void removeDirFromList(list* l, tracker* t);

/*
Frees the list by looping through it and
removing every element one by one
*/
void freeList(list *l, tracker *t);

/*
Controlls if the list IS empty
*/
int isEmpty(tracker *t);

/*
Controlls if the list is non-empty
*/
int nonEmpty(list *l, tracker *t);


