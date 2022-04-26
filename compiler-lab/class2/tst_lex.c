/**
 * @file tst_lex.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Modulo exclusivo para teste do analisador lexico (isolado)
 * @version 0.1
 * @date 2021-11-24
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct_compiler.h"
#include "lex.h"

// Variaveis globais no modulo de teste
type_token *lookahead;
int pos;
char string[MAX_CHAR];

// Funcao principal, para teste do lexico
int main(){
    int acept = false;
    
    initLex();
    lookahead = getToken();

    //Processa todos os tokens a partir da entrada
    while (lookahead->tag != ENDTOKEN) {
        printf("Tag:   %d\n", lookahead->tag);
        printf("Token: %s\n\n", lookahead->lexema);

        // Verifica se ocorreu erro
        if (lookahead->tag == ERROR)
            exit(1);

        lookahead = getToken();
    }
    // Imprimindo o ultimo token obtido
    printf("Tag:   %d\n", lookahead->tag);
    printf("Token: %s\n", lookahead->lexema);
    
    return 1;
}