%define api.prefix {classdefine}
%define api.pure
%locations
%parse-param {void* classdefinescanner}
%lex-param {void* classdefinescanner}

%{
#include <stdio.h>
#define CLASSDEFINESTYPE char*

#define __RAYMON_SHAN_FOR_L_Y
#include "../include/infra.hpp"
#undef  __RAYMON_SHAN_FOR_L_Y

void classdefineerror(CLASSDEFINELTYPE *yylloc_param, void *yyscanner, const char *msg);
int classdefinelex (CLASSDEFINESTYPE *yyval_param, CLASSDEFINELTYPE *yylloc_param , void* yyscanner);
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
		{ DefineClass(classdefinescanner, $2); free($2); }
	| K_CLASS D_IDENTIFIER K_INHERIT D_IDENTIFIER '{' defineGroup '}' ';'														
		{ DefineInheritClass(classdefinescanner, $2, $4); free($2); free($4); }
	| K_CLASS D_IDENTIFIER K_AGGREGATION D_IDENTIFIER '{' defineGroup '}' ';'												
		{ DefineAggregationClass(classdefinescanner, $2, $4); free($2); free($4); }
	| K_CLASS D_IDENTIFIER K_INHERIT D_IDENTIFIER K_AGGREGATION D_IDENTIFIER '{' defineGroup '}' ';'	
		{ DefineInheritAggregationClass(classdefinescanner, $2, $4, $6); free($2); free($4); free($6); }
	| K_CLASS D_IDENTIFIER K_AGGREGATION D_IDENTIFIER K_INHERIT D_IDENTIFIER '{' defineGroup '}' ';'	
		{ DefineInheritAggregationClass(classdefinescanner, $2, $6, $4); free($2); free($4); free($6); }
	;

defineGroup
	: defineFieldLine
	| defineGroup defineFieldLine
	;

defineFieldLine
	: categoryDefine typeDefine	D_IDENTIFIER ';'					{ DefineField(classdefinescanner, $3); free($3); }
	;

categoryDefine
	: K_UNIQUE				{ DefineFieldCategory(classdefinescanner, K_UNIQUE); }
	| K_ESSENTIAL			{ DefineFieldCategory(classdefinescanner, K_ESSENTIAL); }
	| K_ATTRIBUTE			{ DefineFieldCategory(classdefinescanner, K_ATTRIBUTE); }
	;

typeDefine
	: T_STRING				{ DefineFieldType(classdefinescanner, T_STRING); }
	| T_INT  					{ DefineFieldType(classdefinescanner, T_STRING); }
	| T_PERCENT 			{ DefineFieldType(classdefinescanner, T_STRING); }
	| T_MONEY 				{ DefineFieldType(classdefinescanner, T_STRING); }
	| T_HASH  				{ DefineFieldType(classdefinescanner, T_STRING); }
	| T_TIME  				{ DefineFieldType(classdefinescanner, T_STRING); }
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
	: strings																			{ }//printf("ONESTRING %s \n", $1); }
	| D_INT																				{ }//printf("ONEINT %s \n", $1); }

strings
	: D_STRING
	| strings D_STRING
