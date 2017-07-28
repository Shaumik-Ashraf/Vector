//vector.h 

/* defines a vector datatype API
 * - automatically allocates and resizes memory
 * - only stores ints
 * - 
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_
 
#include<stdlib.h>
 
//======type decleration======
typedef struct {
	int* array;
	size_t capacity;
	size_t length; 
} vector_t;
 
//========functions============

//prints error_msg to stderr and exits program
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
void vector_insert(vector_t* vec);

//insert element at index i, and shift other elements over by one
//grows if necessary
void vector_insert_at(vector_t* vec, int i);

//remove last element and return, shifts other elements over
int vector_remove(vector_t* vec);

//remove element at index i and return, shifts other elements over
int vector_remove_at(vector_t* vec, int i);

/** more functions for later
vector_scale
vector_add
vector_copy

 */

#endif 
 
