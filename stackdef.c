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

#include "stackdef.h"
#include<stdbool.h>
#include <stdlib.h>

stack *initStack() {
  stack *pt_stack = (stack *)calloc(1,sizeof(stack));
  if (pt_stack == NULL) {
    printf("Error in stack: failed to initialize\n");
  }
  pt_stack->size = STK_SZ;
  pt_stack->arr =
      (void **)calloc(1,sizeof(void *) * (pt_stack->size));
  if (pt_stack->arr == NULL) {
    perror("Error in stack: failed to initialize\n");
  }
  pt_stack->top = 0;
  return pt_stack;
}


void *top(stack *pt_stack) {
  if (pt_stack->top == 0) {
    return NULL;
  } else {
    return pt_stack->arr[pt_stack->top - 1];
  }
}


void push(stack *pt_stack, void *node) {
  if (pt_stack->top == (pt_stack->size)) {
    pt_stack->size *= 2;
    void **tmp =
        realloc(pt_stack->arr, sizeof(void *) * pt_stack->size);
    if (tmp == NULL) {
      perror("Error in doubling stack's size: realloc failed\n");
    } else {
      pt_stack->arr = tmp;
    }
  }
  pt_stack->arr[pt_stack->top] = node;
  pt_stack->top++;
}

void *pop(stack *pt_stack) {
  if (pt_stack->top == 0) {
    return NULL;
  }

  pt_stack->top--;
  return pt_stack->arr[pt_stack->top];
}



bool stackisEmpty(stack *pt_stack)
{
    if(pt_stack->top == 0){
        return true;
    }
    else{
        return false;}
}