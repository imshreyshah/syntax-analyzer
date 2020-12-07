/*
=======================================================================================================
PPL ASSIGNMENT 1 2020
GROUP NUMBER 14
RUSHIKESH ZAWAR 2017B1A70977P
SHREY SHAH 		2017B2A71038P
ABHIMANYU SETHI 2017B3A70637P
PRANALI SANCHETI 2017B3A70736P
 =======================================================================================================
*/


#ifndef LEXER_H
#define LEXER_H

typedef enum {
  #include "tokens.txt"
}token_name;

typedef struct TokenStream{
  token_name name;
  int tag; // 0 -string, 1 - number 2 - Real number
  union Data {
    char str[21];
    int num;
    double rnum;
  } data;
  int line_no;
  struct TokenStream* next;
} tokenStream;

typedef struct TokenStreamHead{
  int count;
  tokenStream* head;
} tokenStreamHead;

token_name give_token_enum(char* s);
void tokeniseSourceCode(FILE *f, tokenStreamHead* streamHead);
void printTokenStream(tokenStream* ts);


#endif