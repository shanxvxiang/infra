%option prefix="xy"
%option reentrant noyywrap yylineno
%option bison-bridge bison-locations
%{
#include <stdio.h>
#define XYSTYPE char*
#define YYSTYPE         XYSTYPE
#define YYLTYPE         XYLTYPE

#include "configfile.bison.hpp"
#define _DUPTEXT {*yylval = strdup(yytext);}

#define YY_USER_ACTION                                             \
    yylloc->first_line = yylloc->last_line;                          \
    yylloc->first_column = yylloc->last_column;                      \
    if (yylloc->last_line == yylineno)                               \
      yylloc->last_column += yyleng;                                 \
    else {                                                           \
      yylloc->last_line = yylineno;                                  \
      yylloc->last_column = yytext + yyleng - strrchr(yytext, '\n'); \
    }
    
%}

%x MULCOMMENT
splice                  (\\[[:blank:]]*\n)*

/* " \x22; ' \x27; / \x2F; \ \x5c; */
DIGIT 				([0-9])
HEXDIGIT			([0-9A-Fa-f])
ALPHABET			([_A-Za-z])
GBK						([\x81-\xFE][\x40-\xFE])

ESCONE				(\x5C[abfnrtv?\x22\x27\x5C])
ESCX					(\x5C([x]|[X]){HEXDIGIT}{HEXDIGIT})
ESCCHAR				({ESCONE}|{ESCX})
DISPLAYCHAR		([\x20-\xFE\t])

IDENTIFIER		({ALPHABET}({ALPHABET}|{DIGIT})*)
INT						({DIGIT}+)
STRING				(\x22([^\x22\x5c]|{ESCCHAR})*\x22)
IPADDRESS			({INT}"."{INT}"."{INT}"."{INT}":"{INT})
COMMENT				("//"[^\n]*)
SEGMENT				("["{DISPLAYCHAR}*"]")

%%
{IDENTIFIER}			{ _DUPTEXT; return IDENTIFIER; }
{INT}							{ _DUPTEXT; return INT; }
{STRING}          { _DUPTEXT; return STRING; }
{IPADDRESS}				{ _DUPTEXT; return IPADDRESS; }
[;=]							{ return yytext[0]; }
[\n]							{ /*yylineno++;*/ }
[ \t\r]+					{ }
{COMMENT}					{ }
{SEGMENT}					{ }


[/]{splice}[*]          { BEGIN(MULCOMMENT); }

<MULCOMMENT>{
  [^*\\\n]+             /* eat anything that's not a '*' or line end */
  "*"+[^*/\\\n]*        /* eat up '*'s not followed by '/'s or line end */
  [*]{splice}[/]        { BEGIN(INITIAL);}
  [*\\]                 /* stray '*' or backslash */
  \n                    /* Reduce the amount of work needed for yylineno */
}


<<EOF>>						{ return 0; }
%%
int main() {      
	yyscan_t yyscanner;
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     
	yylex_init ( &yyscanner );
	
	yyset_in(fopen("../infra.conf", "rb"), yyscanner);

	//yyin = fopen("../infra.conf", "r" );
		//printf("after open %p\n", yyin);

	//if (!yyin) {
	//	printf("error in open file\n");
	//	exit(1);
	//}
	//printf("yyin %p\n", yyin);
	xyparse ( yyscanner );
	yylex_destroy ( yyscanner );

	return 0;
}


