#include "mfind.h"


int main(int argc, char* argv[]){

						//keyword*1 == keyword*sizeof(char))
	char *key = calloc(1,(strlen(argv[argc-1])+1)*1);
		//check if key malloc worked.
	checkIfNULLMEM(key);
	
	int opt,checkedOpt = 1;
	strcpy(key,argv[argc-1]);

	opt = getOption(argc,argv);
	int lineErr = (argc-1);//remove programname from argc
	
	//if this is true, then there are 4 args inputed
	if(checkOPT(argv) > 0){
		lineErr--;
		
	}
	else if(opt > 0 && checkedOpt == 1){
		lineErr -= 3; //program name, -t + (option)

	}
	
	if(lineErr < 2){
		printf("Usage: %s [-t option] <directory> [directory2...] ", argv[0]);
		printf("<keyword>\n");
		free(key);
		exit(1);
	}

	runSearch(opt,argc,argv,key,lineErr);

	//check if index needs to be moved +2 in argv vector
	
	free(key);
	return 0;
}

int checkOPT(char *argv[]){
	//if this is true, then there are 4 args inputed
	if(strlen(argv[1])> 1){
		return 1;
	}
	return 0;
}


void runSearch(int opt, int argc,char* argv[], char* key, int index){
	int i = 0;
	char *p_name;

	if( opt != 0 ){

		for( i = index; i < (argc-1); i++){

			p_name = calloc(1,(strlen(argv[i])+2)*sizeof(char));	
				fprintf(stderr,"\n%s\n",argv[i]);
				//check if malloc for path_name worked.
			checkIfNULLMEM(p_name);

			strcpy(p_name, argv[i]);

			pathNameCorrection(p_name);
				//check if path is ok
			if( checkPATH(p_name) ){

				fileSearch(p_name, key,opt);
			}
			free(p_name);
		}
	}
	else{
		for(i = 1; i < (argc-1); i++){
					
			p_name = calloc(1,(strlen(argv[i])+2)*sizeof(char));
			checkIfNULLMEM(p_name);
			strcpy(p_name, argv[i]);

			pathNameCorrection(p_name);
				// check if path is ok
			if( checkPATH(p_name) ){

				fileSearch(p_name, key,opt);

			}
			free(p_name);
		}
	}
}

/*
Desc: Adds an directory to a list 
Input: file name , path name, a list and it's element
Output: none.
*/

void addDirr(char *file_name, char *path_name, list *l, tracker *t){
						
	char *f_name;
	char *new_path;

	f_name = calloc(1, (strlen(file_name)+2) *sizeof(char) );
	checkIfNULLMEM(f_name);

	strcpy(f_name,file_name);
	pathNameCorrection(file_name);

	new_path = calloc(1, (strlen(t->current->dir_name) +
	strlen(file_name)+2)*sizeof(char) );

	//check if new_path malloc worked
	checkIfNULLMEM(new_path);
		
	strcpy(new_path,t->current->dir_name);
	strcat(new_path,file_name);
			
	l = insertDirToList(l,t,new_path);
	//check if list element malloc worked
	checkIfNULLMEM(l->dir_name);
	//check if list element malloc worked
	checkIfNULLMEM(l);

	l->read = 0;
	free(f_name);
	free(new_path);


}


/*
Desc: Will check within the arguments sent to the program
	if one of the arguments is a -t followed by "t,d,l" which then will return
	an int to indicate which option was sent to the program.
Input: argc which counts the argument sents to program and argv which contains 
	every argument sent to main.
Output: an integer between 0-3
*/
int getOption(int argc, char *argv[]){

	int option;

	while( (option = getopt (argc,argv, "t:")) != -1 ){
		switch (option) {
			case 't':
				if(strcmp(optarg,"f")== 0){
					return 1;
				} 
				else if( strcmp(optarg,"d")== 0 ){
					return 2;
				}
				else if( strcmp(optarg, "l")== 0){
					return 3;
				}
				else{
					fprintf(stderr,"Wrong type of input for file search\n");
					exit(-1);
				}
				break;
			default:
				fprintf(stderr, "something went very wrong with getopt\n");
				abort();
		}
	}
	// no option to be used.
	return 0;
}

/*
Desc: Used to check if the path is correct.
Input: a char pointer containing a path to a file.
Output: None
*/

int checkPATH(char *argv){
	
	struct stat st;

	if((stat(argv, &st)) ==-1){

	
		perror(argv);
		return FALSE;
	}
	return 1;

}
/*
Desc: Checks if the program has access to the file
Input: path to a file
Output: None
*/
int checkIfAccessiblePATH(char *argv){

	if(access(argv, R_OK) == 0 ){
		return TRUE;
	}
	fprintf(stderr, "%s Permission denied\n", argv);
	return FALSE;
}

