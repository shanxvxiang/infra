%define api.prefix {classdefine}
%define api.pure full
%parse-param {const char* yyscanner}
%{
#include <stdio.h>
#define CLASSDEFINESTYPE char*


#define __RAYMON_SHAN_FOR_L_Y
#include "../include/infra.hpp"
#undef  __RAYMON_SHAN_FOR_L_Y

int classdefinelex(char**);
extern "C" { int classdefinewrap(void); };
void classdefineerror(const char *s, const char *m);

extern int classdefinelineno;
extern char *classdefinetext;
//extern const char *ClassDefineName;				// declare in classdefine.hpp

%}

%token K_CLASS K_INHERIT K_AGGREGATION K_UNIQUE K_ESSENTIAL K_ATTRIBUTE
%token K_VALUE K_DELETED
%token T_STRING T_INT T_PERCENT T_MONEY T_HASH T_TIME T_ID
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
	: K_UNIQUE typeDefine							{ DefineProperty(K_UNIQUE); }
	| K_ESSENTIAL typeDefine					{ DefineProperty(K_ESSENTIAL); }
	| K_ATTRIBUTE typeDefine					{ DefineProperty(K_ATTRIBUTE); }
	;

typeDefine
	: T_STRING D_IDENTIFIER ';'				{ DefineType(T_STRING, $2); free($2); }
	| T_INT D_IDENTIFIER ';'					{ DefineType(T_INT, $2); free($2); }
	| T_PERCENT D_IDENTIFIER ';'			{ DefineType(T_PERCENT, $2); free($2); }
	| T_MONEY D_IDENTIFIER ';'				{ DefineType(T_MONEY, $2); free($2); }
	| T_HASH D_IDENTIFIER ';'					{ DefineType(T_HASH, $2); free($2); }
	| T_TIME D_IDENTIFIER ';'					{ DefineType(T_TIME, $2); free($2); }
	;

classValue
	: K_VALUE D_IDENTIFIER '{' valueGroup '}' ';' { }//printf("CLASSVALUE %s \n", $2); }
	;	

valueGroup
	: valueLine																		{ }//printf("  LEVEL NORMAL 1 %s\n", $1); }
	| valueGroup valueLine												{ }//printf("  LEVEL NORMAL 2 %s %s \n", $1, $2); }
	| valueGroup '{' valueGroup '}' ';'						{ }//printf("  LEVELPLUS %s %s \n", $1, $2); }
	;
	
valueLine
	: valueType ';'																{ }//printf("NORMAL LINE COMPLETE\n"); }
	| K_DELETED valueType ';'											{ }//printf("DELETED LINE COMPLETE\n"); }
	;

valueType
	: valueOne 
	| valueType ',' valueOne
	;

valueOne
	: D_STRING																		{ }//printf("ONESTRING %s \n", $1); }
	| D_INT																				{ }//printf("ONEINT %s \n", $1); }

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



