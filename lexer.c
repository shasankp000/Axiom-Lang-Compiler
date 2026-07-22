#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "keywords.h"
#include "lexer_token.h"
#include "lexer_node.h"
#include "lexer.h"
// #include "memory_pool.h"

/*
// an enumeration is the perfect way to define a token.
enum TOKEN {
  ALPHABET,
  DIGIT,
  PUNCTUATION,
  WHITESPACE,
  OPERATOR,
  INVALID,
};

// the LargeTOKEN will be applied after the initial round of 1:1 character:token mapping is done
enum LargeTOKEN {
  WORD,
  IDENTIFIER,
  KEYWORD,
  DELIMITER,
  NUMBER,
  PURPOSELY_UNDEFINED,
  ILLEGAL
};
*/

enum TOKEN assign_token(char input){

// the biggest problem in this dang function was to figure out
// how do I pass something like a generic input type?
// void* input was part of the solution, but I didn't want to dive too deep into complicated solutions,
// so I came up with this:
// okay, it just reads input chars, not anything truly generic.
// just changing input type to char input does the job here.

  enum TOKEN token = INVALID;

  if ((isalpha(input))) {
    token = ALPHABET;
  }
  if (isdigit(input)) {
    token = DIGIT;
  }
  if (ispunct(input)) {
    token = PUNCTUATION;
  }
  if (ispunct(input)) {
    if (input == '+' || input == '-' || input == '/' || input == '*') {
      token = OPERATOR;
    }
  }
  if (isspace(input)) {
    token = WHITESPACE;
  }

  return token;
}

void print_token(enum TOKEN token) {
  switch(token) {
    case ALPHABET:
      printf("TOKEN: ALPHABET \n");
      break;
    case DIGIT:
      printf("TOKEN: DIGIT \n");
      break;
    case PUNCTUATION:
      printf("TOKEN: PUNCTUATION \n");
      break;
    case OPERATOR:
      printf("TOKEN: OPERATOR \n");
      break;
    case WHITESPACE:
      printf("TOKEN: WHITESPACE \n");
      break;
    case INVALID:
      printf("TOKEN: INVALID \n");
      break;
    default:
      printf("TOKEN: INVALID \n");
      break;
  }
}

void print_large_token(enum LargeTOKEN token) {
  switch(token) {
    case IDENTIFIER:
      printf("LARGE TOKEN: IDENTIFER \n");
      break;
    case KEYWORD:
      printf("LARGE TOKEN: KEYWORD \n");
      break;
    case NUMBER:
      printf("LARGE TOKEN: NUMBER \n");
      break;
    case DELIMITER:
      printf("LARGE TOKEN: DELIMITER \n");
      break;
    case PURPOSELY_UNDEFINED:
      printf("LARGE TOKEN: PURPOSELY_UNDEFINED \n");
      break;
    case ILLEGAL:
      printf("LARGE TOKEN: ILLEGAL \n");
      break;
    case STRING_LITERAL:
      printf("LARGE TOKEN: STRING LITERAL \n");
      break;
    case COMMENT:
      printf("LARGE TOKEN: COMMENT \n");
      break;
    case LEFT_PAREN:
      printf("LARGE TOKEN: LEFT_PAREN \n");
      break;
    case RIGHT_PAREN:
      printf("LARGE TOKEN: RIGHT_PAREN \n");
      break;
    case LEFT_BRACE:
      printf("LARGE TOKEN: LEFT_BRACE \n");
      break;
    case RIGHT_BRACE:
      printf("LARGE TOKEN: RIGHT_BRACE \n");
      break;
    case COLON:
      printf("LARGE TOKEN: COLON \n");
      break;
    case SEMICOLON:
      printf("LARGE TOKEN: SEMICOLON \n");
      break;
    default:
      printf("LARGE TOKEN: ILLEGAL \n");
      break;
  }
}

