#include <stdio.h>
#include <stdlib.h>

//Constantes
#define MAX_CHAR 32
#define true 1
#define false 0
//Variaveis globais
int pos = 0;
char string[MAX_CHAR];
char lookahead;

//Prototipos
int list();
int listR();
int digit();
int match(char c);
void nextToken();

//Verifica o proximo caracter (a frente) na cadeia eh o esperado
int match(char c) {
    if ( lookahead == c ) {
        nextToken();
        return true;
    }
    return false;
}

//Funcao que passa ao proximo simbolo da cadeia
void nextToken() {
    pos++;
    lookahead = string[pos];
}

//Funcao da regra de derivacao 'list'
int list() {
    if ( digit() && listR() ) 
        return true;
    return false;
}

//Funcao da regra de derivacao 'listR'
int listR() {
    int test1, test2, test3;
    if ( lookahead == '+' ) {
        test1 = match('+');
        test2 = digit();
        //Adicao de comando para geracao de codigo:
        printf("add\n");
        if (test1 && test2)
            return listR();
        return false;
    } else if ( lookahead == '-' ) {
        test1 = match('-');
        test2 = digit();
        //Adicao de comando para geracao de codigo:
        printf("sub\n");
        if (test1 && test2)
            return listR();
        return false;
    } else {
        if ( match('\0') )
            return true;
        return false;
    }
}

//Funcao da regra de derivacao 'digit''
int digit() {
    char ch;
    ch = lookahead;
    if ( 
        match('0') || match('1') ||
        match('2') || match('3') ||
        match('4') || match('5') ||
        match('6') || match('7') ||
        match('8') || match('9') ) 
    {
        //Adicao de comando para geracao de codigo:
        printf("push %c\n", ch);
        return true;
    }
    return false;
}



//Funcao principal
int main() {

    int acept = false;

    printf("Informe uma cadeia:");
    scanf("%s", string); //leitura da cadeia
    
    lookahead = string[0]; //inicializacao do lookahead

    acept = list(); //Chamada da derivacao/funcao inicial da gramatica

    if (acept) {
        printf("Cadeia PERTENCENTE a linguagem\n");
    } else {
        printf("Cadeia NAO pertencente a linguagem\n");
    }

    return 1;
}