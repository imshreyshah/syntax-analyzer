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
# define GRAMMAR_SIZE 100 // check the final length of grammar which is not 100 atleast now
# define HASHTAG 10000

#include<stdio.h>
#include<stdlib.h>
#include "treenode.h"

char* enum_to_token[] = {
  "ASSIGNOP","SEMICOL", "COL", "SQBO", "SQBC", "BO","BC","COMMA","PLUS","MINUS","MUL","DIV",
  "CBO","CBC","PROGRAM", "DECLARE","LIST","OF","VARIABLES","ARRAY","SIZE",
  "VALUES","JAGGED","INTEGER","REAL","BOOLEAN","LOGAND","LOGOR",
  "RANGEOP","NUMBER","RNUMBER","VAR_ID","UNKNOWN","VAR_ERR","R1","EPSILON"};

char* enum_to_nonterm[] = {
"START","MAINPROGRAM","DECLARATIONSTMTS","ASSIGNMENTSTMTS","DECLARATIONSTMT","ASSIGNMENTSTMT","DEC",
"SINGLE","TYPE","ARRAYTYPE","VARIABLE_NAMES","RECTANGULAR_ARRAY","JAGGED_ARRAY","RANGES","RANGE",
"INDEX","DIMJAGGED","MAKEROWS","MAKEROWS2","NUM_LIST",
"LISTOFNUMLIST","NUMS","ARITHMETICSTATEMENT","LOGICALSTATEMENT","VAR","ARITHMETICOP","INDEX_LIST",
"ADDSUBOP","TERM","MULTDIVOP","INDEX2","LOGICALOP","LOGICALTERM","LOGICALFACTOR"};


void add_child(tree_node *parent, tree_node *child) {
  if (parent->rightmost_child == NULL) {
    parent->leftmost_child = child;
    parent->rightmost_child = child;
  } else {
    parent->rightmost_child->sibling = child;
    parent->rightmost_child = child;
  }
  parent->num_child++;
  child->parent = parent;
  child->sibling = NULL;
  
}

void deallocate1(tree_node* node)
{
  //do nothing if passed a non-existent node
    if(node == NULL)
        return;
    //now onto the recursion
    deallocate1(node->leftmost_child);
    deallocate1(node->sibling);
    // KEPP THIS FOR AFTER WARDS num_tree_nodes--;
    //free(node);
}



