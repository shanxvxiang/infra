%define api.prefix {configfile}
%{
#include <stdio.h>
#define CONFIGFILESTYPE char*

int configfilelex();
int configfilewrap(void);
void configfileerror(char *s);

const char* AssignInt(const char* key, char* value);
const char* AssignString(const char* key, char* value);
const char* AssignIpaddress(const char* key, char* value);
%}

%token IDENTIFIER INT STRING IPADDRESS

%%

allFile
	: assign											{ }
	| allFile assign							{ }
	;

assign
	: IDENTIFIER '=' INT ';'					{ AssignInt($1, $3); free($1); free($3); }
	| IDENTIFIER '=' STRING ';'				{ AssignString($1, $3);  free($1); free($3); }
	| IDENTIFIER '=' IPADDRESS ';'		{ AssignIpaddress($1, $3); free($1); free($3); }
	;

%%

void configfileerror(char* s) {
    fprintf(stderr, "error: %s\n", s);
}

int configfilewrap(void) {
	return 1;
}



