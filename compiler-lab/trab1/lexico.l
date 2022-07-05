%{
	#include <string.h>
	#include <stdio.h>
	#include "sintatico.tab.h"
	#include "symbolTable.h"
	void yyerror(char *); 
%}

ws [ \t]
letter [A-Za-z]
digit [0-9]



%%

"//".*\n\r  {
	cont_lines++;
}
"//".*\r\n  {
	cont_lines++;
}

"int"	{
	printf("Lexic: int found\n");
	strcpy(yylval.c.str, yytext);
	return INT;
}

"float"	{
	printf("Lexic: int found\n");
	strcpy(yylval.c.str, yytext);
	return FLOAT;
}

"read"	{
	printf("Lexic: int found\n");
	strcpy(yylval.c.str, yytext);
	return READ;
}

"write"	{
	printf("Lexic: int found\n");
	strcpy(yylval.c.str, yytext);
	return WRITE;
}

"if"	{
	printf("Lexic: int found\n");
	strcpy(yylval.c.str, yytext);
	return IF;
}

"else"	{
	printf("Lexic: int found\n");
	strcpy(yylval.c.str, yytext);
	return ELSE;
}

"while"	{
	printf("Lexic: int found\n");
	strcpy(yylval.c.str, yytext);
	return WHILE;
}

"<="	{
	printf("Lexic: int found\n");
	strcpy(yylval.c.str, yytext);
	return LE;
}
">="	{
	printf("Lexic: int found\n");
	strcpy(yylval.c.str, yytext);
	return GE;
}
"=="	{
	printf("Lexic: int found\n");
	strcpy(yylval.c.str, yytext);
	return EQ;
}
"!="	{
	printf("Lexic: int found\n");
	strcpy(yylval.c.str, yytext);
	return NE;
}

{digit}+  {
	strcpy(yylval.c.str, yytext);
	return NUM;
}


{letter}({letter}|{digit}|_)*	{
	printf("Lexic: %s found\n", yytext);
	strcpy(yylval.c.str, yytext);
	return ID;
}


[-;:={}+*()<>/%] {
	printf("Lexic: %c found\n", *yytext);
	// strcpy(yylval.str, yytext);
	return *yytext;
}


{ws}           { }

\n\r             { cont_lines++; }
\r\n             { cont_lines++; }


. { yyerror("Invalid character"); }

%%

int yywrap (void)
{
 	return 1;
}