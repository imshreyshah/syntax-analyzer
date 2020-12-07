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

#ifndef TE_H
#define TE_H

#include<stdio.h>
#include<stdbool.h>
//#include "treenode.h"

typedef enum ArrayType{prim, rect, jag} arrayType;
typedef enum BindType{static_bind, dynamic_bind, not_applicable} bindType;

typedef struct Range{
    int start;
    int end;
}range;

typedef struct JaggedTE{
    char* type;
    int dim;
    //struct Range* r;
   
    int* range; 
    char** range3d;
    int bound;
    int index;
    int lowerRange;
    int upperRange;

    char* elem;
} jaggedTE;

typedef struct RectTE{
    char* type;
    int dim;
    //struct Range* r;
    char* elem;
   char** range_rt;

    int bound; //Utility
} rectTE;

typedef struct PrimTE{
    char* type;
} primTE;

union TypeExpression{
        primTE pt;
        rectTE rt;
        jaggedTE jt;    
};

typedef struct TypeExpressionCell{
    char name[21]; //FIELD-1
    arrayType at; //FIELD-2 0-prim 1- rect 2- jag}
    bindType bt; //FIELD-3 0- static_bind 1- dynamic_bind 2- not_applicable}
    int tag; //0 - primtTE, 1- rectTE, 2-jaggedTE
    union TypeExpression te; //FIELD-4
} typeExpressionCell;

typeExpressionCell typeExpressionTable[100];

void init_global_var();
void printTypeexpressiontable();

#endif