#include "common.h"
#include <inttypes.h>
#include <time.h>

void mem_read(uintptr_t block_num, uint8_t *buf);
void mem_write(uintptr_t block_num, const uint8_t *buf);

static uint64_t cycle_cnt = 0;

typedef struct 
{
  int valid_bit;  // 1合法， 0不合法
  int dirty_bit;  // 1修改， 0未修改
  uint8_t Block[64];  // 64B
  uint32_t tag;
}  Cache_block;

Cache_block Cache[64][4];  // 4*64*64 = 16KB

void cycle_increase(int n) { cycle_cnt += n; }

// TODO: implement the following functions

uint32_t cache_read(uintptr_t addr) {
  return 0;
}

void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
}

void init_cache(int total_size_width, int associativity_width) {
}

void display_statistic(void) {
}
