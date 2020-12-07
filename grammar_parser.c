/*
=======================================================================================================
PPL ASSIGNMENT 1 2020
GROUP NUMBER 14
RUSHIKESH ZAWAR 2017B1A70977P
SHREY SHAH 	2017B2A71038P
ABHIMANYU SETHI 2017B3A70637P
PRANALI SANCHETI 2017B3A70736P
 =======================================================================================================
*/

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grammar_parser.h"



int search_exists(char* lexeme)
{
	
    //non terminals
	if(strcmp(lexeme,"START") == 0) return 0;
	else if(strcmp(lexeme,"MAINPROGRAM") == 0) return 1;
	else if(strcmp(lexeme,"DECLARATIONSTMTS") == 0) return 2;
	else if(strcmp(lexeme,"ASSIGNMENTSTMTS") == 0) return 3;
	else if(strcmp(lexeme,"DECLARATIONSTMT") == 0) return 4;
	else if(strcmp(lexeme,"ASSIGNMENTSTMT") == 0) return 5;
	else if(strcmp(lexeme,"DEC") == 0) return 6;
	else if(strcmp(lexeme,"SINGLE") == 0) return 7;
	else if(strcmp(lexeme,"TYPE") == 0) return 8;
	else if(strcmp(lexeme,"ARRAYTYPE") == 0) return 9;
	else if(strcmp(lexeme,"VARIABLE_NAMES") == 0) return 10;
	else if(strcmp(lexeme,"RECTANGULAR_ARRAY") == 0) return 11;
	else if(strcmp(lexeme,"JAGGED_ARRAY") == 0) return 12;
	else if(strcmp(lexeme,"RANGES") == 0) return 13;
	else if(strcmp(lexeme,"RANGE") == 0) return 14;
	else if(strcmp(lexeme,"INDEX") == 0) return 15;
	else if(strcmp(lexeme,"DIMJAGGED") == 0) return 16;
	else if(strcmp(lexeme,"MAKEROWS") == 0) return 17;
	else if(strcmp(lexeme,"MAKEROWS2") == 0) return 18;
	else if(strcmp(lexeme,"NUM_LIST") == 0) return 19;
	else if(strcmp(lexeme,"LISTOFNUMLIST") == 0) return 20;
	else if(strcmp(lexeme,"NUMS") == 0) return 21;
	else if(strcmp(lexeme,"ARITHMETICSTATEMENT") == 0) return 22;
	else if(strcmp(lexeme,"LOGICALSTATEMENT") == 0) return 23;
	else if(strcmp(lexeme,"VAR") == 0) return 24;
	else if(strcmp(lexeme,"ARITHMETICOP") == 0) return 25;
	else if(strcmp(lexeme,"INDEX_LIST") == 0) return 26;
	else if(strcmp(lexeme,"ADDSUBOP") == 0) return 27;
	else if(strcmp(lexeme,"TERM") == 0) return 28;
	else if(strcmp(lexeme,"MULTDIVOP") == 0) return 29;
	else if(strcmp(lexeme,"INDEX2") == 0) return 30;
	else if(strcmp(lexeme,"LOGICALOP") == 0) return 31;
	else if(strcmp(lexeme,"LOGICALTERM") == 0) return 32;
	else if(strcmp(lexeme,"LOGICALFACTOR") == 0) return 33;
	
    // tokens
    if(strcmp(lexeme,"ASSIGNOP") == 0) return 0;
	else if(strcmp(lexeme,"SEMICOL") == 0) return 1;
    else if(strcmp(lexeme,"COL") == 0) return 2;
	else if(strcmp(lexeme,"SQBO") == 0) return 3;
	else if(strcmp(lexeme,"SQBC") == 0) return 4;
	else if(strcmp(lexeme,"BO") == 0) return 5;
	else if(strcmp(lexeme,"BC") == 0) return 6;
	else if(strcmp(lexeme,"COMMA") == 0) return 7;
	else if(strcmp(lexeme,"PLUS") == 0) return 8;
	else if(strcmp(lexeme,"MINUS") == 0) return 9;
	else if(strcmp(lexeme,"MUL") == 0) return 10;
	else if(strcmp(lexeme,"DIV") == 0) return 11;
	else if(strcmp(lexeme,"CBO") == 0) return 12;
	else if(strcmp(lexeme,"CBC") == 0) return 13;
	else if(strcmp(lexeme,"PROGRAM") == 0) return 14;
	else if(strcmp(lexeme,"DECLARE") == 0) return 15;
	else if(strcmp(lexeme,"LIST") == 0) return 16;
	else if(strcmp(lexeme,"OF") == 0) return 17;
	else if(strcmp(lexeme,"VARIABLES") == 0) return 18;
	else if(strcmp(lexeme,"ARRAY") == 0) return 19;
	else if(strcmp(lexeme,"SIZE") == 0) return 20;
	else if(strcmp(lexeme,"VALUES") == 0) return 21;
	else if(strcmp(lexeme,"JAGGED") == 0) return 22;
	else if(strcmp(lexeme,"INTEGER") == 0) return 23;
	else if(strcmp(lexeme,"REAL") == 0) return 24;
    else if(strcmp(lexeme,"BOOLEAN") == 0) return 25;
	else if(strcmp(lexeme,"LOGAND") == 0) return 26;
	else if(strcmp(lexeme,"LOGOR") == 0) return 27;
	else if(strcmp(lexeme,"RANGEOP") == 0) return 28;
	else if(strcmp(lexeme,"NUMBER") == 0) return 29;
	else if(strcmp(lexeme,"RNUMBER") == 0) return 30;
	else if(strcmp(lexeme,"VAR_ID") == 0) return 31;
	else if(strcmp(lexeme,"UNKNOWN") == 0) return 32;
	else if(strcmp(lexeme,"VAR_ERR") == 0) return 33;
	else if(strcmp(lexeme,"R1") == 0) return 34;
	else if(strcmp(lexeme,"EPSILON") == 0) return 35;




	else {
		printf(" %s \n",lexeme);
		return 10000;
	}
}


