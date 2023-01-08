%define api.prefix {configfile}
%{
#include <stdio.h>
#define CONFIGFILESTYPE char*

int configfilelex();
int configfilewrap(void);
void configfileerror(char *s);
%}

%token COMMENT
%token DIGIT HEXDIGIT	ALPHABET GBK	
%token ESCONE ESCX ESCU ESCCHAR
%token INT STRING IDENTIFIER
%token IS DOT

%%

allFile
	: assign											{ printf("Assgin1 \n"); }
	| allFile assign							{ printf("Assgin2 \n"); }
	;


assign
	: IDENTIFIER IS INT					{ printf("Assgin int %s %s \n", $1, $3); free($1); free($3);}
	| IDENTIFIER IS STRING				{ printf("Assgin string  \n"); }
	| IDENTIFIER IS INT DOT INT DOT INT DOT INT { printf("Assgin ip %s %s \n", $1, $3); }
	;

%%
int main(int argc, char **argv) {
    configfileparse();
}
void configfileerror(char* s) {
    fprintf(stderr, "error: %s\n", s);
}

int configfilewrap(void) {
	return 1;
}



