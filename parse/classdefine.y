%define api.prefix {classdefine}
%{
#include <stdio.h>
#define CLASSDEFINESTYPE char*

int classdefinelex();
int classdefinewrap(void);
void classdefineerror(char *s);

const char* DefineString(const char* identifier);
const char* DefineInt(const char* identifier);
const char* DefinePercent(const char* identifier);
const char* DefineMoney(const char* identifier);
const char* DefineHash(const char* identifier);
const char* DefineTime(const char* identifier);
%}

%token K_CLASS K_INHERIT K_AGGREGATION K_UNIQUE K_ESSENTIAL K_ATTRIBUTE
%token T_STRING T_INT T_PERCENT T_MONEY T_HASH T_TIME
%token D_IDENTIFIER D_STRING

%%

allFile
	: sentence										{ }
	| allFile sentence						{ }
	;

sentence
	: classDefine									{ }
	;

classDefine
	: K_CLASS D_IDENTIFIER '{' defineBody '}' ';'																										{ printf("in classDefine %s\n", $2); free($2); }
	| K_CLASS D_IDENTIFIER K_INHERIT D_IDENTIFIER '{' defineBody '}' ';'														{ printf("in classDefine %s inherit %s\n", $2, $4); free($2); free($4); }
	| K_CLASS D_IDENTIFIER K_AGGREGATION D_IDENTIFIER '{' defineBody '}' ';'												{ }
	| K_CLASS D_IDENTIFIER K_INHERIT D_IDENTIFIER K_AGGREGATION D_IDENTIFIER '{' defineBody '}' ';'	{ }
	;

defineBody
	: defineLine																																										{ }
	| defineBody defineLine																																					{ }
	;

defineLine
	: T_STRING D_IDENTIFIER ';'				{ DefineString($2); free($2); }
	| T_INT D_IDENTIFIER ';'					{ DefineInt($2); free($2); }
	| T_PERCENT D_IDENTIFIER ';'			{ DefinePercent($2); free($2); }
	| T_MONEY D_IDENTIFIER ';'				{ DefineMoney($2); free($2); }
	| T_HASH D_IDENTIFIER ';'					{ DefineHash($2); free($2); }
	| T_TIME D_IDENTIFIER ';'					{ DefineTime($2); free($2); }
	;
%%

void classdefineerror(char* s) {
	fprintf(stderr, "error: %s\n", s);
}

int classdefinewrap(void) {
	return 1;
}



