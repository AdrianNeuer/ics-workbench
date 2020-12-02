#include <stdint.h>
#include <stdio.h>
#include <time.h>

int *sieve(int n);

int main() {
  int *primes = sieve(9999998);
  printf("%f s\n", (double)clock()/CLOCKS_PER_SEC);
  for (int *cur = primes, i = 0; *cur; cur++, i++) {
    printf("%8d", *cur);
    if (i % 8 == 7 || !*(cur + 1)) printf("\n");
  }
}
