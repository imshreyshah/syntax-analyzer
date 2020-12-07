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
#include "typeExpression.h"
#include <stdbool.h>
#include "treenode.h"
#define MAX_VAR 100

char *storage[MAX_VAR]; //To store variables
int stor_ptr = 0;
char* arr[MAX_VAR*2];// To store range values
int arr_ptr = 0;


int te_ptr = 0;
typeExpressionCell tempcell;


char *enum_to_at[] = {"Primitive", "Rectangular", "Jagged"};
char *enum_to_bt[] = {"Static", "Dynamic", "N/A"};

void traverseParseTree(tree_node *t)
{

    if (t == NULL)
        return;

    init_global_var();
    //root
    if (t->leftmost_child)
    {
        tree_node *temp = t->leftmost_child;
        while (temp != NULL)
        {

            if (t->sym->is_terminal == false)
            {
                if (t->sym->nt == DECLARATIONSTMT)
                {

                    traverseDeclareStmt(t);
                    //Populate the typeExpression table
                }
                else if (t->sym->nt == ASSIGNMENTSTMT)
                {

                    //Check type compatibility from type expression table
                }
            }
            traverseParseTree(temp);
            if (temp != NULL)
            {

                temp = temp->sibling;
            }
        }
    }
}


void traverseDeclareStmt(tree_node *root)
{

    if (root == NULL)
        return;
    if (root->visited == true)
        return;

    if (root->leftmost_child)
    {
        tree_node *temp = root->leftmost_child;

        while (temp != NULL)
        {

            traverseDeclareStmt(temp);
            temp = temp->sibling;
        }
    }

    //TERMINALS
    if (root->sym->is_terminal == true)
    {

        //CHECKS VARID
        if (root->sym->t == VAR_ID)
        {

            if (root->parent->sym->nt == VARIABLE_NAMES || root->parent->sym->nt == DEC)
            {

                if (stor_ptr < MAX_VAR)
                {
                    storage[stor_ptr] = (char *)calloc(1, sizeof(root->token->data.str));
                    strncpy(storage[stor_ptr], root->token->data.str, sizeof(root->token->data.str));
                    stor_ptr++;
                }
                else
                {
                    printf(" ---- LIMIT OF NUMBER OF VARIABLES THAT CAN BE DECLARED IN ONE LINE IS EXCEEDED ----\n");
                }
            }
            else if (root->parent->sym->nt == INDEX)
            {
                tempcell.bt = dynamic_bind;

                arr[arr_ptr] = (char*)calloc(1,sizeof(root->token->data.str));
                strncpy(arr[arr_ptr],root->token->data.str,sizeof(root->token->data.str));
                arr_ptr++;
            }
        }
        else if (root->sym->t == RANGEOP)
        {

            //Check if jagged or rect
            if (tempcell.tag == 1)
            {
                //Increase dimension
                tempcell.te.rt.dim++;
                root->parent->tag = 1;
                root->parent->te.rt.dim++; //CHECK IF WE CAN INITIALIZE DIMENSIONS IN PARENT NODE TO 0
            }
            else if (tempcell.tag == 2)
            {
                tempcell.te.jt.dim = 1;
                root->parent->tag = 2;
                root->parent->te.jt.dim = 1;
            }
        }
        else if (root->sym->t == INTEGER)
        {

            if (root->parent->sym->nt == TYPE)
            {

                char *t = "INTEGER";

                root->parent->tag = 0;
                root->parent->te.pt.type = (char *)calloc(1, sizeof(t));
                strncpy(root->parent->te.pt.type, t, sizeof(t));
                tempcell.te.pt.type = (char *)calloc(1, sizeof(t));
                strncpy(tempcell.te.pt.type, t, sizeof(t));

                tempcell.at = prim;
                tempcell.bt = not_applicable;
                tempcell.tag = 0;
            }
            else
            {

                char *t = "INTEGER";
                //CHECKS IF RECT OR JAGGED
                if (root->parent->sym->nt == RECTANGULAR_ARRAY)
                {
                    root->parent->tag = 1;
                    root->parent->te.rt.elem = (char *)calloc(1, sizeof(t));
                    strncpy(root->parent->te.rt.elem, t, sizeof(t));
                    tempcell.te.rt.elem = (char *)calloc(1, sizeof(t));
                    strncpy(tempcell.te.rt.elem, t, sizeof(t));
                    tempcell.at = rect;
                    tempcell.tag = 1;
                }
                else
                {
                    root->parent->tag = 2;
                    root->parent->te.jt.elem = (char *)calloc(1, strlen(t)+1);
                    strncpy(root->parent->te.jt.elem, t, strlen(t)+1);
                    tempcell.te.jt.elem = (char *)calloc(1, strlen(t)+1);
                    strncpy(tempcell.te.jt.elem, t, strlen(t)+1);
                    tempcell.at = jag;
                    tempcell.bt = not_applicable;
                    tempcell.tag = 2;
                }
            }
        }
        else if (root->sym->t == REAL)
        {

            char *t = "REAL";
            root->parent->tag = 0;
            root->parent->te.pt.type = (char *)calloc(1, sizeof(t));
            strncpy(root->parent->te.pt.type, t, sizeof(t));
            tempcell.te.pt.type = (char *)calloc(1, sizeof(t));
            strncpy(tempcell.te.pt.type, t, sizeof(t));
            tempcell.at = prim;
            tempcell.bt = not_applicable;
            tempcell.tag = 0;
        }
        else if (root->sym->t == BOOLEAN)
        {

            char *t = "BOOLEAN";
            root->parent->tag = 0;
            root->parent->te.pt.type = (char *)calloc(1, sizeof(t));
            strncpy(root->parent->te.pt.type, t, sizeof(t));
            tempcell.te.pt.type = (char *)calloc(1, sizeof(t));
            strncpy(tempcell.te.pt.type, t, sizeof(t));
            tempcell.at = prim;
            tempcell.bt = not_applicable;
            tempcell.tag = 0;
        }
        else if (root->sym->t == JAGGED)
        {
            root->parent->te.jt.type = (char *)calloc(1, strlen("JAGGED_ARRAY") + 1);
            strncpy(root->parent->te.jt.type, "JAGGED_ARRAY", (strlen("JAGGED_ARRAY") + 1));
            tempcell.te.jt.type = (char *)calloc(1, (strlen("JAGGED_ARRAY") + 1));
            strncpy(tempcell.te.jt.type, "JAGGED_ARRAY", (strlen("JAGGED_ARRAY") + 1));
            tempcell.tag = 2;
            tempcell.te.jt.dim = 0;
            root->parent->tag = 2;

        }

        else if (root->sym->t == NUMBER)
        {

            
             if (root->parent->sym->nt == INDEX)
            {
                if(arr_ptr < 2*MAX_VAR)
                {
                    char temp[10];
                    snprintf(temp,10,"%d",root->token->data.num);
                    arr[arr_ptr] = (char*)calloc(1,sizeof(temp));
                    strncpy(arr[arr_ptr],temp,sizeof(temp));
                    arr_ptr++;
                }

                else
                {
                    printf(" ---- ERROR: MAXIMUM STORAGE REACHED TO STORE RANGES -----\n");
                }
            }
            else if (root->parent->sym->is_terminal == false && root->parent->sym->nt == MAKEROWS)
            {
                if(root->sibling->sym->is_terminal == true && root->sibling->sym->t == SQBC)
                {
                    //DO NOTHING AS OF NOW. CHECK ARRAY BOUNDS

                }
                else if(root->sibling->sym->is_terminal == true && root->sibling->sym->t == COL)
                {
                    if(tempcell.te.jt.index < tempcell.te.jt.bound)
                    {
                        tempcell.te.jt.range[tempcell.te.jt.index] = root->token->data.num;
                
                        tempcell.te.jt.index++;
                    }
                    else
                    {
                        printf(" LINE NUM: %d -ERROR IN DECLARATION OF JAGGED ARRAY. DIMENSION MISMATCH AT LINE NUM: %d\n ",root->token->line_no,root->token->line_no);
                    }
                }

            }
            else if(root->parent->sym->is_terminal == false && root->parent->sym->nt == JAGGED_ARRAY)
            {
                root->parent->tag = 2;
                root->tag =2;
                if(root->sibling->sym->t == RANGEOP)
                {
                    tempcell.te.jt.lowerRange = root->token->data.num;
                }
                
                else
                {
                    tempcell.te.jt.upperRange = root->token->data.num;
                    tempcell.te.jt.bound = tempcell.te.jt.upperRange - tempcell.te.jt.lowerRange + 1;
                     if(tempcell.te.jt.bound <= 0)
                    {
                        printf(" LINE NUM: %d -ERROR UPPER BOUND CANNOT BE LESSER THAN LOWER BOUND\n ",root->token->line_no);
                        exit(1);
                    }
                    tempcell.te.jt.range = (int*)calloc(1,sizeof(int)*(tempcell.te.jt.upperRange - tempcell.te.jt.lowerRange + 1));
                    
                    tempcell.te.jt.index = 0;
                   
                }
            }

        }
    
        
        else if (root->sym->t == SQBO)
        {
            if (root->parent->sym->nt == JAGGED_ARRAY || root->parent->sym->nt == DIMJAGGED)
            {
                tempcell.te.jt.dim++;
                root->parent->te.jt.dim++;
                root->parent->tag = 2;
            }
        }

        else if (root->sym->t == SEMICOL && root->sibling == NULL)
        {
            //We are the end of the line
            for (int i = 0; i < stor_ptr; i++)
            {

                strncpy(typeExpressionTable[te_ptr].name, storage[i], sizeof(storage[i]));
                typeExpressionTable[te_ptr].at = tempcell.at;
                typeExpressionTable[te_ptr].bt = tempcell.bt;
                //CHECK TAG AND THEN ALLOCATE
                if (tempcell.tag == 0)
                {
                    root->parent->te.pt = tempcell.te.pt;
                    root->parent->tag = 0;
                    typeExpressionTable[te_ptr].tag = 0;
                    typeExpressionTable[te_ptr].te.pt.type = (char *)calloc(1, strlen(tempcell.te.pt.type) + 1);
                    strncpy(typeExpressionTable[te_ptr].te.pt.type, tempcell.te.pt.type, sizeof(tempcell.te.pt.type));
                }
                else if (tempcell.tag == 1)
                {
                    root->parent->te.rt = tempcell.te.rt;
                    root->parent->tag = 1;
                    typeExpressionTable[te_ptr].tag = 1;
                    typeExpressionTable[te_ptr].te.rt.range_rt = (char**)calloc(1,sizeof(char*)*arr_ptr);
                    //typeExpressionTable[te_ptr].te.rt.range_rt = (int*)calloc(1,sizeof(int)*arr_ptr);
                    for(int i=0; i < arr_ptr;i++)
                    {
                        
                        typeExpressionTable[te_ptr].te.rt.range_rt[i] = (char*)calloc(1,sizeof(char)* (strlen(arr[i]) + 1 ));
                        strncpy(typeExpressionTable[te_ptr].te.rt.range_rt[i], arr[i],sizeof(char)* (strlen(arr[i]) + 1 ));

                    }
                    typeExpressionTable[te_ptr].te.rt.bound = arr_ptr;
                    typeExpressionTable[te_ptr].te.rt.type = (char *)calloc(1, strlen(tempcell.te.rt.type) + 1);
                    strncpy(typeExpressionTable[te_ptr].te.rt.type, tempcell.te.rt.type, strlen(tempcell.te.rt.type) + 1);
                    typeExpressionTable[te_ptr].te.rt.dim = tempcell.te.rt.dim;
                    typeExpressionTable[te_ptr].te.rt.elem = (char *)calloc(1, strlen(tempcell.te.rt.elem) + 1);
                    strncpy(typeExpressionTable[te_ptr].te.rt.elem, tempcell.te.rt.elem, strlen(tempcell.te.rt.elem) + 1);
                }
                /*
                else
                {
                    root->parent->te.jt = tempcell.te.jt;
                    root->parent->tag = 2;
                    typeExpressionTable[te_ptr].tag = 2;
                    typeExpressionTable[te_ptr].te.jt.type = (char *)calloc(1, strlen(tempcell.te.jt.type) + 1);
                    strncpy(typeExpressionTable[te_ptr].te.jt.type, tempcell.te.jt.type, strlen(tempcell.te.jt.type) + 1);
                    typeExpressionTable[te_ptr].te.jt.dim = tempcell.te.jt.dim;
                    typeExpressionTable[te_ptr].te.jt.elem = (char *)calloc(1, strlen(tempcell.te.jt.elem) + 1);
                    strncpy(typeExpressionTable[te_ptr].te.jt.elem, tempcell.te.jt.elem, strlen(tempcell.te.jt.elem) + 1);
                    //FILLING BOUND, INDEX, LOWER RANGE AND UPPER RANGE
                    typeExpressionTable[te_ptr].te.jt.bound = tempcell.te.jt.bound;
                    typeExpressionTable[te_ptr].te.jt.index = tempcell.te.jt.index;
                    typeExpressionTable[te_ptr].te.jt.lowerRange = tempcell.te.jt.lowerRange;
                    typeExpressionTable[te_ptr].te.jt.upperRange = tempcell.te.jt.upperRange;
                }
                */
                te_ptr++;

                if (te_ptr >= 100)
                {
                    printf("LINE NO: %d--STROAGE IN TYPEEXPRESSION TABLE IS EXCEEDED---\n",root->token->line_no);
                }
            }
            if(root->sibling == NULL)
            {
                init_global_var();
            } 
        }
        
        else if(root->sym->t == EPSILON && root->parent->parent->rightmost_child->sym->nt == MAKEROWS2 )//&& root->parent->sym->nt == MAKEROWS2 )
        {
            if(root->parent->sym->is_terminal == false && root->parent->sym->nt == MAKEROWS2)
            {
               for (int i = 0; i < stor_ptr; i++)
                {   
                    strncpy(typeExpressionTable[te_ptr].name, storage[i], sizeof(storage[i]));
                    typeExpressionTable[te_ptr].at = tempcell.at;
                    typeExpressionTable[te_ptr].bt = tempcell.bt;
                   //FILLING UP TEH JAGGED ARRAY
                    root->parent->te.jt = tempcell.te.jt;
                    root->parent->tag = 2;
                    //FILLING TAG
                    typeExpressionTable[te_ptr].tag = 2;
                    //FILLING TYPE OF ARRAY
                    typeExpressionTable[te_ptr].te.jt.type = (char *)calloc(1, strlen(tempcell.te.jt.type) + 1);
                    strncpy(typeExpressionTable[te_ptr].te.jt.type, tempcell.te.jt.type, strlen(tempcell.te.jt.type) + 1);
                    //FILLING DIMS
                    typeExpressionTable[te_ptr].te.jt.dim = tempcell.te.jt.dim;
                    //FILLING BASIC ELEMENT TYPE
                    typeExpressionTable[te_ptr].te.jt.elem = (char *)calloc(1, strlen(tempcell.te.jt.elem) + 1);
                    strncpy(typeExpressionTable[te_ptr].te.jt.elem, tempcell.te.jt.elem, strlen(tempcell.te.jt.elem) + 1);
                    //FILLING BOUND, INDEX, LOWER RANGE AND UPPER RANGE
                    typeExpressionTable[te_ptr].te.jt.bound = tempcell.te.jt.bound;
                    typeExpressionTable[te_ptr].te.jt.index = tempcell.te.jt.index;
                    typeExpressionTable[te_ptr].te.jt.lowerRange = tempcell.te.jt.lowerRange;
                    typeExpressionTable[te_ptr].te.jt.upperRange = tempcell.te.jt.upperRange;
                    //CHECK DIMS AND ASSIGN RANGE
                    if(tempcell.te.jt.dim == 2)
                    {
                        //FILL only RANGE
                        typeExpressionTable[te_ptr].te.jt.range = (int*)calloc(1,sizeof(int)*tempcell.te.jt.bound);
                        for(int i=0; i < tempcell.te.jt.bound;i++)
                        {   
                            
                        
                            typeExpressionTable[te_ptr].te.jt.range[i] = tempcell.te.jt.range[i];
                            
                        /*else
                        {
                                printf("\n\n ERROR IN JAGGED ARRAY DECLARATION AT LINE NUMBER: %d \n\n ",root->token->line_no);
                        }*/
                        }

                    }
                    else if(tempcell.te.jt.dim == 3)
                    {
                        //FILL RANGE and 3D range
                         //FILL only RANGE
                        typeExpressionTable[te_ptr].te.jt.range = (int*)calloc(1,sizeof(int)*tempcell.te.jt.bound);
                        for(int i=0; i < tempcell.te.jt.bound;i++)
                        {   
                            
                        
                            typeExpressionTable[te_ptr].te.jt.range[i] = tempcell.te.jt.range[i];
                            
                        /*else
                        {
                                printf("\n\n ERROR IN JAGGED ARRAY DECLARATION AT LINE NUMBER: %d \n\n ",root->token->line_no);
                        }*/
                        }


                    }

                    te_ptr++;
                    if (te_ptr >= 100)
                    {
                        printf("--STROAGE IN TYPEEXPRESSION TABLE IS EXCEEDED---\n");
                    }
                }
                
            }
        
        init_global_var();
        }
        
    
    }
    else
    {
        
        //NON TERMINALS
        
        
        if(root->sym->nt == SINGLE || root->sym->nt == RECTANGULAR_ARRAY || root->sym->nt == JAGGED_ARRAY 
            || root->sym->nt == LISTOFNUMLIST ||root->sym->nt == NUM_LIST || root->sym->nt == DEC 
            || root->sym->nt == DECLARATIONSTMT || root->sym->nt == ARRAYTYPE || root->sym->nt == MAKEROWS
            || root->sym->nt == MAKEROWS2)
        {
            if(root->tag == 0)
            {
                root->parent->tag = 0;
                root->parent->te.pt = root->te.pt;
            }
            else if(root->tag == 1)
            {
                root->parent->tag = 1;
                root->parent->te.rt = root->te.rt;

            }
            else if(root->tag == 2)
            {
                root->parent->tag = 2;
                root->parent->te.jt = root->te.jt;

            }
        }


        else if(root->sym->nt == RANGES || root->sym->nt == RANGE)
        {
            if(root->tag == 1)
            {
                root->parent->tag = 1;
                root->parent->te.rt.dim += root->te.rt.dim;

            }
            else if(root->tag == 2)
            {
                root->parent->tag = 2;
                root->parent->te.jt.dim += root->te.jt.dim;

            }
        }

        else if(root->sym->nt == DIMJAGGED)
        {
            if(root->tag == 2)
            {
                root->parent->tag = 2;
                root->parent->te.jt.dim += root->te.jt.dim;

            }
        }


    
    
    }

    root->visited = true;

    return;
}