tree_node *createParseTree(tokenStream* streamHead, cell* grammar)
{
  stack *main_stack = initStack();
  stack *aux_stack = initStack();
  tree_node *root = create_tree_node();

  /******************************************************************************************************************/

  root->sym->nt = START;    // FIRST WORD 

  /******************************************************************************************************************/
  root->sym->is_terminal = false; // THIS MEANS 1st word is not terminal
  push(main_stack, root);        // push start symbol on stack
  tokenStream *tkn = streamHead; // gives the next token

  int present_rule_no = 0; // FOR every new non terminal start with 0 and when backtracking continue with the stored rule_no + 1
  // This is a pointer_to_traverse_grammar

  tree_node *last_popped_nt_node; // USE THIS AHEAD SOMEHWERE

  while (true)
  {
    //num_tree_nodes++;
    tree_node *node = (tree_node *)pop(main_stack);

    if(tkn == NULL)              //    if(tkn.name == NULL)  //HASHTAG) // HASHTAG an ending symbol to mark the end of source code
    {
      if(node != NULL)
        printf(" This is an error: STACK NOT EMPTIED but SOURCE CODE is finished parsing \n");
      break;
    }
    if(node == NULL)
    {
        if(tkn == NULL)        //if(tkn.name != NULL)//HASHTAG)
        printf(" This is an error: STACK EMPTIED but still symbols are left in source code \n");
      
    break;
    } // This is when source code ends? but what if just the stack became empty?
    // add a symbol at the end of source code to check if that is what we have reached

    if ((node != NULL) && (node->sym)->is_terminal == true)
    {
      
      //CHECK IF WE REALLY NEED THIS EPSILON
      
      if (node->sym->t == EPSILON)
      {
        node->token->name = EPSILON;
        strncpy(node->token->data.str, "epsilon", 21);
        continue;
      }

      if (node->sym->t != tkn->name) // terminal on top of stack does not match
                                   // with lookhead symbol
      {
        // Make a function ot free children nodes : make the pointer of the parent to its chilren as NULL and also update
        // its no of childten count and also free the nodes to save memory
        //TREENODE *popped = pop(main_stack);
        tree_node* popped;
        popped = node;

        
        while (popped->last_popped_nt == NULL)
        {
          popped = pop(main_stack); 
        }

        last_popped_nt_node = popped->last_popped_nt; 
        last_popped_nt_node->rule_no += 1;
        present_rule_no = last_popped_nt_node->rule_no;
        
        deallocate1(last_popped_nt_node->leftmost_child);
        free(last_popped_nt_node->leftmost_child);

        last_popped_nt_node->num_child = 0;

        last_popped_nt_node->leftmost_child = NULL;
        last_popped_nt_node->rightmost_child = NULL;
        tkn = last_popped_nt_node->prev_stream_pointer;
        push(main_stack,last_popped_nt_node);
        //printf("%u no match\n",tkn->name);
        continue;
      }

      if (node->sym->t == tkn->name)
      {

        node->token->line_no = tkn->line_no;// DONT KNOW WHY saving the line_no
        node->token->name = tkn->name; // why???- > TYPE EXPRESSINO K LIYE
        switch(tkn->name)
        {
        case NUMBER:
          node->token->data.num = tkn->data.num;
          break;

        case RNUMBER:
          node->token->data.rnum = tkn->data.rnum;
          break;

        default:
          //node->token->data.str = (char *)malloc(sizeof(21));
          strncpy(node->token->data.str, tkn->data.str, 21);
          //printf("%s\n",node->token->data.str);
        }

        tkn = tkn->next;
        //printf("%u match\n",node->sym->t + 1);
        //pop(main_stack); // AS OF NOW THIS IS REPEATED POP SINCE WE HAVE ALREADY POPPED JUST AFTER WHILE
        continue;
      }
    }
    else
    //if ((node != NULL) && (node->sym).is_terminal == false) // make this one else both are same
    // We are always assuming node is not null
    {
      //printf("%d non terminal expansion\n", node->sym->nt + 1);
      //node->rule_no = present_rule_no;
      present_rule_no = node->rule_no; // we'll have to intitalize rule_no of every node as 0
      //printf("gtg/n");
      while(grammar[present_rule_no].lhs != node->sym->nt) 
      {
        if(present_rule_no >= GRAMMAR_SIZE) break;
        present_rule_no++; 
      }
      if(present_rule_no >= GRAMMAR_SIZE) {
        tree_node* popped;
        popped = node;
       
        while (popped->last_popped_nt == NULL)
        {
          popped = pop(main_stack); 
        }

        last_popped_nt_node = popped->last_popped_nt; 
        last_popped_nt_node->rule_no += 1;
        present_rule_no = last_popped_nt_node->rule_no;
        
        deallocate1(last_popped_nt_node->leftmost_child);
        free(last_popped_nt_node->leftmost_child);

        last_popped_nt_node->num_child = 0;

        last_popped_nt_node->leftmost_child = NULL;
        last_popped_nt_node->rightmost_child = NULL;
        tkn = last_popped_nt_node->prev_stream_pointer;
        push(main_stack,last_popped_nt_node);
        continue; 
      }// also add a ending condition when it ends normally 
      // GRAMMAR_SIZE : hardcoded size of the grammar

      cell rule = grammar[present_rule_no];
      node->rule_no = present_rule_no;
      rhsnode_ptr rhs_ptr = rule.head;
      tree_node *temp;

      while(rhs_ptr != NULL)
      {
        temp = create_tree_node();
        
        temp->parent = node;

        temp->depth = node->depth + 1;
      
        temp->sym = rhs_ptr->sym;
      
        add_child(node, temp);
      
        push(aux_stack, temp);
      

        rhs_ptr = rhs_ptr->next;

      }

      node->prev_stream_pointer = tkn;
      temp->last_popped_nt = node;
      temp = (tree_node*)pop(aux_stack);

      while(temp != NULL)
      {
        push(main_stack, temp);
        temp = (tree_node*)pop(aux_stack);
      }

    }
  }
  printf(" \n\n");
  printf(" ----PARSE TREE IS CREATED SUCCESSFULLY---- \n\n \n");
  return root;
}


  