void insert_at_end(rhsnode_ptr *ptr_tail, symbol* sym) {

// to insert at end of stack
  rhsnode_ptr node = (rhsnode_ptr)malloc(sizeof(rhsnode));

  if (node == NULL) {
	printf("Failure to insert at end \n");
	exit(1);
  }
  node->sym = sym;
  node->next = NULL;

//traverse till end 
  if (*ptr_tail != NULL) {
	(*ptr_tail)->next = node;
  }
  *ptr_tail = node;
}



void readGrammar(FILE *fptr,cell* grammar) {

  char buffer[MAX_RHSLEN];
  int no = 0;

  while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
	char *sym_read;
	int i;
// strtok to read one line at atime
	sym_read = strtok(buffer, " \n\r\t");
	for (i = 0; sym_read != NULL; i++) {
	  if (i == 0) 
	  {
		  //to read LHS
		grammar[no].head = NULL;
		grammar[no].tail = NULL;
		grammar[no].lhs = sym_get(sym_read)->nt;
		
	  } else {
		  // to read and convert
		symbol* sym = sym_get(sym_read);
		insert_at_end(&(grammar[no].tail), sym);
		if (grammar[no].head == NULL) {
		  grammar[no].head = grammar[no].tail;
		}
	  }
	  sym_read = strtok(NULL, " \n\r\t");
	}
	no++;
  }
}


symbol* sym_get(char str[]) {
  symbol* sym = (symbol*) malloc(sizeof(symbol));
  if ((str[0] >= 'A') && (str[0] <= 'Z')) {
	
	sym->nt = search_exists(str);
	sym->is_terminal = false;
  } 
  else {

	char tmp[100];
	// converting small to upper alphabets
	strcpy(tmp, str);
	for (int i = 0; i < strlen(tmp); i++) 
	{
	  tmp[i] = toupper(tmp[i]);// to capital
	}
	sym->is_terminal = true;
//check if it exists
	sym->t = search_exists(tmp);
  }
  return sym;
}
