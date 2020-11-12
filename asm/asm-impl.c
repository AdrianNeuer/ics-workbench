#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
  int64_t z;
  asm(
    "lea (%1, %2, 1), %0"
    : "=r" (z)
    : "r" (a), "r" (b)
  );
  return z;
}

int asm_popcnt(uint64_t x) {
  int s = 0;
  //for (int i = 0; i < 64; i++) {
  //  if ((x >> i) & 1) s++;
  //}
  asm(
    "mov $0x0, %%ecx\n"
    "mov %0, %%eax\n"
    "loop: mov %1, %%rdx\n"
    "shr %%cl, %%rdx\n"
    "and $0x1, %%rdx\n"
    "add %%edx, %%eax\n"
    "add $0x1, %%ecx\n"
    "cmp 0x40, %%ecx\n"
    "jne loop\n"
    : "=r" (s)
    : "r" (x)
  );
  return s;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  return memcpy(dest, src, n);
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}
