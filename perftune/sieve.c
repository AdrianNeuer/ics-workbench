#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define N 10000000

static bool is_prime[N];
static int  primes[N];

int *sieve(int n) {
  assert(n + 1 < N);
  for (int i = 0; i <= n; i++)
    is_prime[i] = true;
  int i = 2
  while (i <= n) {
    if(is_prime[i]){
      for (int j = i + i; j <= n; j += i) {
        is_prime[j] = false;
      }
    }
    if (i==2){
      i++;
    }
    else
    {
      i += 2; 
    }
  }

  int *p = primes;
  for (int i = 2; i <= n; i++)
    if (is_prime[i]) {
      *p++ = i;
    }
  *p = 0;
  return primes;
}
