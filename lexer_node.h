#ifndef LEXER_NODE_H
#define LEXER_NODE_H
#include "lexer_token.h"

struct LexerNode {
  char c;
  int index;
  enum TOKEN token;
  enum LargeTOKEN largetoken;
  struct LexerNode* next;
  struct LexerNode* prev;
};

#endif
