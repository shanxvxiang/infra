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

#define YY_USER_ACTION																								\
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
INT						({DIGIT}+)
STRING				(\x22([^\x22\x5c]|{ESCCHAR})*\x22)

COMMENT				("//"[^\n]*)

%%
"class"						{ return K_CLASS; }
"inherit"					{ return K_INHERIT; }
"aggregation"			{ return K_AGGREGATION; }
"unique"					{ return K_UNIQUE; }
"essential"				{ return K_ESSENTIAL; }
"attribute"				{ return K_ATTRIBUTE; }
"value"						{ return K_VALUE; }
"deleted"					{ return K_DELETED; }

"string"					{ return T_STRING; }
"int"							{ return T_INT; }
"percent"					{ return T_PERCENT; }
"money"						{ return T_MONEY; }
"hash"						{ return T_HASH; }
"time"						{ return T_TIME; }

[{};,]						{ return yytext[0]; }
{IDENTIFIER}			{ _DUPTEXT; return D_IDENTIFIER; }
{STRING}          { _DUPTEXT; return D_STRING; }
{INT}							{ _DUPTEXT; return D_INT; }
[\n]							{ }
[ \t\r]+					{ }
{COMMENT}					{ }

[/]{splice}[*]		{ BEGIN(MULCOMMENT); }
<MULCOMMENT>{
  [^*\\\n]+				/* eat anything that's not a '*' or line end */
  "*"+[^*/\\\n]*	/* eat up '*'s not followed by '/'s or line end */
  [*]{splice}[/]	{ BEGIN(INITIAL);}
  [*\\]						/* stray '*' or backslash */
  \n							/* Reduce the amount of work needed for yylineno */
}

<<EOF>>						{ return 0; }

%%
int DoClassDefineParse(FILE* in) {      
	yyscan_t yyscanner;
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     
	yylex_init ( &yyscanner );
	yyset_in(in, yyscanner);
	classdefineparse ( yyscanner );
	yylex_destroy ( yyscanner );
	return 0;
}


