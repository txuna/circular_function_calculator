%{

#include "main.h"


static void yyerror(struct ParseState *p, const char* s);
%}

%union {
	value_t value;
    tri_t tri;
    struct Node *node;
}

%token<value> T_VALUE
%token T_SIN T_COS T_TAN 
%token T_ADD T_SUB T_MUL T_DIV
%token T_NEWLINE;

%type<node> program expr term factor
%type<tri> tri

%parse-param {struct ParseState* p}

%{
int yylex();
%}

%left T_ADD T_SUB
%left T_MUL T_DIV

%start program

%%

program : expr
        {
            p->node = $1;
        }

expr : expr T_ADD expr 
    {
        $$ = gen_op_node(OP_ADD, $1, $3); 
    }
    | expr T_SUB expr 
    {
        $$ = gen_op_node(OP_SUB, $1, $3);
    }
    | expr T_MUL expr 
    {
        $$ = gen_op_node(OP_MUL, $1, $3);
    }
    | expr T_DIV expr 
    {
        $$ = gen_op_node(OP_DIV, $1, $3);
    }
    | '(' expr ')' 
    {
        $$ = $2;
    }
    | term
    {
        $$ = $1;
    }
    ;

term : factor 
    {
        $$ = $1;
    }
    ; 

factor : T_VALUE
        {
            $$ = gen_value_node(TRI_NONE, $1);
        }
        | tri '{' T_VALUE '}' 
        {
            $$ = gen_value_node($1, $3);
        }
        ;

tri : T_SIN
    {
        $$ = TRI_SIN; 
    }
    | T_COS
    {
        $$ = TRI_COS;
    }
    | T_TAN
    {
        $$ = TRI_TAN;
    }
    ; 

%%

void yyerror(struct ParseState *p, const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
}