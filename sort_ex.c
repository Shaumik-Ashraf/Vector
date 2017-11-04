//sort example

#include<stdio.h>
#include<stdlib.h>  //contains qsort()
#include<time.h>
#include<string.h>  //contains int strcmp(char* s1, char* s2)

//sorting strings example

char* new_string(char* s);
int my_strcmp(void* a, void* b);

int main(void) {
	
	int len = 5;
	char *str_array[len];
	int (*comparer)(void* a, void* b);
	int i;
	
	//create the string array
	str_array[0] = new_string("i");
	str_array[1] = new_string("fuqd");
	str_array[2] = new_string("up");
	str_array[3] = new_string("my");
	str_array[4] = new_string("exam");
	
	//qsort()
	comparer = &my_strcmp;
	qsort(str_array, len, sizeof(char*), comparer);
	
	//print string array
	for(i=0; i<len; i++) {
		printf("%s\n", str_array[i]);
	}
	
	//destroy string array
	for(i=0; i<len; i++) {
		free(str_array[i]);
	}
	
	return(0);
}

char* new_string(char* s) {
	char* ret = malloc(strlen(s)+1);
	if( !ret ) {
		fprintf(stderr, "Error\n");
		exit(1);
	}
	strncpy(ret, s, strlen(s)+1);
	
	return(ret);
}

int my_strcmp(void* a, void* b) {
	return( strcmp( *(char**)a, *(char**)b ) );
}

/* Sorting double example
int dblcmp(void* a, void* b);

int main(int argc, char** argv) {

	srand(time(NULL));

	double arr[5]; 
	int i;
	double rand_val;
	
	printf("rand array:");
	for(i=0; i<5; i++) {
		rand_val = (rand()%100 + 100.00)/10.0;
		arr[i] = rand_val;
		printf("%.2lf ", (arr[i]));
	}
	printf("\n");

	//printf("cmp [0] and [1]:%i\n", dblcmp(arr,arr+1)); just testing cmp function
	qsort(arr, 5, sizeof(double), &dblcmp);
	
	printf("sorted array:");
	for(i=0; i<5; i++) {
		printf("%.2lf ", (arr[i]));
	}
	printf("\n");
	
	return(0);
}

int dblcmp(void* a, void* b) {

	double d1 = *((double*)a);
	double d2 = *((double*)b);

	if( d1>d2 ) {
		return(1);
	}
	else if( d1==d2 ) {
		return(0);
	}
	else {
		return(-1);
	}
}
*/