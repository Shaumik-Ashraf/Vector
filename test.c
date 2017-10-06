//test.c

#include<stdio.h>
#include<stdio.h>
#include<stdio.h>

#include"vector.h"

int main(void) {
	
	vector_t* v;
	char buf[256];
	int x;
	int i;
	
	v = new_vector(2, &print_int);
	printf("Vector initialized\n");
	
	for(i=0; i<5; i++) {
		printf("Enter a int:");
		fgets(buf, 255, stdin);
		sscanf(buf, "%i", &x);
		
		vector_insert(v, x);
		printf("%i inserted\n", x);
		
	}
	printf("================\n");
	vector_put(v);
	
	vector_kill(v);
	return(0);
}
