%option prefix="classdefine"
%option reentrant noyywrap yylineno
%option bison-bridge bison-locations

%{
#define CLASSDEFINESTYPE 			char*
#define YYSTYPE         			CLASSDEFINESTYPE
#define YYLTYPE         			CLASSDEFINELTYPE

#define __RAYMON_SHAN_FOR_L_Y
#include "../include/infra.hpp"
#undef  __RAYMON_SHAN_FOR_L_Y

#define _DUPTEXT {*yylval = strdup(yytext);}

#define YY_USER_ACTION																							\
	yylloc->first_line = yylloc->last_line;														\
	yylloc->first_column = yylloc->last_column;												\
	if (yylloc->last_line == yylineno)																\
		yylloc->last_column += yyleng;																	\
	else {																														\
		yylloc->last_line = yylineno;																		\
		yylloc->last_column = yytext + yyleng - strrchr(yytext, '\n');	\
	}
%}

/*  https://www.nuomiphp.com/eplan/518696  for multi comment */
%x MULCOMMENT
splice				(\\[[:blank:]]*\n)*

/* " \x22; ' \x27; / \x2F; \ \x5c; */

DIGIT 				([0-9])
HEXDIGIT			([0-9A-Fa-f])
ALPHABET			([_A-Za-z])
GBK						([\x81-\xFE][\x40-\xFE])

ESCONE				(\x5C[abfnrtv?\x22\x27\x5C])
ESCX					(\x5C([x]|[X]){HEXDIGIT}{HEXDIGIT})
ESCCHAR				({ESCONE}|{ESCX})
AHEADCHAR			({ALPHABET}|{GBK})
ALLCHAR				({ALPHABET}|{DIGIT}|{GBK})

IDENTIFIER		({AHEADCHAR}{ALLCHAR}*)
STRING				(\x22([^\x22\x5c\n]|{ESCCHAR})*\x22)
INT						({DIGIT}+)
DOUBLE				({DIGIT}+(.{DIGIT}*)?)
MONEY					({DIGIT}+(.{DIGIT}*)?)
HASH					([0-9A-Fa-f]{16})
TIME					([0-9A-Fa-f]{16})

COMMENT				("//"[^\n]*)

%%
"class"						{ return K_CLASS; }
"inherit"					{ return K_INHERIT; }
"aggregation"			{ return K_AGGREGATION; }
"key"							{ return K_KEY; }
"unique"					{ return K_UNIQUE; }
"essential"				{ return K_ESSENTIAL; }
"attribute"				{ return K_ATTRIBUTE; }
"value"						{ return K_VALUE; }
"deleted"					{ return K_DELETED; }

"string"					{ return T_STRING; }
"int"							{ return T_INT; }
"double"					{ return T_DOUBLE; }
"money"						{ return T_MONEY; }
"hash"						{ return T_HASH; }
"time"						{ return T_TIME; }

[.,;(){}]					{ return yytext[0]; }
{IDENTIFIER}			{ _DUPTEXT; return D_IDENTIFIER; }
{STRING}          { _DUPTEXT; return D_STRING; }
{INT}							{ _DUPTEXT; return D_INT; }
{DOUBLE}					{ _DUPTEXT; return D_DOUBLE; }
{MONEY}						{ _DUPTEXT; return D_MONEY; }
{HASH}						{ _DUPTEXT; return D_HASH; }
{TIME}						{ _DUPTEXT; return D_TIME; }

[\n]							{ }
[ \t\r]+					{ }
{COMMENT}					{ }

[/]{splice}[*]		{ BEGIN(MULCOMMENT); }
<MULCOMMENT>{
  [^*\\\n]+				/* eat anything that's not a '*' or line end */
  "*"+[^*/\\\n]*	/* eat up '*'s not followed by '/'s or line end */
  [*]{splice}[/]	{ BEGIN(INITIAL); }
  [*\\]						/* stray '*' or backslash */
  \n							/* Reduce the amount of work needed for yylineno */
}

[[:^blank:]]			{ }
<<EOF>>						{ return 0; }

%%
int DoClassDefineFileParse(FILE* in, ScanExtra *name) {
	yyscan_t yyscanner;
	yylex_init ( &yyscanner );
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     
	yyextra = (void*)name;
	yyset_in(in, yyscanner);
	classdefineparse ( yyscanner );
	yylex_destroy ( yyscanner );
	return 0;
}

int DoClassDefineMemoryParse(char* buffer, int length, ScanExtra *name) {
// https://www.coder.work/article/1567976
    YY_BUFFER_STATE buf;
	yyscan_t yyscanner;
	yylex_init ( &yyscanner );
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     
	yyextra = (void*)name;
//	yyset_in(in, yyscanner);
    buf = yy_scan_bytes( buffer, length , yyscanner);
	classdefineparse ( yyscanner );
    yy_delete_buffer(buf, yyscanner);
	yylex_destroy ( yyscanner );
	return 0;
}

void classdefineerror(CLASSDEFINELTYPE * yylloc_param, void* yyscanner, const char *msg) {
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

	ScanExtra* extra = (ScanExtra*)yyextra;
  _LOG_CRIT("configure file [%s:%d,%d] %s:%s ", extra->fileName.c_str(), yylineno, yylloc_param->first_column, msg, yytext );
	exit(1);
};




