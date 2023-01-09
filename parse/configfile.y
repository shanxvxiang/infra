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

%token COMMENT SEGMENT
%token DIGIT HEXDIGIT	ALPHABET GBK	
%token ESCONE ESCX ESCU ESCCHAR ALLCHAR
%token IDENTIFIER INT STRING IPADDRESS
%token IS DOT SEMI

%%

allFile
	: assign											{ }
	| allFile assign							{ }
	;


assign
	: IDENTIFIER IS INT	SEMI					{ AssignInt($1, $3); free($1); free($3);}
	| IDENTIFIER IS STRING SEMI				{ AssignString($1, $3);  free($1); free($3);}
	| IDENTIFIER IS IPADDRESS SEMI		{ AssignIpaddress($1, $3); free($1); free($3); }
	;

%%

void configfileerror(char* s) {
    fprintf(stderr, "error: %s\n", s);
}

int configfilewrap(void) {
	return 1;
}



