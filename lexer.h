#ifndef LEXER_H
#define LEXER_H
#include "lexer_token.h"
#include "lexer_node.h"

void assign_token(struct LexerNode* head);
void assign_large_token(struct LexerNode* head);
void print_token(enum TOKEN token);
void print_large_token(enum LargeTOKEN token);
void recognize(struct LexerNode* head);
void detect_keyword(struct LexerNode* head);

#endif
