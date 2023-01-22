%define api.pure
%parse-param {void* yyscanner}
%lex-param {int* yylval, void* yyscanner}

%{
#include <stdio.h>
void yyerror(void* yyscanner, const char* msg);
int yylex (int* yylval, void* yyscanner);


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
void yyerror(void* yyscanner, const char* msg) {
	printf("error\n");
}



