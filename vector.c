//vector.c

#include<stdio.h>
#include<stdlib.h>
 

//========functions============

//prints error_msg to stderr and exits program
	
void _vector_error(char* error_msg) {
	fprintf(stderr, "Error: %s\n", error_msg);
	exit(1);
}

//constructors
vector_t* new_vector(int init_cap) {
	
	vector_t* ret;
	
	ret = (vector_t*)malloc( sizeof(vector_t) );
	if( ret==NULL ) {
		_vector_error("malloc failed in constructor");
	}
	
	(*ret).length = 0;
	ret->capacity = init_cap;
	ret->array = (int*)malloc( init_cap*sizeof(int) );
	if( ret->array==NULL ) {
		//free(ret);
		_vector_error("malloc failed for array");
	}
	
	return(ret);
}

//destroyer
void vector_kill(vector_t* vec) {
	
	free(vec->array);
	free(vec);
	
}

//print to screen
void vector_put(vector_t* vec) {
	
	int i;
	
	for(i=0; i<length; i++) {
		printf("%i\n", vec->array[i]);
	}
	
}

//reallocate to twice the current capacity
void _vector_grow(vector_t* vec) {
	
	int new_cap = vec->capacity * 2;
	
	vec->array = (int*)realloc(vec->array, new_cap*sizeof(int));
	if( vec->array == NULL ) {
		_vector_error("grow failed");
	}
	
	vec->capacity = new_cap;
	
}

//insert element at end
//grows if necessary
void vector_insert(vector_t* vec, int element) {
	
	if( vec->length == vec->capacity ) {
		_vector_grow(vec);
	}
	
	//arr[i] = 5;
	vec->array[vec->length] = element;
	vec->length++;
}

//insert element at index i, and shift other elements over by one
//grows if necessary
//note: i<length must be true
void vector_insert_at(vector_t* vec, int element, int i) {
	
	int temp;
	int j;
	int to_insert;
	
	if( vec->length == vec->capacity ) {
		_vector_grow(vec);
	}
	
	if( vec->length==0 ) {
		vector_insert(vec, element);
	}
	else {
		to_insert = element;
		for(j=i; j<vec->length; j++) {
			temp = vec->array[j];
			vec->array[j] = to_insert;
			to_insert = temp;
		}
		vec->array[j] = to_insert;
	}
	
}

//remove last element and return,
int vector_remove(vector_t* vec) {
	
	int ret;
	
	ret = vec->array[vec->length];
	vec->length--;
	
	return(ret);
}

//remove element at index i and return, shifts other elements over
int vector_remove_at(vector_t* vec, int i) {
	
	int ret;
	int j, temp, to_shift;
	
	ret = vec->array[i];
	for(j=i; j<array->length-1; j++) {
		vec->array //!!!!!!!! CONTINUE HERE
	}
	
}

 