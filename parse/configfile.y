%define api.prefix {configfile}
%define api.pure
%locations
%parse-param {void* configfilescanner}
%lex-param {void* configfilescanner}

%{
#include <stdio.h>
#define CONFIGFILESTYPE char*

#define __RAYMON_SHAN_FOR_L_Y
#include "../include/infra.hpp"
#undef  __RAYMON_SHAN_FOR_L_Y

void configfileerror(CONFIGFILELTYPE *yylloc_param, void *yylval_param, const char *msg);
int configfilelex (CONFIGFILESTYPE *yyval_param, CONFIGFILELTYPE *yylloc_param , void* yyscanner);
%}

%token IDENTIFIER INT STRING IPADDRESS

%%

allFile
	: assign
	| allFile assign
	;

assign
	: IDENTIFIER '=' INT ';'					{ AssignInt($1, $3); free($1); free($3); }
	| IDENTIFIER '=' STRING ';'				{ AssignString($1, $3);  free($1); free($3); }
	| IDENTIFIER '=' IPADDRESS ';'		{ AssignIpaddress($1, $3); free($1); free($3); }
	;

%%
void configfileerror(CONFIGFILELTYPE * yylloc_param, void* yylval_param, const char *msg) {
	printf("in error lineno=%d:%d\n", yylloc_param->first_line, yylloc_param->first_column);
  //_LOG_CRIT("%s:%s [%s:%d]", msg, yytext, ConfigFileName, yylineno);
	exit(1);
}



