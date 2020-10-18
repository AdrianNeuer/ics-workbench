#include <stdint.h>

uint64_t mod(uint64_t x, uint64_t m) {
  if (x < m){
    return x;
  }
  else if (x == m){
    return 0;
  }
  else if(x - m < m){
    return x - m;
  }
  else if (x - m == m){
    return 0;
  }
  else
  {
    uint64_t t = m;
    for (int i = 1; i <= 64; i++){
      t = t << 1;
      if (x == t){
        return 0;
      }
      if (x < t << 1) {
        break;
      }
    }
    return mod(x - t, m);
  }
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  uint64_t present = mod(b,m);
  uint64_t sum = 0;
  
  while(a) {
    if ((a & 1) == 1) {
      if (sum + present < sum) {
        sum = mod (sum + present, m) + mod(mod(-1ULL, m) + mod(1, m), m);
      }
      sum  = mod(sum, m);
    }
    if ((present << 1) < present) {
      present = mod(present << 1, m) + mod(mod(-1ULL, m) + mod(1, m), m);
    }
    else {
      present <<= 1;
    }
    a >>= 1;
  }

  return mod(sum, m);
}
