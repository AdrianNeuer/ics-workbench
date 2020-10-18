#include <stdint.h>

int32_t A[64];

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
  else if (x - m >= m){
    uint64_t t = m;
    for (int i = 1; i <= 64; i++){
      t = t << 1;
      if (x == t){
        return 0;
      }
      else if (x < t){
        break;
      } 
      else {
        continue;
      }
    }
    t = t >> 1;
    return mod(x - t, m);
  }
  return 0;
}

void breakdown (uint64_t a) {
  for (int i = 0; i <= 63; i++) {
    A[i] = a & 1;
    a >>= 1;
  }
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  breakdown(a);
  uint64_t present = mod(b,m);
  uint64_t sum = 0;
  
  for (int i = 0; i <= 63; i++) {
    if (A[i] == 1) {
      if (sum + present < sum) {
        sum = mod (sum + present, m) + mod(-1ULL, m) + mod(1, m);
      }
      sum  = mod(sum, m);
    }
    if (present << 1 < present) {
      present = mod(present << 1, m) + mod(-1ULL, m) + mod(1, m);
    }
    else {
      present <<= 1;
    }
  }

  return mod(sum, m);
}
