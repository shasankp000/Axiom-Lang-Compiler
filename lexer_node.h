#ifndef LEXER_NODE_H
#define LEXER_NODE_H
#include "lexer_token.h"
#include "keywords.h"

struct LexerNode {
  char c;
  int index;
  enum TOKEN token;
  enum LargeTOKEN largetoken;
  enum KEYWORD_TYPE keyword_type;
  enum KEYWORD keyword;
  struct LexerNode* next;
  struct LexerNode* prev;
};

#endif
