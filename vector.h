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
	void** array;
	size_t capacity;
	size_t length;
	void (*print)(void* x);
	unsigned int (*size)(void* x);
} vector_t;
 
/* funciton pointer quick demo
int* foo(int arg);
int main() {
	int* (*func_p)(int arg);
	func_p = &foo;
	foo();
	func_p();
}
*/

//======helper functions=======
void print_int(void* x);
void print_double(void* x);
void print_string(void* x);

unsigned int size_int(void*);
unsigned int size_double(void*);
unsigned int size_string(void*);

/* In C Code
  v.print = &print_int;
*/
 
//========functions============

//prints error_msg to stderr and exits program
void _vector_error(char* error_msg);

//constructors
vector_t* new_vector(int init_cap, void (*print_f)(void* x), unsigned (*size_f)(void* x));

//destroyer
void vector_kill(vector_t* vec);

//print to screen
void vector_put(vector_t* vec);

//reallocate to twice the current capacity
void _vector_grow(vector_t* vec);

//insert element at end
//grows if necessary
void vector_insert(vector_t* vec, void* element);

//remove last element and return, shifts other elements over
void vector_remove_last(vector_t* vec);

///TODO
void vector_sort(vector_t* vec);

#endif 
 