void init_global_var()
{
    stor_ptr = 0;
    tempcell.tag = 1;
    tempcell.te.rt.dim = 0;
    tempcell.bt = static_bind;
    char *t = "RECTANGULAR_ARRAY";
    tempcell.te.rt.type = (char *)calloc(1, (strlen("RECTANGULAR_ARRAY") + 1));

    strncpy(tempcell.te.rt.type, t, strlen("RECTANGULAR_ARRAY") + 1);

    arr_ptr = 0;
}

/*
void printTypeexpressiontable()
{
    for (int i = 0; i < 30; i++)
    {
        if (typeExpressionTable[i].tag == 0)
            printf("%s %d %d %s\n", typeExpressionTable[i].name, typeExpressionTable[i].at, typeExpressionTable[i].bt, typeExpressionTable[i].te.pt.type);

        else if (typeExpressionTable[i].tag == 1)
        {
        
            printf("%s %d %d %s %d %s\n", typeExpressionTable[i].name, typeExpressionTable[i].at, typeExpressionTable[i].bt, typeExpressionTable[i].te.rt.type, typeExpressionTable[i].te.rt.dim, typeExpressionTable[i].te.rt.elem);
            for(int j=0 ; j < typeExpressionTable[i].te.rt.bound;j++)
            {
                printf(" %s \n,",typeExpressionTable[i].te.rt.range_rt[j]);
            }
        }
        else if (typeExpressionTable[i].tag == 2)
        {
            printf("%s %d %d %s %d %s\n", typeExpressionTable[i].name, typeExpressionTable[i].at, typeExpressionTable[i].bt, typeExpressionTable[i].te.jt.type, typeExpressionTable[i].te.jt.dim, typeExpressionTable[i].te.jt.elem);
            printf("LOWER RANGE:%d UPPER RANGE: %d \n",typeExpressionTable[i].te.jt.lowerRange,typeExpressionTable[i].te.jt.upperRange);
            
            
            printf(" RANGE R2 \n");
            for(int j = 0; j < typeExpressionTable[i].te.jt.bound;j++)
            {
                printf(" %d ",typeExpressionTable[i].te.jt.range[j]);
            }
            printf(" \n");
            
            
        }
    }
    return;
}

*/
void printTypeexpressiontable()
{
    pretty_print("Variable Name");
    pretty_print("Type");
    pretty_print("BindingType");
    pretty_print("TypeExpression");
    printf("\n\n");
    for (int i = 0; i < te_ptr; i++)
    {
        if (typeExpressionTable[i].tag == 0)
        {
            char s[15];
            for (int i = 0; i < 15; i++)
            {
                s[i] = '\0';
            }
            pretty_print(typeExpressionTable[i].name);
            snprintf(s, 15, "%s", enum_to_at[typeExpressionTable[i].at]);
            pretty_print(s);
            snprintf(s, 15, "%s", enum_to_bt[typeExpressionTable[i].bt]);
            pretty_print(s);
            printf(" <type = %s >\n",typeExpressionTable[i].te.pt.type);
            //pretty_print(typeExpressionTable[i].te.pt.type);
            printf("\n\n");
        }
        else if (typeExpressionTable[i].tag == 1)
        {
            char s[15];
            for (int i = 0; i < 15; i++)
            {
                s[i] = '\0';
            }
            pretty_print(typeExpressionTable[i].name);
            snprintf(s, 15, "%s", enum_to_at[typeExpressionTable[i].at]);
            pretty_print(s);
            snprintf(s, 15, "%s", enum_to_bt[typeExpressionTable[i].bt]);
            pretty_print(s);
            
            //pretty_print(typeExpressionTable[i].te.rt.type);
            //snprintf(s, 15, "%d", typeExpressionTable[i].te.rt.dim);
            //pretty_print(s);
            //pretty_print(typeExpressionTable[i].te.rt.elem);
            printf(" <type = %s, dim = %d, ",typeExpressionTable[i].te.rt.type,typeExpressionTable[i].te.rt.dim);
            for(int j = 0; j< typeExpressionTable[i].te.rt.bound;j+= 2)
            {
                printf("range_R%d=(%s,%s), ",((j/2)+1),typeExpressionTable[i].te.rt.range_rt[j],typeExpressionTable[i].te.rt.range_rt[j+1]);
            }
            printf("basicElementType = %s",typeExpressionTable[i].te.rt.elem);
            printf(">");
            printf("\n");

            printf("\n\n");
            
            //printf("%s %d %d %s %d %s\n", typeExpressionTable[i].name, typeExpressionTable[i].at, typeExpressionTable[i].bt,typeExpressionTable[i].te.rt.type,typeExpressionTable[i].te.rt.dim,typeExpressionTable[i].te.rt.elem);
        }
        else if (typeExpressionTable[i].tag == 2)
        {
            char s[15];
            for (int i = 0; i < 15; i++)
            {
                s[i] = '\0';
            }
            pretty_print(typeExpressionTable[i].name);
            snprintf(s, 15, "%s", enum_to_at[typeExpressionTable[i].at]);
            pretty_print(s);
            snprintf(s, 15, "%s", enum_to_bt[typeExpressionTable[i].bt]);
            pretty_print(s);
            //pretty_print(typeExpressionTable[i].te.jt.type);
            //snprintf(s, 15, "%d",typeExpressionTable[i].te.jt.dim);
            //pretty_print(s);
            //pretty_print(typeExpressionTable[i].te.jt.elem);

            printf(" <type = %s, dim = %d, ",typeExpressionTable[i].te.jt.type,typeExpressionTable[i].te.jt.dim);
            printf("range_R1=(%d,%d), range_R2=(",typeExpressionTable[i].te.jt.lowerRange,typeExpressionTable[i].te.jt.upperRange);
            for(int j = 0; j< typeExpressionTable[i].te.jt.bound-1;j++)
            {
                printf("%d,",typeExpressionTable[i].te.jt.range[j]);
            }
            printf("%d),",typeExpressionTable[i].te.jt.range[typeExpressionTable[i].te.jt.bound-1]);
            printf(" basicElementType = %s",typeExpressionTable[i].te.jt.elem);
            printf(">");
            printf("\n");
            printf("\n\n");



            //printf("%s %d %d %s %d %s\n", typeExpressionTable[i].name, typeExpressionTable[i].at, typeExpressionTable[i].bt, typeExpressionTable[i].te.jt.type, typeExpressionTable[i].te.jt.dim, typeExpressionTable[i].te.jt.elem);
        }
    }
    te_ptr = 0;

    printf(" \n\n ----TYPE EXPRESSION TABLE PRINTED SUCCESSFULLY---- \n\n \n");
    return;
}

