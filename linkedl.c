#include "linkedl.h"
/*
Creates a linked list which keeps track of directories to search
inside. Creates the list with one directory to begin with.
*/
list* createList(char* dir_name){
	
	if(dir_name == NULL){
		printf("Error, trying to insert empty value to list\n");
		exit(-1);
	}
	list* l = (list*)calloc(1,sizeof(list));
	if(l == NULL){
		
		fprintf(stderr,"something went wrong with mem-allocation.\n");
	}
	l->dir_name = calloc(1,(strlen(dir_name)+2)*sizeof(char));

	strcpy(l->dir_name,dir_name);

	l->prev = NULL;
	l->next = NULL;
	return l;
}


/*inserts a directory in the list.
and returns the the newly inserted directory
at the end of list to call.
*/
list *insertDirToList(list* l,tracker *t, char* dir_name){
	
	list* new_Dir;
	

	while(l->next != NULL){
		
			l = l->next;
	}

	new_Dir = createList(dir_name);
	new_Dir->prev = l;
	l->next = new_Dir;
	t->tail = new_Dir;	
	
	return t->tail;
}

/*
Removes the last element from list
and returns the second last element back to call.
*/
void removeDirFromList(list* l,tracker *t){
	
	if(isEmpty(t) == TRUE ){
		
		printf("Trying to remove element from empty list.\n");
		exit(-1);
	}
	
	t->current = t->tail->prev;
	free(t->tail->dir_name);
	free(t->tail);
	t->tail = t->current;
	if(t->tail != NULL){

		t->tail->next = NULL;
	}
}
/*
Frees the list by looping through it and
removing every element one by one
*/
void freeList(list *l,tracker *t){
	
	l = t->head;
	while(l->next != NULL){
		t->head = t->head->next;	
		t->current = l;	
		
		if( !(strlen(t->current->dir_name)) == 0){
			
			free(t->current->dir_name);
		}

		free(t->current);
		l = t->head;
	}
	t->current = l;
	free(t->current->dir_name);
	free(t->current);
}

/*
Controlls if the list IS empty
*/
int isEmpty(tracker *t){

	
	if(t->tail == NULL){
		return TRUE;
		
	}
	else{
		return FALSE;
	}
	
}

/*
Controlls if the list is non-empty
*/
int nonEmpty(list *l, tracker *t){

	int nrE = 0;
	t->current = t->head;
	while(t->current != NULL){
		
		t->current = t->current->next;
		nrE++;
	}
	if(nrE>0){

		return TRUE;
	}
	else{
		return FALSE;
	}
}




