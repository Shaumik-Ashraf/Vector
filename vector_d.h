//vector_d.h

#ifndef _VECTOR_D_H_
#define _VECTOR_D_H_
 
#include<stdlib.h>
 
//======type declaration======
typedef struct {
	double* array;
	size_t capacity;
	size_t length; 
} vector_t;

void _vector_error(char* error_msg);

//constructors
vector_t* new_vector(int init_cap);
//destroyer
void vector_kill(vector_t* vec); 

//print to screen
void vector_put(vector_t* vec);
//reallocate to twice the current capacity
void _vector_grow(vector_t* vec);

//insert element at end
//grows if necessary
void vector_insert(vector_t* vec, double element); 

//insert element at index i, and shift other elements over by one
//grows if necessary
//note: i<length must be true
void vector_insert_at(vector_t* vec, double element, int i); 

//remove last element and return,
int vector_remove(vector_t* vec);

//remove element at index i and return, shifts other elements over
int vector_remove_at(vector_t* vec, int i); 

#endif 
