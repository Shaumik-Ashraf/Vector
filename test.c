//test.c

#include<stdio.h>
#include<stdio.h>
#include<stdio.h>

#include"vector_d.h"

int main(void) {
	
	vector_t* v;
	char buf[256];
	double x;
	int i;
	
	v = new_vector(2);
	printf("Vector initialized\n");
	
	for(i=0; i<5; i++) {
		printf("Enter an int/double:");
		fgets(buf, 255, stdin);
		sscanf(buf, "%lf", &x);
		
		vector_insert(v, x);
		printf("%lf inserted\n", x);
		
	}
	printf("================\n");
	vector_put(v);
	
	vector_kill(v);
	return(0);
}
