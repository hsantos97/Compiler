/**
 * @file synt.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo do analisador sintatico
 * @version 0.2
 * @date 2021-11-30
 * 
 */

// Inclusao do cabecalho
#include "synt.h"

/**
 * @brief Verifica se o proximo caracter (a frente) na cadeia eh o esperado
 * 
 * @param token_tag (int) codigo do token a ser verificado 
 * @return int true/false
 */
int match(int token_tag) {
    if ( lookahead->tag == token_tag ) {
        lookahead = getToken(); //Pega o proximo token por meio do lexico
        return true;
    }
    return false;
}

/**
 * @brief Regra de derivacao da gramatica: DIGIT
 * 
 * @return int true/false
 */
int digit() {
    char aux_lexema[MAX_TOKEN];
    strcpy(aux_lexema, lookahead->lexema); //armazena temporariamente o lexema

    if ( match(NUM) ) {
        genNum(aux_lexema); //Geracao de codigo por meio de funcao do GERADOR
        return true;
    }
    return false;
}

/**
 * @brief Regra de derivacao da gramatica: E->TE'
 * 
 * @return int true/false
 */
int E() {
    int test1, test2;
    test1 = T();
    if (test1) {
        test2 = ER();
    }
    return test1 && test2;
}

/**
 * @brief Regra de derivacao da gramatica: E'->+TE'
 * 
 * @return int true/false
 */
int ER() {
    int test1, test2;
    if ( lookahead->tag == PLUS ) {
        test1 = match(PLUS);
        test2 = T();
        genAdd();
        if (test1 && test2)
            return ER();
        return false;
    } else if ( lookahead->tag == MINUS ) {
        test1 = match(MINUS);
        test2 = T();
        genSub();
        if (test1 && test2)
            return ER();
        return false;
    } else if ( lookahead->tag == CLOSE_PAR ) {
        return true;
    } else if ( match('\0') ) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Regra de derivacao da gramatica: T->FT'
 * 
 * @return int true/false
 */
int T() {
    int test1, test2;
    test1 = F();
    if (test1)
        test2 = TR();
    return test1 && test2;
}

/**
 * @brief Regra de derivacao da gramatica: T'->*FT'
 * 
 * @return int true/false
 */
int TR() {
    int test1, test2;
    if ( lookahead->tag == MULT ) {
        test1 = match(MULT);
        test2 = F();
        genMult();
        if (test1 && test2)
            return TR();
        return false;
    } else if( lookahead->tag == DIV) {
        test1 = match(DIV);
        test2 = F();
        genDiv();
        if (test1 && test2)
            return TR();
        return false;
    } else if ( lookahead->tag == CLOSE_PAR) {
        return true;
    } else if ( match('\0') ) {
        return true;
    } else if ( lookahead->tag == PLUS) {
        return true;
    } else if ( lookahead->tag == MINUS) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Regra de derivacao da gramatica: F->(E)
 * 
 * @return int true/false
 */
int F() {
    if ( lookahead->tag == OPEN_PAR ) {
        int test1, test2;
        match(OPEN_PAR);
        test1 = E();
        if (test1)
            test2 = match(CLOSE_PAR);
        return test1 && test2;
    } else if ( digit() ) { //Processa o digito e gera codigo
        return true;
    } else {
        return false;
    }
}



//--------------------- MAIN -----------------------

/**
 * @brief Funcao principal (main) do compilador
 * 
 * @return int 
 */
int main() {

    int acept;
    acept = false;
    
    initLex(); //Carrega codigo
    lookahead = getToken(); //Inicializacao do lookahead

    acept = E(); //Chamada da derivacao/funcao inicial da gramatica

    //Verifica aceitacao da cadeia/codigo
    if (acept) {
        printf("\tCadeia PERTENCENTE a linguagem\n");
    } else {
        printf("\tCadeia NAO pertencente a linguagem\n");
    }

    return 1;
}