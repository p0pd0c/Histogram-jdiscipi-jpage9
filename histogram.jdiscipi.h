#include <pthread.h>

typedef struct {
	int startIndex;  // first index in my region
	int endIndex;    // last indexc in my region
	int* histogram;  // global histogram
	pthread_mutex_t* mutex; // mutex for synchronization 
}	ThreadInfo;
#define N 100000000
#define NUM_THREADS 16
#define MAXVAL 256

