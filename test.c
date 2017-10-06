//test.c

#include<stdio.h>
#include<stdio.h>
#include<stdio.h>

#include"vector_s.h"

int main(void) {
	
	vector_t* v;
	char buf[256];
	//double x;
	int i;
	
	v = new_vector(2);
	printf("Vector initialized\n");
	
	for(i=0; i<5; i++) {
		printf("Enter a string:");
		fgets(buf, 255, stdin);
		
		vector_insert(v, buf);
		printf("%s inserted\n", buf);
		
	}
	printf("================\n");
	vector_put(v);
	
	vector_kill(v);
	return(0);
}
