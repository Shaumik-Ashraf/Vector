//strings in C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>  //no strdup() or new_string(), but has strcpy() and strlen()

char* new_string(char* s);

int main(int argc, char** argv) {
	
	char* literal = "The bus fricking drove straight past my stop today.";
	char buffer[256];
	char* preferred;
	
	strncpy(buffer, literal, 255);
	
	preferred = new_string(literal);  //this creates a string
	
	printf("literal: %s\n", literal);
	printf("buffer: %s\n", buffer);
	printf("preferred: %s\n", preferred);
	
	//literal can't be modified, but the others can
	buffer[9] = '*';
	buffer[10] = '*';
	preferred[9] = '*';
	preferred[10] = '*';
	
	printf("\nAfter modifications===========\n\n");
	printf("literal: %s\n", literal);
	printf("buffer: %s\n", buffer);
	printf("preferred: %s\n", preferred);
	
	free(preferred);   //don't forget this
	
	return(0);
}

char* new_string(char* s) {
	char* ret;
	int size = strlen(s) + 1; //add 1 for '\0'
	
	ret = malloc( size*sizeof(char) );  //rmbr, malloc memory can returned from functions
	if( ret==NULL ) {
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	
	strncpy(ret, s, size);
	
	return(ret);
}