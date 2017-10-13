//test.c

#include<stdio.h>
#include<stdio.h>
#include<stdio.h>

#include"vector.h"

int main(void) {
	
	vector_t* vec1;
	vector_t* vec2;
	vector_t* vec3;
	char buf[256];
	int ctr;
	int i;
	double d;
	
	vec1 = new_vector(2, &print_int, &size_int);
	vec2 = new_vector(2, &print_double, &size_double);
	vec3 = new_vector(2, &print_string, &size_string);
	printf("Vectors all initialized!\n");
	
	for(ctr=0; ctr<3; ctr++) {
		printf("Enter an int:");
		fgets(buf, 255, stdin);
		sscanf(buf, "%i", &i);
		
		vector_insert(vec1, &i);
	}
	
	for(ctr=0; ctr<3; ctr++) {
		printf("Enter a double:");
		fgets(buf, 255, stdin);
		sscanf(buf, "%lf", &d);
		
		vector_insert(vec2, &d);
	}
	
	for(ctr=0; ctr<3; ctr++) {
		memset(buf, 0, 255);
		printf("Enter a string:");
		fgets(buf, 255, stdin);
		
		vector_insert(vec3, buf);
	}
	
	printf("================\n");
	vector_put(vec1);
	vector_put(vec2);
	vector_put(vec3);
	
	printf("================\n");
	vector_kill(vec1);
	vector_kill(vec2);
	vector_kill(vec3);
	
	printf("Vectors freed!\n");
	
	return(0);
}
