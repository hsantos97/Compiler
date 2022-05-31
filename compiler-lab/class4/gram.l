%{
#include <string.h>
#include <stdio.h>
#include "gram.tab.h"

%}
ws [ \t]
%%
ws           { }

"o"          { printf("yytext: %s\n", yytext);
               strcpy( yylval.str,yytext);  return O;}
"a"          { printf("yytext: %s\n", yytext);
               strcpy(yylval.str,yytext); return A; }
"gato"       { printf("yytext: %s\n", yytext); 
               strcpy( yylval.str,yytext);  return GATO; }
"cachorro"   { printf("yytext: %s\n", yytext);
               strcpy(yylval.str,yytext); return CACHORRO;}
"comida"     { printf("yytext: %s\n", yytext);
               strcpy(yylval.str,yytext); return COMIDA;}

%%

int yywrap (void)
{
  return 1;
}