#include "keywords.h"
#include <stddef.h>

const struct KeywordMap KEYWORD_TABLE[] = {
    // Control Flow -> SYSTEM_RESERVED
    {"if",    IF,    SYSTEM_RESERVED},
    {"let",   LET,   SYSTEM_RESERVED},
    {"for",   FOR,   SYSTEM_RESERVED},
    {"while", WHILE, SYSTEM_RESERVED},
    {"loop",  LOOP,  SYSTEM_RESERVED},
    {"do",    DO,    SYSTEM_RESERVED},
    {"fn",    FN,    SYSTEM_RESERVED},
    {"ret",   RET,   SYSTEM_RESERVED},
    {"brk",   BRK,   SYSTEM_RESERVED},
    {"cont",  CONT,  SYSTEM_RESERVED},
    {"const", CONST, SYSTEM_RESERVED},
    {"true",  TRUE,  SYSTEM_RESERVED},
    {"false", FALSE, SYSTEM_RESERVED},
    {"none",  NONE, SYSTEM_RESERVED}, // none in Axiom is the same as NULL, in C.

    // Data Types -> DATA_TYPE
    {"i8",   INT_8,     DATA_TYPE},
    {"i16",  INT_16,    DATA_TYPE},
    {"i32",  INT_32,    DATA_TYPE},
    {"i64",  INT_64,    DATA_TYPE},
    {"i128", INT_128,   DATA_TYPE},
    {"i512", INT_512,   DATA_TYPE},
    {"f8",   FLOAT_8,   DATA_TYPE},
    {"f16",  FLOAT_16,  DATA_TYPE},
    {"f32",  FLOAT_32,  DATA_TYPE},
    {"f64",  FLOAT_64,  DATA_TYPE},
    {"f128", FLOAT_128, DATA_TYPE},
    {"f512", FLOAT_512, DATA_TYPE},
    {"char",  CHAR,  DATA_TYPE},
    {"bool",  BOOL,  DATA_TYPE},
    {"str",   STR,   DATA_TYPE}
};

// Calculate size safely in the .c file where the size is known
const size_t TOTAL_KEYWORDS = sizeof(KEYWORD_TABLE) / sizeof(KEYWORD_TABLE[0]);
