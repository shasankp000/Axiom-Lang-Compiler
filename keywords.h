#include<stddef.h>
#ifndef KEYWORDS_H
#define KEYWORDS_H

enum KEYWORD {
  IF,
  LET,
  FOR,
  WHILE,
  LOOP,
  DO,
  FN,
  RET,
  BRK,
  CONT,
  CONST,
  TRUE,
  FALSE,
  INT,
  FLOAT,
  DLOAT,
  SINT,
  LINT,
  CHAR,
  BOOL,
  STR,
  NONE,
  NULL_KEYWORD,
  NOT_IMPLEMENTED,
  KEYWORD_COUNT
};

enum KEYWORD_TYPE {
  SYSTEM_RESERVED,
  DATA_TYPE,
  PURPOSELY_UNDEFINED_KEYWORD,
  NOT_FOUND,
  ILLEGAL_KEYWORD
};

struct KeywordMap {
    const char* string_representation;
    enum KEYWORD id;
    enum KEYWORD_TYPE type;
};

extern const struct KeywordMap KEYWORD_TABLE[];
extern const size_t TOTAL_KEYWORDS;

#endif