tree_node *create_tree_node() {

  tree_node* node = (tree_node*)malloc(sizeof(tree_node));
  node->tag = -1;
  
  if (node == NULL) {
    perror("tree_node allocation error..\n");
    exit(0);
  }

  node->visited = false;
  node->parent = NULL;
  node->sibling = NULL;
  
  node->leftmost_child = NULL;
  node->rightmost_child = NULL;
  
  node->sym = (symbol* )malloc(sizeof(symbol));
  node->token = (tokenStream* )malloc(sizeof(tokenStream));
  node->depth = 0;

  node->num_child = 0;
  strncpy(node->token->data.str, "", 21);

  node->rule_no = 0; // specially done
  node->last_popped_nt = NULL;// specially done
  node->prev_stream_pointer = NULL;
  return node;


}

void print_parse_tree(tree_node *root, cell G[]) {
	if (root == NULL) return;
  	
  print_node(root,G);
	
  if (root->leftmost_child)
  {
		tree_node *temp = root->leftmost_child;

		while (temp != NULL) 
		{
			print_parse_tree(temp,G);
			temp = temp->sibling;
		}
  }

}

void print_node(tree_node *node, cell G[]) 
{
	char s[100];
	for (int i = 0; i < LEX_MAX_LEN; i++) 
	{
		s[i] = '\0';
	}

	if(node == NULL){
		return;
  }

	bool is_terminal = node->sym->is_terminal;

	if (is_terminal == true){
        pretty_print( enum_to_token[node->sym->t] );
        pretty_print("Terminal");
        pretty_print("-----");
        if((node->token)->name==NUMBER)
        {
          snprintf(s, LEX_MAX_LEN, "%d", (node->token)->data.num);
          pretty_print(s);            
        }
        else if((node->token)->name==RNUMBER)
        {
			    snprintf(s, LEX_MAX_LEN, "%f", (node->token)->data.rnum);
			    pretty_print(s);
        }
        else
        {
          //snprintf(s, LEX_MAX_LEN, "%s", (node->token)->data.str);
          snprintf(s, 21, "%s", node->token->data.str);
          //printf("%s\n", node->token->data.str);
          pretty_print(s);           
        }        
        snprintf(s, LEX_MAX_LEN, "%d", (node->token)->line_no);
		    pretty_print(s);
        snprintf(s, LEX_MAX_LEN, "%d", node->depth);
        pretty_print(s);
        //pretty_print();//Depth
        printf("\n\n");
        printf("\n\n");
	} 
	else 
	{

    pretty_print( enum_to_nonterm[node->sym->nt]);
		pretty_print("Non Terminal");
		//pretty_print();//Type Expression
		pretty_print("----");
		pretty_print("----");
    pretty_print("----");

    snprintf(s, LEX_MAX_LEN, "%d", node->depth);
    pretty_print(s);

    tree_node* t1 = node->leftmost_child;
    char* st = (char*) malloc(20*sizeof(char));
    if(t1!= NULL){
      if(t1->sym->is_terminal)
        st = enum_to_token[t1->sym->t];
      else
        st = enum_to_nonterm[t1->sym->nt];
      printf(" %s ==>"  ,enum_to_nonterm[node->sym->nt]);
      t1 = t1->sibling;
      printf(" %s ",st);
      //pretty_print(st);
    }
    while(t1 != NULL){
      if(t1->sym->is_terminal)
        st = enum_to_token[t1->sym->t];
      else
        st = enum_to_nonterm[t1->sym->nt];
      printf("%s ",st); //(st);
      t1 = t1->sibling;
    }
        //pretty_print();//Depth
        printf("\n\n");
        printf("\n\n");
	}
}

void pretty_print(char *s) {
	int cols = 18;
    int len, lt_margin;

	len = strlen(s);
	lt_margin = (cols - len) / 2;

	for (int i = 0; i < lt_margin; i++)
	{
		printf(" ");
	}

	printf("%s", s);
	
	int rt_margin = lt_margin;
	
	if (len % 2 == 1)
		rt_margin++;
	for (int i = 0; i < rt_margin; i++) 
	{
		printf(" ");
	}
	
	printf("|");
}


