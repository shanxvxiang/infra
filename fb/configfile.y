%define api.prefix {xy}
%define api.pure
%locations
%parse-param {void* xyscanner}
%lex-param {void* xyscanner}

%{
#include <stdio.h>
#define XYSTYPE char*

//#define __RAYMON_SHAN_FOR_L_Y
//#include "../include/infra.hpp"
//#undef  __RAYMON_SHAN_FOR_L_Y

#include "configfile.bison.hpp"
void xyerror(XYLTYPE * xylloc_param, void * xylval_param, const char* msg);
int xylex (XYSTYPE * xylval_param, XYLTYPE * xylloc_param , void* xyscanner);

void AssignInt(char* id, char* val, XYLTYPE * xylloc_param);

//extern int xylineno;
//extern char *xytext;
//extern const char *ConfigFileName;		// declare in configurefile.hpp

%}

%token IDENTIFIER INT STRING IPADDRESS MULTILINE

%%

allFile
	: assign
	| allFile assign
	;


assign
	: IDENTIFIER '=' INT ';'					{ AssignInt($1, $3, &yylloc); free($1); free($3); }
	| IDENTIFIER '=' strings ';'			{ printf("ID is %s\n", $1); free($1); }
	| IDENTIFIER '=' IPADDRESS ';'		{ AssignInt($1, $3, &yylloc); free($1); free($3); }
	;

strings
	: STRING													{ printf("STRING1 is %s\n", $1); free($1); }
	| strings STRING									{ printf("STRING2 is %s\n", $2); free($2); }
	;
	
%%

void xyerror(XYLTYPE * xylloc_param, void * xylval_param, const char* msg) {
	printf("in error lineno=%d:%d\n", xylloc_param->first_line, xylloc_param->first_column);
  //_LOG_CRIT("%s:%s [%s:%d]", msg, xytext, ConfigFileName, xylineno);
	exit(1);
}


void AssignInt(char* id, char* val, XYLTYPE * xylloc_param) {
printf("in assgin %s = %s, lineno=%d:%d\n", id, val, xylloc_param->first_line, xylloc_param->first_column);
}


