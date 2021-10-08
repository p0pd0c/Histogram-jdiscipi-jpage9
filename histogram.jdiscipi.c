#include "histogram.jdiscipi.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Initialize the array
int values[N];

// Declare methods
int tallySerial(int* histogram); 
void* tallyBad(void* param);

int main() {	
	// Make random values
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

	// Create data for threads
	pthread_mutex_t mutex;
	ThreadInfo t1data = {0, N/4, &histogram, &mutex};
	ThreadInfo t2data = {N/4 + 1, N/2, &histogram, &mutex};
	ThreadInfo t3data = {N/2 + 1, (3*N)/4, &histogram, &mutex};
	ThreadInfo t4data = {(3*N)/4 + 1, N, &histogram, &mutex};
	ThreadInfo threadData[] = {t1data, t2data, t3data, t4data};
	pthread_t tIds[NUM_THREADS];

	// Start threads
	for(i = 0; i < NUM_THREADS; i++) {
		pthread_t tId;
		tIds[i] = tId;
		pthread_create(&tIds[i], NULL, tallyBad, &threadData[i]);
	}

	// Wait for all threads
	for(i = 0; i < NUM_THREADS; i++) {
		pthread_join(tIds[i], NULL);
	}
	
	// Look at buckets
	for(i = 0; i < MAXVAL; i++) {
		printf("Bucket: %d\n", histogram[i]);
	}

	return 0;
}

// Define serial implementation
int tallySerial(int* histogram) {
	int i;
	for(i = 0; i < N; i++) {
		histogram[values[i]] += 1;
	}
	return 0;	
}

// Define bad implementation
void* tallyBad(void* param) {
	ThreadInfo* data = (ThreadInfo*) param;	
	int i;
	for(i = data->startIndex; i <= data->endIndex; i++) {
		pthread_mutex_lock(data->mutex);
		data->histogram[values[i]] += 1;
		pthread_mutex_unlock(data->mutex);
	}
	pthread_exit(0);
}
