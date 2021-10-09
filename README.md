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

## Results
| Algorithm | I1        | I2        | I3        | I4        | I5        | Average Runtime |
|-----------|-----------|-----------|-----------|-----------|-----------|-----------------|
| Serial    | 3.058000  | 3.098000  | 3.005000  | 3.308000  | 3.040000  | 3.1018          |
| Bad       | 77.890999 | 65.616997 | 76.075996 | 63.355000 | 76.143997 | 71.8165978      |
| Good      | 1.499000  | 1.476000  | 2.279000  | 3.976000  | 1.473000  | 2.1406          |

## TL;DR
The difference between serial and good is not noticable until N grows large or NUM_THREADS is increased. The program evaluates the equality of the histograms in its output
