/**
 * @file synt.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo do analisador sintatico COM GERACAO DE CODIGO INTERMEDIARIO
 * @version 0.3
 * @date 2022-04-25
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
int match(int token_tag)
{
    if (lookahead->tag == token_tag)
    {
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
int digit()
{
    char aux_lexema[MAX_TOKEN];
    strcpy(aux_lexema, lookahead->lexema); //armazena temporariamente o lexema

    if (match(NUM))
    {
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
int E(type_code *e_code)
{
    int test1, test2;
    type_code *t_code;
    type_code *er_code;
    int *last_operation;

    last_operation = (int *)malloc(sizeof(int));
    t_code = (type_code *)malloc(sizeof(type_code));
    er_code = (type_code *)malloc(sizeof(type_code));

    newTemp(e_code->temp);
    test1 = T(t_code);

    if (test1)
        test2 = ER(last_operation, er_code);

    strcpy(e_code->code, t_code->code);
    test2 = ER(last_operation, er_code);

    strcpy(e_code->code, t_code->code);
    strcat(e_code->code, er_code->code);

    switch (*last_operation)
    {
    case '+':
        strcat(e_code->code, e_code->temp);
        strcat(e_code->code, "=");
        strcat(e_code->code, t_code->temp);
        strcat(e_code->code, "+");
        strcat(e_code->code, er_code->temp);
        break;
    case '-':
        strcat(e_code->code, e_code->temp);
        strcat(e_code->code, "=");
        strcat(e_code->code, t_code->temp);
        strcat(e_code->code, "-");
        strcat(e_code->code, er_code->temp);
        break;
    case '\0':
        printf("[ERRO] Operacao nao definida!\n");
        break;
    }

    return test1 && test2;
}

/**
 * @brief Regra de derivacao da gramatica: E'->+TE'
 * 
 * @return int true/false
 */
