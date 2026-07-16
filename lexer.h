#ifndef LEXER_H
#define LEXER_H
#include "lexer_token.h"
#include "lexer_node.h"

enum TOKEN assign_token(char input);
void assign_large_token(struct LexerNode* head);
void print_token(enum TOKEN token);
void print_large_token(enum LargeTOKEN token);
void recognize(struct LexerNode* head);

#endif
