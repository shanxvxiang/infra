%option prefix="configfile"
%{
#define CONFIGFILESTYPE char*
#include "configfile.bison.h"
#define _DUPTEXT {configfilelval = strdup(configfiletext);}
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
GBK						([\x81-\xFE][\x40-\xFE])

ESCONE				(\x92[?abfnrtv\x34\x39\x92])
ESCX					(\x92([x]|[X]){HEXDIGIT}{HEXDIGIT})
ESCU					(\x92([u]|[U]){HEXDIGIT}{HEXDIGIT}{HEXDIGIT}{HEXDIGIT})
ESCCHAR				({ESCONE}|{ESCX}|{ESCU})
ALLCHAR				({ALPHABET}|{DIGIT}|{GBK}|{ESCCHAR})

IDENTIFIER		({ALPHABET}+)
INT						({DIGIT}+)
STRING				(\x34([^\x34])*\x34)
IPADDRESS			({INT}"."{INT}"."{INT}"."{INT})

COMMENT				("//"[^\n]*)
SEGMENT				("["{ALLCHAR}*"]")
IS						("=")
DOT						(".")
SEMI					(";")

%%
[ \t\r\n]+				{ }
{IDENTIFIER}			{ _DUPTEXT; return IDENTIFIER; }
{INT}							{ _DUPTEXT; return INT; }
{IPADDRESS}				{ _DUPTEXT; return IPADDRESS; }
{IS}							{ return IS; }
{DOT}							{ return DOT; }
{SEMI}						{ return SEMI; }
{COMMENT}					{ }
{SEGMENT}					{ }

<<EOF>>						{ return 0; }