void print_keyword_type(enum KEYWORD_TYPE keyword_type) {
  switch(keyword_type) {
    case SYSTEM_RESERVED:
      printf("KEYWORD TYPE: SYSTEM_RESERVED \n");
      break;
    case DATA_TYPE:
      printf("KEYWORD TYPE: DATA_TYPE \n");
      break;
    case PURPOSELY_UNDEFINED_KEYWORD:
      printf("KEYWORD TYPE: PURPOSELY_UNDEFINED_KEYWORD \n");
      break;
    case NOT_FOUND:
      printf("KEYWORD TYPE: NOT_FOUND \n");
      break;
    case ILLEGAL_KEYWORD:
      printf("KEYWORD TYPE: ILLEGAL_KEYWORD \n");
      break;
    default:
      printf("KEYWORD TYPE: ILLEGAL_KEYWORD \n");
      break;
  }
}

void print_keyword(enum KEYWORD keyword) {
  switch(keyword) {
    case IF:
      printf("KEYWORD: IF \n");
      break;
    case LET:
      printf("KEYWORD: LET \n");
      break;
    case FOR:
      printf("KEYWORD: FOR \n");
      break;
    case WHILE:
      printf("KEYWORD: WHILE \n");
      break;
    case LOOP:
      printf("KEYWORD: LOOP \n");
      break;
    case DO:
      printf("KEYWORD: DO \n");
      break;
    case FN:
      printf("KEYWORD: FN \n");
      break;
    case RET:
      printf("KEYWORD: RET \n");
      break;
    case BRK:
      printf("KEYWORD: BRK \n");
      break;
    case CONT:
      printf("KEYWORD: CONT \n");
      break;
    case CONST:
      printf("KEYWORD: CONST \n");
      break;
    case TRUE:
      printf("KEYWORD: TRUE \n");
      break;
    case FALSE:
      printf("KEYWORD: FALSE \n");
      break;
    case INT_8:
      printf("KEYWORD: INT_8 \n");
      break;
    case INT_16:
      printf("KEYWORD: INT_16 \n");
      break;
    case INT_32:
      printf("KEYWORD: INT_32 \n");
      break;
    case INT_64:
      printf("KEYWORD: INT_64 \n");
      break;
    case INT_128:
      printf("KEYWORD: INT_128 \n");
      break;
    case INT_512:
      printf("KEYWORD: INT_512 \n");
      break;
    case FLOAT_8:
        printf("KEYWORD: FLOAT_8 \n");
        break;
    case FLOAT_16:
        printf("KEYWORD: FLOAT_16 \n");
        break;
    case FLOAT_32:
        printf("KEYWORD: FLOAT_32 \n");
        break;
    case FLOAT_64:
        printf("KEYWORD: FLOAT_64 \n");
        break;
    case FLOAT_128:
        printf("KEYWORD: FLOAT_128 \n");
        break;
    case FLOAT_512:
        printf("KEYWORD: FLOAT_512 \n");
        break;
    case CHAR:
      printf("KEYWORD: CHAR \n");
      break;
    case BOOL:
      printf("KEYWORD: BOOL \n");
      break;
    case STR:
      printf("KEYWORD: STR \n");
      break;
    case NONE:
      printf("KEYWORD: NONE \n");
      break;
    case NULL_KEYWORD:
      printf("KEYWORD: NULL_KEYWORD \n");
      break;
    case NOT_IMPLEMENTED:
      printf("KEYWORD: NOT_IMPLEMENTED \n");
      break;
    case KEYWORD_COUNT:
      printf("KEYWORD: KEYWORD_COUNT (should never appear on a real node) \n");
      break;
    default:
      printf("KEYWORD: NOT_IMPLEMENTED \n");
      break;
  }
}

// time to represent the connection with tokens in a meaningful way now.
// Yes it will be a bi-directional linked list (I forgot the proper industry term)

/*
struct LexerNode {
  char c;
  int index;
  enum TOKEN token;
  enum LargeTOKEN largetoken;
  struct LexerNode* next;
  struct LexerNode* prev;
};
*/

enum KEYWORD_TYPE check_keyword_type(char* word) {
    for (size_t i = 0; i < TOTAL_KEYWORDS; i++) {
            if (strcmp(word, KEYWORD_TABLE[i].string_representation) == 0) {
                return KEYWORD_TABLE[i].type;
            }
        }

    return NOT_FOUND;
}