int ER(int *lastoperation, type_code *er_code)
{
    int test1, test2;
    type_code *t_code;
    type_code *er1_code;
    int *lOperation;
    lOperation = (int *)malloc(sizeof(int));
    t_code = (type_code *)malloc(sizeof(type_code));
    er1_code = (type_code *)malloc(sizeof(type_code));

    if (lookahead->tag == '+')
    {
        match('+');
        *lastoperation = (int)'+';
        test1 = T(t_code);
        strcpy(er_code->temp, t_code->temp);
        if (test1)
            test2 = ER(lOperation, er1_code);
        strcpy(er_code->code, t_code->code);
        strcpy(er_code->code, er1_code->code);
        return test1 && test2;
    }
    else if (lookahead->tag == '-')
    {
        match('-');
        *lastoperation = (int)'-';
        test1 = T(t_code);
        strcpy(er_code->temp, t_code->temp);
        if (test1)
            test2 = ER(lOperation, er1_code);
        strcpy(er_code->code, t_code->code);
        strcpy(er_code->code, er1_code->code);
        return test1 && test2;
    }
    else if (lookahead->tag == ')')
    {
        strcpy(er_code->code, '\0');
        return true;
    }
    else if (lookahead->tag == ENDTOKEN)
    {
        strcpy(er_code->temp, ' ');
        (*lastoperation) = '\0';
        return true;
    }
    else if (lookahead->tag == '*')
    {
        strcpy(er_code->temp, ' ');
        (*lastoperation) = '\0';
        return true;
    }
    else if (lookahead->tag == ENDTOKEN)
    {
        strcpy(er_code->temp, ' ');
        (*lastoperation) = '\0';
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Regra de derivacao da gramatica: T->FT'
 * 
 * @return int true/false
 */
int T(type_code *t_code)
{
    int test1, test2;
    type_code *f_code;
    type_code *tr_code;
    int *lastoperation;

    newTemp(t_code->temp);
    lastoperation = (int *)malloc(sizeof(int));
    f_code = (type_code *)malloc(sizeof(type_code));
    tr_code = (type_code *)malloc(sizeof(type_code));

    test1 = F(f_code);

    if (test1)
        test2 = TR(lastoperation, tr_code);
    strcpy(t_code->code, f_code->code);
    strcpy(t_code->code, tr_code->code);

    switch (*lastoperation)
    {
    case '+':
        strcat(t_code->code, t_code->temp);
        strcat(t_code->code, '=');
        strcat(t_code->code, f_code->temp);
        strcat(t_code->code, '+');
        strcat(t_code->code, tr_code->temp);
        break;
    case '-':
        strcat(t_code->code, t_code->temp);
        strcat(t_code->code, '=');
        strcat(t_code->code, f_code->temp);
        strcat(t_code->code, '-');
        strcat(t_code->code, tr_code->temp);
        break;
    case '\0':
        strcat(t_code->code, t_code->temp);
        strcat(t_code->code, '=');
        strcat(t_code->code, tr_code->temp);
        strcat(t_code->code, '\n');
        break;
    }
    return test1 && test2;
}

/**
 * @brief Regra de derivacao da gramatica: T'->*FT'
 * 
 * @return int true/false
 */
int TR(int *lastoperation, type_code *tr_code)
{
    int test1, test2;
    type_code *f_code;
    type_code *tr1_code;
    int *lOperation;
    lOperation = (int *)malloc(sizeof(int));
    f_code = (type_code *)malloc(sizeof(type_code));
    tr1_code = (type_code *)malloc(sizeof(type_code));

    if (lookahead->tag == '+')
    {
        match('+');
        *lastoperation = (int)'+';
        test1 = F(f_code);
        strcpy(tr_code->temp, f_code->temp);
        if (test1)
            test2 = TR(lOperation, tr1_code);
        strcpy(tr_code->code, f_code->code);
        strcpy(tr_code->code, tr1_code->code);
        return test1 && test2;
    }
    else if (lookahead->tag == '-')
    {
        match('-');
        *lastoperation = (int)'-';
        test1 = F(f_code);
        strcpy(tr_code->temp, f_code->temp);
        if (test1)
            test2 = ER(lOperation, tr1_code);
        strcpy(tr_code->code, f_code->code);
        strcpy(tr_code->code, tr1_code->code);
        return test1 && test2;
    }
    else if (lookahead->tag == ')')
    {
        strcpy(tr_code->code, '\0');
        return true;
    }
    else if (lookahead->tag == ENDTOKEN)
    {
        strcpy(tr_code->temp, ' ');
        (*lastoperation) = '\0';
        return true;
    }
    else if (lookahead->tag == '*')
    {
        strcpy(tr_code->temp, ' ');
        (*lastoperation) = '\0';
        return true;
    }
    else if (lookahead->tag == ENDTOKEN)
    {
        strcpy(tr_code->temp, '0');
        (*lastoperation) = '\0';
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Regra de derivacao da gramatica: F->(E)
 * 
 * @return int true/false
 */
int F(type_code *f_code)
{
    type_code *e_code;
    e_code = (type_code *)malloc(sizeof(type_code));
    if (lookahead->tag == '(')
    {
        int test1, test2;
        match('(');
        test1 = E(e_code);
        if (test1)
            test2 = match(')');
        strcpy(f_code->temp, e_code->temp);
        strcpy(f_code->code, e_code->code);
        return test1 && test2;
    }
    else if (lookahead->tag == NUM)
    {
        int test1;
        char lexema[MAX_TOKEN];
        strcpy(lexema, lookahead->lexema);
        test1 = match(NUM);
        newTemp(f_code->temp);
        strcpy(f_code->code, f_code->temp);
        strcpy(f_code->code, '=');
        strcpy(f_code->code, lexema);
        strcpy(f_code->code, '\n');
        return test1;
    }
    else
    {
        return false;
    }
}

//--------------------- MAIN -----------------------

/**
 * @brief Funcao principal (main) do compilador
 * 
 * @return int 
 */
int main()
{

    type_code *e_code;
    int accept;

    e_code = (type_code *)malloc(sizeof(type_code));
    accept = false;

    initLex();              //Carrega codigo
    lookahead = getToken(); //Inicializacao do lookahead

    accept = E(e_code); //Chamada da derivacao/funcao inicial da gramatica

    //Imprime na tela o codigo intermediario gerado
    printf("%s\n", e_code->code);

    //Verifica aceitacao da cadeia/codigo
    if (accept)
    {
        printf("\tCadeia PERTENCENTE a linguagem\n");
    }
    else
    {
        printf("\tCadeia NAO pertencente a linguagem\n");
    }

    return 1;
}