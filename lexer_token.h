#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

// an enumeration is the perfect way to define a token.
enum TOKEN {
  ALPHABET,
  DIGIT,
  PUNCTUATION,
  WHITESPACE,
  OPERATOR,
  PURPOSELY_NOT_DEFINED,
  INVALID,
};

// the LargeTOKEN will be applied after the initial round of 1:1 character:token mapping is done
enum LargeTOKEN {
  IDENTIFIER,
  KEYWORD,
  DELIMITER,
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COLON,
  SEMICOLON,
  NUMBER,
  STRING_LITERAL, // a literal string, as literal as it gets, lol.
  COMMENT,
  PURPOSELY_UNDEFINED,
  ILLEGAL
};

#endif
