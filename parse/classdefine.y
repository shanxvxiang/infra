%define api.prefix {classdefine}
%{
#include <stdio.h>
#define CLASSDEFINESTYPE char*

#define __RAYMON_SHAN_FOR_L_Y
#include "../include/logdirectly.hpp"
#undef  __RAYMON_SHAN_FOR_L_Y

int classdefinelex();
extern "C" { int classdefinewrap(void); };
void classdefineerror(const char *s);

extern int classdefinelineno;
extern char *classdefinetext;
extern const char *ClassDefineName;				// declare in classdefine.hpp

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
%token K_VALUE K_DELETED
%token T_STRING T_INT T_PERCENT T_MONEY T_HASH T_TIME
%token D_IDENTIFIER D_STRING D_INT

%%

allFile
	: sentence
	| allFile sentence
	;

sentence
	: classDefine
	| classValue
	;

classDefine
	: K_CLASS D_IDENTIFIER '{' defineGroup '}' ';'																										
		{ DefineClass($2); free($2); }
	| K_CLASS D_IDENTIFIER K_INHERIT D_IDENTIFIER '{' defineGroup '}' ';'														
		{ DefineInheritClass($2, $4); free($2); free($4); }
	| K_CLASS D_IDENTIFIER K_AGGREGATION D_IDENTIFIER '{' defineGroup '}' ';'												
		{ DefineAggregationClass($2, $4); free($2); free($4); }
	| K_CLASS D_IDENTIFIER K_INHERIT D_IDENTIFIER K_AGGREGATION D_IDENTIFIER '{' defineGroup '}' ';'	
		{ DefineInheritAggregationClass($2, $4, $6); free($2); free($4); free($6); }
	| K_CLASS D_IDENTIFIER K_AGGREGATION D_IDENTIFIER K_INHERIT D_IDENTIFIER '{' defineGroup '}' ';'	
		{ DefineInheritAggregationClass($2, $6, $4); free($2); free($4); free($6); }
	;

defineGroup
	: defineLine
	| defineGroup defineLine
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

classValue
	: K_VALUE D_IDENTIFIER '{' valueGroup '}' ';' { printf("CLASSVALUE %s \n", $2); }
	;	

valueGroup
	: valueLine																		{ printf("  LEVEL NORMAL 1 %s\n", $1); }
	| valueGroup valueLine												{ printf("  LEVEL NORMAL 2 %s %s \n", $1, $2); }
	| valueGroup '{' valueGroup '}' ';'						{ printf("  LEVELPLUS %s %s \n", $1, $2); }
	;
	
valueLine
	: valueType ';'																{ printf("NORMAL LINE COMPLETE\n"); }
	| K_DELETED valueType ';'											{ printf("DELETED LINE COMPLETE\n"); }
	;

valueType
	: valueOne 
	| valueType ',' valueOne
	;

valueOne
	: D_STRING																		{ printf("ONESTRING %s \n", $1); }
	| D_INT																				{ printf("ONEINT %s \n", $1); }

%%

void classdefineerror(const char* s) {
  _LOG_CRIT("%s:%s [%s:%d]", s, classdefinetext, ClassDefineName, classdefinelineno);
	exit(1);
	//fprintf(stderr, "error: %s line: %d\n", configfiletext, configfilelineno);
}

int classdefinewrap(void) {
	classdefinelineno = 1;
	return 1;
}



