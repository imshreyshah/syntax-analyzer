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


#ifndef STACKDEF_H
#define STACKDEF_H
#include<stdio.h>
#include<stdlib.h>

# define STK_SZ 200;
typedef struct
{
    void **arr;
    int top;
    int size;
} stack;

stack *initStack();
void *top(stack *pt_stack);
void *pop(stack *pt_stack);
void push(stack *pt_stack, void *node);

#endif