enum KEYWORD get_keyword_id(const char* word) {
    // Loop through the existing table
    for (size_t i = 0; i < TOTAL_KEYWORDS; i++) {
        if (strcmp(word, KEYWORD_TABLE[i].string_representation) == 0) {
            return KEYWORD_TABLE[i].id; // Return the exact enum ID (e.g., IF, INT)
        }
    }

    // Fallback if the string is not a known language keyword
    return NOT_IMPLEMENTED;
}

void detect_keyword(struct LexerNode* head) {
    enum LargeTOKEN token = ILLEGAL;
    struct LexerNode* temp = head;
    struct LexerNode* lexeme_start = temp;
    struct LexerNode* lexeme_start2 = lexeme_start;
    struct LexerNode* lexeme_start3 = lexeme_start; // there is a reason for this third pointer.
    int word_length = 0;
    char* word_array = NULL;
    int word_array_index = 0;
    enum KEYWORD_TYPE keyword_type = NOT_FOUND;
    enum KEYWORD keyword = NULL_KEYWORD;

    // so what I am trying to do here is firstly collect the total number characters that have the large token WORD
    // then dynamically create a char array with length as the total number of chars + 1 extra character for a null terminator
    // then concatenate all the characters in that array ending with the null terminator.
    // then run a switch case check against keywords to detect if it as a keyword or not.

    while (temp!=NULL) {
        if (temp->largetoken == DELIMITER) {
          // find the first DELIMITER.
          while(lexeme_start!=temp) {
              if (lexeme_start->largetoken == IDENTIFIER) {
                  word_length+=1;
              }
              else {
                  break; // don't consider looping if the first char has some large token other than WORD.
              }
              lexeme_start = lexeme_start->next;
          }
          // before we proceed to the next lexeme
          if (word_length>0) {
              word_length += 1; // one extra slot for the null terminator
              word_array = malloc(word_length * sizeof(char)); // initialize the array.
              while(lexeme_start2!=lexeme_start) { // technically the same as lexeme_start2 != temp
                  word_array[word_array_index] = lexeme_start2->c;
                  word_array_index+=1;
                  lexeme_start2 = lexeme_start2->next;
              }
              word_array[word_array_index] = '\0'; // terminate the string.

              // check the keyword type
              keyword_type = check_keyword_type(word_array);
              if (keyword_type!=NOT_FOUND) {
                  // check the actual keyword.
                  keyword = get_keyword_id(word_array);
              }

              // great, now that we have the correct keyword type and the keyword to assign to, let's run one final loop.
              while(lexeme_start3!=lexeme_start) {// again, technically the same as lexeme_start3 != temp
                  lexeme_start3->keyword_type = keyword_type;
                  lexeme_start3->keyword = keyword;

                  // then this piece of error correction code here specifically IDENTIFIERS.
                  if (lexeme_start3->largetoken == IDENTIFIER) {
                      if (keyword_type != NOT_FOUND) {
                          lexeme_start3->largetoken = KEYWORD;
                      }
                  }

                  lexeme_start3 = lexeme_start3->next;
              }

              free(word_array);
          }

          word_array = NULL;
          word_array_index = 0;
          word_length = 0;
          temp = temp->next; // push past the delimiter.
          lexeme_start = temp; // set to the start of the next lexeme.
          lexeme_start2 = lexeme_start;
          lexeme_start3 = lexeme_start;
          keyword_type = NOT_FOUND;
          keyword = NOT_IMPLEMENTED;
          continue;
        }
        temp = temp->next;
    }

    // same edge case as assign_large_token, what if the last/only lexeme ends without any delimiter?
    // lexeme_start is still sitting at the start of that lexeme.

    if (lexeme_start!=NULL) {
        while(lexeme_start!=temp) {
            if (lexeme_start->largetoken == IDENTIFIER) {
                word_length+=1;
            }
            else {
                break; // don't consider looping if the first char has some large token other than WORD.
            }
            lexeme_start = lexeme_start->next;
        }
        // before we proceed to the next lexeme
        if (word_length>0) {
            word_length += 1; // one extra slot for the null terminator
            word_array = malloc(word_length * sizeof(char)); // initialize the array.
            while(lexeme_start2!=lexeme_start) { // technically the same as lexeme_start2 != temp
                word_array[word_array_index] = lexeme_start2->c;
                word_array_index+=1;
                lexeme_start2 = lexeme_start2->next;
            }
            word_array[word_array_index] = '\0'; // terminate the string.

            // check the keyword type
            keyword_type = check_keyword_type(word_array);
            if (keyword_type!=NOT_FOUND) {
                // check the actual keyword.
                keyword = get_keyword_id(word_array);
            }

            // great, now that we have the correct keyword type and the keyword to assign to, let's run one final loop.
            while(lexeme_start3!=lexeme_start) {// again, technically the same as lexeme_start3 != temp
                lexeme_start3->keyword_type = keyword_type;
                lexeme_start3->keyword = keyword;

                // then this piece of error correction code here specifically for IDENTIFIERS.
                if (lexeme_start3->largetoken == IDENTIFIER) {
                    if (keyword_type != NOT_FOUND) {
                        lexeme_start3->largetoken = KEYWORD;
                    }
                }

                lexeme_start3 = lexeme_start3->next;
            }

            free(word_array);
        }

        word_array = NULL;
        word_array_index = 0;
        word_length = 0;
        keyword_type = NOT_FOUND;
        keyword = NOT_IMPLEMENTED;
    }
}

