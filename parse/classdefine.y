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

%token K_CLASS K_INHERIT K_AGGREGATION K_KEY K_UNIQUE K_ESSENTIAL K_ATTRIBUTE
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
	| '{' valueGroup '}' 								{ DefineValueLevel(classdefinescanner, -1); EndofValueClass(classdefinescanner); }
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
	: K_KEY						{ DefineFieldCategory(classdefinescanner, K_KEY); }
	| K_UNIQUE				{ DefineFieldCategory(classdefinescanner, K_UNIQUE); }
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
	: K_VALUE D_IDENTIFIER 												{ DefineClassValue(classdefinescanner, $2, 1);  free($2);}
	| K_VALUE D_IDENTIFIER '(' valueOrder ')'			{ DefineClassValue(classdefinescanner, $2, 0);  free($2);}
	;	

valueOrder
	: D_IDENTIFIER																{ DefineValueOrder(classdefinescanner, $1, 1);  free($1);}
	| valueOrder ',' D_IDENTIFIER									{ DefineValueOrder(classdefinescanner, $3, 0);  free($3);}
	;

valueGroup
	: valueLine																		{ DefineValueLevel(classdefinescanner, 1); }
	| valueGroup valueLine												{ DefineValueLevel(classdefinescanner, 0); }
	| valueGroup '{' valueGroup '}' ';'						{ DefineValueLevel(classdefinescanner, -1); }
	| valueGroup '{' valueGroup '}'								{ DefineValueLevel(classdefinescanner, -1); }
	;
	
valueLine
	: valueType ';'																{ DefineFieldLine(classdefinescanner, 0); }
	| K_DELETED valueType ';'											{ DefineFieldLine(classdefinescanner, K_DELETED); }
	;

valueType
	: valueOne 																		{ DefineFieldValue(classdefinescanner, $1, 1);  free($1); }
	| valueType ',' valueOne											{ DefineFieldValue(classdefinescanner, $3, 0);  free($3); }
	;

valueOne
	: strings																			{ }
	| D_INT																				{ }
	| D_DOUBLE																		{ }
	| D_MONEY 																		{ }
	| D_HASH  																		{ }
	| D_TIME  																		{ }
	;

strings
	: D_STRING  																	{ }
	| strings D_STRING 														{ yyval = (char*)malloc(strlen($1)+strlen($2)+1); strcpy(yyval, $1); *(yyval+strlen($1)-1) = 0; strcat(yyval, $2+1); free($1); free($2); }

