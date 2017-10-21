//sort example
//BUG

#include<stdio.h>
#include<stdlib.h>  //contains qsort()
#include<time.h>

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