void assign_large_token(struct LexerNode* head) {
   enum LargeTOKEN token = ILLEGAL;
   struct LexerNode* temp = head;
   struct LexerNode* lexeme_start = NULL;
   struct LexerNode* comment_start = NULL;
   struct LexerNode* string_start = NULL;
   int digit_occurrence = 0;
   int alphabet_occurence = 0;
   int start_index = 0;
   int current_index = 0;
   int first_char_is_digit = 0;
   int comment_start_detected = 0;
   int comment_end_detected = 0;
   int string_literal_start_detected = 0;
   int string_literal_end_detected = 0;
   lexeme_start = temp;

   printf("Before while loop....\n");
   while (temp!=NULL) {

    // for ILLEGAL identifiers:
    if (lexeme_start->token == DIGIT) {
      first_char_is_digit = 1;
    }

    // comment detection (/* ... */)
    if (temp->token == OPERATOR && temp->c == '/' &&
        temp->next != NULL && temp->next->token == OPERATOR && temp->next->c == '*') {

      comment_start_detected = 1;
      comment_end_detected = 0;
      comment_start = temp; // remember exactly where the comment began

      temp = temp->next->next; // move past the opening /*

      while (temp != NULL) {
        if (temp->token == OPERATOR && temp->c == '*' &&
            temp->next != NULL && temp->next->token == OPERATOR && temp->next->c == '/') {
          comment_end_detected = 1;
          break; // temp is now sitting on the closing '*'
        }
        temp = temp->next;
      }

      if (comment_start_detected && comment_end_detected) {
        // confirmed fully-enclosed comment - now tag every node from
        // comment_start through the closing '/' (inclusive).
        while (comment_start != temp) {
          comment_start->largetoken = COMMENT;
          comment_start = comment_start->next;
        }
        comment_start->largetoken = COMMENT;      // the closing '*'
        comment_start->next->largetoken = COMMENT; // the closing '/'

        temp = comment_start->next->next; // advance past the closing */
      }
      else {
        // unterminated comment: temp ran off the end (NULL) without
        // finding a closing */. Mark whatever was scanned ILLEGAL.
        while (comment_start != NULL) {
          comment_start->largetoken = ILLEGAL;
          comment_start = comment_start->next;
        }
        temp = NULL;
      }

      comment_start_detected = 0;
      comment_end_detected = 0;
      lexeme_start = temp; // resync - nothing left open from before the comment
      digit_occurrence = 0;
      alphabet_occurence = 0;
      first_char_is_digit = 0;
      continue; // skip the rest of this iteration; temp already advanced
    }


    // string literal detection (" ... ")
    if (temp->token == PUNCTUATION && temp->c == '"') {

      string_literal_start_detected = 1;
      string_literal_end_detected = 0;
      string_start = temp; // remember exactly where the string began

      temp = temp->next; // move past the opening "

      while (temp != NULL) {
        if (temp->token == PUNCTUATION && temp->c == '"') {
          string_literal_end_detected = 1;
          break; // temp is now sitting on the closing '"'
        }
        temp = temp->next;
      }

      if (string_literal_start_detected && string_literal_end_detected) {
        // confirmed fully-enclosed string - now tag every node from
        // string_start through the closing '"' (inclusive).
        while (string_start != temp) {
          string_start->largetoken = STRING_LITERAL;
          string_start = string_start->next;
        }
        string_start->largetoken = STRING_LITERAL;      // the closing '"'

        temp = string_start->next; // advance past the closing "
      }
      else {
        // unterminated string: temp ran off the end (NULL) without
        // finding a closing ". Mark whatever was scanned ILLEGAL.
        while (string_start != NULL) {
          string_start->largetoken = ILLEGAL;
          string_start = string_start->next;
        }
        temp = NULL;
      }

      string_literal_start_detected = 0;
      string_literal_end_detected = 0;
      comment_start_detected = 0;
      comment_end_detected = 0;
      lexeme_start = temp; // resync - nothing left open from before the string
      digit_occurrence = 0;
      alphabet_occurence = 0;
      first_char_is_digit = 0;
      continue; // skip the rest of this iteration; temp already advanced
    }

    // only check if a LexerNode's token is a number or not - this would mean that within the alphabets there is some number somewhere mixed up, so that lexeme would become an IDENTIFIER.
    if (temp->token == DIGIT) {
      digit_occurrence+=1;
    }
    if (temp->token == ALPHABET) {
      alphabet_occurence+=1;
    }

    if (temp->token == WHITESPACE || temp->token == PUNCTUATION || temp->token == OPERATOR) {
      // delimiter reached.

      if (temp->token == PUNCTUATION && temp->c == '(') {
          temp->largetoken = LEFT_PAREN;
      }

      else if (temp->token == PUNCTUATION && temp->c == ')') {
          temp->largetoken = RIGHT_PAREN;
      }

      else if (temp->token == PUNCTUATION && temp->c == '{') {
          temp->largetoken = LEFT_BRACE;
      }

      else if (temp->token == PUNCTUATION && temp->c == '}') {
          temp->largetoken = RIGHT_BRACE;
      }

      else if (temp->token == PUNCTUATION && temp->c == ':') {
          temp->largetoken = COLON;
      }

      else if (temp->token == PUNCTUATION && temp->c == ';') {
          temp->largetoken = SEMICOLON;
      }

      else {
          temp->largetoken = DELIMITER;
      }

      while(lexeme_start!=temp) {
        if (alphabet_occurence > 0) {
            if (first_char_is_digit) {
              lexeme_start->largetoken = ILLEGAL;
            }
            else {
              lexeme_start->largetoken = IDENTIFIER;
            }
        }
        else if (digit_occurrence > 0 && alphabet_occurence==0) {
            lexeme_start->largetoken = NUMBER;
        }
        else {
          lexeme_start->largetoken = ILLEGAL;
        }

        if (lexeme_start->next == temp) {
          // right at the end of lexeme.

          if (alphabet_occurence > 0) {
            if (first_char_is_digit) {
              lexeme_start->largetoken = ILLEGAL;
            }
            else {
              lexeme_start->largetoken = IDENTIFIER;
            }
          }
          else if (digit_occurrence > 0 && alphabet_occurence==0) {
            lexeme_start->largetoken = NUMBER;
          }
          else {
            lexeme_start->largetoken = ILLEGAL;
          }

          lexeme_start = temp;
          digit_occurrence = 0; // reset the counter for the next lexeme
          alphabet_occurence = 0;
          first_char_is_digit = 0;
          break;
        }
        lexeme_start = lexeme_start->next;
      }
     // now we push the lexeme_start past the delimiter, to the next lexeme's start.
     lexeme_start = temp->next;
    }
    temp = temp->next;
 }

  // adding an edge case detection. What if there is no delimiter at the end of the input to trigger the inner loop for the second or in this case, the very last lexeme??
  // This means that temp is already at NULL, so we can't use temp.
  // But lexeme_start is still sitting at a real LexerNode.
  // All we need to do is to keep walk from lexeme_start to NULL, and tag all LexerNodes along the way.
  // This is a one-time cleanup after the main loop has already run, and it already has logged if the last lexeme is an IDENTIFIER or WORD, via the counter variable.

  if (lexeme_start != NULL) {
      while (lexeme_start != NULL) {

          if (lexeme_start->token == PUNCTUATION) {
              switch (lexeme_start->c) {
                  case '(':
                      lexeme_start->largetoken = LEFT_PAREN;
                      break;

                  case ')':
                      lexeme_start->largetoken = RIGHT_PAREN;
                      break;

                  case '{':
                      lexeme_start->largetoken = LEFT_BRACE;
                      break;

                  case '}':
                      lexeme_start->largetoken = RIGHT_BRACE;
                      break;

                  case ':':
                      lexeme_start->largetoken = COLON;
                      break;

                  case ';':
                      lexeme_start->largetoken = SEMICOLON;
                      break;

                  default:
                      lexeme_start->largetoken = DELIMITER;
                      break;
              }
          }
          else if (alphabet_occurence > 0) {
              if (first_char_is_digit) {
                  lexeme_start->largetoken = ILLEGAL;
              }
              else {
                  lexeme_start->largetoken = IDENTIFIER;
              }
          }
          else if (digit_occurrence > 0) {
              lexeme_start->largetoken = NUMBER;
          }
          else {
              lexeme_start->largetoken = ILLEGAL;
          }

          lexeme_start = lexeme_start->next;
      }

      digit_occurrence = 0;
      alphabet_occurence = 0;
      first_char_is_digit = 0;
  }
}

