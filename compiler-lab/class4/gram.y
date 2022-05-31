%{
   #include <string.h>
   #include <stdio.h>
   void yyerror(char *);
%}

%union {
 char str[64];
};

%type <str> art subst sujeito 
%token <str> O A GATO CACHORRO COMIDA

%%

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
      	;

%%

void yyerror(char *s) {
   printf("%s\n",s);

}

int main (void) {
   yyparse();
   return 0;
}
