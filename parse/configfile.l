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
/* " \x22; ' \x27; / \x2F; \ \x5c; */

DIGIT 				([0-9])
HEXDIGIT			([0-9A-Fa-f])
ALPHABET			([_A-Za-z])
GBK						([\x81-\xFE][\x40-\xFE])

ESCONE				(\x5C[abfnrtv?\x22\x27\x5C])
ESCX					(\x5C([x]|[X]){HEXDIGIT}{HEXDIGIT})
ESCCHAR				({ESCONE}|{ESCX})
ALLCHAR				({ALPHABET}|{DIGIT}|{GBK}|{ESCCHAR})

IDENTIFIER		({ALPHABET}+)
INT						({DIGIT}+)
STRING				(\x22([^\x22\x5c]|{ESCCHAR})*\x22)
IPADDRESS			({INT}"."{INT}"."{INT}"."{INT}":"{INT})

COMMENT				("//"[^\n]*)
SEGMENT				("["{ALLCHAR}*"]")


%%
{IDENTIFIER}			{ _DUPTEXT; return IDENTIFIER; }
{INT}							{ _DUPTEXT; return INT; }
{STRING}          { _DUPTEXT; return STRING; }
{IPADDRESS}				{ _DUPTEXT; return IPADDRESS; }
[;=]							{ return configfiletext[0]; }
[ \t\r\n]+				{ }
{COMMENT}					{ }
{SEGMENT}					{ }

<<EOF>>						{ return 0; }

