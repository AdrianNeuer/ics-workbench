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
      if ((t << 1) > t){
        t = t << 1;
        if (x == t){
          return 0;
        }
        if (x < t << 1) {
          break;
        }
      }
      else {
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
        uint64_t fir = mod (sum + present, m);
        uint64_t sec = mod (mod(-1ULL, m) + mod(1, m), m);
        while(fir + sec < fir){
          fir = mod(fir + sec, m);
          sec = mod(mod(-1ULL, m) + mod(1, m), m);
        }
        sum = fir + sec;
      }
      else {
        sum = sum + present;
      }
      sum  = mod(sum, m);
    }
    if ((present << 1) < present) {
      uint64_t one = mod(present << 1, m);
      uint64_t two = mod(mod(-1ULL, m) + mod(1, m), m);
      while(one + two < one){
      one = mod(one + two, m);
      two = mod(mod(-1ULL, m) + mod(1, m), m);
      }
      present  = one + two;
    }
    else {
      present <<= 1;
    }
    a >>= 1;
  }

  return mod(sum, m);
}