/*
Desc: This function will retrive a void pointer where it checks if the value
	of the pointer is null to see if mem-allocation failed.
	The input is set to void so that all types of mem-allocated variables
	will work.

Input:  void pointer which refers to a datatype that has been mallocd
Output: None
*/

void checkIfNULLMEM(void *allocdVar){

	if(allocdVar == NULL){
		
		fprintf(stderr,"something went wrong with mem-allocation.\n");
		exit(-1);
	}
}
/*
Desc: With help of argument, search through folders on the computer and finds
	a file.

Input: A path to a dir to begin search, a keyword to search for and a option 
	identity which tells type of file to tell it found. 
Output: None

*/
void fileSearch(char *path, char *keyword, int optid){

		//unintialized variables
	DIR* dp;                     	//directory pointer
	struct dirent* ds;             //directory struct
	struct stat file_info;

			//initialized variables
	int found_dir = TRUE;
	list *l = createList(path);
	checkIfNULLMEM(l);

	tracker *t = calloc(1,sizeof(tracker));
	checkIfNULLMEM(t);
	t->head = l;
	t->tail = l;
	
	if((dp = opendir( t->tail->dir_name ))== NULL){
				
		fprintf(stderr,"cannot open path ");
		closedir(dp);
		if(!checkIfAccessiblePATH(path) ){
			freeList(l,t);
			free(t);
			free(path);
			return;
		}
	}
	closedir(dp);

	while(nonEmpty(l,t)) {

		if(found_dir == TRUE){
			
			if((dp = opendir( t->tail->dir_name ))== NULL){
				
				perror("t->tail->dir_name");
			}	
			found_dir = FALSE;

		}
		else{

			removeDirFromList(l,t);

			//Nothing more to do in function. Jump out of loop.
			if(isEmpty(t)){
				break;
			}

				if((dp = opendir( t->tail->dir_name ))== NULL){
					perror("t->tail->dir_name");
					
					if( (closedir(dp)) == -1 ){
				
						freeList(l,t);	
						perror("closedir");
						free(t);
						free(path);
						exit(-1);	
					}
					
				}
			}
		if(t->tail->read == 0){

			t->current = t->tail;
			t->tail->read = 1;

			while((ds = readdir(dp))!= NULL  ){
				
				char *tmp = calloc(1,
					(strlen(t->current->dir_name)+(strlen(ds->d_name)+2)));


				checkIfNULLMEM(tmp);
				strcpy(tmp, t->current->dir_name);
				strcat(tmp,ds->d_name);

				if((lstat(tmp, &file_info)) ==-1){
					free(t);
					perror("stat");
					freeList(l,t);
					free(path);
					exit(-1);
				}

				//Check if file is a folder 
				if(S_ISDIR(file_info.st_mode) && !(S_ISLNK(file_info.st_mode))){
								
					if( (strncmp(ds->d_name, ".",1)!= 0) ){
						if( access(tmp,R_OK) == 0 ){
							addDirr(ds->d_name,t->current->dir_name,l,t);
							found_dir = TRUE;
						
							printInfo(optid,t,ds->d_name,keyword,file_info);
						}
						else{
								fprintf(stderr,"%s: Permission denied\n", tmp);
							}
					}
				}
				else if( (strcmp(keyword,ds->d_name)) == 0 ){
				
					printf("%s%s\n",t->current->dir_name,ds->d_name);
					
				}
				free(tmp);
			}
		}
		
		if( (closedir(dp)) == -1 ){
			
			free(t);
			freeList(l,t);	
			perror("closedir");
			free(path);
			exit(1);	
		}	
	}	
	free(t);
}

/*
Desc: Checks if the path name is lacking a backslash or not
Input: A path name 
Output: Corrected path name if it was needed,
	else none.
*/
void pathNameCorrection(char *p_name){
	
	if(p_name[strlen(p_name)-1] != '/'){
		strcat(p_name, "/");
	}
}

void printInfo(int optid,tracker *t,char* d_name,
											char *key,struct stat file_info){

	int optindex = optid;

	if((strncmp(d_name,key,(strlen(key))))== 0){
		printCase(optindex,t,key,file_info);
	}
}


void printCase(int optid,tracker *t, char *keyword,struct stat file_info){

	switch(optid){
		case 0:
			printf("%s%s\n",t->current->dir_name,keyword);
			break;
		case 1:
			if( S_ISDIR (file_info.st_mode) && !S_ISLNK(file_info.st_mode)){
				printf("%s%s\n",t->current->dir_name,keyword);
			}
			break;
		case 2:
			if( S_ISLNK (file_info.st_mode) ){
				printf("%s%s\n",t->current->dir_name,keyword);
			}
			break;
		case 3:
			if( S_ISREG (file_info.st_mode) ){
				printf("%s%s\n",t->current->dir_name,keyword);
			}
	}
}
