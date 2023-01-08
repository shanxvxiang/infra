%option prefix="configfile"
%{
#define CONFIGFILESTYPE char*
#include "configfile.bison.h"
#define _DUPTEXT {configfilelval = strdup(configfiletext); printf("in dup %p\n", configfilelval);}
%}

/* 
GBK						([\x81-\xFE] ([\x40-\x7E] | [\x80-\xFE])) 
STRING				(\x34 ([^\x34\x92] | {ESCCHAR} )* \x34)
IDENTIFIER		(({ALPHABET} | {GBK}) ({ALPHABET} | {DIGIT} | {GBK})*)
*/
/* / \x2F; * \x2A " \x34; ' \x39; [ \x91; \ \x92; ] \x93*/

DIGIT 				([0-9])
HEXDIGIT			([0-9A-Fa-f])
ALPHABET			([_A-Za-z])


ESCONE				(\x92 [?abfnrtv\x34\x39\x92])
ESCX					(\x92 ([x] | [X]) {HEXDIGIT} {HEXDIGHT})
ESCU					(\x92 ([u] | [U]) {HEXDIGIT} {HEXDIGIT} {HEXDIGIT} {HEXDIGIT})
ESCCHAR				({ESCONE} | {ESCX} | {ESCU})

INT						({DIGIT}+)
STRING				(\x34 ([^\x34\x92] )* \x34)
IDENTIFIER		({ALPHABET}+)

COMMENT				("//"[^\n]*)
IS						("=")
DOT						(".")

%%
[ \t\r\n]+				{ }
{INT}							{ _DUPTEXT; printf("in int \n"); return INT; }
{IDENTIFIER}			{ _DUPTEXT; printf("in id \n"); return IDENTIFIER; }
{IS}							{ return IS; }
{DOT}							{ return DOT; }
{COMMENT}					{ }

<<EOF>>						{ return 0; }

