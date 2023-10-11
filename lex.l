%option noyywrap

%{
#include "main.h"

#define YY_DECL int yylex()

#include "parse.tab.h"

%}

%%

[ \t]+	; // ignore all whitespace
\n		{return T_NEWLINE;}
[0-9]+		{yylval.value = atoi(yytext); return T_VALUE;}
"sin" { return T_SIN;}
"cos" { return T_COS;}
"tan" { return T_TAN;}
"{" {return '{';}
"}" {return '}';}
"(" {return '(';}
")" {return ')';}
"+" {return T_ADD;}
"-" {return T_SUB;}
"*" {return T_MUL;}
"/" {return T_DIV;}

. {
    fprintf(stderr, "lexical error ('%s').\n", yytext); 
    exit(1);
};

%%