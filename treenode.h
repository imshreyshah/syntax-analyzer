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
#ifndef TREENODE_H
#define TREENODE_H

#include<string.h>
#include "grammar_parser.h"
#include "stackdef.h"
//#include "lexer.h"
#include<stdbool.h>
#include <stdlib.h>
#include "typeExpression.h"

typedef struct TREENODE
  {
    struct TREENODE *parent;
    struct TREENODE *sibling;
    struct TREENODE *leftmost_child;
    struct TREENODE *rightmost_child;
    
    struct TREENODE *last_popped_nt;
    int rule_no;
    tokenStream* prev_stream_pointer;
    symbol* sym; //simplify this
    tokenStream* token;
    int num_child; // make this 0 when emptied
    bool visited;
    int depth;

    int tag;
    union TypeExpression te;

  }tree_node;


tree_node* create_tree_node();
void add_child(tree_node* parent,tree_node* child);
void deallocate1(tree_node* node);
tree_node *createParseTree(tokenStream* streamHead, cell grammar[]);
void pretty_print(char *s);
void print_node(tree_node *node, cell grammar[]);
void print_parse_tree(tree_node *root, cell grammar[]);
void traverseParseTree(tree_node* t);
void traverse(tree_node* root);
void traverseDeclareStmt(tree_node* root);

#endif