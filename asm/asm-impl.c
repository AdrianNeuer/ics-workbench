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
    "lloop: movzb (%%rsi), %%eax\n"
    "movl %%eax, (%%rdi)\n"
    "add $1, %%rsi\n"
    "add $1, %%rdi\n"
    "sub $1, %%rcx\n"
    "cmp $0, %%rcx\n"
    "jne lloop\n"
    :"=D" (dest)
    :"S" (src), "c" (n), "m" (n)
    :"cc", "eax"
  );

  return dest;
}

int asm_setjmp(asm_jmp_buf env) {
  /*asm volatile (
    "push %%rbp\n"
    "mov %%rsp, %%rbp\n"
    "mov %%rdi, %%rax\n" //rdi = env
    "mov %%rbx, (%%rax)\n"
    "mov %%rcx, 8(%%rax)\n"
    "mov %%rdx, 16(%%rax)\n"
    "mov %%rsi, 24(%%rax)\n"
    "mov (%%rbp), %%rdi\n"
    "mov %%rdi, 32(%%rax)\n"
    "mov (%%rsp), %%rdi\n"
    "mov %%rdi, 40(%%rax)\n"
    "mov 8(%%rbp), %%rdi\n"
    "mov %%rdi, 48(%%rax)\n"
    "pop %%rbp\n"
    "ret\n"
    :
    :
    :"rax", "rbp"
  );*/
  asm volatile(
      ".globl setjmp;"
      "setjmp:;"
      "push %%rbp;"
      "mov %%rsp,%%rbp;"
      "mov %%rdi,%%rax;"//x86-64用寄存器传递参数，rdi就是env
      "mov %%rbx,(%%rax);"//env[0]=rbx;
      "mov %%rcx,8(%%rax);"//env[1]=rcx;
      "mov %%rdx,16(%%rax);"//env[2]=rdx;
      "mov %%rsi,24(%%rax);"//env[3]=rsi;
      "mov (%%rbp),%%rdi;"
      "mov %%rdi,32(%%rax);"//env[4]=rbp;
      "lea 16(%%rbp),%%rdi;"
      "mov %%rdi,40(%%rax);"//env[5]=rsp;
      "mov 8(%%rbp),%%rdi;"
      "mov %%rdi,48(%%rax);"//env[6]=pc;
      "xor %%rax,%%rax;"
      "pop %%rbp;"
      "ret;"
      :
      :
      :
  );
  return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
  asm volatile(
    "mov %%esi, %%eax\n" //esi = val
    "test %%eax, %%eax\n"
    "cmp $0, %%eax\n"
    "jne llloop\n"
    "inc %%eax\n"
    "llloop: mov (%%rdi),%%ebx\n"
    "mov 8(%%rdi),%%rcx;\n"
    "mov 16(%%rdi),%%rdx\n"
    "mov 24(%%rdi),%%rsi\n"
    "mov 32(%%rdi),%%rbp\n"
    "mov 40(%%rdi),%%rsp\n"
    "jmp *48(%%rdi)\n"
    :
    :
    : "eax"
  );
}
