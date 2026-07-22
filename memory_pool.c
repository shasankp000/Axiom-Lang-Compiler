#include <stdio.h>
// #include <stdlib.h>
#include "memory_pool.h"
#include "lexer_token.h"
#include "keywords.h"

// #include <ctype.h>

/*
struct Node {
  int index;
  char character;
  struct Node* prev;
  struct Node* next;
};

struct PoolSlot {
  int slot_index;
  int in_use;
  struct Node node;
};

struct MemoryPool {
  int cursor_val;
  int pool_size;
  struct PoolSlot *slots;
};
*/

void report(struct MemoryPool *mem_pool){
  for (int i = 0; i<mem_pool->pool_size; i++) {
    if (mem_pool->slots[i].in_use == 0) {
      printf("Region %d: Unallocated \n", i+1);
      printf("Character: %c \n", mem_pool->slots[i].node.c);
    }
    else {
      printf("Region %d: Allocated \n", i+1);
      printf("Character: %c \n", mem_pool->slots[i].node.c);
    }
  }
}

void allocate(struct MemoryPool *mem_pool, char c) {
  if (mem_pool->cursor_val >= mem_pool->pool_size) {
    mem_pool->cursor_val = 0; // wrap around to the first slot if cursor reached the end of the current pool.
  }

  if (mem_pool->slots[mem_pool->cursor_val].in_use == 0) { // if free
      mem_pool->slots[mem_pool->cursor_val].in_use = 1; // then allocate
      mem_pool->slots[mem_pool->cursor_val].node.c = c;
  }

  mem_pool->cursor_val+=1;  // increment cursor to track the next slot.
  // easy peasy lemon squeezy (Yes I played Counter-Strike).
}


void release(struct MemoryPool *mem_pool, int free_location) {
  if (mem_pool->slots[free_location].in_use == 1) { // if allocated
      mem_pool->slots[free_location].in_use = 0; // then free
      mem_pool->slots[free_location].node.c = '\0';
      // easy peasy lemon squeezy (Yes I played Counter-Strike).
   }
}

void fill_pool(struct MemoryPool *memory_pool) {

  for (int i=0; i<memory_pool->pool_size; i++) {
    memory_pool->slots[i].slot_index = i;
    memory_pool->slots[i].in_use = 0; // set all slots to free initially.
    memory_pool->slots[i].node.index = i;
    memory_pool->slots[i].node.c = '\0';
    memory_pool->slots[i].node.token = PURPOSELY_NOT_DEFINED;
    memory_pool->slots[i].node.largetoken = PURPOSELY_UNDEFINED;
    memory_pool->slots[i].node.keyword = NULL_KEYWORD;
    memory_pool->slots[i].node.keyword_type = PURPOSELY_UNDEFINED_KEYWORD;

    if (i == memory_pool->pool_size-1) {
      // at the last node.
      memory_pool->slots[i].node.next = NULL;
    }
    else {
      memory_pool->slots[i].node.next = &memory_pool->slots[i+1].node;
    }

    if (i == 0) {
      // at head
      memory_pool->slots[i].node.prev = NULL;
    }
    else {
      memory_pool->slots[i].node.prev = &memory_pool->slots[i-1].node;
    }
  }
}

/*
int main() {
  int buf_size = 0;
  int collect_size = 0;
  char *lexical_buffer;
  printf("Memory pool allocator demo \n");

  printf("Enter size of lexical buffer: ");
  scanf("%d", &buf_size);
  getchar();

  buf_size = buf_size + 1;

  lexical_buffer = (char *) malloc(buf_size * sizeof(char));

  // now we have a dynamically defined buffer to store characters inside it.

  printf("Enter string: ");
  fgets(lexical_buffer, buf_size, stdin);
  printf("\n");

  printf("Entered string: %s \n", lexical_buffer);

  // Let's first "collect" the length of the string we entered.

  for (int i = 0; i<buf_size; i++) {
     if(isalnum((unsigned char) lexical_buffer[i]) || isblank((unsigned char) lexical_buffer[i]) || ispunct((unsigned char) lexical_buffer[i]) ) {
       printf("Collecting: %c \n", lexical_buffer[i]);
       collect_size+=1;
     }
     else {
       printf("Reached end of valid characters/whitespaces, breaking...\n");
       break;
     }
  }

  // this way we don't have to traverse the remaining empty buffer.
  // now we can just:

  for (int i=0; i<collect_size; i++) {
    printf("%d : %c \n", i, lexical_buffer[i]);
  }

  // now we create the memory pool based on collect_size

  struct MemoryPool *memory_pool = malloc(sizeof(struct MemoryPool));

  if (memory_pool == NULL) {
    printf("Error in allocating memory for the allocator object! \n");
    return 1;
  }

  memory_pool->pool_size = collect_size;
  memory_pool->cursor_val = 0;
  memory_pool->slots = calloc(memory_pool->pool_size, sizeof(struct PoolSlot));

  if (memory_pool->slots == NULL) {
    printf("Error in allocating memory for the memory pool slot! \n");
    return 1;
  }

  // now we fill the pool with initial dummy characters

  fill_pool(memory_pool);

  // now it's time to put a node at each one of the slots and then connect the nodes.

  // 0 means unallocated, 1 means allocated.

  // now let's design an allocate method where the allocator automatically
  // it will be simple.
  // call allocate()
  // mark one free slot as USED.
  // left to right only, like a tape head reading a tape on a circular platter.
  printf("\nAfter calling allocate: \n");

  for (int i=0; i<memory_pool->pool_size; i++) {
     allocate(memory_pool, lexical_buffer[i]);
  }

  report(memory_pool);

  printf("\nAfter calling release: \n");

  release(memory_pool, 0); // release the first slot.

  report(memory_pool);

  free(memory_pool->slots);
  free(memory_pool);
  free(lexical_buffer);

  return 0;
}
*/
