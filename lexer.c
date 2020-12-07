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

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include <ctype.h>

token_name give_token_enum(char* s){
    token_name t;
    if(strcmp(s,"=")==0){
        t = ASSIGNOP;
    }
    else if(strcmp(s,"program")==0){
        t = PROGRAM;
    }
    else if(strcmp(s,";")==0){
        t = SEMICOL;
    }
    else if(strcmp(s,":")==0){
        t = COL;
    }
    else if(strcmp(s,"[")==0){
        t = SQBO;
    }
    else if(strcmp(s,"]")==0){
        t = SQBC;
    }
    else if(strcmp(s,"(")==0){
        t = BO;
    }
    else if(strcmp(s,")")==0){
        t = BC;
    }
    else if(strcmp(s,",")==0){
        t = COMMA;
    }
    else if(strcmp(s,"+")==0){
        t = PLUS;
    }
    else if(strcmp(s,"-")==0){
        t = MINUS;
    }
    else if(strcmp(s,"*")==0){
        t = MUL;
    }
    else if(strcmp(s,"/")==0){
        t = DIV;
    }
    else if(strcmp(s,"{")==0){
        t = CBO;
    }
    else if(strcmp(s,"}")==0){
        t = CBC;
    }
    else if(strcmp(s,"program")==0){
        t = DECLARE;
    }
    else if(strcmp(s,"declare")==0){
        t = DECLARE;
    }
    else if(strcmp(s,"list")==0){
        t = LIST;
    }
    else if(strcmp(s,"of")==0){
        t = OF;
    }
    else if(strcmp(s,"variables")==0){
        t = VARIABLES;
    }
    else if(strcmp(s,"array")==0){
        t = ARRAY;
    }
    else if(strcmp(s,"size")==0){
        t = SIZE;
    }
    else if(strcmp(s,"values")==0){
        t = VALUES;
    }
    else if(strcmp(s,"jagged")==0){
        t = JAGGED;
    }
    else if(strcmp(s,"integer")==0){
        t = INTEGER;
    }
    else if(strcmp(s,"real")==0){
        t = REAL;
    }
    else if(strcmp(s,"boolean")==0){
        t = BOOLEAN;
    }
    else if(strcmp(s,"&&&")==0){
        t = LOGAND;
    }
    else if(strcmp(s,"|||")==0){
        t = LOGOR;
    }
    else if(strcmp(s,"..")==0){
        t = RANGEOP;
    }
    else if(strcmp(s,"R1")==0){
        t = R1;
    }
    else{
        int length = strlen(s);

        if(length > 20){
            printf("VARIABLE NAMES SHOULD BE OF LENGTH LESS THAN EQUAL TO 20. ABORTING CODE");
            exit(1);
        }

        int id_flag=0;
        int num_flag=0;
        if(isalpha(s[0])||s[0]=='_'){
            int i;
            for(i=1;i<length;i++){
                if((!isalpha(s[i]))&&(!isdigit(s[i]))&&(s[i]!='_')){
                    id_flag=1;
                    printf("%c %c problem\n", s[i], s[i-1]);
                    break;
                }
            }
            if(id_flag==0){
                t= VAR_ID; //Identifier token
            }
            else{
                t= UNKNOWN; //Unknown token
            }    
        }
        else if(isdigit(s[0])){
        
            int j;
            for(j=1;j<length;j++){
            
                if(!isdigit(s[j])){
    
                    if(s[j]=='.'){ //To check for real numbers
                        
                        if(num_flag==2){ //To check if '.' was already encountered
                            num_flag=1;
                            break;
                        }
                        else{
                            num_flag=2;
                            continue;
                        }
                    }
                    else{
                        num_flag=1;
                        break;
                    }
                }
            }
            if(num_flag==0)
            {
                t= NUMBER; //Integer number
            }
            else if(num_flag==1)
            {
                t = UNKNOWN;
            }
            else
            {
                t = RNUMBER; //Real number
            }
        }
        else
        {
            t = UNKNOWN;
        }
    }
    
    return t;
}


void tokeniseSourceCode(FILE *f, tokenStreamHead* streamHead){
    
    tokenStream* prevnode = (tokenStream* )malloc(sizeof(tokenStream));

    //To store each word and corresponding line number
    char buffer[100];
    int line_num = 1;


    while(fgets(buffer,sizeof(buffer),f) != NULL){
        
        //Seperating each lexeme at a time and storing the corresponding token information
        char *lexeme;
        char delim[] = " \t\r\n";

        lexeme = strtok(buffer, delim);
        
        while(lexeme != NULL){
            tokenStream* newnode = (tokenStream* )malloc(sizeof(tokenStream));
            
            if(streamHead->head == NULL) streamHead->head = newnode;
            else prevnode->next = newnode;

            newnode->name = give_token_enum(lexeme);
            
            if(newnode->name == UNKNOWN){
                printf("INVALID TOKEN ENCOUNTERED AT LINE NUMBER : %d. ABORTING CODE",line_num);
                printf("\n %s",lexeme);
                exit(1);
            }

            if(newnode->name == NUMBER){
                newnode->tag = 1;
                newnode->data.num = atoi(lexeme);
            }else if(newnode->name == RNUMBER){
                newnode->tag = 2;
                newnode->data.rnum = atof(lexeme);
            }else{
                newnode->tag = 0;
                strncpy(newnode->data.str,lexeme, 21);
            }
            
            newnode->line_no = line_num;
            newnode->next = NULL;
            prevnode = newnode;
            
            lexeme = strtok(NULL, delim);
        }
        line_num++;
    }

    printf(" \n\n ---- SOURCE CODE TOKENIZED SUCCESSFULLY ---- \n\n \n");

}

void printTokenStream(tokenStream* ts){

    while (ts != NULL){

        //Using appropriate tag values to read the data
        if(ts->tag == 0){
            printf("\nInfo of token\n Name: %d line Number : %d data : %s",ts->name,ts->line_no,ts->data.str);
        }else if(ts->tag == 1){
            printf("\nInfo of token\n Name: %d line Number : %d data : %d",ts->name,ts->line_no,ts->data.num);
        }else if(ts->tag == 2){
            printf("\nInfo of token\n Name: %d line Number : %d data : %f",ts->name,ts->line_no,ts->data.rnum);
        }else{
            printf("\nUNKNOWN TOKEN");
        }
        ts = ts->next;
    }
}

