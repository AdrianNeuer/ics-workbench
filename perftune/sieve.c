#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define N 10000000

static bool is_prime[N];
static int  primes[N];

int *sieve(int n) {
  for (int i = 3; i <= n; i += 2)
    is_prime[i] = true;

  for (int i = 3; i <= n; i+=2) {
    if(is_prime[i]){
      for (int j = i + 2*i; j <= n; j += 2*i) {
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
