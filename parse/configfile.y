%define api.prefix {configfile}
%{
#include <stdio.h>
#define CONFIGFILESTYPE char*

#define __RAYMON_SHAN_FOR_L_Y
#include "../include/logdirectly.hpp"
#undef  __RAYMON_SHAN_FOR_L_Y

int configfilelex();
extern "C" { int configfilewrap(void); };
void configfileerror(const char *s);

extern int configfilelineno;
extern char *configfiletext;
extern const char *ConfigFileName;		// declare in configurefile.hpp

const char* AssignInt(const char* key, char* value);
const char* AssignString(const char* key, char* value);
const char* AssignIpaddress(const char* key, char* value);
%}

%token IDENTIFIER INT STRING IPADDRESS

%%

allFile
	: assign
	| allFile assign
	;

assign
	: IDENTIFIER '=' INT ';'					{ AssignInt($1, $3); free($1); free($3); }
	| IDENTIFIER '=' STRING ';'				{ AssignString($1, $3);  free($1); free($3); }
	| IDENTIFIER '=' IPADDRESS ';'		{ AssignIpaddress($1, $3); free($1); free($3); }
	;

%%

void configfileerror(const char* s) {
  _LOG_CRIT("%s:%s [%s:%d]", s, configfiletext, ConfigFileName, configfilelineno);
	exit(1);
}

int configfilewrap(void) {
	configfilelineno = 1;
	return 1;
}



