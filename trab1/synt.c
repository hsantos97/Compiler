// Inclusao do cabecalho
#include "synt.h"
#include "lex.h" //COLOQUEI ISSO AQUI 

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


// ------------------------------------- COMEÇEI AS MUDANÇAS AQUI ------------------------

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
    if ( lookahead->tag == PLUS ) {
        match(PLUS);
        //...Geraremos codigo no futuro aqui, para a adicao
        test1 = T();
        if (test1)
            test2 = ER();
        genAdd();
        return test1 && test2;
    } else if ( lookahead->tag == MINUS ) {
        match(MINUS);
        test1 = T();
        if(test1)
            test2 = ER();
        genSub();
        return test1 && test2;
        //Complete o codigo para tratar também a subtracao, que tem mesma precedencia da soma
    } //Vamos tratar o caso da derivacao em "vazio", a partir da TAS
      else if ( lookahead->tag == CLOSEPAREN ) {
        return true;
    } else if ( match(ENDTOKEN) ) {
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
    if ( lookahead->tag == MULT ) {
        match(MULT);
        //...Geraremos codigo no futuro aqui, para multiplicacao
        test1 = F();
        if (test1)
            test2 = TR();
        genMult();
        return test1 && test2;
    } else if( lookahead->tag == DIV) {
        match(DIV);
        test1 = F();
        if(test1)
            test2 = TR();
        return test1 && test2;
        //Complete o codigo para tratar também a divisao, que tem mesma precedencia da multiplicacao
        //...
        //return false; 
    } else if ( lookahead->tag == CLOSEPAREN) {
        return true;
    } else if ( match(ENDTOKEN) ) {
        return true;
    } else if ( lookahead->tag == PLUS) {
        return true;
    } else if ( lookahead->tag == MINUS){
        return true;
    } else {
        return false;
    }
}

//Regra de derivacao: F->(E)
int F() {
    if ( lookahead->tag == OPENPAREN ) {
        int test1, test2;
        match(OPENPAREN);
        test1 = E();
        if (test1)
            test2 = match(CLOSEPAREN);
        return test1 && test2;
    } else if ( digit() ) {
        //Aqui iremos editar no futuro para processar o digito (a partir do lexico) e gerar codigo
        F();
        return true;
    } else {
        return false;
    }
}





/**
 * @brief Regra de derivacao da gramatica: LIST
 * 
 * @return int true/false
 */
/*
int list() {
    if ( digit() && listR() ) 
        return true;
    return false;
}
*/
/**
 * @brief Regra de derivacao da gramatica: LIST_RECURSIVO
 * 
 * @return int true/false
 */
/*   -----------------------------------------COMENTEI AQUIIIII -------------------------------
int listR() {
    int test1, test2;
    //Verifica ocorrencia de terminal '+'
    if ( lookahead->tag == PLUS ) {
        test1 = match(PLUS);
        test2 = digit();
        genAdd(); //Geracao de codigo por meio de funcao do GERADOR
        if (test1 && test2)
            return listR();
        return false;
    } //Verifica ocorrencia de terminal '-' 
    else if ( lookahead->tag == MINUS ) {
        test1 = match(MINUS);
        test2 = digit();
        genSub(); //Geracao de codigo por meio de funcao do GERADOR
        if (test1 && test2)
            return listR();
        return false;
    } //Verifica se fim de entrada
    //ADICIONEI ISSO AQUI
    else if ( lookahead->tag == MULT ) {
        test1 = match(MULT);
        test2 = digit();
        genMult(); //Geracao de codigo por meio de funcao do GERADOR
        if (test1 && test2)
            return listR();
        return false;
    } 
    else {
        if ( lookahead->tag == ENDTOKEN )
            return true;
        //Caso todos os testes falhem, retorna erro (false)
        return false; 
    }
}
----------------------------------------- ATE AQUI ------------------------------------------
*/

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