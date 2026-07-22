#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
// #include "lexer_token.h"
#include "lexer_node.h"
#include "memory_pool.h"
#include "lexer.h"


int main() {
  int buf_size = 0;
  int collect_size = 0;
  char *lexical_buffer;

  printf("Hello world! \n");

  // great, I have managed to write hello world, now what?
  // If I remember correctly from my notes, the first part of compiler design was lexical-something something handling
  // In very simple terms: Hello World -> each letter and whitespace are considered "tokens".
  // now I need to translate that to C somehow.
  // I have forgotten how to take in user inputs in C, so let me look that up first.
  // So standard input usually works with scanf, and for %s strings, it reads right up to the first whitespace.
  // So for multi-spaced strings I need to use fgets, and define a fixed array of characters to store the string in, the size of which shall be passed into fgets as well.
  // Okay, enough comments, let's do this.

  printf("Enter size of lexical buffer: ");
  scanf("%d", &buf_size);
  // so, it turns out that scanf only consumes the integers as per %d, and pressing the enter key generates a \n char in the stdin buffer that's left to consumed by fgets()
  // to tackle this problem we need to use getchar() to remove exactly one char from the stdin stream, and this removes the leftover \n in the stdin stream.
  getchar();

  buf_size+=1; // added an extra slot at the end.
  lexical_buffer = (char *) malloc(buf_size * sizeof(char));

  // now we have a dynamically defined buffer to store characters inside it.

 // printf("%zu \n", sizeof(lexical_buffer));
 // printf("%d \n", buf_size);

  printf("Enter string: ");
  fgets(lexical_buffer, buf_size, stdin);
  printf("\n");

  printf("Entered string: %s \n", lexical_buffer);

  // now let's walk the buffer, print out all the characters with it's indexes.
  // a linkedlist here would be nice.
  // or I can use a far simpler approach, which may appear a bit rudimentary.
  // after repeated mistakes and debugging, I found out how to detect alphanumeric, punctuations and whitespaces in C.
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

  // Now, I am aware that this second loop is redundant and the whole action could have been done in one single loop, but
  // I will keep this code, because it is my own original thinking, even if it is redundant.

  // At this juncture, the code can assign indexes to the string stored in the buffer,
  // but there is no "ontological" relationship between the letters,
  // there is no guarantee, that H->e->l->l->o->,->" "->W->o->r->l->d->!
  // We need to fix that. And this is where I believe linked lists may help us.
  // Actually, scratch that. Arrays already give me what I am asking for.
  // What I instead need, are semantics, some way to encode, what the heck is H, or a comma, or an exclamation mark.
  // This is where tokens come in.
  // And turns out I can integrate linked lists after all.
  // After nearly 4 hours of coding, I am replacing the linkedlist implementation
  // with a custom MemoryPool that is physically an array, but logically a doubly-linked list.
  // Did this so that the lexer becomes significantly faster as the CPU and cache love contiguous memory blocks.

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

  // now we actually fill the pool with the correct characters using allocate();

  for (int i=0; i<memory_pool->pool_size; i++) {
    allocate(memory_pool, lexical_buffer[i]);
  }

  // now it's time to put a node at each one of the slots and then connect the nodes.

  // 0 means unallocated, 1 means allocated.

  // now let's design an allocate method where the allocator automatically
  // it will be simple.
  // call allocate()
  // mark one free slot as USED.
  // left to right only, like a tape head reading a tape on a circular platter.

  // assign single-character tokens
  printf("Assigning single character tokens... \n");
  for (int i=0; i<memory_pool->pool_size; i++) {
    memory_pool->slots[i].node.token = assign_token(memory_pool->slots[i].node.c);
  }

  // assign large tokens
  printf("Assigning large tokens.... \n");
  assign_large_token(&memory_pool->slots[0].node);
  printf("Large token assignment complete.\n");

  printf("Checking keyword type and assigning keywords...\n");
  detect_keyword(&memory_pool->slots[0].node);
  printf("Keyword type and keyword assignment complete.\n");

  // traversal

  struct LexerNode* current = &memory_pool->slots[0].node;
  while (current->next!=NULL) {
    printf("Index: %d \n", current->index);
    printf("Character: %c \n", current->c);
    print_token(current->token);
    print_large_token(current->largetoken);

    current = current->next;

    if (current->next==NULL) {
      // reached last LexerNode
      printf("Index: %d \n", current->index);
      printf("Character: %c \n", current->c);
      print_token(current->token);
      print_large_token(current->largetoken);
    }
  }

  // pretty-print

  recognize(&memory_pool->slots[0].node);

  free(memory_pool->slots);
  free(memory_pool);
  free(lexical_buffer);

  return 0;
}
