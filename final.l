%{
#include "y.tab.h"
void yyerror (char *s);
int yylex();
%}
%%
"PROGRAM"              {return programTemp;}
"VAR"                  {return varTemp;}
"INTEGER"              {return typeTemp;}
"BEGIN"                {return beginTemp;}
"PRINT"				   {return printTemp;}
"END."                 {return endTemp;} 
"exit"				   {return exitTemp;}
[a-zA-Z][0-9a-zA-Z]*   {yylval.id = yytext[0]; return varName;} //variable names <id>
[0-9]+                 {yylval.num = atoi(yytext); return number;} //numbers
[-+*/=;:,."’`\'()]     {return yytext[0];}
\'[0-9a-zA-Z=]+\'      {return str;} //string with single quotes
[ \t\n]                ;
%%
int yywrap (void) {return 1;}


