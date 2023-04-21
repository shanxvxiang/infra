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
%token T_STRING T_INT T_DOUBLE T_MONEY T_HASH T_TIME
%token D_IDENTIFIER D_STRING D_INT D_DOUBLE D_MONEY D_HASH D_TIME

%%

allFile
	: sentence
	| sentence ';'
	| allFile sentence
	| allFile sentence ';'
	;

sentence
	: classDefine
	| classValue
	| '{' classGroup '}'								{ EndofDefineClass(classdefinescanner); }
	| '{' valueGroup '}' 								{ EndofValueClass(classdefinescanner); }
	;

classDefine
	: K_CLASS D_IDENTIFIER
		{ DefineClass(classdefinescanner, $2, NULL, NULL); free($2); }
	| K_CLASS D_IDENTIFIER K_INHERIT D_IDENTIFIER
		{ DefineClass(classdefinescanner, $2, $4, NULL); free($2); free($4); }
	| K_CLASS D_IDENTIFIER K_AGGREGATION D_IDENTIFIER
		{ DefineClass(classdefinescanner, $2, NULL, $4); free($2); free($4); }
	| K_CLASS D_IDENTIFIER K_INHERIT D_IDENTIFIER K_AGGREGATION D_IDENTIFIER
		{ DefineClass(classdefinescanner, $2, $4, $6); free($2); free($4); free($6); }
	| K_CLASS D_IDENTIFIER K_AGGREGATION D_IDENTIFIER K_INHERIT D_IDENTIFIER
		{ DefineClass(classdefinescanner, $2, $6, $4); free($2); free($4); free($6); }
	;

classGroup
	: defineFieldLine
	| classGroup defineFieldLine
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
	| T_INT  					{ DefineFieldType(classdefinescanner, T_INT); }
	| T_DOUBLE 				{ DefineFieldType(classdefinescanner, T_DOUBLE); }
	| T_MONEY 				{ DefineFieldType(classdefinescanner, T_MONEY); }
	| T_HASH  				{ DefineFieldType(classdefinescanner, T_HASH); }
	| T_TIME  				{ DefineFieldType(classdefinescanner, T_TIME); }
	;

classValue
	: K_VALUE D_IDENTIFIER 												{ DefineClassValue(classdefinescanner, $2, 1); }
	| K_VALUE D_IDENTIFIER '(' valueOrder ')'			{ DefineClassValue(classdefinescanner, $2, 0); }
	;	

valueOrder
	: D_IDENTIFIER																{ DefineValueOrder(classdefinescanner, $1, 1); }
	| valueOrder ',' D_IDENTIFIER									{ DefineValueOrder(classdefinescanner, $3, 0); }
	;

valueGroup
	: valueLine																		{ printf("  LEVEL NORMAL 1 %s\n", $1); }
	| valueGroup valueLine												{ printf("  LEVEL NORMAL 2 %s \n", $2); }
	| valueGroup '{' valueGroup '}' ';'						{ printf("  LEVELPLUS %s \n", $2); }
	| valueGroup '{' valueGroup '}'								{ printf("  LEVELPLUS %s \n", $2); }
	;
	
valueLine
	: valueType ';'																{ printf("    NORMAL LINE COMPLETE %s\n", $1); }
	| K_DELETED valueType ';'											{ printf("    DELETED LINE COMPLETE %s\n", $2); }
	;

valueType
	: valueOne 																		{ printf("        value one %s\n", $1); }
	| valueType ',' valueOne											{ printf("        value two %s, %s\n", $1, $3); }
	;

valueOne
	: strings																			{}// printf("ONESTRING %s \n", $1); }
	| D_INT																				{ printf("ONEINT %s \n", $1); }
	| D_DOUBLE																		{ printf("ONEDOUBLE %s \n", $1); }
	| D_MONEY 																		{ printf("ONEMONEY %s \n", $1); }
	| D_HASH  																		{ printf("ONEHASH %s \n", $1); }
	| D_TIME  																		{ printf("ONETIME %s \n", $1); }
	;

strings
	: D_STRING
	| strings D_STRING

