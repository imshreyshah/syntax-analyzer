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
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "grammar_parser.h"
#include "treenode.h"
#include "stackdef.h"
#include "lexer.h"
#include "typeExpression.h"


void print_menu() {
	printf("\t\t Press the option for the defined task\n");
	printf("===================================================================\n");
	printf("0. Exit\n");
	printf("1. Create parse tree\n");
	printf("2. Traverse the parse tree to construct typeExpressionTable. Also print the type errors while traversing the parse tree and accessing the typeExpressionTable.\n");
	printf("3. Print parse tree in the specified format\n");
	printf("4. Print typeExpressionTable in the specified format\n");
	printf("===================================================================\n");
	printf("Enter your choice:  ");
}
int main(int argc, char *argv[]) {
	cell grammar[100];
	int choice;
	char source_file[25];
	tokenStreamHead* streamHead = (tokenStreamHead* )malloc(sizeof(tokenStreamHead)); 
    streamHead->head = NULL;
	strncpy(source_file, argv[1], 25);

	FILE *source = fopen(source_file, "r");
	if (source == NULL) {
		printf("Error opening file\n");
	}

	while (true) {
		print_menu();
		printf("Enter Choice: ");
		scanf("%d", &choice);
		printf("\n");

		switch (choice) {
			case 0:
			{
				exit(0);
			}
			break;

			case 1:
			{
                FILE *fptr = fopen("grammar.txt", "r");
				if(fptr == NULL) 
				{
					perror("fopen");
				}
				
                readGrammar(fptr, grammar);
                tokeniseSourceCode(source, streamHead);
				
				tree_node* temp = createParseTree(streamHead->head, grammar);
				
			} 
				break;

			case 2: 
			{
                FILE *fptr = fopen("grammar.txt", "r");
				if(fptr == NULL) 
				{
					perror("fopen");
				}
                readGrammar(fptr, grammar);
                tokeniseSourceCode(source, streamHead);
			} 
			break;
			
			case 3:
			{
				
                FILE *fptr = fopen("grammar.txt", "r");
				if(fptr == NULL) 
				{
					perror("fopen");
				}
                readGrammar(fptr, grammar);
                tokeniseSourceCode(source, streamHead);
			
				tree_node* temp = createParseTree(streamHead->head, grammar);
				pretty_print("Symbol Name");
				pretty_print("Terminal/Non Terminal");
    			pretty_print("Type Expression");
    			pretty_print("Name of lexeme");
    			pretty_print("Line Number");
    			pretty_print("Depth of node");
    			pretty_print("Grammar Rule");
    			printf("\n\n");
				print_parse_tree(temp, grammar);
				printf(" \n\n ----PARSE TREE PRINTED SUCCESSFULLY---- \n\n \n");
			}
				break;
			
			case 4: 
			{
                FILE *fptr = fopen("grammar.txt", "r");
				if(fptr == NULL) 
				{
					perror("fopen");
				}
                readGrammar(fptr, grammar);
                tokeniseSourceCode(source, streamHead);
				tree_node* temp = createParseTree(streamHead->head, grammar);
				traverseParseTree(temp);
				printTypeexpressiontable();
			} 
			break;
			default: 
			{
				exit(0);
			}
			break;
		} // end of switch
	}
	fclose(source);
} // end of main

