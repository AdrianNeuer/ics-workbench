#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

#define N 10000000

static bool is_prime[N];
static int  primes[N];

int *sieve(int n) {
  for (int i = 3; i <= n; i += 2)
    is_prime[i] = true;

  for (int i = 3; i <= n/4; i+=2) {
    if(is_prime[i]){
      for (int j = i + (i << 1); j <= n; j += (i << 1)) {
        is_prime[j] = false;
      }
    }
  }

  int *p = primes;
  *p++ = 2;
  for (int i = 3; i <= n; i+=2)
    if (is_prime[i]) {
      *p++ = i;
    }
  *p = 0;
  return primes;
}
