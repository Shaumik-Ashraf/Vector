//vector - vector_s.h  

#ifndef _VECTOR_S_H_
#define _VECTOR_S_H_

#include<stdlib.h>

typedef struct {
	char** array;
	size_t capacity;
	size_t length;
}	vector_t;

void _vector_error(char* error_msg);

vector_t* new_vector(int init_cap);

void vector_kill(vector_t* vec);

void vector_insert(vector_t* vec, char* element);

void vector_removelast(vector_t* vec);

void vector_put(vector_t* vec);

void _vector_grow(vector_t* vec);

#endif