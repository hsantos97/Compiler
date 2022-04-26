digit [0-9]
letter [a-zA-Z]
ws [\t\n]

%%
ws {return 1}
{letter}({letter} | {digit})* {printf("id: %s\n", yytext); return 2;}
{digit}+ {printf("num: %s\n", yytext); return 3;}
. {return 4;}
%%

int yywrap(void) {return 1;}

int main(int argc, char *argv[])
{
    yyin = fopen(argv[1], "r");
    int tokentag;
    tokentag = 1;
    while(tokentag != 0){
        tokentag = yylex();
    }
    fclose(yyin);
    return 0;
}