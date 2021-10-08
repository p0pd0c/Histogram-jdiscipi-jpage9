#include "histogram.jdiscipi.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Initialize the array
int values[N];

int tallySerial(int* histogram) {
	int i;
	for(i = 0; i < N; i++) {
		histogram[values[i]] += 1;
	}
	return 0;	
}

int main() {
	int i;
	for(i = 0; i < N; i++) {
		double r = drand48();
		int val = (int) MAXVAL * r;
		values[i] = val;
	}

	// Initialize Histogram
	int histogram[MAXVAL];
	for(i = 0; i < MAXVAL; i++) {
		histogram[i] = 0;
	}
	// Run the serial histogram
	int result = tallySerial(histogram);
	// Look at buckets
	for(i = 0; i < MAXVAL; i++) {
		printf("Bucket: %d\n", histogram[i]);
	}
	return 0;
}


