%option prefix="classdefine"
%{
#define CLASSDEFINESTYPE char*
#include "classdefine.bison.h"
#define _DUPTEXT {classdefinelval = strdup(classdefinetext);}
%}

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

"string"					{ return T_STRING; }
"int"							{ return T_INT; }
"percent"					{ return T_PERCENT; }
"money"						{ return T_MONEY; }
"hash"						{ return T_HASH; }
"time"						{ return T_TIME; }

[{};]							{ return classdefinetext[0]; }
{IDENTIFIER}			{ _DUPTEXT; return D_IDENTIFIER; }
{STRING}          { _DUPTEXT; return D_STRING; }

{COMMENT}					{ }
<<EOF>>						{ return 0; }

