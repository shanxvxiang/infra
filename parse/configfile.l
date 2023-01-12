%option prefix="configfile"
%{
#define CONFIGFILESTYPE char*
#include "configfile.bison.hpp"
#define _DUPTEXT {configfilelval = strdup(configfiletext);}

%}

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
[;=]							{ return configfiletext[0]; }
[\n]							{ configfilelineno++; }
[ \t\r]+					{ }
{COMMENT}					{ }
{SEGMENT}					{ }

<<EOF>>						{ return 0; }

