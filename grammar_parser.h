/*
=======================================================================================================
PPL ASSIGNMENT 1 2020
GROUP NUMBER 14
RUSHIKESH ZAWAR 2017B1A70977P
SHREY SHAH 		2017B2A71038P
ABHIMANYU SETHI 2017B3A70637P
PRANALI SANCHETI 2017B3A70736P
 =======================================================================================================
*/#ifndef GRAMMARPARSER_H

#define GRAMMARPARSER_H

#include<stdbool.h>
#include<stdio.h>

#include "lexer.h"
#define MAX_RHSLEN 1000
#define MAXRULES 61

#define LEX_MAX_LEN 100

typedef enum
{
    #include "nonTerminals.txt"
} nonterminal;



typedef struct{
    union
    {
        token_name t;
        nonterminal nt;
    };
    bool is_terminal;
} symbol;


typedef struct rhsnode
{
    symbol* sym;
    struct rhsnode *next;
} rhsnode;

typedef struct rhsnode *rhsnode_ptr;

typedef struct
{
    nonterminal lhs;
    rhsnode_ptr head;
    rhsnode_ptr tail;
} cell;

cell grammar[MAXRULES];
symbol* sym_get(char str[]);
int search_exists(char* lexeme);
void insert_at_end(rhsnode_ptr *ptr_tail, symbol* sym);
void readGrammar(FILE *fptr, cell grammar[]);

#endif
