#include "common.h"
#include <inttypes.h>

void mem_read(uintptr_t block_num, uint8_t *buf);
void mem_write(uintptr_t block_num, const uint8_t *buf);

static uint64_t cycle_cnt = 0;

typedef struct 
{
  bool valid_bit;  // true已写入， false未写入
  bool dirty_bit;  // true修改， false未修改
  uint8_t Block[64];  // 64B
  uint32_t tag;
}  Cache_block;

Cache_block Cache[64][4];  // 4*64*64 = 16KB  size可以修改，此处为了适配main.c中的初始化

void cycle_increase(int n) { cycle_cnt += n; }

// TODO: implement the following functions

uint32_t cache_read(uintptr_t addr) {
  bool is_hit = false;
  bool empty;

  uint32_t tag = (addr >> 12) & 0xff;  //  标记 
  uint32_t group_num = (addr >> 6) & 0x3f;  // 组号
  uint32_t block_num = addr & 0x3f;  // 内存块内地址

  uint32_t *ret;

  for (int i = 0; i < 4; i++){
    if (Cache[group_num][i].tag == tag && Cache[group_num][i].valid_bit == true){
      ret = (void *)(Cache[group_num][i].Block);
      is_hit = true;
      break;
    }
  }

  if (is_hit == false){
    empty = false;
    for (int i = 0; i < 4; i++){
      if(Cache[group_num][i]. valid_bit == false){
        empty = true;
        mem_read(addr >> 6, Cache[group_num][i].Block);
        Cache[group_num][i].tag = tag;
        Cache[group_num][i].valid_bit = true;
        Cache[group_num][i].dirty_bit = false;
        ret = (void *) Cache[group_num][i].Block;
        break;
      }
    }
    if (empty == false){
      int chose_place = rand() % 4;
      if (Cache[group_num][chose_place].dirty_bit == true){
        mem_write(Cache[group_num][chose_place].tag << 6 | group_num, Cache[group_num][chose_place].Block);
      }
      mem_read(addr >> 6, Cache[group_num][chose_place].Block);
      Cache[group_num][chose_place].tag = tag;
      Cache[group_num][chose_place].valid_bit = true;
      Cache[group_num][chose_place].dirty_bit = false;
      ret = (void *) Cache[group_num][chose_place].Block;
    }
  }
  return *ret;
}

void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
  bool is_hit = false;
  bool empty;

  uint32_t tag = (addr >> 12) & 0xff;  // 标记
  uint32_t group_num = (addr >> 6) & 0x3f;  // 组号
  uint32_t block_num = addr & 0x3f;  // 内存块内地址

  for (int i = 0; i < 4; i++){
    if (Cache[group_num][i].tag == tag && Cache[group_num][i].valid_bit == true){
      is_hit = true;
      uint32_t *place = (void *)(Cache[group_num][i].Block);
      *place = (*place & ~wmask) | (data & wmask);
    }
  }
  if (is_hit == false){
    empty = false;
    for (int i = 0; i < 4; i++){
      if(Cache[group_num][i]. valid_bit == false){
        empty = true;
        mem_read(addr >> 6, Cache[group_num][i].Block);
        uint32_t *place = (void *)(Cache[group_num][i].Block);
        *place = (*place & ~wmask) | (data & wmask);
        Cache[group_num][i].tag = tag;
        Cache[group_num][i].valid_bit = true;
        Cache[group_num][i].dirty_bit = false;
        mem_write(addr >> 6, Cache[group_num][i].Block);
        break;
      }
    }
    if (empty == false){
      int chose_place = rand() % 4;
      if (Cache[group_num][chose_place].dirty_bit == true){
        mem_write(Cache[group_num][chose_place].tag << 6 | group_num, Cache[group_num][chose_place].Block);
      }
      mem_read(addr >> 6, Cache[group_num][chose_place].Block);
      uint32_t *place = (void *)(Cache[group_num][chose_place].Block);
      *place = (*place & ~wmask) | (data & wmask);
      Cache[group_num][chose_place].tag = tag;
      Cache[group_num][chose_place].valid_bit = true;
      Cache[group_num][chose_place].dirty_bit = false;
      mem_write(addr >> 6, Cache[group_num][chose_place].Block);
    }
  }
}

void init_cache(int total_size_width, int associativity_width) {
  int tol_size = 1 << total_size_width;  //  cache总大小
  int association = 1 << associativity_width;  //  cache关联度大小，也即每组行数

  for(int i = 0; i < tol_size / BLOCK_SIZE / association; i ++)
    for (int j = 0; j < association; j ++){
      Cache[i][j].valid_bit = false;
      Cache[i][j].dirty_bit = false;
    }
}

void display_statistic(void) {
}
