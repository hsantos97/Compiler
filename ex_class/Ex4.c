#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constantes
#define MAX_CHAR 32
#define true 1
#define false 0
//Variaveis globais
int pos = 0;
char string[MAX_CHAR];
char lookahead;

//Prototipos
int E();
int ER();
int T();
int TR();
int F();
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

//Regra de derivacao: E->TE'
int E() {
    int test1, test2;
    test1 = T();
    if (test1) {
        test2 = ER();
    }
    return test1 && test2;
}

//Regra de derivacao: E'->+TE' | vazio
int ER() {
    int test1, test2;
    if ( lookahead == '+' ) {
        match('+');
        //...Geraremos codigo no futuro aqui, para a adicao
        test1 = T();
        if (test1)
            test2 = ER();
        return test1 && test2;
    } else if ( lookahead == '-' ) {
        match('-');
        test1 = T();
        if(test1)
            test2 = ER();
        return test1 && test2;
        //Complete o codigo para tratar também a subtracao, que tem mesma precedencia da soma
    } //Vamos tratar o caso da derivacao em "vazio", a partir da TAS
      else if ( lookahead == ')' ) {
        return true;
    } else if ( match('\0') ) {
        return true;
    } else {
        return false;
    }
}

//Regra de derivacao: T->FT'
int T() {
    int test1, test2;
    test1 = F();
    if (test1)
        test2 = TR();
    return test1 && test2;
}

//Regra de derivacao: TR->*FT' | vazio
int TR() {
    int test1, test2;
    if ( lookahead == '*' ) {
        match('*');
        //...Geraremos codigo no futuro aqui, para multiplicacao
        test1 = F();
        if (test1)
            test2 = TR();
        return test1 && test2;
    } else if( lookahead == '/') {
        match('/');
        test1 = F();
        if(test1)
            test2 = TR();
        return test1 && test2;
        //Complete o codigo para tratar também a divisao, que tem mesma precedencia da multiplicacao
        //...
        return false; //Corrigir
    } else if ( lookahead == ')') {
        return true;
    } else if ( match('\0') ) {
        return true;
    } else if ( lookahead == '+') {
        return true;
    } else if ( lookahead == '-'){
        return true;
    } else {
        return false;
    }
}

//Regra de derivacao: F->(E)
int F() {
    if ( lookahead == '(' ) {
        int test1, test2;
        match('(');
        test1 = E();
        if (test1)
            test2 = match(')');
        return test1 && test2;
    } else if ( digit() ) {
        //Aqui iremos editar no futuro para processar o digito (a partir do lexico) e gerar codigo
        //...
        return true;
    } else {
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
        //...
        return true;
    }
    return false;
}



//Funcao principal
int main() {

    int acept = false;

    printf("Informe uma cadeia:");
    scanf("%s", string); //leitura da cadeia
    //strcpy(string,"2+3");
    
    lookahead = string[0]; //inicializacao do lookahead

    acept = E(); //Chamada da derivacao/funcao inicial da gramatica

    if (acept) {
        printf("Cadeia PERTENCENTE a linguagem!\n");
    } else {
        printf("Cadeia NAO pertencente a linguagem.\n");
    }

    return 1;
}