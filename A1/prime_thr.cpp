// This is a placeholder for the "thread" procedure which you are to write
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <pthread.h>

using namespace std;
// Tests numbers for primality
// Where the n_i are numbers to be tested for primality
// Based on Java code written by Alan Kaminsky
// Ported to C++ by Scott B. Baden, UCSD, Dec. 28, 2010
//

#define FALSE 0
#define TRUE 1

double getTime();
double getTime(int DUMMY);
int isPrime(int64_t x);

// Shared globals, allocated before threads are spawned
extern int64_t *candidates;
extern double *timings;
extern int *primes;
extern int n;
extern int NT;
extern int elements_per_thread;
extern double t0;

// This is the function which is called by a newly created thread
void *prime_thr( void *arg )
{
    
    int64_t i = reinterpret_cast<int64_t>(arg);
    int tid = i;
    double t1 = -getTime(1);
    // this is the last thread
    if (tid == NT -1) {
      for (int j = tid * elements_per_thread; j < n; j++){
        if (isPrime(candidates[j])) {
          primes[j] = TRUE;
        }
      }
    } else {
      for (int j = tid * elements_per_thread; j < tid * elements_per_thread + elements_per_thread; j++){
        if (isPrime(candidates[j])) {
          primes[j] = TRUE;
        }
      }
    
    }
    t1 += getTime(1);
    t0 = t1;

    pthread_exit(NULL);
    return 0;
}
