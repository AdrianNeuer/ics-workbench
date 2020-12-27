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
  asm(
    "mov $0x0, %%ecx\n"
    "mov $0x0, %%rbx\n"
    "loop: mov %1, %%rdx\n"
    "shr %%cl, %%rdx\n"
    "and $0x1, %%rdx\n"
    "add %%rdx, %%rbx\n"
    "add $0x1, %%ecx\n"
    "cmp $0x40, %%ecx\n"
    "jne loop\n"
    "mov %%ebx, %0\n"
    : "=r" (s)
    : "r" (x)
    : "cc", "%ecx", "%rbx", "%rdx" 
  );
  
  return s;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {

  asm(
    "lloop: cmp $0, %%rcx\n"
    "jge end\n"
    "movzb (%%rsi), %%eax\n"
    "mov %%al, %%rdi\n"
    "add $1, %%rsi\n"
    "add $1, %%rdi\n"
    "sub $1, %%rcx\n"
    "jmp lloop\n"
    "end:"
    :"=D" (dest)
    :"S" (src), "c" (n), "m" (n)
    :"cc"
  );

  return dest;
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}