// this method will try to pretty-print.
void recognize(struct LexerNode* head) {
  // following similar logic as assign_large_token

  struct LexerNode* temp = head;
  struct LexerNode* lexeme_start = temp;

  if (lexeme_start->largetoken == COMMENT) {
      while (temp!=NULL) {
          // print out all the characters without a newline
          printf("%c", temp->c);

          if (temp->next == NULL) {
              // last character has been printed
              printf("\t\t --> \t\t");
              print_large_token(lexeme_start->largetoken); // this is automatically print a newline too.
          }

          temp = temp->next;
      }
  }
  else {
      while (temp!=NULL) {
        // start looping till a DELIMITER is reached.

        if (temp->largetoken == DELIMITER) {
          while (lexeme_start!=temp) {
            printf("%c", lexeme_start->c); // keep printing characters without newline.
            // once the last character has been printed.
            if (lexeme_start->next == temp) {
              printf("\t\t --> \t\t");
              print_large_token(lexeme_start->largetoken); // this is automatically print a newline too.
              printf("\t\t --> \t\t");
              print_keyword_type(lexeme_start->keyword_type);
              printf("\t\t --> \t\t");
              print_keyword(lexeme_start->keyword);
            }
            lexeme_start = lexeme_start->next;
          }
          // now we print the delimiter as well.
          if (temp->token!=OPERATOR) {
            printf("%c", temp->c);
            printf("\t\t --> \t\t");
            print_large_token(temp->largetoken);
          }
          else{
            printf("%c", temp->c);
            printf("\t\t --> \t\t");
            print_token(temp->token);
          }
          // now we push the lexeme_start past the delimiter, to the next lexeme's start.
          lexeme_start = temp->next;
        }
        temp = temp->next;
      }

    // applying same edge case as assign_large_token here too.

    if (lexeme_start!=NULL) {
      while (lexeme_start!=NULL) {
        printf("%c", lexeme_start->c); // keep printing characters without newline.
        // once the last character has been printed.
        if (lexeme_start->next == temp) {
          printf("\t\t --> \t\t");
          print_large_token(lexeme_start->largetoken); // this is automatically print a newline too.
          printf("\t\t --> \t\t");
          print_keyword_type(lexeme_start->keyword_type);
          printf("\t\t --> \t\t");
          print_keyword(lexeme_start->keyword);
        }
          lexeme_start = lexeme_start->next;
        }
      }
  }


}

/*

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
  printf("Large token assignment complete\n");

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
*/
