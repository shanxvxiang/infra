%define api.pure
%locations
%parse-param {void* yyscanner}
%lex-param {void* yyscanner}

%{
#include <stdio.h>
#include "calc.bison.hpp"
void yyerror(YYLTYPE * yylloc_param, void * yylval_param, const char* msg);
int yylex (YYSTYPE * yylval_param, YYLTYPE * yylloc_param , void* yyscanner);

%}
 
%token T_NUM
 
%left '+' '-'
%left '*' '/'
 
%%
 
S   :   S E '\n'        { printf("ans = %d\n", $2); }
    |   /* empty */     { /* empty */ }
    ;
 
E   :   E '+' E         { $$ = $1 + $3; }
    |   E '-' E         { $$ = $1 - $3; }
    |   E '*' E         { $$ = $1 * $3; }
    |   E '/' E         { $$ = $1 / $3; }
    |   T_NUM           { $$ = $1; }
    |   '(' E ')'       { $$ = $2; }
    ;
 
%%


void yyerror(YYLTYPE * loc, void * yylval_param, const char* msg) {
	printf("error i %d:%d-%d:%d\n", loc->first_line, loc->first_column, loc->last_line, loc->last_column);

}


