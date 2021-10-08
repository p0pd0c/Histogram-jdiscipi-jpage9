typedef struct {
	int startIndex;  // first index in my region
	int endIndex;    // last indexc in my region
	int* histogram;  // global histogram
	pthread_mutex_t* mutex; // mutex for synchronization 
}	ThreadInfo;
#define N 1000000
#define NUM_THREADS 4
#define MAXVAL 256

