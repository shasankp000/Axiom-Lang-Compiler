#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H
#include "lexer_node.h"

struct PoolSlot {
  int slot_index;
  int in_use;
  struct LexerNode node;  
};

struct MemoryPool {
  int cursor_val;
  int pool_size;
  struct PoolSlot *slots;
};

void fill_pool(struct MemoryPool *pool);

void allocate(struct MemoryPool *pool, char c);

void release(struct MemoryPool *pool, int slot);

void report(struct MemoryPool *pool);

#endif
