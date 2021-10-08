#include "histogram.jdiscipi.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int main() {
	// Initialize the array
	int values[N];
	int i;
	for(i = 0; i < N; i++) {
		double r = drand48();
		int val = (int) MAXVAL * r;
		values[i] = val;
	}
	return 0;
}


