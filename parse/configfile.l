%option prefix="cmdline"
%{
#include "configfile.bison.h"
%}
%%
"+"    { return ADD; }
"-"    { return SUB; }
"*"    { return MUL; }
"/"    { return DIV; }
"|"    { return ABS; }
[0-9]+ { cmdlinelval = atoi(yytext); return NUMBER; }
\n     { return EOL; }
[ \t]  {  }
.      { printf("Mystery character %c\n", *yytext); }

