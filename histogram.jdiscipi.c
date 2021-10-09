#include "histogram.jdiscipi.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

// Initialize the array
int values[N];

// Declare methods
int tallySerial(int* histogram); 
void* tallyBad(void* param);
void* tallyGood(void* param);

int main() {	
	// Make random values
	int i;
	for(i = 0; i < N; i++) {
		double r = drand48();
		int val = (int) MAXVAL * r;
		values[i] = val;
	}
	
	// Initialize time vals
	struct timeval t1, t2;
	float elapsedTime;
	// Time Serial
	// Initialize Serial Histogram
	int serialHistogram[MAXVAL];
	for(i = 0; i < MAXVAL; i++) {
		serialHistogram[i] = 0;
	}
	gettimeofday(&t1, NULL);
	tallySerial(serialHistogram);
	gettimeofday(&t2, NULL);
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; // sec to usec
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // usec to ms 
	printf("Serial time: %f\n", elapsedTime);


	// Time Bad
	// Initialize Bad Histogram
	int badHistogram[MAXVAL];
	for(i = 0; i < MAXVAL; i++) {
		badHistogram[i] = 0;
	}
	// Initialize Bad Data
	// Create data for threads
	pthread_mutex_t badMutex;
	ThreadInfo* badThreadData[NUM_THREADS];
	for(i = 1; i <= NUM_THREADS; i++) {
		ThreadInfo* threadDatum = malloc(sizeof(ThreadInfo));
		threadDatum->startIndex = (N * (i - 1)) / NUM_THREADS;
		threadDatum->endIndex = (N * i) / NUM_THREADS - 1; 
		threadDatum->histogram = badHistogram;
		threadDatum->mutex = &badMutex;
		badThreadData[i - 1] = threadDatum;
	}
	pthread_t tIds[NUM_THREADS];
	// Start timer
	gettimeofday(&t1, NULL);
	// Start threads
	for(i = 0; i < NUM_THREADS; i++) {
		pthread_t tId;
		tIds[i] = tId;
		pthread_create(&tIds[i], NULL, tallyBad, badThreadData[i]);
	}
	// Wait for all threads
	for(i = 0; i < NUM_THREADS; i++) {
		pthread_join(tIds[i], NULL);
	}
	gettimeofday(&t2, NULL);
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; // sec to usec
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // usec to ms 
	printf("Bad time: %f\n", elapsedTime);
	
	// Time Good
  // Initialize Good Histogram
  int goodHistogram[MAXVAL];
  for(i = 0; i < MAXVAL; i++) {
    goodHistogram[i] = 0;
  }
  // Initialize Good Data
  // Create data for threads
  pthread_mutex_t goodMutex;
  ThreadInfo* goodThreadData[NUM_THREADS];
  for(i = 1; i <= NUM_THREADS; i++) {
    ThreadInfo* threadDatum = malloc(sizeof(ThreadInfo));
    threadDatum->startIndex = (N * (i - 1)) / NUM_THREADS;
    threadDatum->endIndex = (N * i) / NUM_THREADS - 1;
    threadDatum->histogram = goodHistogram;
    threadDatum->mutex = &goodMutex;
    goodThreadData[i - 1] = threadDatum;
  }
  pthread_t tIdsGood[NUM_THREADS];
  // Start timer
  gettimeofday(&t1, NULL);
  // Start threads
  for(i = 0; i < NUM_THREADS; i++) {
    pthread_t tId;
    tIdsGood[i] = tId;
    pthread_create(&tIdsGood[i], NULL, tallyGood, goodThreadData[i]);
  }
  // Wait for all threads
  for(i = 0; i < NUM_THREADS; i++) {
    pthread_join(tIds[i], NULL);
  }
  gettimeofday(&t2, NULL);
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; // sec to usec
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // usec to ms 
  printf("Good time: %f\n", elapsedTime);
	
	// Test equality of all histograms
	int dataIsGood = 1;
	for(i = 0; i < MAXVAL; i++) {
		if(serialHistogram[i] != badHistogram[i] || serialHistogram[i] != goodHistogram[i] || badHistogram[i] != goodHistogram[i]) {
			dataIsGood = 0;
		}
	}
	if(dataIsGood) {
		printf("All histograms are equal\n");
	} else {
		printf("Histograms are not equal\n");
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

// Define good implementation
void* tallyGood(void* param) {
	ThreadInfo* data = (ThreadInfo*) param;	
	int localHistogram[MAXVAL];
	int i;
	for(i = 0; i < MAXVAL; i++) {
		localHistogram[i] = 0;
	}
	for(i = data->startIndex; i < data->endIndex; i++) {
		localHistogram[values[i]] += 1;
	}
	pthread_mutex_lock(data->mutex);
	for(i = 0; i <= MAXVAL; i++) {
		data->histogram[i] += localHistogram[i];
	}
	pthread_mutex_unlock(data->mutex);
	pthread_exit(0);
}
