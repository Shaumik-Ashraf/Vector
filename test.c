//test.c

#include<stdio.h>

#include"vector.h"

int main(void) {
	
	vector_t* v;
	char buf[256];
	int x;
	int i;
	
	v = new_vector(2);
	
	for(i=0; i<5; i++) {
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