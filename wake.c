//wake.c
//amalgamation file of "wake project"
//wake - windows make; substitutes make with ANSI C 89 only
//efficiency scraped!
//use: wake <MAKEFILENAME>

/* Progress:
 * 
 * Algo - read recipe lines from file into a string list, 
 *        then execute in reverse order
 *
 * compiles and runs so far!
 * file successfully loaded to buffer - maybe make stringio struct?
 * string list implemented but not yet tested
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

struct node {
	char* s;
	struct node* next;
	struct node* prev;
};

typedef struct list {
	struct node* head;
	struct node* tail;
	struct node* iter;
	int iter_pos;
	int len;
} list_t;

const char* RECIPE_CHARSET = "-qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890_. \t\r\n";
const char* BLANK_CHARSET = " \t\v\r\n";

//check if file exists and is readable
static int checkfile(char* filename) {
	FILE* fp;

	fp = fopen(filename, "r");
	if( fp==NULL ) {
		return( 0 );
	}
	else {
		fclose(fp);
		return( 1 );
	}
}

//init string list
static list_t* new_list() {
	list_t* ret = (list_t*)malloc(sizeof(list_t));
	
	if( ret==NULL ) {
		fprintf(stderr, "wake: malloc error\n");
		exit(1);
	}
	
	ret->head = NULL;
	ret->tail = NULL;
	ret->iter = NULL;
	ret->iter_pos = -1;
	ret->len = 0;
	//printf("wake: list %x initiated\n", ret);
	
	return(ret);
}

static char* new_string(char* s) {
	int len = strlen(s)+1;
	char* ret = (char*)malloc(len*sizeof(char*));

	if( !ret ) {
		fprintf(stderr, "wake: malloc error\n");
		exit(1);
	}
	strncpy(ret, s, len);

	return(ret);
}

//adds DUPLICATE of string to list provided
static void add_string(list_t* lp, char* s) {
	
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	//printf("adding %s to list %x\n", s, lp);
	
	if( new_node == NULL ) {
		fprintf(stderr, "wake: malloc error\n");
		exit(1);
	}
	new_node->s = new_string(s);
	new_node->next = NULL;
	new_node->prev = NULL;
	
	if( lp->head == NULL ) {
		lp->head = new_node;
		lp->tail = new_node;
		lp->iter = new_node;
		lp->iter_pos = 0;
		lp->len = 1;
	}
	else {
		lp->tail->next = new_node;
		new_node->prev = lp->tail;
		lp->tail = new_node;
		lp->len++;
	}
	
}

//return ALIAS of string at index
static char* get_string(list_t* lp, int i) {
	
	struct node* nav;
	int j=0;
	
	//assuming in-bounds
	if( i==0 ) {
		return( lp->head->s );
	}
	else if( i==lp->len-1 ) {
		return( lp->tail->s );
	}
	else if( i == lp->iter_pos ) {
		return( lp->iter->s );
	}
	else if( i == lp->iter_pos-1 ) {
		lp->iter = lp->iter->prev;
		lp->iter_pos--;
		return( lp->iter->s );
	}
	else if( i == lp->iter_pos+1 ) {
		lp->iter = lp->iter->next;
		lp->iter_pos++;
		return( lp->iter->s );
	}
	else {
		nav = lp->head;
		while( j<i ) {
			nav = nav->next;
			j++;
		}
		lp->iter = nav;
		lp->iter_pos = j;
		return( nav->s );
	}
	
}

//destroy list and all its nodes and strings
static void free_list(list_t* lp) {
	
	struct node* nav = lp->head;
	int i;
	
	for(i=0; i<lp->len-1; i++) {
		free( nav->s );
		nav = nav->next;
		free( nav->prev );
	}
	free(lp->tail);
	free(lp);
	
}

//returns true if all chars in line also occur in set
static int is_set(char* line, char* set) {
	for(; *line!='\0'; line++) {
		if( strchr(set, *line)==NULL ) {
			return(0);
		}
	}
	return( 1 );
}

static int is_recipe_line(char* line) {
	return( is_set(line, RECIPE_CHARSET) && !is_set(line, BLANK_CHARSET) );
}


static int get_file_size(char* path) {
	FILE* fp = fopen(path, "r");
	int ret;
	
	fseek(fp, 0L, SEEK_END);
	ret = (int)ftell(fp);
	fclose(fp);
	
	return(ret);
}

int main(int argc, char** argv) {

	FILE* fp;
	char filenam[256];
	char filebuf[5000];
	char linebuf[256];
	int filesize;
	list_t* recipe;
	int i, j;
	
	//obtain filename
	if( argc < 2 ) {
		printf("wake: no file specified\n");
		if( checkfile("makefile") ) {
			printf("wake: assuming file \"makefile\"\n");
			strcpy(filenam, "makefile");
		}
		else if( checkfile("Makefile") ) {
			printf("wake: assuming file \"Makefile\"\n");
			strcpy(filenam, "Makefile");
		}
		else if( checkfile("MAKEFILE") ) {
			printf("wake: assuming file \"MAKEFILE\"\n");
			strcpy(filenam, "MAKEFILE");
		}
		else {
			printf("wake: no file found\n");
			printf("wake: exit failure\n");
			return( EXIT_FAILURE );
		}
	}
	else if( checkfile(argv[1])==0 ) {
		printf("wake: filename %s not found\n", argv[1]);
		printf("wake: exit failure\n");
		return( EXIT_FAILURE );
	}
	else {
		strcpy(filenam, argv[1]);
		printf("wake: file name %s\n", filenam);
	}

	recipe = new_list();
	filesize = get_file_size(filenam);
	//printf("filesize: %i\n", filesize);
	memset(filebuf, 0, 5000*sizeof(char));
	memset(linebuf, 0, 256*sizeof(char));
	
	//load file recipe lines to string list
	fp = fopen(filenam, "r");
	fread(filebuf, 4999, sizeof(char), fp);
	printf("wake: file loaded to buffer\n");
	//printf("file buf:\n%s\n\n", filebuf);
	fclose(fp);
	
	//copy char by char here!!
	for(i=0, j=0; i<filesize; i++) {
		//printf("at: %c\n", filebuf[i]);
		if( filebuf[i]=='\n' ) {
			linebuf[j] = '\0';
			//printf("testing line: %s\n", linebuf);
			if( is_recipe_line(linebuf) ) {
				add_string(recipe, linebuf);
			}
			memset(linebuf, 0, 256*sizeof(char));
			j = 0;
		}
		else {
			linebuf[j] = filebuf[i];
			j++;
		}
	}
	
	///*
	//lines extracted
	printf("printing extrated list:=====================\n");
	for(i=0; i<recipe->len; i++) {
		printf("wake: command extracted: %s\n", get_string(recipe,i));
	}
	
	//free_list(recipe); return(0);
	//*/
	
	for(i=recipe->len-1; i+1; i--) {
		printf("wake: calling: %s\n", get_string(recipe,i));
		if( system( get_string(recipe, i) )!=0 ) {
			printf("wake: error: %s\n", get_string(recipe,i));
			exit( EXIT_FAILURE );
		}
	}
	
	free_list(recipe);
	printf("wake: exit success\n");
	return( EXIT_SUCCESS );
}



