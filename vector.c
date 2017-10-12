//vector.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
#include"vector.h"

//=========helper================ 
void print_int(void* x) {
	int* p = (int*)x;
	printf("%i", *p);
}

void print_double(void* x) {
	double* p = (double*)x;
	printf("%lf", *p);	
}

void print_string(void* x) {
	char* p = (char*)x;
	printf("%s", p);	
} 

//returns size of element (not pointer!)
unsigned int size_int(void* x) {
	return( sizeof(int) );
}

//returns size of element (not pointer!)
unsigned int size_double(void* x) {
	return( sizeof(double) );
}

//returns size of element (not pointer!)
unsigned int size_string(void* x) {
	return( strlen((char*)x)+1 );
}


//========functions============

//prints error_msg to stderr and exits program
	
void _vector_error(char* error_msg) {
	fprintf(stderr, "Error: %s\n", error_msg);
	exit(1);
}

//constructors
vector_t* new_vector(int init_cap, void (*print_f)(void* x), unsigned int (*size_f)(void*)) {
	
	vector_t* ret;
	
	ret = (vector_t*)malloc( sizeof(vector_t) );
	if( ret==NULL ) {
		_vector_error("malloc failed in constructor");
	}
	
	(*ret).length = 0;
	ret->capacity = init_cap;
	ret->array = (int*)malloc( init_cap*size_f() );
	if( ret->array==NULL ) {
		//free(ret);
		_vector_error("malloc failed for array");
	}
	
	ret->print = print_f;
	ret->size = size_f;
	
	return(ret);
}

//destroyer
void vector_kill(vector_t* vec) {
	
	while( vec->length ) {
		free( vec->array[vec->length] );
		vec->length--;
	}
	free(vec->array);
	free(vec);
	
}

//print to screen
void vector_put(vector_t* vec) {
	
	int i;
	
	for(i=0; i<vec->length; i++) {
		vec->print( &(vec->array[i]) );
		printf("\n");
	}
	
}

//reallocate to twice the current capacity
void _vector_grow(vector_t* vec) {
	
	int new_cap = vec->capacity * 2;
	
	vec->array = (int*)realloc(vec->array, new_cap*sizeof(void*));
	if( vec->array == NULL ) {
		_vector_error("grow failed");
	}
	
	vec->capacity = new_cap;	
}

//insert element at end
//grows if necessary
void vector_insert(vector_t* vec, void* element) {
	
	void* copy;
	
	if( vec->length == vec->capacity ) {
		_vector_grow(vec);
	}
	
	copy = malloc( vec->size(element) );
	memcpy(copy, element, vec->size(element));
	
	vec->array[vec->length] = copy;
	vec->length++;
}
	

//remove and free last element
void vector_remove_last(vector_t* vec) {
	void* tofree;
	
	tofree = vec->array[vec->length];
	vec->length--;
	
	free(tofree);
}


 