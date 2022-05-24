%{
    #include<stdio.h>
    int yylex(void);
    void yyerror(char *);
%}
%token INTEGER
%left '+' '-'
%left '*' '/'
%%
program:
    program expr '\n' {printf("%d\n", $2);} | ;
expr:
    T {$$ = $1;} |
    expr '+' T {$$ = $1 + $3;} |
    expr '-' T {$$ = $1 - $3;} ;
T:
    F {$$ = $1;} |
    T '*' F {$$ = $1 * $3;} |
    T '/' F {$$ = $1 / $3;} ;
F:
    INTEGER {$$ = $1;} |
    '(' expr ')' {$$ = $2;} ;
%%
void yyerror(char *s){
    printf("%s\n", s);
}
int main(void){
    yyparse();
    return 0;
}