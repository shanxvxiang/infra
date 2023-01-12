%define api.prefix {configfile}
%{
#include <stdio.h>
#define CONFIGFILESTYPE char*

int configfilelex();
extern "C" { int configfilewrap(void); };
void configfileerror(const char *s);

extern int configfilelineno;
extern char *configfiletext;

const char* AssignInt(const char* key, char* value);
const char* AssignString(const char* key, char* value);
const char* AssignIpaddress(const char* key, char* value);
%}

%token IDENTIFIER INT STRING IPADDRESS

%%

allFile
	: assign
	| allFile assign
	;

assign
	: IDENTIFIER '=' INT ';'					{ printf("line %d \n", configfilelineno); AssignInt($1, $3); free($1); free($3); }
	| IDENTIFIER '=' STRING ';'				{ AssignString($1, $3);  free($1); free($3); }
	| IDENTIFIER '=' IPADDRESS ';'		{ AssignIpaddress($1, $3); free($1); free($3); }
	;

%%

void configfileerror(const char* s) {
//_LOG_CRIT("%d", configfilelineno);
	fprintf(stderr, "error: %s line: %d\n", configfiletext, configfilelineno);
}

int configfilewrap(void) {
	return 1;
}



