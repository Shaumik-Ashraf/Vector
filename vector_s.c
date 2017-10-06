#include<stdio.h>
#include"vector_s.h"
#include<stdlib.h>
#include<string.h>


static char* new_string(char* s) {
	char* ret;
	int size = strlen(s) + 1; 
	
	ret = malloc( size*sizeof(char) );  //rmbr, malloc memory can returned from functions
	if( ret==NULL ) {
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	
	strncpy(ret, s, size);
	
	return(ret);
}

void _vector_error(char* error_msg) {
	fprintf(stderr, "Error: %s\n", error_msg);
	exit(1);
}

vector_t* new_vector(int init_cap) {
	
	vector_t* ret;
	
	ret = (vector_t*)malloc( sizeof(vector_t) );
	if( ret==NULL ) {
		_vector_error("malloc failed in constructor");
	}
	
	(*ret).length = 0;
	ret->capacity = init_cap;
	ret->array = (char**)malloc( init_cap*sizeof(char*) );
	if( ret->array==NULL ) {
		//free(ret);
		_vector_error("malloc failed for array");
	}
	
	return(ret);
}

void vector_kill(vector_t* vec) {
	
	int i;
	
	for (i=0; i<(vec->length); i++) {
		free(vec->array[i]);
	}		
	free(vec->array); 
	free(vec);
	
}

void vector_insert(vector_t* vec, char* element) {

	if( vec->length == vec->capacity ) {
		_vector_grow(vec);
	}
	
	//arr[i] = 5;
	vec->array[vec->length] = new_string(element);
	vec->length++;
	
}

void vector_removelast(vector_t* vec) {
	
	free(vec->array[--(vec->length)]);
}

void vector_put(vector_t* vec) {
	
	int i;
	
	for(i=0; i<vec->length; i++) {
		printf("%s\n", vec->array[i]);
	}
	
}

void _vector_grow(vector_t* vec) {
	
	int new_cap = vec->capacity * 2;
	
	vec->array = (char**)realloc(vec->array, new_cap*sizeof(char*));
	if( vec->array == NULL ) {
		_vector_error("grow failed");
	}
	
	vec->capacity = new_cap;
	
}