//%define api.prefix {yy}
%define api.pure
%locations
%parse-param {void* yyscanner}
%lex-param {void* yyscanner}

%{
#include <stdio.h>
#define YYSTYPE char*

//#define __RAYMON_SHAN_FOR_L_Y
//#include "../include/infra.hpp"
//#undef  __RAYMON_SHAN_FOR_L_Y

#include "configfile.bison.hpp"
void yyerror(YYLTYPE * yylloc_param, void * yylval_param, const char* msg);
int yylex (YYSTYPE * yylval_param, YYLTYPE * yylloc_param , void* yyscanner);

void AssignInt(char* id, char* val, YYLTYPE * yylloc_param);

//extern int yylineno;
//extern char *yytext;
//extern const char *ConfigFileName;		// declare in configurefile.hpp

%}

%token IDENTIFIER INT STRING IPADDRESS

%%

allFile
	: assign
	| allFile assign
	;

assign
	: IDENTIFIER '=' INT ';'					{ AssignInt($1, $3, &yylloc); free($1); free($3); }
	| IDENTIFIER '=' STRING ';'				{ AssignInt($1, $3, &yylloc); free($1); free($3); }
	| IDENTIFIER '=' IPADDRESS ';'		{ AssignInt($1, $3, &yylloc); free($1); free($3); }
	;

%%

void yyerror(YYLTYPE * yylloc_param, void * yylval_param, const char* msg) {
	printf("in error lineno=%d:%d\n", yylloc_param->first_line, yylloc_param->first_column);
  //_LOG_CRIT("%s:%s [%s:%d]", msg, yytext, ConfigFileName, yylineno);
	exit(1);
}


void AssignInt(char* id, char* val, YYLTYPE * yylloc_param) {
printf("in assgin %s = %s, lineno=%d:%d\n", id, val, yylloc_param->first_line, yylloc_param->first_column);
}


