# Histogram-jdiscipi-jpage9
Tests a variety of implementations for a histogram.

1. Serial Implementation (no threading)
2. Bad Implementation (NUM_THREADS threads, locking for each write to global histogram)
3. Good Implementation (NUM_THREADS threads, each thread owns its own histogram)

## Compile
```console
gcc histogram.jdiscipi.c -lpthread
```
## Run 
```console
./a.out
```
