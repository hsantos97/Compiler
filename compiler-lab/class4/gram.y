%{
   #include <string.h>
   #include <stdio.h>
   void yyerror(char *);
%}

%union {
 char str[64];
};

%type <str> art subst sujeito predicado verbo complemento oracao
%token <str> O A GATO CACHORRO COMIDA BISCOITO EH COME BONITO FEIO

%%
oracao : sujeito predicado {
        strcpy($$,$1);
        strcat($$," ");
        strcat($$, $2);
        printf("A oração eh: %s\n", $$);
        }

sujeito	: art subst { 
       		strcpy($$,$1);
                strcat($$," ");
                strcat($$, $2);
                printf("O sujeito eh: %s\n", $$);
		}
        ;                
                          
art	: O { 
    		strcpy($$,$1); 
                printf("ART: %s\n",$$);
		}
      	| A {
		strcpy($$,$1); 
                printf("ART: %s\n",$$);
		}
        ;
        
subst	: GATO {
      		strcpy($$,$1);
                printf("SUBST: %s\n",$$);
		}
      	| CACHORRO {
		strcpy($$,$1); 
                printf("SUBST: %s\n",$$);
		}
      	| COMIDA {
		strcpy($$,$1);  
                printf("SUBST: %s\n",$$);
		}
        | BISCOITO {
                strcpy($$,$1);
                printf("SUBST: %s\n", $$);
                }
      	;

predicado: verbo complemento {
        strcpy($$,$1);
        strcat($$," ");
        strcat($$, $2);
        printf("O predicado eh: %s\n", $$);
        }
        ;

verbo: EH {
        strcpy($$,$1);
        printf("VERBO: %s\n",$$);
        }
        | COME {
        strcpy($$,$1);
        printf("VERBO: %s\n",$$);        
        }
        ;

complemento: BONITO {
        strcpy($$,$1);
        printf("COMPLEMENTO: %s\n",$$);
        }
        | FEIO {
        strcpy($$,$1);
        printf("COMPLEMENTO: %s\n",$$);        
        }
        | subst {
        strcpy($$, $1);
        printf("SUBSTANTIVO: %s\n", $$);
        }
        ;


%%

void yyerror(char *s) {
   printf("%s\n",s);

}

int main (void) {
   yyparse();
   return 0;
}
