%option reentrant noyywrap yylineno

%{
#include "calc.bison.hpp"
%}
%option bison-bridge bison-locations
 
%%
[0-9]+          { *yylval = atoi(yytext); return T_NUM; }
[-/+*()\n]      { return yytext[0]; }
.               { return 0; /* end when meet everything else */ }
%%

int main() {
	yyscan_t scanner;
     
	yylex_init ( &scanner );
	yyparse ( scanner );
	yylex_destroy ( scanner );

	return 0;
}
