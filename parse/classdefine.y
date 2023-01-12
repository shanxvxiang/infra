%define api.prefix {classdefine}
%{
#include <stdio.h>
#define CLASSDEFINESTYPE char*

int classdefinelex();
extern "C" { int classdefinewrap(void); };
void classdefineerror(const char *s);

const char* DefineString(const char* id);
const char* DefineInt(const char* id);
const char* DefinePercent(const char* id);
const char* DefineMoney(const char* id);
const char* DefineHash(const char* id);
const char* DefineTime(const char* id);

const char* DefineProperty(int prop);

const char* DefineClass(const char* name);
const char* DefineInheritClass(const char* name, const char* base);
const char* DefineAggregationClass(const char* name, const char* summary);
const char* DefineInheritAggregationClass(const char* name, const char* base, const char* summary);
%}

%token K_CLASS K_INHERIT K_AGGREGATION K_UNIQUE K_ESSENTIAL K_ATTRIBUTE
%token T_STRING T_INT T_PERCENT T_MONEY T_HASH T_TIME
%token D_IDENTIFIER D_STRING

%%

allFile
	: sentence
	| allFile sentence
	;

sentence
	: classDefine
	;

classDefine
	: K_CLASS D_IDENTIFIER '{' defineBody '}' ';'																										
		{ DefineClass($2); free($2); }
	| K_CLASS D_IDENTIFIER K_INHERIT D_IDENTIFIER '{' defineBody '}' ';'														
		{ DefineInheritClass($2, $4); free($2); free($4); }
	| K_CLASS D_IDENTIFIER K_AGGREGATION D_IDENTIFIER '{' defineBody '}' ';'												
		{ DefineAggregationClass($2, $4); free($2); free($4); }
	| K_CLASS D_IDENTIFIER K_INHERIT D_IDENTIFIER K_AGGREGATION D_IDENTIFIER '{' defineBody '}' ';'	
		{ DefineInheritAggregationClass($2, $4, $6); free($2); free($4); free($6); }
	| K_CLASS D_IDENTIFIER K_AGGREGATION D_IDENTIFIER K_INHERIT D_IDENTIFIER '{' defineBody '}' ';'	
		{ DefineInheritAggregationClass($2, $6, $4); free($2); free($4); free($6); }
	;

defineBody
	: defineLine
	| defineBody defineLine
	;

defineLine
	: K_UNIQUE typeDefine							{ DefineProperty(1); }
	| K_ESSENTIAL typeDefine					{ DefineProperty(2); }
	| K_ATTRIBUTE typeDefine					{ DefineProperty(3); }
	;

typeDefine
	: T_STRING D_IDENTIFIER ';'				{ DefineString($2); free($2); }
	| T_INT D_IDENTIFIER ';'					{ DefineInt($2); free($2); }
	| T_PERCENT D_IDENTIFIER ';'			{ DefinePercent($2); free($2); }
	| T_MONEY D_IDENTIFIER ';'				{ DefineMoney($2); free($2); }
	| T_HASH D_IDENTIFIER ';'					{ DefineHash($2); free($2); }
	| T_TIME D_IDENTIFIER ';'					{ DefineTime($2); free($2); }
	;
%%

void classdefineerror(const char* s) {
	fprintf(stderr, "error: %s\n", s);
}

int classdefinewrap(void) {
	return 1;
}



